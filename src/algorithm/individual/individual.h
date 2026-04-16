#pragma once

#include <vector>

class Individual
{
private:
    std::vector<unsigned> genom;
    unsigned score;

public:
    Individual(const std::vector<unsigned>& g, unsigned s);
    
    bool operator<(const Individual& individual) const;
    bool operator>(const Individual& individual) const;
};
