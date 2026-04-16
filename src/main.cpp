#include <config.h>
#include <algorithm/geneticAlgorithm.h>
#include <util/logger.h>

int main()
{
    GeneticAlgorithm algorithm;
    algorithm.loadGraph(std::string(RES_DIR) + "city.json");
    algorithm.setSize(100);
    algorithm.populate();
    LOG_INFO("Test");
    return 0;
}