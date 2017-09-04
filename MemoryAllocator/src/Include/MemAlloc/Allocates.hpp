#pragma once

namespace agora
{
    template<class Allocator>
    class Allocates
    {
    protected:
        Allocates(Allocator& alloc) :
            m_Allocator(alloc) {}

        Allocator& m_Allocator;
    };
}