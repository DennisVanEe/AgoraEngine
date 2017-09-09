#pragma once

#include <cstddef>
#include <cassert>
#include <cstdint>
#include <MemAlloc/Allocates.hpp>
#include <glad/glad.h>

#include "Include/Types.hpp"

#define AGORA_DEBUG

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
        T* getVertexData(unsigned startLoc);
        template<typename T>
        const T* getVertexData(unsigned startLoc) const;
        // Get max amount of space that is accessible for use (0 if non was allocated or there was an error)
        unsigned getVertexBufferSize() const;

        template<typename T>
        T* releaseVertexData(unsigned startLoc);
        void returnVertexData();
        GLuint* releaseIndexData(unsigned startLoc = 0);
        void returnIndexData();

        GLuint* getIndexData(unsigned startLoc = 0);
        const GLuint* getIndexData(unsigned startLoc = 0) const;
        unsigned getIndexBufferSize() const;

        unsigned getNumIndices() const;

        void addAttrib(unsigned index, VertexAttrib attrib);

        void sendToGPU(GLenum usage = GL_STATIC_DRAW);
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
        friend class Model;

        // Memory is purely managed by the model itself
        unsigned prepare(void* baseLocation, unsigned vertexBuffSize, unsigned numAttrib, unsigned stride, unsigned indexBuffSize);

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

#   ifdef AGORA_DEBUG
        bool            m_VBOReleased;
        bool            m_EBOReleased;
#   endif
    };
    static_assert(alignof(Mesh) == alignof(void*), "");
}

#include "Mesh.inl"