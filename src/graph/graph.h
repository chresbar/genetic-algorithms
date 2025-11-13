#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>

struct Edge
{
    unsigned begin;
    unsigned end;
    unsigned weight;
    bool directed;
};

class Graph
{
private:
    std::unordered_map<unsigned, Edge> edges_;
    std::unordered_map<unsigned, std::unordered_set<unsigned>> vertices_;   

    unsigned edgeCounter_ = 0;

    void clear_();

public:
    static std::unique_ptr<Graph> gen(const std::string& filepath);

    bool load(const std::string& filepath);

    unsigned addEdge(const Edge& edge);
};
