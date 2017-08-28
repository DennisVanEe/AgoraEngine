#pragma once

#include <cassert>
#include <cstddef>
#include <algorithm>
#include <memory>

#include "Allocator.hpp"
#include <Types.hpp>
#include <Utility.hpp>

namespace agora
{
    template<class Allocator, bool COUNT_ALLOC>
    class StackAllocator : public MemCheckAlloc<COUNT_ALLOC>
    {
    public:
        StackAllocator(const char* id, Allocator* allocator);
        StackAllocator(Allocator* allocator);
        ~StackAllocator();

        bool prepare(std::size_t size);

        // need to be held constant throughout all allocators:

        void* allocate(std::size_t size, int flags);
        void* allocate(std::size_t size, std::size_t alignment, int flags);

        void free(void* memory);

        const char* getID() const;
        void setID(const char* id);

    private:
        const char* m_id;
        Allocator* const m_allocator;

        std::size_t m_stackSize;
        aByte* m_stack; // used to delete the stack
        aByte* m_currPos;
    };
}

#include "StackAllocator.inl"