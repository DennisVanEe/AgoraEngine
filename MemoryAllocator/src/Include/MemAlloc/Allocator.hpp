#pragma once

#include <cassert>
#include <cstddef>
#include <algorithm>
#include <type_traits>

#include <Types.hpp>
#include <Utility.hpp>

namespace agora
{
    template<bool COUNT_ALLOC>
    class MemCheckAlloc
    {
    public:
    protected:
        void incCnt(void* check);
        void decCnt();
    };

    template<>
    class MemCheckAlloc<true>
    {
    public:
        MemCheckAlloc();
        ~MemCheckAlloc();

    protected:
        void incCnt(void* check);
        void decCnt();

    private:
        unsigned m_allocCount;
    };
}

#include "Allocator.inl"