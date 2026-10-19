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

    double mutationRate_ = 0;

    Population selectFittest_();
    Population genNextPopuation_(Population& population);
    std::pair<Individual, Individual> cross_(Individual childA, Individual childB);

public:
    
    void loadGraph(const std::string& filepath);
    void genInitialPopulation();
    void run();

    void setBegin(unsigned begin);
    void setSize(unsigned size);
    void setMutationRate(double rate);
    void setSelectStrategy(Selector::Select strategy);
};
