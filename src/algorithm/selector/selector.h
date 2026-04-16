#pragma once

#include <individual/individual.h>
#include <util/rng.h>

#include <functional>

namespace Selector
{
    template <typename Strategy>
    std::vector<Individual> select(std::vector<Individual> population)
    {
        return Strategy::apply(std::move(population));
    }

    struct Tournament 
    {
        static std::vector<Individual> apply(std::vector<Individual> population) 
        {
            std::vector<Individual> result;
            result.reserve(population.size() / 2);

            auto& gen = Rng::get();

            std::shuffle(population.begin(), population.end(), gen);

            for (size_t i = 0; i + 1 < population.size(); i += 2)
            {
                result.push_back(population[i] < population[i + 1] ? population[i + 1] : population[i]);
            }

            return result;
        }
    };

    struct Elitism 
    {
        static std::vector<Individual> apply(std::vector<Individual> population) 
        {
            std::nth_element(population.begin(), population.begin() + (population.size() / 2), population.end(), std::greater<>());
            return std::vector<Individual>(population.begin(), population.begin() + (population.size() / 2));
        }
    };

    struct Shuffle 
    {
        static std::vector<Individual> apply(std::vector<Individual> population) 
        {
            auto& gen = Rng::get();

            std::shuffle(population.begin(), population.end(), gen);
            return std::vector<Individual>(population.begin(), population.begin() + (population.size() / 2));
        }
    };
}
