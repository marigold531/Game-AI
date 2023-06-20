#include "Graph.hpp"

unordered_map<string, float> Graph::neighbors(string id)
{
    return edges[id];
}

void Graph::addEdge(string src, string dest, float weight)
{
    edges[src][dest] = weight;
}


void Graph::addCoordinates(string id, float x, float y)
{
    // if(edges.find(id) == edges.end()) {
    //     exit(1);
    // }
    coordinates[id] = make_pair(x, y);
}


Graph Graph::generateGraph(int numVertices, int weightMin, int weightMax, double edgeProb)
{
    std::random_device rd;
    std::mt19937 gen(1);

    Graph g;

    // Assign coordinates to vertices randomly in a square region
    std::uniform_int_distribution<int> coordDistribution(0, 100);
    for (int i = 0; i < numVertices; ++i) {
        float x = coordDistribution(gen);
        float y = coordDistribution(gen);
        g.addCoordinates(std::to_string(i), x, y);
    }

    // Generate edges using Erdős–Rényi model
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) {
            if (distribution(gen) < edgeProb) {
                float weight = std::uniform_real_distribution<float>(weightMin, weightMax)(gen);
                g.addEdge(std::to_string(i), std::to_string(j), weight);
            }
        }
    }

    return g;
}

void Graph::printGraph()
{
    for (const auto& vertex : edges) {
        const std::string& src = vertex.first;
        const std::unordered_map<std::string, float>& neighbors = vertex.second;

        std::cout << "Vertex " << src << " has edges to: ";

        for (const auto& neighbor : neighbors) {
            const std::string& dest = neighbor.first;
            int weight = neighbor.second;

            std::cout << "(" << dest << ", weight: " << weight << ") ";
        }
        std::cout << std::endl;
    }

    //print coordinates
    for(auto vertex : coordinates) {
        cout << vertex.first << ": (" << vertex.second.first << ", " << vertex.second.second << ")" << endl;
    }
}
