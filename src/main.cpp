#include <config.h>
#include <algorithm/geneticAlgorithm.h>
#include <util/logger/logger.h>

int main()
{
    try
    {
        GeneticAlgorithm algorithm(std::string(RES_DIR) + "config/shuffle_run.json");
        algorithm.run();
        LOG_INFO("Best score: ", algorithm.getBestScore());
    }
    catch(const std::exception& e)
    {
        LOG_ERROR(e.what());
    }
    
    return 0;
}