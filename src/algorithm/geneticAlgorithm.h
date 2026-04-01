#pragma once

#include <vector>
#include <random>

#include "graph.h"

struct Individual
{
    std::vector<unsigned> genom;
    unsigned score;

    Individual(const std::vector<unsigned>& g, unsigned s): genom(g), score(s) {}
};

class GeneticAlgorithm
{
private:
    std::unique_ptr<Graph> graph_;
    std::vector<Individual> population_;

    std::mt19937 gen;
    
    unsigned size_; // population size

    unsigned calculateScore_(const std::vector<unsigned>& genom) const;

public:
    
    void loadGraph(const std::string& filepath);
    bool populate();

    void setBegin(unsigned begin);
    void setSize(unsigned size);
};
