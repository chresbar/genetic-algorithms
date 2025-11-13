#pragma once

#include <unordered_map>
#include <unordered_set>

struct Edge
{
    unsigned mBegin;
    unsigned mEnd;
    unsigned mWeight;
    bool mDirected;
};

class Graph
{
private:
    std::unordered_map<unsigned, Edge> mEdges;
    std::unordered_map<unsigned, std::unordered_set<unsigned>> mVertices;   

    unsigned mEdgeCounter = 0;

public:
    unsigned addEdge(const Edge& edge);
};
