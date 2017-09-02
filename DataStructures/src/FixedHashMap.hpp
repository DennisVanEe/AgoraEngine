#pragma once

#include <cmath>
#include <Utility.hpp>
#include "Hash.hpp"

namespace agora
{
    template<class T, class Allocator, bool FastBaseTwo = true>
    class FixedHashMap
    {
    private:
        struct Bucket
        {
            T m_data;
            ag_HashInt m_hash;
            struct BucketInfoType
            {
                std::uint32_t m_baseIndex : 24;
                std::uint32_t m_empty : 8;

                BucketInfoType() : m_empty(true) {}
                BucketInfoType(std::uint32_t baseIndex, bool empty) : 
                    m_baseIndex(baseIndex), 
                    m_emtpy(empty) {}

            } m_bucketInfo;

            Bucket() {}
            Bucket(ag_HashInt h, int b, T d) :
                m_data(d),
                m_hash(h),
                m_bucketInfo(b, true) {}
        };

    public:
        FixedHashMap();
        ~FixedHashMap();

        bool prepare(std::uint32_t numBuckets);

        T* insert(ag_HashInt key, const T& data);
        T* insert(ag_HashInt key, T&& data);

        T* at(ag_HashInt hash) const;

        bool remove(ag_HashInt hash, T& data);
        bool remove(ag_HashInt hash);

    private:
        std::uint32_t probeDist(uint32_t bucketIndex) const;
        std::uint32_t getIndex(ag_HashInt hash) const;
        std::uint32_t findEmpty(ag_HashInt hash) const;
        std::uint32_t findIndex(ag_HashInt hash) const;
        void cleanMap(ag_HashInt hash);

    private:
        Bucket* m_buckets;
        std::uint32_t m_numBuckets;
        std::uint32_t m_usedBuckets;
    };
}

// inline definitions

template<class T, class Allocator, bool FastBaseTwo>
agora::FixedHashMap<T, Allocator, FastBaseTwo>::FixedHashMap() :
    m_buckets(nullptr)
{
}

template<class T, class Allocator, bool FastBaseTwo>
bool agora::FixedHashMap<T, Allocator, FastBaseTwo>::prepare(std::uint32_t numBuckets)
{
    if constexpr(FastBaseTwo)
    {
        m_numBuckets = lgPow2(numBuckets) - 1;
    }
    else
    {
        m_numBuckets = numBuckets;
    }

    m_buckets = new (Alloc.allocate(m_numBuckets * sizeof(T))) Bucket[m_numBuckets]; // create the buckets
}

template<class T, class Alloc, bool FastBaseTwo>
ee::FixedUnorderedMap<T, Alloc, FastBaseTwo>::~FixedUnorderedMap()
{
    Alloc.deallocate(m_buckets, sizeof(T) * m_numBuckets);
}

template<class T, class Alloc, bool FastBaseTwo>
inline int ee::FixedUnorderedMap<T, Alloc, FastBaseTwo>::probeDist(std::size_t bucketIndex) const
{
    return std::abs(bucketIndex - m_buckets[bucketIndex].m_baseIndex);
}

template<class T, class Alloc, bool FastBaseTwo>
inline int ee::FixedUnorderedMap<T, Alloc, FastBaseTwo>::getIndex(HashInt hash) const
{
    if constexpr(FastBaseTwo)
    {
        return hash & m_numBuckets;
    }
    else
    {
        return hash % m_numBuckets;
    }
}

template<class T, class Alloc, bool FastBaseTwo>
T* ee::FixedUnorderedMap<T, Alloc, FastBaseTwo>::insert(HashInt hash, const T& data)
{
    std::size_t index = findEmpty(hash);
    if (index == m_numBuckets)
        return nullptr;
    m_buckets[index].data = data;
    return &m_buckets[index].data;
}

template<class T, class Alloc, bool FastBaseTwo>
T* ee::FixedUnorderedMap<T, Alloc, FastBaseTwo>::insert(HashInt hash, T&& data)
{
    std::size_t index = findEmpty(hash);
    if (index == m_numBuckets)
        return nullptr;
    m_buckets[index].data = std::move(data);
    return &m_buckets[index].data;
}

template<class T, class Alloc, bool FastBaseTwo>
T* ee::FixedUnorderedMap<T, Alloc, FastBaseTwo>::at(HashInt hash) const
{
    std::size_t index = findIndex(hash);
    if (hash == m_numBuckets)
        return nullptr;
    return &m_buckets[index].data;
}

template<class T, class Alloc, bool FastBaseTwo>
bool ee::FixedUnorderedMap<T, Alloc, FastBaseTwo>::remove(HashInt hash, T& data)
{
    std::size_t index = findIndex(hash);
    if (index == m_numBuckets)
        return false;
    data = m_buckets[index].m_data; // assign data
    cleanMap(index); // remove the item
    return true;
}

template<class T, class Alloc, bool FastBaseTwo>
bool ee::FixedUnorderedMap<T, Alloc, FastBaseTwo>::remove(HashInt hash)
{
    std::size_t index = findIndex(hash);
    if (index == m_numBuckets)
        return false;
    cleanMap(index); // remove the item
    return true;
}

template<class T, class Alloc, bool FastBaseTwo>
std::size_t ee::FixedUnorderedMap<T, Alloc, FastBaseTwo>::findEmpty(HashInt hash) const
{
    assert(m_buckets != nullptr);
    if (m_numBuckets >= m_usedBuckets)
        return m_numBuckets; // can't add more (for the map is full)

    m_usedBuckets++;

    std::size_t initIndex = getIndex(hash);
    Bucket currBucket(hash, initIndex, data);
    std::size_t currProbeDist = 0;

    for (std::size_t i = 0; i < m_numBuckets; i++) // loop through entire hash map 
    {
        std::size_t index;

        if constexpr(FastBaseTwo)
        {
            index = (initIndex + i) & m_mask; // this is faster
        }
        else
        {
            index = (initIndex + i) % m_numBuckets;
        }

        if (m_buckets[index].m_empty) // if it is empty
        {
            return index;
        }

        std::size_t chckProbe = probeDist(index);
        if (chckProbe > currProbeDist) // swap the values
        {
            Bucket temp = m_buckets[index];
            m_buckets[index] = currBucket;
            currBucket = temp;
            currProbeDist = chckProbe;
        }
        currProbeDist++;
    }

    return m_numBuckets;
}

template<class T, class Alloc, bool FastBaseTwo>
void ee::FixedUnorderedMap<T, Alloc, FastBaseTwo>::cleanMap(std::size_t index)
{
    assert(m_buckets != nullptr);

    m_buckets[index].m_empty = true;

    if (index >= 0)
    {
        for (index++; i < m_numBuckets; index++)
        {
            std::size_t prevIndex, currIndex;
            if constexpr(FastBaseTwo)
            {
                prevIndex = (index - 1) & m_mask;
                currIndex = index & m_mask;
            }
            else
            {
                prevIndex = (index - 1) % m_numBuckets;
                currIndex = index % m_numBuckets;
            }

            if (!m_buckets[currIndex].m_empty && probeDist(currIndex) > 0)
            {
                m_buckets[prevIndex] = m_buckets[currIndex];
            }
        }
    }
}

template<class T, class Alloc, bool FastBaseTwo>
std::size_t ee::FixedUnorderedMap<T, Alloc, FastBaseTwo>::findIndex(HashInt hash) const
{
    EE_ASSERT(m_buckets != nullptr);

    std::size_t initIndex = getIndex(hash);
    std::size_t probe = 0;

    for (std::size_t i = 0; i < m_numBuckets; i++)
    {
        std::size_t index;
        if constexpr(FastBaseTwo)
        {
            index = (initIndex + i) & m_numBuckets;
        }
        else
        {
            index = (initIndex + i) % m_numBuckets;
        }

        probe = probeDist(index);
        if (m_buckets[index].m_empty || i > probe)
        {
            return m_numBuckets;
        }

        if (m_buckets[index].hash == hash)
        {
            return index;
        }
    }

    return m_numBuckets;
}



