#pragma once

#include <memory>
#include <MemAlloc/Allocates.hpp>
#include <ZIPArchive.hpp>

#include "Mesh.hpp"

namespace agora
{
    template<class Allocator>
    class Model : public Allocates<Allocator>
    {
    public:
        Model(Allocator& allocator);

        bool prepare(const ZIPArchive::File& numMesh);
        
    private:
        struct MeshBucket
        {
            Mesh m_mesh;
            unsigned m_nChildren; // number of children
            unsigned m_nLoc; // where in meshRelations can we find this

            MeshBucket() :
                m_mesh(m_allocator) {}
        };
        static_assert(alignof(MeshBucket) == alignof(unsigned), "This is to keep buffers in itself.");

    private:
        // Basic Layout:
        // m_meshList just stores all the meshes (yawn)
        // Each MeshBuckets points into the m_meshRelations 

        MeshBucket* m_meshList;
        unsigned* m_meshRelations;
        unsigned m_numMeshes;
    };
}

// inline definitions

template<class Allocator>
agora::Model<Allocator>::Model(Allocator& allocator) :
    Allocates<Allocator>(allocator),
    m_meshList(nullptr),
    m_meshRelations(nullptr),
    m_numMeshes(0)
{
}

template<class Allocator>
inline bool agora::Model<Allocator>::prepare(const ZIPArchive::File& numMesh)
{
    aByte tempBuffer[8];

    numMesh.readBytes(tempBuffer, 4);
    numMesh.


    // get alignment information first:
    std::size_t relationsListSize = sizeof(unsigned) * (numMesh - 1);

    // get alignment information all worked out:
    void* location = reinterpret_cast<void*>(numMesh * sizeof(MeshBucket));
    void* result = std::align(alignof(unsigned), relationsListSize, location, std::numeric_limits<std::size_t>::max()); // essentially all of it
    std::size_t size = reinterpret_cast<std::uintptr_t>(result) + relationsListSize;
    std::uintptr_t mem = reinterpret_cast<std::uintptr_t>(m_Allocator.allocate(size, alignof(MeshBucket), 0));

    m_meshList = reinterpret_cast<MeshBucket*>(mem);
    m_meshRelations = reinterpret_cast<unsigned*>(mem + reinterpret_cast<std::uintptr_t>(result));
    m_numMeshes = numMesh;
    return mem != 0;
}

template<class Vertex, class Allocator>
void agora::Model<Vertex, Allocator>::prepare(const std::size_t numMesh)
{
    m_numMeshes = numMesh;
    if (m_numMeshes == 0)
    {
        return;
    }

    // NOTE: all necessary memory should already have been allocated, so we can't run out of memory at this stage
    void* meshListLoc = m_allocator->allocate(m_numMeshes * sizeof(MeshBucket), alignof(MeshBucket)); assert(meshListLoc);
    m_meshList = new(meshListLoc) MeshBucket[m_numMeshes];

    void* meshRelationsLoc = m_allocator->allocate(m_numMeshes * sizeof(unsigned), alignof(unsigned)); assert(meshListLoc);
    m_meshRelations = new(meshRelationsLoc) unsigned[m_numMeshes];
}