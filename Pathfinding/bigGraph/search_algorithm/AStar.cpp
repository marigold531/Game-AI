#include "AStar.hpp"

struct CompareNodes {
    bool operator()(const Node& a, const Node& b) const {
        return a.fScore > b.fScore;
    }
};

float AStar::heuristic(std::string a, std::string b, Graph &graph) {
    auto aCoord = graph.coordinates.at(a);
    auto bCoord = graph.coordinates.at(b);
    float dx = bCoord.first - aCoord.first;
    float dy = bCoord.second - aCoord.second;
    float result = std::sqrt(dx * dx + dy * dy);
    //cout << result << endl;
    return result;
}

float AStar::inadmissible(std::string a, std::string b, Graph& graph, std::unordered_map<std::string, std::string> came_from) {
    auto aCoord = graph.coordinates.at(a);
    auto bCoord = graph.coordinates.at(b);
    int idDiff = abs(stoi(a) - stoi(b));
    float x = std::abs(aCoord.first - bCoord.first);
    float y = std::abs(aCoord.second - bCoord.second);
    float distance = x + y;

    int numUnvisited = graph.coordinates.size() - came_from.size();
    // float avgNeighbors = 0;
    // for (auto node : graph.coordinates) {
    //     if (node.first != a) {
    //         avgNeighbors += graph.neighbors(node.first).size();
    //     }
    //     else {
    //         // Don't include the start node in the average degree calculation
    //         numUnvisited--;
    //     }
    // }
    // if (numUnvisited > 0) {
    //     avgNeighbors /= numUnvisited;
    // }

    return distance + 1.5 * idDiff + 1 * numUnvisited + 1;
}
std::vector<std::string> AStar::searchPath(Graph& graph, std::string start, std::string goal) {
    
    std::priority_queue<Node, std::vector<Node>, CompareNodes> frontier;
    frontier.push({start, 0});

    std::unordered_map<std::string, std::string> came_from;
    std::unordered_map<std::string, float> cost_so_far;

    came_from[start] = "";
    cost_so_far[start] = 0;

    while(!frontier.empty()) {

        //the current lowest estimated cost is removed
        Node current = frontier.top();
        frontier.pop();

        //algorithm run until target location is reached 
        if(current.id == goal) {
            break;
        }

        for(auto& neighbor : graph.neighbors(current.id)) {
            std::string next = neighbor.first;
            float weight = neighbor.second;

            float new_cost = cost_so_far[current.id] + weight;
            
            if(cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                float priority = new_cost + heuristic(next, goal, graph);
                frontier.push({next, priority});
                came_from[next] = current.id;
            }
        }
    } // end of while loop - A* done
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


std::vector<std::string> AStar::inadmissibleSearchPath(Graph& graph, std::string start, std::string goal) {
    
    std::priority_queue<Node, std::vector<Node>, CompareNodes> frontier;
    frontier.push({start, 0});

    std::unordered_map<std::string, std::string> came_from;
    std::unordered_map<std::string, float> cost_so_far;

    came_from[start] = "";
    cost_so_far[start] = 0;

    while(!frontier.empty()) {

        //the current lowest estimated cost is removed
        Node current = frontier.top();
        frontier.pop();

        //algorithm run until target location is reached 
        if(current.id == goal) {
            break;
        }

        for(auto& neighbor : graph.neighbors(current.id)) {
            std::string next = neighbor.first;
            float weight = neighbor.second;

            float new_cost = cost_so_far[current.id] + weight;
            
            if(cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                float priority = new_cost + inadmissible(next, goal, graph, came_from);
                frontier.push({next, priority});
                came_from[next] = current.id;
            }
        }
    } // end of while loop - A* done
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
