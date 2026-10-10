#pragma once

#include <vector>
#include <unordered_map>

using Genom = std::vector<unsigned>;
using GenomMap = std::unordered_map<unsigned, unsigned>;

class Individual
{
private:
    Genom genom;
    unsigned score;

public:
    Individual(const Genom& g, unsigned s);
    
    bool operator<(const Individual& individual) const;
    bool operator>(const Individual& individual) const;
    unsigned& operator[](size_t index);

    size_t size() const;
    void mapGenom(size_t begin, size_t end, const GenomMap& genomMap);

    Genom& getGenom();
    void setScore(unsigned score);

};
