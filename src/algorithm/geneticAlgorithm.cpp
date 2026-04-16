#include "geneticAlgorithm.h"

#include <selector/selector.h>
#include <algorithm>

void GeneticAlgorithm::loadGraph(const std::string& filepath)
{
    graph_ = Graph::gen(filepath);
}

bool GeneticAlgorithm::populate()
{
    if (!graph_)
        return false;

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

    return true;
}

void GeneticAlgorithm::setSize(unsigned size)
{
    size_ = size;
}   

unsigned GeneticAlgorithm::calculateScore_(const std::vector<unsigned>& genom) const
{
    unsigned score = 0;

    if (genom.size() < 2u || !graph_)
        return score;

    for (size_t i = 0; i < genom.size() - 1; ++i)
    {
        if(auto weight = graph_->getPathLength(genom[i], genom[i + 1]))
            score += weight.value();
    }

    return score;
}
