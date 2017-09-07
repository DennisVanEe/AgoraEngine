#pragma once

#include <cstddef>
#include <cassert>
#include <cstdint>
#include <MemAlloc/Allocates.hpp>
#include <glad/glad.h>

#include "Include/Types.hpp"

namespace agora
{
    // the allocator can either be managed by the mesh itself, or be the same
    // allactor of the model class that will ultimately hold it. I decided to 
    // go with this approach of keeping them seperate to offer the most 
    // flexiblity (if for instance, one mesh was used by multiple allocators,
    // they could have some marked for sharing.

    struct VertexAttrib
    {
        GLint       m_size;
        GLenum      m_type;
        GLuint      m_offset;
        GLboolean   m_normalized;
    };
    static_assert(alignof(VertexAttrib) == alignof(float), "Size and alignment should be same as float for performance");

    class Mesh
    {
    public:
        Mesh();
        ~Mesh();

        // when moving around a mesh, it MUST be the same allocator, one can't move memory between
        // different allocators.
        Mesh(Mesh&& mesh);

        // When loading a mesh (or modifying the mesh's RAM buffer) use this dangerous function 
        // (I leave it to the user to keep track of everything).
        template<typename T>
        inline T* getVertexData(unsigned startLoc);
        template<typename T>
        inline const T* getVertexData(unsigned startLoc) const;
        // Get max amount of space that is accessible for use (0 if non was allocated or there was an error)
        inline unsigned getVertexBufferSize() const;

        // the memory is managed by the central mesh manager (the buffer in RAM, that is)
        // Size indicates a size in bytes
        // num indicates the number of objects
        template<class Allocator>
        inline bool prepare(Allocator& allocator, unsigned vertexBuffSize, unsigned numAttrib, unsigned stride, unsigned indexBuffSize);
        template<class Allocator>
        inline bool free(Allocator& allocator);

        inline GLuint* getIndexData(unsigned startLoc = 0);
        inline const GLuint* getIndexData(unsigned startLoc = 0) const;
        inline unsigned getIndexBufferSize() const;

        inline void addAttrib(unsigned index, VertexAttrib attrib);

        template<GLenum USAGE = GL_STATIC_DRAW>
        void sendToGPU();
        void releaseFromGPU();

        bool isInGPU() const;

        // anything that wants to draw will need to call this function (and have this function if it 
        // wishes to be rendered as such).
        GLuint VAO() const;

        // The copying of a mesh is a slow and (often) unnecessary procedure.
        // Though, the act itself will be allowed, but only with an explicit
        // function call to copyMesh.
        Mesh(const Mesh&) = delete;
        void operator=(const Mesh&) = delete;
        void operator=(Mesh&&) = delete;

    private:
        VertexAttrib*   m_attributes; // always comes first in the buffer (so, this is what is first pointed at)
        unsigned        m_numAttributes;
        aByte*          m_vertexBuffer;
        unsigned        m_vertexBufferSize;
        unsigned        m_vertexStride;

        GLuint*         m_indexBuffer;
        unsigned        m_indexBufferSize;

        GLuint          m_VAO;
        GLuint          m_VBO;
        GLuint          m_EBO;
    };
}

#include "Mesh.inl"