#pragma once

#include <cstdint>
#include <util/rng.h>

std::size_t genHash(unsigned a, unsigned b)
{
    return (static_cast<uint64_t>(a) << 32) | b;
}

std::pair<size_t, size_t> genRange(size_t ceiling, size_t floor)
{
    if (ceiling - 1 < floor)
        throw std::runtime_error("Ceiling value needs to be larger then floor");

    auto& gen = Rng::get();
    std::uniform_int_distribution<size_t> dist(floor, ceiling - 1);

    size_t begin = dist(gen);
    dist.param(std::uniform_int_distribution<size_t>::param_type(begin + 1, ceiling));

    size_t end = dist(gen);

    return {begin, end};
}