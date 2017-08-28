template<class Allocator, bool COUNT_ALLOC>
agora::StackAllocator<Allocator, COUNT_ALLOC>::StackAllocator(const char* const id, Allocator* const allocator) :
    m_id(id),
    m_allocator(allocator),
    m_stackSize(0),
    m_stack(nullptr),
    m_currPos(nullptr)
{
}

template<class Allocator, bool COUNT_ALLOC>
agora::StackAllocator<Allocator, COUNT_ALLOC>::StackAllocator(Allocator* const allocator) :
    m_id(nullptr),
    m_allocator(allocator),
    m_stackSize(0),
    m_stack(nullptr),
    m_currPos(nullptr)
{
}

template<class Allocator, bool COUNT_ALLOC>
agora::StackAllocator<Allocator, COUNT_ALLOC>::~StackAllocator()
{
    m_allocator->free(m_stack);
}

template<class Allocator, bool COUNT_ALLOC>
bool agora::StackAllocator<Allocator, COUNT_ALLOC>::prepare(std::size_t const size)
{
    assert(m_stack == nullptr);

    m_stack = reinterpret_cast<aByte*>(m_allocator->allocate(size, 0));
    if (m_stack == nullptr)
    {
        return false;
    }

    m_stackSize = size;
    m_currPos = m_stack;
    return true;
}

template<class Allocator, bool COUNT_ALLOC>
void* agora::StackAllocator<Allocator, COUNT_ALLOC>::allocate(std::size_t const size, int const flags)
{
    assert(m_stack != nullptr);

    std::ptrdiff_t used = m_currPos - m_stack;
    if (used + size + 1 > m_stackSize)
    {
        return nullptr; // too full
    }

    m_currPos[0] = static_cast<aByte>(1); // set
    aByte* result = m_currPos + 1;
    m_currPos = result + size;
    return result;
}

template<class Allocator, bool COUNT_ALLOC>
void* agora::StackAllocator<Allocator, COUNT_ALLOC>::allocate(std::size_t size, std::size_t alignment, int flags)
{
    assert(m_stack != nullptr);
    assert(alignment >= 1);
    assert(alignment <= 8 * alignof(std::max_align_t));
    assert(isPow2(alignment)); // pwr of 2

    std::size_t spaceLeft = m_stackSize - (m_currPos - m_stack) - 1; // need at least some left
    void* startLoc = m_currPos + 1;
    aByte* result = reinterpret_cast<aByte*>(std::align(alignment, size, startLoc, spaceLeft));

    if (result == nullptr)
    {
        return nullptr; // too full
    }

    result[-1] = static_cast<aByte>(result - m_currPos);
    m_currPos = result + size;
    return result;
}

template<class Allocator, bool COUNT_ALLOC>
void agora::StackAllocator<Allocator, COUNT_ALLOC>::free(void* memory)
{
    if (memory == nullptr)
    {
        return;
    }

    aByte* pMem = reinterpret_cast<aByte*>(memory);
    std::uintptr_t mem = reinterpret_cast<std::uintptr_t>(memory);
    // retrieve the adjustment:
    std::ptrdiff_t diff = static_cast<std::ptrdiff_t>(pMem[-1]);
    std::uintptr_t unalignMem = mem - diff;

    m_currPos = reinterpret_cast<aByte*>(unalignMem);
}

template<class Allocator, bool COUNT_ALLOC>
const char* agora::StackAllocator<Allocator, COUNT_ALLOC>::getID() const
{
    return m_id;
}

template<class Allocator, bool COUNT_ALLOC>
void agora::StackAllocator<Allocator, COUNT_ALLOC>::setID(const char* id)
{
    m_id = id;
}