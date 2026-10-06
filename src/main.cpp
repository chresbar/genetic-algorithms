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
        algorithm.populate();
    }
    catch(const std::exception& e)
    {
        LOG_ERROR(e.what());
    }
    
    LOG_INFO("Main");
    return 0;
}