#pragma once

#include <random>

class Rng
{
public:
    static std::mt19937& get() {
        static std::mt19937 gen(std::random_device{}());
        return gen;
    }
};
