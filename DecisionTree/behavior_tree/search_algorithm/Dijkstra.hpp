#pragma once

#include "../graph/Graph.hpp"
#include <queue>
#include <algorithm>

struct NodeD {
    std::string id;
    //double gScore;
    float cost;
};

class Dijkstra
{
    public:
        std::vector<std::string> searchPath(Graph& graph, std::string start, std::string goal);
};