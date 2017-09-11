#pragma once

#include <cmath>
#include <cstdint>

#include "hashcrc32.hpp"
#include "number_ops.hpp"

namespace agora
{
    class ModelIndexTable
    {
    public:
                ModelIndexTable();
                ~ModelIndexTable();

        bool    initialize(int num_buckets);
        bool    insert(HashInt hash, uint32_t offset);
        bool    get(HashInt hash, uint32_t* o_item) const;

        size_t  prepareToWriteBuffer();
        void    resetToWriteBuffer();
        bool    writeToBuffer(uByte* o_buffer, size_t max_write);

    private:
        struct Bucket
        {
            HashInt    hash;
            int        baseIndex;
            uint32_t   offset;

            Bucket() :
                baseIndex(-1) {}

            Bucket(HashInt h, size_t b, uint32_t d) :
                hash(h),
                baseIndex(b),
                offset(d) {}
        };
        static_assert(sizeof(Bucket) == 3 * sizeof(uint32_t), "There can be no padding in the bucket struct");

    private:
        const size_t    TABLE_PROP_INT_SIZE = 4;

        inline int      probeDist(int bucketIndex) const;
        inline int      getIndex(HashInt hash) const;
        inline int      findIndex(HashInt hash) const;

        Bucket*         m_buckets;
        size_t          m_numBuckets;
        size_t          m_usedBuckets;
        int             m_mask;

        size_t          m_maxArrSizeNeeded;
    };
}

int agora::ModelIndexTable::findIndex(HashInt hash) const
{
    int initIndex = getIndex(hash);
    int probe = 0;

    for (int i = 0; i < m_numBuckets; i++)
    {
        int index = (initIndex + i) & m_mask;

        probe = probeDist(index);
        if (m_buckets[index].baseIndex < 0 || i > probe)
        {
            return -1;
        }

        if (m_buckets[index].hash == hash) // swap the values
        {
            return index;
        }
    }

    return -1;
}

int agora::ModelIndexTable::probeDist(int bucketIndex) const
{
    return std::abs(bucketIndex - m_buckets[bucketIndex].baseIndex);
}

int agora::ModelIndexTable::getIndex(HashInt hash) const
{
    return hash & m_mask;
}