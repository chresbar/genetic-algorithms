#pragma once

#include <fstream>
#include <jsoncpp/json/json.h>

namespace ConfigKeys
{
    constexpr auto Graph = "graph";
    constexpr auto Size = "size";
    constexpr auto Iterations = "iterations";
    constexpr auto Mutation = "mutation";
    constexpr auto Strategy = "strategy";
}

namespace GraphKeys
{
    constexpr auto Edges = "edges";
    constexpr auto Begin = "begin";
    constexpr auto End = "end";
    constexpr auto Weight = "weight";
    constexpr auto Directed = "directed";
}

inline bool isJsonType(const Json::Value& value, Json::ValueType type)
{
    switch (type)
    {
    case Json::ValueType::booleanValue:
        return value.isBool();
    case Json::ValueType::intValue:
        return value.isInt();
    case Json::ValueType::uintValue:
        return value.isUInt();
    case Json::ValueType::realValue:
        return value.isDouble();
    case Json::ValueType::stringValue:
        return value.isString();
    case Json::ValueType::arrayValue:
        return value.isArray();
    case Json::ValueType::nullValue:
        return value.isNull();
    case Json::ValueType::objectValue:
        return value.isObject();
    }
    return false;
}

inline const Json::Value loadJson(const std::string& filepath)
{
    std::ifstream file(filepath, std::ifstream::binary);

    if (!file.is_open())
        throw std::runtime_error("Faild to open file: " + filepath);

    Json::Value root;
    file >> root;

    return root;
}
