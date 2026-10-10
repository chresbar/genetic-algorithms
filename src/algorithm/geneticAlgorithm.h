#pragma once

#include <algorithm/individual/individual.h>
#include <graph/graph.h>
#include <algorithm/selector/selector.h>

using Population = std::vector<Individual>;

class GeneticAlgorithm
{
private:
    std::unique_ptr<Graph> graph_;
    Population population_;

    Selector::Select strategy_;
    
    unsigned size_; // population size

    unsigned calculateScore_(const std::vector<unsigned>& genom) const;
    Population selectFittest_();
    Population genNewPopuation_(Population& population);
    std::pair<Individual, Individual> cross_(Individual childA, Individual childB);

public:
    
    void loadGraph(const std::string& filepath);
    void populate();
    void run();

    void setBegin(unsigned begin);
    void setSize(unsigned size);
    void setSelectStrategy(Selector::Select strategy);
};
