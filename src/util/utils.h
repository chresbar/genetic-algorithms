#pragma once

#include <cstdint>

std::size_t genHash(unsigned a, unsigned b)
{
    return (static_cast<uint64_t>(a) << 32) | b;
}