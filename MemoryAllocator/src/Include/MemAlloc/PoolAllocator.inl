template<class Allocator, bool COUNT_ALLOC>
agora::PoolAllocator<Allocator, COUNT_ALLOC>::PoolAllocator(const char* const id, Allocator* const allocator) :
    m_id(id),
    m_allocator(allocator),
    m_pool(nullptr),
    m_currFree(nullptr),
    m_blockSize(0),
    m_poolSize(0)
{
}

template<class Allocator, bool COUNT_ALLOC>
agora::PoolAllocator<Allocator, COUNT_ALLOC>::PoolAllocator(Allocator* const allocator) :
    m_id(nullptr),
    m_allocator(allocator),
    m_pool(nullptr),
    m_currFree(nullptr),
    m_blockSize(0),
    m_poolSize(0)
{
}

template<class Allocator, bool COUNT_ALLOC>
agora::PoolAllocator<Allocator, COUNT_ALLOC>::~PoolAllocator()
{
    m_allocator->free(m_pool);
}

template<class Allocator, bool COUNT_ALLOC>
bool agora::PoolAllocator<Allocator, COUNT_ALLOC>::prepare(std::size_t const minBlockSize, std::size_t const numBlocks, std::size_t const minAlignment)
{
    assert(minBlockSize >= sizeof(void*)); // make sure it can store a pointer
    assert(minAlignment >= 1);
    assert(minAlignment <= 8 * alignof(std::max_align_t));
    assert(isPow2(minAlignment)); // pwr of 2
    assert(m_pool == nullptr);

    m_blockSize = std::max(lgPow2(minBlockSize), minAlignment);
    m_poolSize = m_blockSize * numBlocks;

    if (m_blockSize % minAlignment != 0)
    {
        m_blockSize = (m_blockSize / minAlignment + 1) * minAlignment;
    }

    // allocate using the allocator as usual:
    m_pool = reinterpret_cast<aByte*>(m_allocator->allocate(m_poolSize, m_blockSize, 0)); // in case block size is greater than alignment

    if (m_pool == nullptr)
    {
        m_blockSize = m_poolSize = 0;
        return false;
    }

    m_currFree = m_pool;

    aByte* nextPtr = m_pool;
    for (std::size_t i = 0; i < numBlocks - 1; i++)
    {
        *reinterpret_cast<aByte**>(nextPtr) = nextPtr + m_blockSize;
        nextPtr += m_blockSize;
    }
    *reinterpret_cast<aByte**>(nextPtr) = nullptr; // cap the end of with a nullptr
    return true;
}

template<class Allocator, bool COUNT_ALLOC>
void* agora::PoolAllocator<Allocator, COUNT_ALLOC>::allocate(std::size_t size, int flags)
{
    assert(m_pool != nullptr);

    if (m_currFree == nullptr || size > m_blockSize)
    {
        return nullptr; // doesn't update m_curr_free
    }

    void* result = m_currFree;
    MemCheckAlloc<COUNT_ALLOC>::incCnt(m_currFree);
    m_currFree = *reinterpret_cast<aByte**>(m_currFree);
    return result;
}

template<class Allocator, bool COUNT_ALLOC>
void* agora::PoolAllocator<Allocator, COUNT_ALLOC>::allocate(std::size_t size, std::size_t alignment, int flags)
{
    if (alignment > m_blockSize || size > m_blockSize)
    {
        return nullptr; // can't satisfy given alignment
    }

    return allocate(size, flags);
}

template<class Allocator, bool COUNT_ALLOC>
void agora::PoolAllocator<Allocator, COUNT_ALLOC>::free(void* memory)
{
    assert(m_pool != nullptr);

    if (memory == nullptr)
    {
        return;
    }

    if (memory < m_pool || memory > m_pool + m_poolSize - m_blockSize)
    {
        return;
    }

    *reinterpret_cast<aByte**>(memory) = m_currFree;
    m_currFree = reinterpret_cast<aByte*>(memory);
    MemCheckAlloc<COUNT_ALLOC>::decCnt();
}

template<class Allocator, bool COUNT_ALLOC>
const char* agora::PoolAllocator<Allocator, COUNT_ALLOC>::getID() const
{
    return m_id;
}

template<class Allocator, bool COUNT_ALLOC>
void agora::PoolAllocator<Allocator, COUNT_ALLOC>::setID(const char* id)
{
    m_id = id;
}