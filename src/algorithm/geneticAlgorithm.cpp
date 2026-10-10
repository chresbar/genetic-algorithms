#include "geneticAlgorithm.h"

#include <algorithm>
#include <utility>
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

Population GeneticAlgorithm::selectFittest_()
{
    if (!strategy_)
        throw std::runtime_error("Selection strategy has not been set");

    return strategy_(std::move(population_));
}

Population GeneticAlgorithm::genNewPopuation_(Population& population)
{
    if (population.empty())
        throw std::runtime_error("Empty population vector");

    auto& gen = Rng::get();
    Population children;
    children.reserve(population.size() * 2);

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

std::pair<Individual, Individual> GeneticAlgorithm::cross_(Individual childA, Individual childB)
{
    try
    {
        auto [begin, end] = genRange(childA.size() - 1);
        GenomMap mapA;
        GenomMap mapB;

        for (auto i = begin; i <= end; ++i)
        {
            mapA[childB[i]] = childA[i];
            mapB[childA[i]] = childB[i];
            std::swap(childA[i], childB[i]);
        }

        childA.mapGenom(0, begin, mapA);
        childA.mapGenom(end + 1, childA.size(), mapA);

        childB.mapGenom(0, begin, mapB);
        childB.mapGenom(end + 1, childB.size(), mapB);

        childA.setScore(calculateScore_(childA.getGenom()));
        childB.setScore(calculateScore_(childB.getGenom()));
    }
    catch(const std::exception& e)
    {
        throw;
    }

    return {childA, childB};
}

void GeneticAlgorithm::run()
{
    try
    {
        auto population = selectFittest_();
        population_ = genNewPopuation_(population);
    }
    catch(const std::exception& e)
    {
        throw;
    }
}
