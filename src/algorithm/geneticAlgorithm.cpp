#include "geneticAlgorithm.h"

#include <algorithm>
#include <util/logger.h>
#include <util/utils.h>
#include <stdexcept>

void GeneticAlgorithm::loadGraph(const std::string& filepath)
{
    try
    {
        graph_ = Graph::gen(filepath);
    }
    catch(const std::exception& e)
    {
        throw;
    }
}

void GeneticAlgorithm::populate()
{
    if (!graph_)
        throw std::runtime_error("Graph is not initialized");
        
    unsigned vertexCount = graph_->vertexCount();

    std::vector<unsigned> individual(vertexCount);
    std::iota(individual.begin(), individual.end(), 0);

    auto& gen = Rng::get();

    population_.clear();
    population_.reserve(size_);
    for (unsigned i = 0; i < size_; ++i)
    {
        std::shuffle(individual.begin(), individual.end(), gen);
        auto score = calculateScore_(individual);
        population_.emplace_back(individual, score);
    }
}

void GeneticAlgorithm::setSize(unsigned size)
{
    size_ = size;
}

void GeneticAlgorithm::setSelectStrategy(Selector::Select strategy)
{
    strategy_ = std::move(strategy);
}

unsigned GeneticAlgorithm::calculateScore_(const std::vector<unsigned>& genom) const
{
    unsigned score = 0;

    if (!graph_)
        throw std::runtime_error("Graph is not initialized");

    if (genom.size() < 2u || !graph_)
        return score;

    for (size_t i = 0; i < genom.size() - 1; ++i)
    {
        if(auto weight = graph_->getPathLength(genom[i], genom[i + 1]))
            score += weight.value();
    }

    return score;
}

std::vector<Individual> GeneticAlgorithm::selectFittest_()
{
    if (!strategy_)
        throw std::runtime_error("Selection strategy has not been set");

    return strategy_(std::move(population_));
}

std::vector<Individual> GeneticAlgorithm::genNewPopuation_(std::vector<Individual> population)
{
    if (population.empty())
        throw std::runtime_error("Empty population vector");

    auto& gen = Rng::get();
    std::vector<Individual> children(population.size() * 2);

    for (size_t round = 0; round < 2; ++round)
    {
        std::shuffle(population.begin(), population.end(), gen);

        for (size_t i = 0; i < population.size(); i += 2)
        {
            auto [childA, childB] = cross_(population[i], population[i + 1]);

            children.push_back(std::move(childA));
            children.push_back(std::move(childB));
        }
    }

    return children;
}

std::pair<Individual, Individual> GeneticAlgorithm::cross_(Individual parentA, Individual parentB)
{
    try
    {
        auto [begin, end] = genRange(0, parentA.size() - 1);
    }
    catch(const std::exception& e)
    {
        throw;
    }
    
    return {Individual({}, -1), Individual({}, -1)};
}
