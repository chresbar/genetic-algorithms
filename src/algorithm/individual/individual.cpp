#include "individual.h"

#include <stdexcept>

Individual::Individual(const Genom& g, unsigned s): genom(g), score(s) {}

bool Individual::operator<(const Individual& individual) const
{
    return this->score < individual.score;
}

bool Individual::operator>(const Individual& individual) const
{
    return this->score > individual.score;
}

unsigned& Individual::operator[](size_t index)
{
    if (index >= genom.size())
        throw std::out_of_range("Index out of range");

    return genom[index];
}

size_t Individual::size() const
{
    return this->genom.size();
}

void Individual::mapGenom(size_t begin, size_t end, const GenomMap& genomMap)
{
    if (end < begin || genom.size() < begin || genom.size() < end)
        throw std::out_of_range("Genom map out of range");
    
    for (auto i = begin; i < end; ++i)
    {
        if (genomMap.find(genom[i]) != genomMap.end())
            genom[i] = genomMap.at(genom[i]);
    }
}

Genom& Individual::getGenom()
{
    return genom;
}

void Individual::setScore(unsigned score)
{
    this->score = score;
}