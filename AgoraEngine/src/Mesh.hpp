#pragma once

#include <cstddef>
#include <cassert>
#include <glad/glad.h>

namespace agora
{
    // the allocator can either be managed by the mesh itself, or be the same
    // allactor of the model class that will ultimately hold it. I decided to 
    // go with this approach of keeping them seperate to offer the most 
    // flexiblity (if for instance, one mesh was used by multiple allocators,
    // they could have some marked for sharing.
    template<class Vertex, class Allocator>
    class Mesh
    {
    public:
        Mesh(Allocator* allocator);
        ~Mesh();

        // when moving around a mesh, it MUST be the same allocator, one can't move memory between
        // different allocators.
        Mesh(Mesh<Vertex, Allocator>&& mesh);

        // Both of these are to be called ONLY ONCE during initialization!
        template<class CAllocator>
        void copyMesh(const Mesh<Vertex, CAllocator>& mesh);

        void copyVertices(const Vertex* data, unsigned nVertices);
        void copyIndices(const GLuint* data, unsigned nIndices);
        // both of these NEED to have the same allocator, or else....
        void moveVertices(Vertex* data, unsigned nVertices);
        void moveIndices(GLuint* data, unsigned nIndices);

        template<GLenum USAGE = GL_STATIC_DRAW>
        void sendToGPU();
        void releaseFromGPU();

        // anything that wants to draw will need to call this function (and have this function if it 
        // wishes to be rendered as such).
        GLuint VAO() const;

        // The copying of a mesh is a slow and (often) unnecessary procedure.
        // Though, the act itself will be allowed, but only with an explicit
        // function call to copyMesh.
        Mesh(const Mesh& mesh) = delete;
        void operator=(const Mesh& mesh) = delete;

    private:
        Allocator* const m_allocator;

        Vertex* m_vertexBuffer; 
        unsigned m_numVertices;

        GLuint*  m_indexBuffer;  
        unsigned m_numIndices;

        GLuint m_VAO;
    };
}

// inline/template definitions

template<class Vertex, class Allocator>
agora::Mesh<Vertex, Allocator>::Mesh(Allocator* const allocator) :
    m_allocator(allocator),
    m_VAO(0),
    m_vertexBuffer(nullptr),
    m_indexBuffer(nullptr)
{
}

template<class Vertex, class Allocator>
agora::Mesh<Vertex, Allocator>::~Mesh()
{
    m_allocator->free(m_indexBuffer);
    m_allocator->free(m_vertexBuffer);
    glDeleteVertexArrays(1, &m_VAO);
}

template<class Vertex, class Allocator>
agora::Mesh<Vertex, Allocator>::Mesh(Mesh&& mesh) :
    m_allocator(mesh.m_allocator),
    m_vertexBuffer(mesh.m_vertexBuffer),
    m_numVertices(mesh.m_numVertices),
    m_indexBuffer(mesh.m_indexBuffer),
    m_numIndices(mesh.m_numIndices),
    m_VAO(mesh.m_VAO)
{
    mesh.m_allocator = nullptr;
    mesh.m_vertexBuffer = nullptr;
    mesh.m_indexBuffer = nullptr;
    m_VAO(0);
}

template<class Vertex, class Allocator>
template<class CAllocator>
void agora::Mesh<Vertex, Allocator>::copyMesh(const Mesh<Vertex, CAllocator>& mesh)
{
    assert(m_vertexBuffer == nullptr);
    copyVertices(mesh.m_vertexBuffer, mesh.m_numVertices);
    copyIndices(mesh.m_indexBuffer, mesh.m_numIndices);
}

template<class Vertex, class Allocator>
void agora::Mesh<Vertex, Allocator>::copyVertices(const Vertex* const buffer, unsigned const nVertices)
{
    assert(m_vertexBuffer == nullptr);
    m_vertexBuffer = m_allocator->allocate(sizeof(Vertex) * nVertices, alignof(Vertex), 0);
    m_numVertices = nVertices;
}

template<class Vertex, class Allocator>
void agora::Mesh<Vertex, Allocator>::copyIndices(const GLuint* const buffer, unsigned const nIndices)
{
    assert(m_vertexBuffer == nullptr);
    m_indexBuffer = m_allocator->allocate(sizeof(GLuint) * nVertices, alignof(GLuint), 0);
    m_numIndices = nIndices;
}

template<class Vertex, class Allocator>
void agora::Mesh<Vertex, Allocator>::moveVertices(Vertex* const buffer, unsigned const nVertices)
{
    assert(m_vertexBuffer == nullptr);
    m_vertexBuffer = buffer;
    m_numVertices = nVertices;
}

template<class Vertex, class Allocator>
void agora::Mesh<Vertex, Allocator>::moveIndices(GLuint* const buffer, unsigned const nIndices)
{
    assert(m_vertexBuffer == nullptr);
    m_indexBuffer = buffer;
    m_numIndices = nIndices;
}

template<class Vertex, class Allocator> 
template<GLenum USAGE>
void agora::Mesh<Vertex, Allocator>::sendToGPU()
{
    if (m_VAO == 0)
    {
        GLuint VBO, EBO;

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(Vertex), m_vertexBuffer, USAGE);

        // for now, the indices will retain the same alloc hint as the vertices:
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numIndices * sizeof(GLuint), m_indexBuffer, USAGE);

        Vertex::setVertexAttributes(); // set the attributes needed here

        glBindVertexArray(0);

        glDeleteBuffers(1, &EBO);
        glDeleteBuffers(1, &VBO);
    }
}

template<class Vertex, class Allocator>
void agora::Mesh<Vertex, Allocator, AType>::releaseFromGPU()
{
    glDeleteVertexArrays(1, &m_VAO);
}

template<class Vertex, class Allocator>
GLuint agora::Mesh<Vertex, Allocator>::VAO() const
{
    return m_VAO;
}