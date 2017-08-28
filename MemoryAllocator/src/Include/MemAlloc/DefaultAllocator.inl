template<bool COUNT_ALLOC>
bool agora::DefaultAllocator<COUNT_ALLOC>::DefaultAllocator::m_initialized = false;

template<bool COUNT_ALLOC>
const char agora::DefaultAllocator<COUNT_ALLOC>::DefaultAllocator::m_id[] = "DEFAULT_ALLOCATOR";

template<bool COUNT_ALLOC>
agora::DefaultAllocator<COUNT_ALLOC>::DefaultAllocator() :
    MemCheckAlloc<COUNT_ALLOC>()
{
}

template<bool COUNT_ALLOC>
agora::DefaultAllocator<COUNT_ALLOC>& agora::DefaultAllocator<COUNT_ALLOC>::initialize()
{
    assert(m_initialized == false);
    static DefaultAllocator<COUNT_ALLOC> defaultAllocator;
    return defaultAllocator;
}

template<bool COUNT_ALLOC>
void* agora::DefaultAllocator<COUNT_ALLOC>::allocate(std::size_t size, int flags)
{
    void* result = std::malloc(size);
    MemCheckAlloc<COUNT_ALLOC>::incCnt(result);
    return result;
}

template<bool COUNT_ALLOC>
void* agora::DefaultAllocator<COUNT_ALLOC>::allocate(std::size_t size, std::size_t alignment, int flags)
{
    return allocate(size, flags);
}

template<bool COUNT_ALLOC>
void agora::DefaultAllocator<COUNT_ALLOC>::free(void* memory)
{
    std::free(memory);
    MemCheckAlloc<COUNT_ALLOC>::decCnt();
}

template<bool COUNT_ALLOC>
const char* agora::DefaultAllocator<COUNT_ALLOC>::getID() const
{
    return m_id;
}
