#pragma once

#include <memory>
#include <MemAlloc/Allocates.hpp>
#include <ZIPArchive.hpp>

#include "Include/Utility.hpp"
#include "Mesh.hpp"

namespace agora
{
    struct Model
    {
    public:
        Model();

        template<class Allocator>
        bool prepare(Allocator& allocator, const ZIPArchive::File& numMesh);

    private:
        struct MeshBucket
        {
            Mesh m_mesh;
            unsigned m_nChildren; // number of children
            unsigned m_nLoc; // where in meshRelations can we find this
        };

    private:
        // Basic Layout:
        // m_meshList just stores all the meshes (yawn)
        // Each MeshBuckets points into the m_meshRelations 

        MeshBucket*     m_meshList;
        unsigned*       m_meshRelations;
        unsigned        m_numMeshes;
    };
}

// inline definitions

agora::Model::Model() :
    m_meshList(nullptr),
    m_meshRelations(nullptr),
    m_numMeshes(0)
{
}

template<class Allocator>
bool agora::Model::prepare(Allocator& allocator, const ZIPArchive::File& meshFile)
{
    aByte tempBuffer[6 * UINT32_SIZE];
    bool readCheck;

    // Get the number of meshes:
    readCheck = meshFile.readBytes(tempBuffer, UINT32_SIZE); assert(readCheck);
    m_numMeshes = loadUINT32(tempBuffer); assert(m_numMeshes > 0);

    // Calculate other values from this:
    const std::uint32_t meshListSize = sizeof(MeshBucket) * m_numMeshes;
    const std::uint32_t meshRelationsSize = UINT32_SIZE * (m_numMeshes - 1);

    // Get the size of the vertex buffer (includes indices buffer):
    readCheck = meshFile.readBytes(tempBuffer, UINT32_SIZE); assert(readCheck);
    const std::uint32_t meshDataSize = loadUINT32(tempBuffer); assert(meshDataSize > 0);

    // Calculate total amount to allocate
    const std::uint32_t totalAllocSize = meshListSize + meshRelationsSize + meshDataSize; // because of the alignments, no padding is required here

    // allocate the memory:
    aByte* memory = allocator.allocate(totalAllocSize, alignof(MeshBucket), 0);

    if (memory == nullptr)
    {
        m_numMeshes = 0;
        return false; // there was probably not enough memory (this is, really, the ONLY reason an allocator can fail (invalid param. causes undefined behaviour)
    }

    // prepare the MeshList:
    m_meshList = new(memory) MeshBucket[m_numMeshes];
    memory += meshListSize;

    // Load the rest:
    readCheck = meshFile.readBytes(memory, meshRelationsSize + meshDataSize); assert(readCheck);

    // Now set up this memory for others to use:
    m_meshRelations = memory;
    memory += meshRelationsSize;

    // Now read the information pertaining to each mesh and prepare them as appropriate:
    for (std::uint32_t i = 0; i < m_numMeshes; i++)
    {
        readCheck = meshFile.readBytes(tempBuffer, 6 * UINT32_SIZE); assert(readCheck); // load all of the mesh information we need:
        const unsigned vertexBuffSize = loadUINT32(tempBuffer + UINT32_SIZE * 0);
        const unsigned numAttrib      = loadUINT32(tempBuffer + UINT32_SIZE * 1);
        const unsigned stride         = loadUINT32(tempBuffer + UINT32_SIZE * 2);
        const unsigned indexBuffSize  = loadUINT32(tempBuffer + UINT32_SIZE * 3);
        const unsigned nChildren      = loadUINT32(tempBuffer + UINT32_SIZE * 4);
        const unsigned nLoc           = loadUINT32(tempBuffer + UINT32_SIZE * 5);
        
        memory += m_meshList[i].m_mesh.prepare(memory, vertexBuffSize, numAttrib, stride, indexBuffSize);
        m_meshList[i].m_nChildren = nChildren;
        m_meshList[i].m_nLoc      = nLoc;
    }

    return true;
}