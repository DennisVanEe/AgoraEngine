#include "model_index_table.hpp"

size_t agora::ModelIndexTable::prepareToWriteBuffer()
{
    if (m_maxArrSizeNeeded == 0)
    {
        size_t i;
        for (i = m_numBuckets - 1; i >= 0; i--)
        {
            if (m_buckets[i].baseIndex >= 0)
            {
                break;
            }
        }

        m_maxArrSizeNeeded = i + 1;
    }

    size_t dataSize = m_maxArrSizeNeeded * (3 * TABLE_PROP_INT_SIZE);

    return 3 * TABLE_PROP_INT_SIZE + dataSize;
}

void agora::ModelIndexTable::resetToWriteBuffer()
{
    m_maxArrSizeNeeded = 0;
}

bool agora::ModelIndexTable::writeToBuffer(uByte* o_buffer, size_t max_write)
{
    size_t dataArrSize = prepareToWriteBuffer();
    if (dataArrSize > max_write) { return false; }

    std::memcpy(o_buffer,                           &m_numBuckets,  TABLE_PROP_INT_SIZE);
    std::memcpy(o_buffer +     TABLE_PROP_INT_SIZE, &m_usedBuckets, TABLE_PROP_INT_SIZE);
    std::memcpy(o_buffer + 2 * TABLE_PROP_INT_SIZE, &m_mask,        TABLE_PROP_INT_SIZE);
    std::memcpy(o_buffer + 3 * TABLE_PROP_INT_SIZE, m_buckets,      dataArrSize);

    return true;
}

agora::ModelIndexTable::ModelIndexTable() :
    m_buckets(nullptr),
    m_numBuckets(0),
    m_usedBuckets(0),
    m_mask(0),
    m_maxArrSizeNeeded(0)
{
}

agora::ModelIndexTable::~ModelIndexTable()
{
    delete[] m_buckets;
}

bool agora::ModelIndexTable::initialize(int num_buckets)
{
    if (num_buckets <= 0) { return false; }

    m_numBuckets = LG_POW2(num_buckets);
    m_mask = m_numBuckets - 1;

    m_buckets = new Bucket[m_numBuckets];

    return true;
}

bool agora::ModelIndexTable::get(HashInt hash, uint32_t* o_item) const
{
    if (m_buckets == nullptr) { return false; }

    int index = findIndex(hash);

    if (index >= 0)
    {
        *o_item = m_buckets[index].offset;
        return true;
    }

    return false;
}

bool agora::ModelIndexTable::insert(HashInt hash, uint32_t data)
{
    if (m_buckets == nullptr) { return false; }

    if (m_numBuckets == m_usedBuckets) { return false; }

    m_usedBuckets++;

    int initIndex = getIndex(hash);
    Bucket currBucket(hash, initIndex, data);
    int currProbeDist = 0;

    for (int i = 0; i < m_numBuckets; i++)
    {
        int index = (initIndex + i) & m_mask;

        if (m_buckets[index].baseIndex < 0) // if it is empty
        {
            m_buckets[index] = currBucket;
            return true;
        }

        int chckProbe = probeDist(index);
        if (chckProbe > currProbeDist) // swap the values
        {
            Bucket temp = m_buckets[index];
            m_buckets[index] = currBucket;
            currBucket = temp;
            currProbeDist = chckProbe;
        }
        currProbeDist++;
    }

    return false;
}