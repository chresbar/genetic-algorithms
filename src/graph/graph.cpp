#include "graph.h"
#include <json/json.h>
#include <fstream>
#include <iostream>

std::unique_ptr<Graph> Graph::gen(const std::string& filepath)
{
    auto graph = std::make_unique<Graph>();
    if (!graph->load(filepath))
        return nullptr;
    return graph;
}

bool Graph::load(const std::string& filepath)
{
    std::ifstream file(filepath, std::ifstream::binary);

    if (!file.is_open())
    {
        std::cout << "Failed to open file: " << filepath << std::endl;
        return false;
    }

    Json::Value root;
    file >> root;

    const Json::Value& edgesJson = root["edges"];
    if (!edgesJson.isArray())
    {
        std::cout << "Expected 'edges' array in JSON file" << std::endl;
        return false;
    }

    clear_();

    for (const auto& edge : edgesJson)
    {
        addEdge({
            edge["begin"].asUInt(),
            edge["end"].asUInt(),
            edge["weight"].asUInt(),
            edge["directed"].asBool()
        });
    }

    return true;
}

unsigned Graph::addEdge(const Edge& edge)
{
    if (!edge.directed)
        vertices_[edge.end].insert(edge.begin);

    vertices_[edge.begin].insert(edge.end);
    edges_.emplace(edgeCounter_, edge);
    return edgeCounter_++;
}

void Graph::clear_()
{
    vertices_.clear();
    edges_.clear();
    edgeCounter_ = 0;
}
