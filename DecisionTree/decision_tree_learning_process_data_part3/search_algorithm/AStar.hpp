#pragma once

#include "../graph/Graph.hpp"
#include <queue>
#include <algorithm>


struct Node {
    std::string id;
    //double gScore;
    float fScore;
};

class AStar
{
    private:
        float heuristic(std::string a, std::string b, Graph &graph);
        float inadmissible(std:: string a, std::string b, Graph &graph, std::unordered_map<std::string, std::string> came_from);
    public:
        std::vector<std::string> searchPath(Graph& graph, std::string start, std::string goal);
        std::vector<std::string> inadmissibleSearchPath(Graph& graph, std::string start, std::string goal);
};  