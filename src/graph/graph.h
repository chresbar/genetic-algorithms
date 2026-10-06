#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <optional>

class Graph
{
private:
    std::unordered_map<unsigned, std::unordered_map<unsigned, unsigned>> vertices_;
    std::unordered_map<size_t, unsigned> paths_;

    void clear_();

    std::optional<unsigned> calculatePathLength_(unsigned begin, unsigned end) const;
    void findAllPaths_();

public:
    static std::unique_ptr<Graph> gen(const std::string& filepath);

    void load(const std::string& filepath);

    void addEdge(unsigned begin, unsigned end, unsigned weight, bool isDirected);

    bool containsVertex(unsigned vertex);

    size_t vertexCount() const;

    std::optional<unsigned> getPathLength(unsigned v1, unsigned v2) const;
};
