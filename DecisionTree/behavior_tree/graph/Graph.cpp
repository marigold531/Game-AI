#include "Graph.hpp"

unordered_map<string, float> Graph::neighbors(string id)
{
    return edges[id];
}

void Graph::addEdge(string src, string dest, float weight)
{
    edges[src][dest] = weight;
    edges[dest][src] = weight;
}


void Graph::addCoordinates(string id, float x, float y)
{
    coordinates[id] = make_pair(x, y);
}


Graph Graph::generateGraph(int numVertices, int weightMin, int weightMax, double edgeProb)
{
    std::default_random_engine generator(std::time(0));
    std::uniform_int_distribution<int> weightDistribution(weightMin, weightMax);
    std::uniform_real_distribution<double> edgeDistribution(0, 1);

    Graph graph;
    for (int src = 0; src < numVertices; ++src) {
        for (int dest = 0; dest < numVertices; ++dest) {
            if (src == dest) {
                continue; // Skip self-loops
            }

            if (edgeDistribution(generator) < edgeProb) {
                int weight = weightDistribution(generator);
                graph.addEdge("Node" + std::to_string(src), "Node" + std::to_string(dest), weight);
            }
        }
    }
    return graph;
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