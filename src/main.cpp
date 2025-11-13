#include "config.h"
#include "graph.h"

int main()
{
    auto graph = Graph::gen(std::string(RES_DIR) + "small_graph.json");
    return 0;
}