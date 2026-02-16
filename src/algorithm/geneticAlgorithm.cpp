#include "geneticAlgorithm.h"
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

    std::random_device rd;
    gen = std::mt19937(rd());

    population_.clear();
    population_.reserve(size_);
    for (unsigned i = 0; i < size_; ++i)
    {
        std::shuffle(individual.begin(), individual.end(), gen);
        population_.push_back(individual);
    }

    return true;
}

void GeneticAlgorithm::setSize(unsigned size)
{
    size_ = size;
}   
