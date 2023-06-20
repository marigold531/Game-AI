#include "graph/Graph.hpp"
#include "search_algorithm/AStar.hpp"
#include <SFML/Graphics.hpp>
#include "search_algorithm/Dijkstra.hpp"

int main()
{
   
    Graph graph;
    graph = graph.generateGraph(30000, 1, 20, 0.1);
    //graph.printGraph();
    AStar aStart;
    Dijkstra dijkstra;
    //smallGraph.printGraph();
    sf::Clock clock;
    clock.restart();
    std::vector<std::string> path1 = aStart.searchPath(graph, "1", "28888");
    float time_taken = clock.getElapsedTime().asSeconds();
    clock.restart();
    std::vector<std::string> path2 = dijkstra.searchPath(graph, "1", "28888");
    float time_taken2 = clock.getElapsedTime().asSeconds();

    clock.restart();
    std::vector<std::string> path3 = aStart.inadmissibleSearchPath(graph, "1", "28888");
    float time_taken3 = clock.getElapsedTime().asSeconds();

    //a star
    cout << "Time for A*: " << time_taken << endl;

    int costAStar = 0;
    for(int i = 0; i < path1.size() - 1; i++) {
        const auto& src = path1[i];
        const auto& dest = path1[i+1];
        int weight = graph.edges.at(src).at(dest);
        costAStar += weight;
    }
    cout << "Cost for A*: " << costAStar << endl;
    cout << "vertex path: ";
    for(int i = 0; i < path1.size(); i++) {
        cout << path1.at(i) << " ";
    }
    cout << endl;
    cout << "Cost path: ";
    for(int i = 0; i < path1.size() - 1; i++) {
        const auto& src = path1[i];
        const auto& dest = path1[i+1];
        int weight = graph.edges.at(src).at(dest);
        cout << weight << " ";
    }
    cout << endl << endl;


    cout << "Time for A* inadmissable: " << time_taken3 << endl;

    int costAStar3 = 0;
    for(int i = 0; i < path3.size() - 1; i++) {
        const auto& src = path3[i];
        const auto& dest = path3[i+1];
        int weight = graph.edges.at(src).at(dest);
        costAStar3 += weight;
    }
    cout << "Cost for A* inadmissable: " << costAStar3 << endl;
    cout << "vertex path: ";
    for(int i = 0; i < path3.size(); i++) {
        cout << path3.at(i) << " ";
    }
    cout << endl;
    cout << "Cost path: ";
    for(int i = 0; i < path3.size() - 1; i++) {
        const auto& src = path3[i];
        const auto& dest = path3[i+1];
        int weight = graph.edges.at(src).at(dest);
        cout << weight << " ";
    }
    cout << endl << endl;

    // dijkstra
    cout << "Time for dijkstra*: " << time_taken2 << endl;
    int costdijkstra = 0;
    for(int i = 0; i < path2.size() - 1; i++) {
        const auto src = path2[i];
        const auto dest = path2[i+1];
        int weight = graph.edges[src][dest];
        costdijkstra += weight;
    }
    cout << "Cost for dijkstra: " << costdijkstra << endl;
    cout << "vertex path: ";
    for(int i = 0; i < path2.size(); i++) {
        cout << path2.at(i) << " ";
    }
    cout << endl;
    cout << "Cost path: " ;
    for(int i = 0; i < path2.size() - 1; i++) {
        const auto& src = path2[i];
        const auto& dest = path2[i+1];
        int weight = graph.edges.at(src).at(dest);
        cout << weight << " ";
    }
    cout << endl;

    
    return 0;
}