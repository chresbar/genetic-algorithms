#pragma once

#include <algorithm/individual/individual.h>
#include <graph/graph.h>
#include <algorithm/selector/selector.h>

class GeneticAlgorithm
{
private:
    std::unique_ptr<Graph> graph_;
    std::vector<Individual> population_;

    Selector::Select strategy_;
    
    unsigned size_; // population size

    unsigned calculateScore_(const std::vector<unsigned>& genom) const;
    std::vector<Individual> selectFittest_();

public:
    
    void loadGraph(const std::string& filepath);
    void populate();

    void setBegin(unsigned begin);
    void setSize(unsigned size);
    void setSelectStrategy(Selector::Select strategy);
};
