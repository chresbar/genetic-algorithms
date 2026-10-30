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
        algorithm.setSelectStrategy(Selector::Shuffle::apply);
        algorithm.run();
    }
    catch(const std::exception& e)
    {
        LOG_ERROR(e.what());
    }
    
    LOG_INFO("Main");
    return 0;
}