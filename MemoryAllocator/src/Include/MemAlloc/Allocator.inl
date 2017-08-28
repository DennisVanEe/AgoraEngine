agora::MemCheckAlloc<true>::MemCheckAlloc() :
    m_allocCount(0)
{
}

agora::MemCheckAlloc<true>::~MemCheckAlloc()
{
    assert(m_allocCount == 0);
}

void agora::MemCheckAlloc<true>::incCnt(void* check)
{
    if (check != nullptr) m_allocCount++;
}

void agora::MemCheckAlloc<true>::decCnt()
{
    m_allocCount--;
}

template<bool COUNT_ALLOC>
void agora::MemCheckAlloc<COUNT_ALLOC>::incCnt(void* check)
{
}

template<bool COUNT_ALLOC>
void agora::MemCheckAlloc<COUNT_ALLOC>::decCnt()
{
}