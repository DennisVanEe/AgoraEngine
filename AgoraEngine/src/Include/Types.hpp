#pragma once

namespace agora
{
    enum class aByte : unsigned char {};

    // Used by FileIO when writing data to and from.
    const std::size_t UINT32_SIZE = 4;
    const std::size_t UINT64_SIZE = 8;
}