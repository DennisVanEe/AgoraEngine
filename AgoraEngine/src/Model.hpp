#pragma once

#include "Mesh.hpp"

namespace agora
{
    template<class Vertex, class Allocator>
    class Model
    {
    public:
        Model(Allocator* allocator);

        void prepare(std::size_t numMesh);
        
    private:
        struct MeshBucket
        {
            Mesh<Vertex, Allocator> m_mesh;
            unsigned m_nChildren; // number of children
            unsigned m_nLoc; // where in meshRelations can we find this

            MeshBucket() :
                m_mesh(m_allocator) {}
        };

    private:
        Allocator* const m_allocator;

        // Basic Layout:
        // m_meshList just stores all the meshes (yawn)
        // Each MeshBuckets points into the m_meshRelations 

        MeshBucket* m_meshList;
        unsigned* m_meshRelations;
        unsigned m_numMeshes;
    };
}

// inline definitions

template<class Vertex, class Allocator>
agora::Model<Vertex, Allocator>::Model(Allocator* const allocator) :
    m_allocator(allocator),
    m_meshList(nullptr),
    m_meshRelations(nullptr),
    m_numMeshes(0)
{
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