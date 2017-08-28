#pragma once

#include <cassert>
#include <cstddef>
#include <algorithm>

#include "Allocator.hpp"
#include <Types.hpp>
#include <Utility.hpp>

namespace agora
{
    template<class Allocator, bool COUNT_ALLOC>
    class PoolAllocator : public MemCheckAlloc<COUNT_ALLOC>
    {
    public:
        PoolAllocator(const char* id, Allocator* allocator);
        PoolAllocator(Allocator* allocator);
        ~PoolAllocator();

        bool prepare(std::size_t minBlockSize, std::size_t numBlocks, std::size_t minAlignment);

        // need to be held constant throughout all allocators:

        void* allocate(std::size_t size, int flags = 0);
        void* allocate(std::size_t size, std::size_t alignment, int flags = 0);

        void free(void* memory);

        const char* getID() const;
        void setID(const char* id);

    private:
        const char* m_id;
        Allocator* const m_allocator;

        aByte* m_pool;
        aByte* m_currFree;
        std::size_t m_blockSize, m_poolSize;
    };
}

#include "PoolAllocator.inl"