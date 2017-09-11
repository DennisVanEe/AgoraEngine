#pragma once

#include <vector>
#include "number_ops.hpp"
#include <math/float3.hpp>
#include <math/float4.hpp>
#include <math/float2.hpp>

namespace agora
{
    // this is just the version used by the importer, and is not 
    // indicative of the actual format used by the game engine.
    class Mesh
    {
    public:
        inline void addPositions(std::vector<math::Float3> pos);
        inline void addNormals(std::vector<math::Float3> norms);
        inline void addTangents(std::vector<math::Float3> tans);
        inline void addBitangents(std::vector<math::Float3> bitans);
        inline void addUVCoords(std::vector<math::Float2> textcoord);
        inline void addUVWCoords(std::vector<math::Float3> textcoord);
        inline void addVertColor(std::vector<math::Float4> vertcolor);
        inline void addIndices(std::vector<unsigned> indices);

    private:
        const uByte NORMALS     = 0x01;
        const uByte TANGENTS    = 0x02;
        const uByte UVCOORD     = 0x04;
        const uByte VERTCOLOR   = 0x08;
        const uByte BITANGENT   = 0x10;

        uint8_t m_flags;

        std::vector<math::Float3> m_pos;
        std::vector<math::Float3> m_norms;
        std::vector<unsigned> m_indices;

        std::vector<math::Float3> m_tangents;
        std::vector<math::Float3> m_bitangents;

        std::vector<math::Float2> m_textCoords2;
        std::vector<math::Float3> m_textCoords3;

        std::vector<math::Float4> m_vertColor;
    };
}

void agora::Mesh::addPositions(std::vector<math::Float3> pos)
{
    m_pos = std::move(pos);
}

void agora::Mesh::addNormals(std::vector<math::Float3> norms)
{
    m_flags |= NORMALS;
    m_norms = std::move(norms);
}

void agora::Mesh::addTangents(std::vector<math::Float3> tans)
{
    m_flags |= TANGENTS;
    m_tangents = std::move(tans);
}

void agora::Mesh::addBitangents(std::vector<math::Float3> bitans)
{
    m_flags |= BITANGENT;
    m_bitangents = std::move(bitans);
}

void agora::Mesh::addUVCoords(std::vector<math::Float2> textcoord)
{
    m_flags |= UVCOORD;
    m_textCoords2 = std::move(textcoord);
}

void agora::Mesh::addUVWCoords(std::vector<math::Float3> textcoord)
{
    m_flags |= UVCOORD;
    m_textCoords3 = std::move(textcoord);
}

void agora::Mesh::addVertColor(std::vector<math::Float4> vertcolor)
{
    m_flags |= VERTCOLOR;
    m_vertColor = std::move(vertcolor);
}

inline void agora::Mesh::addIndices(std::vector<unsigned> indices)
{

}
