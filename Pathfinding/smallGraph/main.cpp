#include "graph/Graph.hpp"
#include "search_algorithm/AStar.hpp"
#include <SFML/Graphics.hpp>
#include "search_algorithm/Dijkstra.hpp"

int main()
{
    Graph smallGraph;
    //Vertex 1
    smallGraph.addEdge("1", "26", 30);
    smallGraph.addEdge("1", "2", 10);
    //vertex 2
    smallGraph.addEdge("2", "1", 10);
    smallGraph.addEdge("2", "3", 12);
    smallGraph.addEdge("2", "4", 20);
    //vertex 3
    smallGraph.addEdge("3", "2", 12);
    smallGraph.addEdge("3", "9", 8);
    //vertex 4
    smallGraph.addEdge("4", "2", 20);
    smallGraph.addEdge("4", "5", 21);
    smallGraph.addEdge("4", "6", 14);
    smallGraph.addEdge("4", "7", 18);
    //vertex 5
    smallGraph.addEdge("5", "4", 21);
    smallGraph.addEdge("5", "25", 21);
    //vertex 6
    smallGraph.addEdge("6", "4", 14);
    smallGraph.addEdge("6", "7", 16);
    //vertex 7
    smallGraph.addEdge("7", "4", 18);
    smallGraph.addEdge("7", "6", 16);
    smallGraph.addEdge("7", "8", 10);
    //vertex 8
    smallGraph.addEdge("8", "10", 10);
    smallGraph.addEdge("8", "7", 10);
    //vertex 9
    smallGraph.addEdge("9", "10", 15);
    smallGraph.addEdge("9", "11", 15);
    smallGraph.addEdge("9", "3", 8);
    smallGraph.addEdge("9", "15", 19);
    smallGraph.addEdge("9", "19", 14);
    //vertex 10
    smallGraph.addEdge("10", "8", 10);
    smallGraph.addEdge("10", "9", 15);
    smallGraph.addEdge("10", "14", 15);
    smallGraph.addEdge("10", "24", 17);
    //vertex 11
    smallGraph.addEdge("11", "9", 15);
    smallGraph.addEdge("11", "12", 10);
    smallGraph.addEdge("11", "7", 10);
    //vertex 12
    smallGraph.addEdge("12", "11", 10);
    smallGraph.addEdge("12", "13", 19);
    //vertex 13
    smallGraph.addEdge("13", "12", 19);
    //vertex 14
    smallGraph.addEdge("14", "15", 19);
    smallGraph.addEdge("14", "10", 15);
    smallGraph.addEdge("14", "21", 10);
    smallGraph.addEdge("14", "20", 35);    
    //vertex 15
    smallGraph.addEdge("15", "9", 19);
    smallGraph.addEdge("15", "18", 22);
    smallGraph.addEdge("15", "16", 10);
    smallGraph.addEdge("15", "17", 19);
    smallGraph.addEdge("15", "14", 19);
    //vertex 16
    smallGraph.addEdge("16", "15", 10);
    smallGraph.addEdge("16", "17", 13);
    //vertex 17
    smallGraph.addEdge("17", "18", 15);
    smallGraph.addEdge("17", "16", 13);
    smallGraph.addEdge("17", "15", 19);
    //vertex 18
    smallGraph.addEdge("18", "17", 15);
    smallGraph.addEdge("18", "25", 21);
    smallGraph.addEdge("18", "19", 8);
    smallGraph.addEdge("18", "15", 22);
    //vertex 19
    smallGraph.addEdge("19", "18", 8);
    smallGraph.addEdge("19", "9", 14);
    //vertex 20
    smallGraph.addEdge("20", "14", 35);
    smallGraph.addEdge("20", "12", 1);
    smallGraph.addEdge("20", "1", 1);
    //vertex 21
    smallGraph.addEdge("21", "14", 10);
    smallGraph.addEdge("21", "22", 26);
    smallGraph.addEdge("21", "23", 30);
    smallGraph.addEdge("21", "24", 10);
    //vertex 22
    smallGraph.addEdge("22", "21", 26);
    smallGraph.addEdge("22", "23", 15);
    //vertex 23
    smallGraph.addEdge("23", "22", 15);
    smallGraph.addEdge("23", "21", 30);
    smallGraph.addEdge("23", "24", 22);
    //vertex 24
    smallGraph.addEdge("24", "21", 10);
    smallGraph.addEdge("24", "23", 22);
    smallGraph.addEdge("24", "10", 17);
    //vertex 25
    smallGraph.addEdge("25", "18", 21);
    smallGraph.addEdge("25", "5", 21);
    //vertex 26
    smallGraph.addEdge("26", "1", 35);
    
    smallGraph.addCoordinates("1", 62, 38);
    smallGraph.addCoordinates("2", 71, 44);
    smallGraph.addCoordinates("3", 71, 55);
    smallGraph.addCoordinates("4", 81, 56);
    smallGraph.addCoordinates("5", 91, 43);
    smallGraph.addCoordinates("6", 85, 67);
    smallGraph.addCoordinates("7", 71, 68);
    smallGraph.addCoordinates("8", 62, 70);
    smallGraph.addCoordinates("9", 64, 57);
    smallGraph.addCoordinates("10", 56, 67);
    smallGraph.addCoordinates("11", 75, 63);
    smallGraph.addCoordinates("12", 83, 64);
    smallGraph.addCoordinates("13", 93, 63);
    smallGraph.addCoordinates("14", 44, 66);
    smallGraph.addCoordinates("15", 47, 53);
    smallGraph.addCoordinates("16", 39, 45);
    smallGraph.addCoordinates("17", 49, 31);
    smallGraph.addCoordinates("18", 58, 44);
    smallGraph.addCoordinates("19", 66, 45);
    smallGraph.addCoordinates("20", 25, 66);
    smallGraph.addCoordinates("21", 47, 76);
    smallGraph.addCoordinates("22", 34, 92);
    smallGraph.addCoordinates("23", 43, 98);
    smallGraph.addCoordinates("24", 51, 83);
    smallGraph.addCoordinates("25", 76, 37);
    smallGraph.addCoordinates("26", 55, 17);

    AStar aStart;
    Dijkstra dijkstra;
    //smallGraph.printGraph();
    sf::Clock clock;
    clock.restart();
    std::vector<std::string> path1 = aStart.searchPath(smallGraph, "1", "23");
    float time_taken = clock.getElapsedTime().asSeconds();
    clock.restart();
    std::vector<std::string> path2 = dijkstra.searchPath(smallGraph, "1", "23");
    float time_taken2 = clock.getElapsedTime().asSeconds();

    clock.restart();
    std::vector<std::string> path3 = aStart.inadmissibleSearchPath(smallGraph, "1", "23");
    float time_taken3 = clock.getElapsedTime().asSeconds();

    //a star
    cout << "Time for A*: " << time_taken << endl;

    int costAStar = 0;
    for(int i = 0; i < path1.size() - 1; i++) {
        const auto& src = path1[i];
        const auto& dest = path1[i+1];
        int weight = smallGraph.edges.at(src).at(dest);
        costAStar += weight;
    }
    cout << "Cost for A*: " << costAStar << endl;
    for(int i = 0; i < path1.size(); i++) {
        cout << path1.at(i) << " ";
    }
    cout << endl;
    cout << "Cost path: ";
    for(int i = 0; i < path1.size() - 1; i++) {
        const auto& src = path1[i];
        const auto& dest = path1[i+1];
        int weight = smallGraph.edges.at(src).at(dest);
        cout << weight << " ";
    }
    cout << endl << endl;
    

    cout << "Time for A* inadmissable: " << time_taken3 << endl;

    int costAStar3 = 0;
    for(int i = 0; i < path3.size() - 1; i++) {
        const auto& src = path3[i];
        const auto& dest = path3[i+1];
        int weight = smallGraph.edges.at(src).at(dest);
        costAStar3 += weight;
    }
    cout << "Cost for A* inadmissable: " << costAStar3 << endl;
    for(int i = 0; i < path3.size(); i++) {
        cout << path3.at(i) << " ";
    }
    cout << endl;
    cout << "Cost path: ";
    for(int i = 0; i < path3.size() - 1; i++) {
        const auto& src = path3[i];
        const auto& dest = path3[i+1];
        int weight = smallGraph.edges.at(src).at(dest);
        cout << weight << " ";
    }
    cout << endl << endl;



    // dijkstra
    cout << "Time for dijkstra*: " << time_taken2 << endl;
    int costdijkstra = 0;
    for(int i = 0; i < path2.size() - 1; i++) {
        const auto src = path2[i];
        const auto dest = path2[i+1];
        int weight = smallGraph.edges[src][dest];
        costdijkstra += weight;
    }
    cout << "Cost for dijkstra: " << costdijkstra << endl;
    for(int i = 0; i < path2.size(); i++) {
        cout << path2.at(i) << " ";
    }
    cout << endl;
    cout << "Cost path: " ;
    for(int i = 0; i < path2.size() - 1; i++) {
        const auto& src = path2[i];
        const auto& dest = path2[i+1];
        int weight = smallGraph.edges.at(src).at(dest);
        cout << weight << " ";
    }
    cout << endl;
    return 0;
}