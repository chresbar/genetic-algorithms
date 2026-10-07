#include <catch2/catch_all.hpp>
#include <algorithm/geneticAlgorithm.h>

// Negative Test Cases

TEST_CASE("Genetic_Algorithm_Load_Graph_With_Wrong_File_Path") 
{
    GeneticAlgorithm algorithm;
    REQUIRE_THROWS(algorithm.loadGraph("incorrect_filepath.json"));
}

TEST_CASE("Genetic_Algorithm_Populate_Without_Graph") 
{
    GeneticAlgorithm algorithm;
    REQUIRE_THROWS(algorithm.populate());
}

// Positive Test Cases
