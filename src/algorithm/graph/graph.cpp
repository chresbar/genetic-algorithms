#include "graph.h"
#include <util/logger/logger.h>
#include <util/utils.h>
#include <util/jsonUtil.h>
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

    if (!isJsonType(root[GraphKeys::Edges], Json::ValueType::arrayValue))
        throw std::runtime_error("Expected 'edges' array in JSON file.");

    clear_();

    static const std::unordered_map<std::string, Json::ValueType> graphKeys = {
        {GraphKeys::Begin, Json::ValueType::uintValue},
        {GraphKeys::End, Json::ValueType::uintValue},
        {GraphKeys::Weight, Json::ValueType::uintValue},
        {GraphKeys::Directed, Json::ValueType::booleanValue}
    };

    for (const auto& edge : root[GraphKeys::Edges])
    {
        for (const auto& [key, value] : graphKeys)
        {
            if (!isJsonType(edge[key], value))
                throw std::runtime_error("Missing '" + key + "' json key or wrong value type.");
        }

        addEdge(
            edge[GraphKeys::Begin].asUInt(),
            edge[GraphKeys::End].asUInt(),
            edge[GraphKeys::Weight].asUInt(),
            edge[GraphKeys::Directed].asBool()
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

unsigned Graph::getEdgeWeight(unsigned v1, unsigned v2) const
{
    for (const auto& v : {v1, v2}) 
    {
        if (vertices_.find(v) == vertices_.end())
            throw std::runtime_error("Graph does not contain vertex with ID: " + v);
    }

    auto pathID = genHash(v1, v2);
    if (paths_.find(pathID) == paths_.end())
        throw std::runtime_error("Graph does not contain edge with ID: " + pathID);
    return paths_.at(pathID);
}

unsigned Graph::getPathLength(const std::vector<unsigned>& path) const
{
    unsigned length = 0;

    try
    {
        for (size_t i = 1; i < path.size(); ++i)
            length += getEdgeWeight(path[i - 1], path[i]);
    }
    catch(const std::exception& e)
    {
        throw;
    }

    return length;
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
