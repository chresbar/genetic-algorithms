#include <catch2/catch_all.hpp>
#include "graph.h"

// Negative Test Cases

TEST_CASE("Graph_Load_Wrong_File_Path") 
{
    Graph graph;

    auto result = graph.load("incorrect_filepath.json");
    REQUIRE_FALSE(result);
}

TEST_CASE("Graph_Gen_Wrong_File_Path") 
{
    auto graph = Graph::gen("incorrect_filepath.json");
    REQUIRE_FALSE(graph);
}

// Positive Test Cases

TEST_CASE("Graph_Add_Edge") 
{
    Graph graph;

    auto result = graph.addEdge({0, 1, 0, false});
    REQUIRE(result == 0);
}

