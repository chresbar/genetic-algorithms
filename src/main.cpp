#include <config.h>
#include <algorithm/geneticAlgorithm.h>
#include <util/logger.h>

int main()
{
    try
    {
        GeneticAlgorithm algorithm;
        algorithm.loadGraph(std::string(RES_DIR) + "city.json");
        algorithm.setSize(100);
        algorithm.setIterationCount(1000);
        algorithm.setMutationRate(0.1);
        algorithm.setSelectStrategy(Selector::Elitism::apply);
        algorithm.run();
        LOG_INFO("Best score: ", algorithm.getBestScore());
    }
    catch(const std::exception& e)
    {
        LOG_ERROR(e.what());
    }
    
    return 0;
}