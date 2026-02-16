#pragma once

#include <vector>
#include <random>

#include "graph.h"

class GeneticAlgorithm
{
private:
    std::unique_ptr<Graph> graph_;
    std::vector<std::vector<unsigned>> population_;

    std::mt19937 gen;
    
    unsigned size_; // population size

public:
    
    void loadGraph(const std::string& filepath);
    bool populate();

    void setBegin(unsigned begin);
    void setSize(unsigned size);
};
