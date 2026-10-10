#include <catch2/catch_all.hpp>
#include "util/utils.h"

// Negative Test Cases

TEST_CASE("Utils_Get_Range_Floor_Larger_Then_Celling") 
{
    REQUIRE_THROWS(genRange(1, 2));
}

// Positive Test Cases
