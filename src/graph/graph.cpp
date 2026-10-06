#include "graph.h"
#include <util/logger.h>
#include <util/utils.h>
#include <json/json.h>
#include <fstream>
#include <queue>
#include <stdexcept>

std::unique_ptr<Graph> Graph::gen(const std::string& filepath)
{
    auto graph = std::make_unique<Graph>();

    try
    {
        graph->load(filepath);
    }
    catch(const std::exception& e)
    {
        throw;
    }
        
    return graph;
}

void Graph::load(const std::string& filepath)
{
    std::ifstream file(filepath, std::ifstream::binary);

    if (!file.is_open())
        throw std::runtime_error("Faild to open file: " + filepath);

    Json::Value root;
    file >> root;

    const Json::Value& edgesJson = root["edges"];
    if (!edgesJson.isArray())
        throw std::runtime_error("Expected 'edges' array in JSON file.");

    clear_();

    for (const auto& edge : edgesJson)
    {
        addEdge(
            edge["begin"].asUInt(),
            edge["end"].asUInt(),
            edge["weight"].asUInt(),
            edge["directed"].asBool()
        );
    }

    try
    {
        findAllPaths_();
    }
    catch(const std::exception& e)
    {
        LOG_ERROR(e.what());
    }
}

void Graph::addEdge(unsigned begin, unsigned end, unsigned weight, bool isDirected)
{
    if (!isDirected)
        vertices_[end][begin] = weight;

    vertices_[begin][end] = weight;
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

std::optional<unsigned> Graph::getPathLength(unsigned v1, unsigned v2) const
{
    if (vertices_.find(v1) == vertices_.end() || vertices_.find(v2) == vertices_.end())
        return std::nullopt;

    auto pathID = genHash(v1, v2);
    if (paths_.find(pathID) != paths_.end())
        return paths_.at(pathID);
    return std::nullopt;
}

void Graph::clear_()
{
    vertices_.clear();
    paths_.clear();
}

std::optional<unsigned> Graph::calculatePathLength_(unsigned begin, unsigned end) const
{
    if (vertices_.find(begin) == vertices_.end() || vertices_.find(end) == vertices_.end())
        return std::nullopt;

    std::vector<unsigned> dist(vertices_.size(), UINT32_MAX);
    dist[begin] = 0;

    std::priority_queue<std::pair<unsigned, unsigned>, std::vector<std::pair<unsigned, unsigned>>, std::greater<std::pair<unsigned, unsigned>>> pq;
    pq.emplace(0, begin);

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        if (u == end)
            return d;

        if (d > dist[u])
            continue;

        for (const auto& [v, w]: vertices_.at(u))
        {
            if (d + w < dist[v])
            {
                dist[v] = d + w;
                pq.emplace(dist[v], v);
            }
        }
    }

    return std::nullopt;
}

void Graph::findAllPaths_()
{
    if (vertices_.empty())
        throw std::runtime_error("There are no vertices");

    for (const auto& [begin, _] : vertices_)
    {
        for (const auto& [end, _] : vertices_)
        {
            if (auto length = calculatePathLength_(begin, end))
            {
                auto pathID = genHash(begin, end);
                paths_[pathID] = length.value();
            }
        }
    }
}
