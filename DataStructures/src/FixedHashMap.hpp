#pragma once

#include <cmath>
#include <cassert>

#include <Utility.hpp>
#include <MemAlloc/Allocates.hpp>
#include "Hash.hpp"

namespace agora
{
    template<class T, class Allocator, bool FastBaseTwo = true>
    class FixedHashMap : public Allocates<Allocator>
    {
    private:
        struct Bucket
        {
            T m_data;
            HashInt m_hash;
            struct BucketInfoType
            {
                std::uint32_t m_baseIndex : 24;
                std::uint32_t m_empty : 8;

                BucketInfoType() : 
                    m_empty(true) {}
                BucketInfoType(std::uint32_t baseIndex, bool empty) : 
                    m_baseIndex(baseIndex), 
                    m_empty(empty) {}

            } m_bucketInfo;

            Bucket() {}
            Bucket(HashInt h, std::uint32_t b) :
                m_hash(h),
                m_bucketInfo(b, true) {}
            Bucket(HashInt h, std::uint32_t b, T d) :
                m_data(d),
                m_hash(h),
                m_bucketInfo(b, true) {}
        };

    public:
        FixedHashMap(Allocator& allocator);
        ~FixedHashMap();

        //
        // Only returns false if there is a memory absense issue
        bool prepare(std::uint32_t numBuckets);

        T* insert(HashInt key, T data);

        T* at(HashInt hash);
        const T* at(HashInt hash) const;

        bool remove(HashInt hash, T& data);
        bool remove(HashInt hash);

    private:
        std::uint32_t probeDist(std::uint32_t bucketIndex) const;
        std::uint32_t getIndex(HashInt hash) const;
        std::uint32_t findEmpty(HashInt hash) const;
        std::uint32_t findIndex(HashInt hash) const;

        void cleanMap(std::uint32_t index);

    private:
        Bucket* m_buckets;
        std::uint32_t m_numBuckets;
        std::uint32_t m_usedBuckets;
    };
}


template<class T, class Allocator, bool FastBaseTwo>
inline agora::FixedHashMap<T, Allocator, FastBaseTwo>::FixedHashMap(Allocator & allocator) :
    Allocates<Allocator>(allocator), m_buckets(nullptr) {}

template<class T, class Allocator, bool FastBaseTwo>
agora::FixedHashMap<T, Allocator, FastBaseTwo>::~FixedHashMap() { m_Allocator.free(m_buckets, sizeof(Bucket) * m_numBuckets); }

//
// Only returns false if there is a memory absense issue
template<class T, class Allocator, bool FastBaseTwo>
bool agora::FixedHashMap<T, Allocator, FastBaseTwo>::prepare(std::uint32_t numBuckets)
{
    assert(numBuckets > 0); // no point in it being 

    if constexpr(FastBaseTwo)
    {
        m_numBuckets = lgPow2(numBuckets); // fixed size is a minimum power of 2 for faster modulation
    }
    else
    {
        m_numBuckets = numBuckets; // otherwise, just use what is given
    }

    void* memLoc = m_Allocator.allocate(m_numBuckets * sizeof(Bucket), alignof(Bucket), 0);

    if (memLoc == nullptr)
    {
        return false;
    }

    m_buckets = new(memLoc) Bucket[m_numBuckets]; // create the buckets
    return true;
}

template<class T, class Allocator, bool FastBaseTwo>
T* agora::FixedHashMap<T, Allocator, FastBaseTwo>::insert(HashInt hash, T data)
{
    const auto index = findEmpty(hash);
    if (index == m_numBuckets)
    {
        return nullptr;
    }
    m_buckets[index].m_data = data; // explicit move construction if the user wants it
    m_buckets[index].m_bucketInfo.m_empty = false;
    m_usedBuckets++;
    return &m_buckets[index].m_data;
}

template<class T, class Allocator, bool FastBaseTwo>
inline T* agora::FixedHashMap<T, Allocator, FastBaseTwo>::at(HashInt hash)
{
    const auto index = findIndex(hash);
    if (index == m_numBuckets)
    {
        return nullptr;
    }
    return &m_buckets[index].m_data;
}

template<class T, class Allocator, bool FastBaseTwo>
const T* agora::FixedHashMap<T, Allocator, FastBaseTwo>::at(HashInt hash) const
{
    return at(hash);
}

template<class T, class Allocator, bool FastBaseTwo>
bool agora::FixedHashMap<T, Allocator, FastBaseTwo>::remove(HashInt hash, T& data)
{
    const auto index = findIndex(hash);
    if (index == m_numBuckets)
    {
        return false;
        data = std::move(m_buckets[index].m_data); // assign data
    }
    cleanMap(index); // remove the item
    return true;
}

template<class T, class Allocator, bool FastBaseTwo>
bool agora::FixedHashMap<T, Allocator, FastBaseTwo>::remove(HashInt hash)
{
    const auto index = findIndex(hash);
    if (index == m_numBuckets)
    {
        return false;
    }
    cleanMap(index); // remove the item
    return true;
}

template<class T, class Allocator, bool FastBaseTwo>
std::uint32_t agora::FixedHashMap<T, Allocator, FastBaseTwo>::probeDist(std::uint32_t bucketIndex) const
{
    // this way it'll always be positive:
    if constexpr(FastBaseTwo)
    {
        return (bucketIndex + m_numBuckets - m_buckets[bucketIndex].m_bucketInfo.m_baseIndex) & (m_numBuckets - 1);
    }
    else
    {
        return (bucketIndex + m_numBuckets - m_buckets[bucketIndex].m_bucketInfo.m_baseIndex) & m_numBuckets;
    }
}

template<class T, class Allocator, bool FastBaseTwo>
std::uint32_t agora::FixedHashMap<T, Allocator, FastBaseTwo>::getIndex(HashInt hash) const
{
    if constexpr(FastBaseTwo)
    {
        return hash & (m_numBuckets - 1);
    }
    else
    {
        return hash % m_numBuckets;
    }
}

template<class T, class Allocator, bool FastBaseTwo>
std::uint32_t agora::FixedHashMap<T, Allocator, FastBaseTwo>::findEmpty(HashInt hash) const
{
    if (m_numBuckets <= m_usedBuckets)
    {
        return m_numBuckets; // can't add more (for the map is full)
    }

    const auto initIndex = getIndex(hash); // get what the index should have been
    Bucket currBucket(hash, initIndex); // let's construct the bucket

    std::uint32_t currProbeDist = 0;
    for (std::size_t i = 0; i < m_numBuckets; i++) // loop through entire hash map 
    {
        std::size_t index;

        if constexpr(FastBaseTwo)
        {
            index = (initIndex + i) & (m_numBuckets - 1); // this is faster
        }
        else
        {
            index = (initIndex + i) % m_numBuckets;
        }

        if (m_buckets[index].m_bucketInfo.m_empty) // if it is empty
        {
            m_buckets[index] = currBucket;
            return index;
        }

        const auto chckProbe = probeDist(index);
        if (chckProbe < currProbeDist) // swap the values
        {
            std::swap(m_buckets[index], currBucket);
            currProbeDist = chckProbe;
        }
        currProbeDist++;
    }

    return m_numBuckets;
}

template<class T, class Allocator, bool FastBaseTwo>
void agora::FixedHashMap<T, Allocator, FastBaseTwo>::cleanMap(std::uint32_t index)
{
    m_buckets[index].m_bucketInfo.m_empty = true;

    for (std::uint32_t i = 1; i < m_numBuckets; i++)
    {
        std::size_t prevIndex, currIndex;
        if constexpr(FastBaseTwo)
        {
            prevIndex = (index + i - 1) & (m_numBuckets - 1);
            currIndex = (index + i) & (m_numBuckets - 1);
        }
        else
        {
            prevIndex = (index + i - 1) % m_numBuckets;
            currIndex = (index + i) % m_numBuckets;
        }

        if (!m_buckets[currIndex].m_bucketInfo.m_empty && probeDist(currIndex) > 0)
        {
            m_buckets[prevIndex] = m_buckets[currIndex];
        }
    }
}

template<class T, class Allocator, bool FastBaseTwo>
std::uint32_t agora::FixedHashMap<T, Allocator, FastBaseTwo>::findIndex(HashInt hash) const
{
    assert(m_buckets != nullptr);

    const auto initIndex = getIndex(hash);
    std::uint32_t probe = 0;

    for (std::uint32_t i = 0; i < m_numBuckets; i++)
    {
        std::uint32_t index;
        if constexpr(FastBaseTwo)
        {
            index = (initIndex + i) & (m_numBuckets - 1);
        }
        else
        {
            index = (initIndex + i) % m_numBuckets;
        }

        if (m_buckets[index].m_hash == hash)
        {
            return index;
        }

        probe = probeDist(index);
        if (m_buckets[index].m_bucketInfo.m_empty || i > probe)
        {
            return m_numBuckets;
        }
    }

    return m_numBuckets;
}