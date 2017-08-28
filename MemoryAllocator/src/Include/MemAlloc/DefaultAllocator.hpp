#pragma once

#include <cstddef>
#include <type_traits>

#include "Allocator.hpp"

namespace agora
{
    const bool AGORA_DEBUG_ALLOCATORS = false;

    template<bool COUNT_ALLOC>
    class DefaultAllocator : public MemCheckAlloc<COUNT_ALLOC>
    {
    public:
        DefaultAllocator(const DefaultAllocator&) = delete;
        DefaultAllocator(DefaultAllocator&&) = delete;
        void operator=(const DefaultAllocator&) = delete;

       static DefaultAllocator& initialize();

        void* allocate(std::size_t size, int flags = 0);
        void* allocate(std::size_t size, std::size_t alignment, int flags = 0);

        void free(void* memory);

        const char* getID() const;

    private:
        DefaultAllocator();

        static bool m_initialized;
        static const char m_id[];
    };

    // There can be only one

    using DefaultAlloc = DefaultAllocator<AGORA_DEBUG_ALLOCATORS>;
    DefaultAlloc &g_defaultAllocator = DefaultAlloc::initialize();
}

#include "DefaultAllocator.inl"