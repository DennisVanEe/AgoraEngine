#pragma once

#include <amath/float3.hpp>
#include <amath/float2.hpp>
#include <glad/glad.h>

namespace agora
{
    // TODO: formalize this, but, this is the shader convention:
    // 0: position, 1: normal, 2: textCoord, 3: tangent, 4: bitangent
    // The vertex itself sets up the attribute so that it remains independent 
    // of the system itself.

    template<class VecType3 = math::Float3, class VecType2 = math::Float2>
    struct Vertex
    {
        VecType3 position;
        VecType3 normal;
        VecType2 textCoord;

        static inline void setVertexAttributes(GLuint VAO);
        static inline void setVertexAttributes();
    };

    // also has tangent and bitangent info
    template<class VecType3 = math::Float3, class VecType2 = math::Float2>
    struct TVertex
    {
        VecType3 position;
        VecType3 normal;
        VecType2 textCoord;

        VecType3 tangent;
        VecType3 bitangent;

        static inline void setVertexAttributes(GLuint VAO);
        static inline void setVertexAttributes();
    };
}

// inline/template definitions

template<class VecType3, class VecType2>
inline void Vertex<VecType3, VecType2>::setVertexAttributes(GLuint const VAO)
{
    glBindVertexArray(VAO);
    setVertexAttributes();
    glBindVertexArray(0);
}

template<class VecType3, class VecType2>
inline void Vertex<VecType3, VecType2>::setVertexAttributes()
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(*this), (void*)offsetof(Vertex<VecType3, VecType2>, position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(*this), (void*)offsetof(Vertex<VecType3, VecType2>, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(*this), (void*)offsetof(Vertex<VecType3, VecType2>, textCoord));
}

template<class VecType3, class VecType2>
inline void TVertex<VecType3, VecType2>::setVertexAttributes(GLuint const VAO)
{
    glBindVertexArray(VAO);
    setVertexAttributes();
    glBindVertexArray(0);
}

template<class VecType3, class VecType2>
inline void TVertex<VecType3, VecType2>::setVertexAttributes()
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(*this), (void*)offsetof(TVertex<VecType3, VecType2>, position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(*this), (void*)offsetof(TVertex<VecType3, VecType2>, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(*this), (void*)offsetof(TVertex<VecType3, VecType2>, textCoord));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(*this), (void*)offsetof(TVertex<VecType3, VecType2>, tangent));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(*this), (void*)offsetof(TVertex<VecType3, VecType2>, bitangent));
}