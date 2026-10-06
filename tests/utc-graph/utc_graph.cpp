#include <catch2/catch_all.hpp>
#include "graph.h"

// Negative Test Cases

TEST_CASE("Graph_Load_Wrong_File_Path") 
{
    Graph graph;

    REQUIRE_THROWS(graph.load("incorrect_filepath.json"));
}

TEST_CASE("Graph_Gen_Wrong_File_Path") 
{
    REQUIRE_THROWS(Graph::gen("incorrect_filepath.json"));
}

// Positive Test Cases
