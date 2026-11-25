#include "geneticAlgorithm.h"

#include <algorithm>
#include <utility>
#include <util/logger.h>
#include <util/utils.h>
#include <stdexcept>
#include <json/json.h>
#include <fstream>

GeneticAlgorithm::GeneticAlgorithm() {}

GeneticAlgorithm::GeneticAlgorithm(const std::string& configPath)
{
    std::ifstream file(configPath, std::ifstream::binary);

    if (!file.is_open())
        throw std::runtime_error("Faild to open file: " + configPath);

    Json::Value root;
    file >> root;

    const Json::Value& graphJson = root["graph"];
    if (!graphJson.isString())
        throw std::runtime_error("Expected 'graph' key in JSON config file.");

    loadGraph(graphJson.asString());

    const Json::Value& sizeJson = root["size"];
    if (!sizeJson.isUInt())
        throw std::runtime_error("Expected 'size' key in JSON config file.");

    setSize(sizeJson.asUInt());

    const Json::Value& iterationsJson = root["iterations"];
    if (!iterationsJson.isUInt())
        throw std::runtime_error("Expected 'iterations' key in JSON config file.");

    setIterationCount(iterationsJson.asUInt());

    const Json::Value& mutationJson = root["mutation"];
    if (!mutationJson.isDouble())
        throw std::runtime_error("Expected 'mutation' key in JSON config file.");

    setMutationRate(mutationJson.asDouble());

    static const std::unordered_map<std::string, Selector::Select> strategyMap = {
        {"shuffle", Selector::Shuffle::apply},
        {"elitism", Selector::Elitism::apply},
        {"tournament", Selector::Tournament::apply}
    };

    const Json::Value& strategyJson = root["strategy"];
    if (!strategyJson.isString())
        throw std::runtime_error("Expected 'strategy' key in JSON config file.");

    if (strategyMap.find(strategyJson.asString()) != strategyMap.end())
        setSelectStrategy(strategyMap.at(strategyJson.asString()));
}

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

void GeneticAlgorithm::genInitialPopulation()
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
        try
        {
            population_.emplace_back(individual, graph_->getPathLength(individual));
        }
        catch(const std::exception& e)
        {
            throw;
        }  
    }
}

void GeneticAlgorithm::setSize(unsigned size)
{
    size_ = size;
}

void GeneticAlgorithm::setIterationCount(unsigned count)
{
    iterationCount_ = count;
}

void GeneticAlgorithm::setMutationRate(double rate)
{
    mutationRate_ = rate;
}

void GeneticAlgorithm::setSelectStrategy(Selector::Select strategy)
{
    strategy_ = std::move(strategy);
}

unsigned GeneticAlgorithm::getBestScore() const
{
    if (bestIndividual_)
        return bestIndividual_.value().getScore();
    throw std::runtime_error("No best individual found yet");
}

Population GeneticAlgorithm::selectFittest_()
{
    if (!strategy_)
        throw std::runtime_error("Selection strategy has not been set");

    return strategy_(std::move(population_));
}

Population GeneticAlgorithm::genNextPopuation_(Population& population)
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

            if (!bestIndividual_)
                bestIndividual_ = std::min(childA, childB);
            else
                bestIndividual_ = std::min(bestIndividual_.value(), std::min(childA, childB));

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

        auto& gen = Rng::get();
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        if (dist(gen) <= mutationRate_)
            childA.mutate();

        if (dist(gen) <= mutationRate_)
            childB.mutate();

        childA.setScore(graph_->getPathLength(childA.getGenom()));
        childB.setScore(graph_->getPathLength(childB.getGenom()));
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
        genInitialPopulation();
        for (unsigned i = 0; i < iterationCount_; ++i)
        {
            auto population = selectFittest_();
            population_ = genNextPopuation_(population);
        }
    }
    catch(const std::exception& e)
    {
        throw;
    }
}
