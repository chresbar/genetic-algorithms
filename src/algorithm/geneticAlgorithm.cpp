#include "geneticAlgorithm.h"

#include <selector/selector.h>
#include <algorithm>
#include <util/logger.h>
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
