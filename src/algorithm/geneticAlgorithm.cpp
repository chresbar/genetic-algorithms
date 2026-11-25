#include "geneticAlgorithm.h"

#include <algorithm>
#include <utility>
#include <util/logger/logger.h>
#include <util/utils.h>
#include <util/jsonUtil.h>
#include <stdexcept>
#include <fstream>

GeneticAlgorithm::GeneticAlgorithm() {}

GeneticAlgorithm::GeneticAlgorithm(const std::string& configPath)
{
    std::ifstream file(configPath, std::ifstream::binary);

    if (!file.is_open())
        throw std::runtime_error("Faild to open file: " + configPath);

    Json::Value root;
    file >> root;

    static const std::unordered_map<std::string, Json::ValueType> configKeys = {
        {ConfigKeys::Graph, Json::ValueType::stringValue},
        {ConfigKeys::Size, Json::ValueType::uintValue},
        {ConfigKeys::Iterations, Json::ValueType::uintValue},
        {ConfigKeys::Mutation, Json::ValueType::realValue},
        {ConfigKeys::Strategy, Json::ValueType::stringValue}
    };

    for (const auto& [key, value] : configKeys)
    {
        if (!isJsonType(root[key], value))
            throw std::runtime_error("Missing '" + key + "' json key or wrong key type.");
    }

    try
    {
        loadGraph(root[ConfigKeys::Graph].asString());
        setSize(root[ConfigKeys::Size].asUInt());
        setIterationCount(root[ConfigKeys::Iterations].asUInt());
        setMutationRate(root[ConfigKeys::Mutation].asDouble());
        setSelectStrategy(root[ConfigKeys::Strategy].asString());
    }
    catch(const std::exception& e)
    {
        throw;
    }    
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

void GeneticAlgorithm::setSelectStrategy(const std::string& strategy)
{
    static const std::unordered_map<std::string, Selector::Select> strategyMap = {
        {"shuffle", Selector::Shuffle::apply},
        {"elitism", Selector::Elitism::apply},
        {"tournament", Selector::Tournament::apply}
    };

    if (strategyMap.find(strategy) == strategyMap.end())
        throw std::runtime_error("Strategy '" + strategy + "' not found.");
    setSelectStrategy(strategyMap.at(strategy));
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
