#include "graph.h"
#include "logger.h"
#include <json/json.h>
#include <fstream>

void Graph::clear_()
{
    vertices_.clear();
    edges_.clear();
    edgeCounter_ = 0;
}

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
        LOG_ERROR("Failed to open file: ", filepath);
        return false;
    }

    Json::Value root;
    file >> root;

    const Json::Value& edgesJson = root["edges"];
    if (!edgesJson.isArray())
    {
        LOG_ERROR("Expected 'edges' array in JSON file.");
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

bool Graph::containsVertex(unsigned vertex)
{
    if (vertices_.find(vertex) != vertices_.end())
        return true;
    return false;
}

size_t Graph::vertexCount() const
{
    return vertices_.size();
}
