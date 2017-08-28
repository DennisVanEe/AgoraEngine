#pragma once

#include <cstdint>

namespace agora
{
    inline bool isPow2(unsigned long num);
    inline std::uint32_t lgPow2(std::uint32_t num);
    inline std::uint64_t lgPow2(std::uint64_t num);
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