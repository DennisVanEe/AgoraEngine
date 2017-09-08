#pragma once

#include <cstdint>

namespace agora
{
    inline bool isPow2(unsigned long num);
    inline std::uint32_t lgPow2(std::uint32_t num);
    inline std::uint64_t lgPow2(std::uint64_t num);

    inline std::uint32_t loadUINT32(aByte* buffer);
    inline std::uint64_t loadUINT64(aByte* buffer);

    inline void storeUINT32(aByte* buffer, std::uint32_t num);
    inline void storeUINT64(aByte* buffer, std::uint64_t num);
}

inline bool agora::isPow2(unsigned long num)
{
    return (num != 0) && ((num & (num - 1)) == 0);
}

inline std::uint32_t agora::lgPow2(std::uint32_t num)
{
    num--;
    num |= num >> 1;
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;
    num++;
    return num;
}

inline std::uint64_t agora::lgPow2(std::uint64_t num)
{
    num--;
    num |= num >> 1;
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;
    num |= num >> 32;
    num++;
    return num;
}

std::uint32_t agora::loadUINT32(aByte* buffer)
{
    return *reinterpret_cast<std::uint32_t*>(buffer);
}

std::uint64_t agora::loadUINT64(aByte* buffer)
{
    return *reinterpret_cast<std::uint64_t*>(buffer);
}

void agora::storeUINT32(aByte* buffer, std::uint32_t num)
{
    aByte* numPtr = reinterpret_cast<aByte*>(&num);
    for (int i = 0; i < 4; i++) // this should get unrolled
        buffer[i] = numPtr[i];
}

void agora::storeUINT64(aByte* buffer, std::uint64_t num)
{
    aByte* numPtr = reinterpret_cast<aByte*>(&num);
    for (int i = 0; i < 8; i++) // this should get unrolled
        buffer[i] = numPtr[i];
}