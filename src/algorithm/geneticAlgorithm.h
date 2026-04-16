#pragma once

#include <algorithm/individual/individual.h>
#include <graph/graph.h>

class GeneticAlgorithm
{
private:
    std::unique_ptr<Graph> graph_;
    std::vector<Individual> population_;
    
    unsigned size_; // population size

    unsigned calculateScore_(const std::vector<unsigned>& genom) const;
    // std::vector<Individual> genNextPopulation_();

public:
    
    void loadGraph(const std::string& filepath);
    bool populate();

    void setBegin(unsigned begin);
    void setSize(unsigned size);
};
