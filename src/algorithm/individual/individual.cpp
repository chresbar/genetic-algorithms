#include "individual.h"

Individual::Individual(const std::vector<unsigned>& g, unsigned s): genom(g), score(s) {}

bool Individual::operator<(const Individual& individual) const
{
    return this->score < individual.score;
}

bool Individual::operator>(const Individual& individual) const
{
    return this->score > individual.score;
}
