#include <catch2/catch_all.hpp>
#include "graph.h"

TEST_CASE("Graph_Add_Edge") 
{
    Graph graph;

    auto result = graph.addEdge({0, 1, 0, false});
    REQUIRE(result == 0);
}