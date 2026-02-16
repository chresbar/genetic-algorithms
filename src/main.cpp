#include "config.h"
#include "geneticAlgorithm.h"
#include "logger.h"

int main()
{
    GeneticAlgorithm algorithm;
    algorithm.loadGraph(std::string(RES_DIR) + "small_graph.json");
    algorithm.setSize(10);
    algorithm.populate();
    LOG_INFO("Test");
    return 0;
}