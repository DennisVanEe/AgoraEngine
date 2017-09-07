#include "Mesh.hpp"

agora::Mesh::Mesh() :
    m_attributes(nullptr),
    m_vertexBuffer(nullptr),
    m_vertexBufferSize(0),
    m_indexBuffer(nullptr),
    m_indexBufferSize(0),
    m_VAO(0),
    m_VBO(0),
    m_EBO(0)
{
}

agora::Mesh::~Mesh()
{
    assert(m_attributes == nullptr);
    assert(m_vertexBuffer == nullptr);
    assert(m_indexBuffer == nullptr);
    releaseFromGPU();
}

agora::Mesh::Mesh(Mesh&& mesh) :
    m_attributes(mesh.m_attributes),
    m_vertexBuffer(mesh.m_vertexBuffer),
    m_vertexBufferSize(mesh.m_vertexBufferSize),
    m_indexBuffer(mesh.m_indexBuffer),
    m_indexBufferSize(mesh.m_indexBufferSize),
    m_VAO(mesh.m_VAO)
{
    mesh.m_attributes = nullptr;
    mesh.m_vertexBuffer = nullptr;
    mesh.m_vertexBufferSize = 0;
    mesh.m_indexBuffer = nullptr;
    mesh.m_indexBufferSize = 0;
    mesh.m_VAO = 0;
}

inline unsigned agora::Mesh::getVertexBufferSize() const
{
    return m_vertexBufferSize;
}

template<class Allocator>
inline bool agora::Mesh::prepare(Allocator& allocator, unsigned vertexBuffSize, unsigned numAttrib, unsigned stride, unsigned indexBuffSize)
{
    m_numAttributes = numAttrib;
    m_vertexBufferSize = vertexBuffSize;
    m_vertexStride = stride;
    m_indexBufferSize = indexBuffSize;
    
    unsigned attribBuffSize = numAttrib * sizeof(VertexAttrib);

    std::uintptr_t mem = reinterpret_cast<std::uintptr_t>(allocator.allocate(attribBuffSize + vertexBuffSize + indexBuffSize, alignof(GLfloat), 0));
    m_attributes = new(reinterpret_cast<void*>(mem)) VertexAttrib[m_numAttributes];
    m_indexBuffer = reinterpret_cast<GLuint*>(mem + attribBuffSize);
    m_vertexBuffer = reinterpret_cast<aByte*>(mem + attribBuffSize + m_indexBufferSize);
    return mem != 0;
}

template<class Allocator>
inline bool agora::Mesh::free(Allocator& allocator)
{
    assert(m_numAttributes != nullptr); // though it wouldn't cause any runtime errors, indicative of design error

    bool result = allocator.free(m_attributes, numAttrib * sizeof(VertexAttrib) + vertexBuffSize + indexBuffSize);

    m_attributes = nullptr;
    m_indexBuffer = nullptr;
    m_vertexBuffer = nullptr;

    m_numAttributes = 0;
    m_vertexBufferSize = 0;
    m_indexBufferSize = 0;

    return result;
}

inline GLuint* agora::Mesh::getIndexData(unsigned startLoc)
{
    return &m_indexBuffer[startLoc];
}


inline const GLuint* agora::Mesh::getIndexData(unsigned startLoc) const
{
    return getIndexData(startLoc);
}


inline unsigned agora::Mesh::getIndexBufferSize() const
{
    return m_indexBufferSize;
}


inline void agora::Mesh::addAttrib(unsigned index, VertexAttrib attrib)
{
    assert(index < m_numAttributes);
    m_attributes[index] = attrib;
}


template<typename T>
inline T* agora::Mesh::getVertexData(unsigned startLoc)
{
    return reinterpret_cast<T*>(&m_vertexBuffer[startLoc]);
}


template<typename T>
inline const T* agora::Mesh::getVertexData(unsigned startLoc) const
{
    return getVertexData(startLoc);
}


template<GLenum Usage>
void agora::Mesh::sendToGPU()
{
    if (m_VAO == 0)
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        // load into GPU:
        glNamedBufferData(m_VBO, m_vertexBufferSize, m_vertexBuffer, Usage);
        glNamedBufferData(m_EBO, m_indexBufferSize, m_indexBuffer, Usage);

        glVertexArrayVertexBuffer(m_VAO, 0, m_VBO, 0, m_vertexStride);
        for (unsigned i = 0; i < NumAttrib; i++)
        {
            glEnableVertexAttribArray(i);
            glVertexArrayAttribFormat(m_VAO, i, m_attributes[i].m_size, m_attributes[i].m_type, m_attributes[i].m_normalized, m_attributes[i].m_offset);
            glVertexAttribBinding(i, 0);
        }
    }
}

template<class Vertex, class Allocator>
void agora::Mesh<Vertex, Allocator, AType>::releaseFromGPU()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

bool agora::Mesh::isInGPU() const
{
    return m_VAO != 0;
}

template<class Vertex, class Allocator>
GLuint agora::Mesh<Vertex, Allocator>::VAO() const
{
    return m_VAO;
}