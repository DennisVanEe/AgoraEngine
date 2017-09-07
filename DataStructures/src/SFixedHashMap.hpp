#pragma once

#include <cmath>
#include <cassert>

#include <Utility.hpp>
#include "Hash.hpp"

namespace agora
{
    template<class T, std::uint32_t NumBuckets, bool FastBaseTwo = true>
    class SFixedHashMap
    {
        static_assert(FastBaseTwo ? ((isPow2(NumBuckets) ? true : false)) : true, "NumBuckets not a power of 2");
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
        SFixedHashMap();

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
        Bucket m_buckets[NumBuckets];
        std::uint32_t m_usedBuckets;
    };
}


template<class T, std::uint32_t NumBuckets, bool FastBaseTwo>
agora::SFixedHashMap<T, NumBuckets, FastBaseTwo>::SFixedHashMap() :
    m_usedBuckets(0) {}

template<class T, std::uint32_t NumBuckets, bool FastBaseTwo>
T* agora::SFixedHashMap<T, NumBuckets, FastBaseTwo>::insert(HashInt hash, T data)
{
    const auto index = findEmpty(hash);
    if (index == NumBuckets)
    {
        return nullptr;
    }
    m_buckets[index].m_data = data; // explicit move construction if the user wants it
    m_buckets[index].m_bucketInfo.m_empty = false;
    m_usedBuckets++;
    return &m_buckets[index].m_data;
}

template<class T, std::uint32_t NumBuckets, bool FastBaseTwo>
T* agora::SFixedHashMap<T, NumBuckets, FastBaseTwo>::at(HashInt hash)
{
    const auto index = findIndex(hash);
    if (index == NumBuckets)
    {
        return nullptr;
    }
    return &m_buckets[index].m_data;
}

template<class T, std::uint32_t NumBuckets, bool FastBaseTwo>
const T* agora::SFixedHashMap<T, NumBuckets, FastBaseTwo>::at(HashInt hash) const
{
    return at(hash);
}

template<class T, std::uint32_t NumBuckets, bool FastBaseTwo>
bool agora::SFixedHashMap<T, NumBuckets, FastBaseTwo>::remove(HashInt hash, T& data)
{
    const auto index = findIndex(hash);
    if (index == NumBuckets)
    {
        return false;
        data = std::move(m_buckets[index].m_data); // assign data
    }
    cleanMap(index); // remove the item
    m_usedBuckets--;
    return true;
}

template<class T, std::uint32_t NumBuckets, bool FastBaseTwo>
bool agora::SFixedHashMap<T, NumBuckets, FastBaseTwo>::remove(HashInt hash)
{
    const auto index = findIndex(hash);
    if (index == NumBuckets)
    {
        return false;
    }
    cleanMap(index); // remove the item
    m_usedBuckets--;
    return true;
}

template<class T, std::uint32_t NumBuckets, bool FastBaseTwo>
std::uint32_t agora::SFixedHashMap<T, NumBuckets, FastBaseTwo>::probeDist(std::uint32_t bucketIndex) const
{
    // this way it'll always be positive:
    if constexpr(FastBaseTwo)
    {
        return (bucketIndex + NumBuckets - m_buckets[bucketIndex].m_bucketInfo.m_baseIndex) & (NumBuckets - 1);
    }
    else
    {
        return (bucketIndex + NumBuckets - m_buckets[bucketIndex].m_bucketInfo.m_baseIndex) & NumBuckets;
    }
}

template<class T, std::uint32_t NumBuckets, bool FastBaseTwo>
std::uint32_t agora::SFixedHashMap<T, NumBuckets, FastBaseTwo>::getIndex(HashInt hash) const
{
    if constexpr(FastBaseTwo)
    {
        return hash & (NumBuckets - 1);
    }
    else
    {
        return hash % NumBuckets;
    }
}

template<class T, std::uint32_t NumBuckets, bool FastBaseTwo>
std::uint32_t agora::SFixedHashMap<T, NumBuckets, FastBaseTwo>::findEmpty(HashInt hash) const
{
    if (NumBuckets <= m_usedBuckets)
    {
        return NumBuckets; // can't add more (for the map is full)
    }

    const auto initIndex = getIndex(hash); // get what the index should have been
    Bucket currBucket(hash, initIndex); // let's construct the bucket

    std::uint32_t currProbeDist = 0;
    for (std::size_t i = 0; i < NumBuckets; i++) // loop through entire hash map 
    {
        std::size_t index;

        if constexpr(FastBaseTwo)
        {
            index = (initIndex + i) & (NumBuckets - 1); // this is faster
        }
        else
        {
            index = (initIndex + i) % NumBuckets;
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

    return NumBuckets;
}

template<class T, std::uint32_t NumBuckets, bool FastBaseTwo>
void agora::SFixedHashMap<T, NumBuckets, FastBaseTwo>::cleanMap(std::uint32_t index)
{
    m_buckets[index].m_bucketInfo.m_empty = true;

    for (std::uint32_t i = 1; i < NumBuckets; i++)
    {
        std::size_t prevIndex, currIndex;
        if constexpr(FastBaseTwo)
        {
            prevIndex = (index + i - 1) & (NumBuckets - 1);
            currIndex = (index + i) & (NumBuckets - 1);
        }
        else
        {
            prevIndex = (index + i - 1) % NumBuckets;
            currIndex = (index + i) % NumBuckets;
        }

        if (!m_buckets[currIndex].m_bucketInfo.m_empty && probeDist(currIndex) > 0)
        {
            m_buckets[prevIndex] = m_buckets[currIndex];
        }
    }
}

template<class T, std::uint32_t NumBuckets, bool FastBaseTwo>
std::uint32_t agora::SFixedHashMap<T, NumBuckets, FastBaseTwo>::findIndex(HashInt hash) const
{
    assert(m_buckets != nullptr);

    const auto initIndex = getIndex(hash);
    std::uint32_t probe = 0;

    for (std::uint32_t i = 0; i < NumBuckets; i++)
    {
        std::uint32_t index;
        if constexpr(FastBaseTwo)
        {
            index = (initIndex + i) & (NumBuckets - 1);
        }
        else
        {
            index = (initIndex + i) % NumBuckets;
        }

        if (m_buckets[index].m_hash == hash)
        {
            return index;
        }

        probe = probeDist(index);
        if (m_buckets[index].m_bucketInfo.m_empty || i > probe)
        {
            return NumBuckets;
        }
    }

    return NumBuckets;
}