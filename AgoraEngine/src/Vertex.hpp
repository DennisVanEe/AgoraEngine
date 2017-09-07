#pragma once

#include <Math/Float2.hpp>
#include <Math/Float3.hpp>
#include <cassert>
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
        VecType3* m_positionList;
        VecType3* m_normalList;
        VecType2* m_textCoordList;

        inline void setVertexAttributes(GLuint VBO, unsigned numVert);
        inline void setVertexAttributes(unsigned numVert);
    };

    // also has tangent and bitangent info
    template<class VecType3 = math::Float3, class VecType2 = math::Float2>
    struct TVertex
    {
        VecType3* m_positionList;
        VecType3* m_normalList;
        VecType2* m_textCoordList;

        VecType3* m_tangents;
        VecType3* m_bitangents;

        inline void setVertexAttributes(GLuint VBO, unsigned numVert);
        inline void setVertexAttributes(unsigned numVert);
    };
}

// inline/template definitions

template<class VecType3, class VecType2>
void agora::Vertex<VecType3, VecType2>::setVertexAttributes(GLuint VBO, unsigned numVert)
{
    assert(VBO != 0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    setVertexAttributes(numVert);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<class VecType3, class VecType2>
void agora::Vertex<VecType3, VecType2>::setVertexAttributes(unsigned numVert)
{
    // assign the data to the currently bound buffer object

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VecType3) * numVert, m_positionList); assert(glGetError() == GL_NO_ERROR);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(VecType3) * numVert, sizeof(VecType3) * numVert, m_normalList); assert(glGetError() == GL_NO_ERROR);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(VecType3) * 2 * numVert, sizeof(VecType2) * numVert, m_textCoordList); assert(glGetError() == GL_NO_ERROR);

    // vertex attribute data:
    // attribute information (can be inferred)
    // attribute size (easy enough to supply)
    // type (always GL_FLOAT in this case)
    // normalize (true or false, easy enough)
    // offset (provide a simple numerical value)
    // location to start (easy enough, this will be provided as well)

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(VecType3) * numVert));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(VecType3) * 2 * numVert));
}

template<class VecType3, class VecType2>
void agora::TVertex<VecType3, VecType2>::setVertexAttributes(GLuint VBO, unsigned numVert)
{
    assert(VBO != 0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    setVertexAttributes(numVert);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<class VecType3, class VecType2>
void agora::TVertex<VecType3, VecType2>::setVertexAttributes(unsigned numVert)
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