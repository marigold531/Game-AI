#include "Dijkstra.hpp"

struct CompareNodes {
    bool operator()(const NodeD& a, const NodeD& b) const {
        return a.cost > b.cost;
    }
};

std::vector<std::string> Dijkstra::searchPath(Graph& graph, std::string start, std::string goal) {

    std::priority_queue<NodeD, std::vector<NodeD>, CompareNodes> frontier;
    frontier.push({start, 0});

    std::unordered_map<std::string, std::string> came_from;
    std::unordered_map<std::string, float> cost_so_far;

    came_from[start] = "";
    cost_so_far[start] = 0;

    while(!frontier.empty()) {

        NodeD current = frontier.top();
        frontier.pop();
        
        if(current.id == goal) {
            break;
        }

        for(auto& neighbor : graph.neighbors(current.id)) {
            std::string next = neighbor.first;
            float weight = neighbor.second;

            float new_cost = cost_so_far[current.id] + weight;

            if(cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                float priority = new_cost;
                frontier.push({next, priority});
                came_from[next] = current.id;
            }
        }
    } // end of frontier while loop
    std::vector<std::string> path;
    std::string current = goal;
    while(current != start) {
        path.push_back(current);
        current = came_from[current];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}