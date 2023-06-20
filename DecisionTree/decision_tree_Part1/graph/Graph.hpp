#pragma once

using namespace std;
#include <vector>
#include <unordered_map>
#include <iostream>
#include <random>
#include <ctime>

class Graph
{
    public:
        unordered_map<string, unordered_map<string, float>> edges;
        unordered_map<string, pair<float, float>> coordinates;

        unordered_map<string, float> neighbors(string id);
        void addEdge(string src, string dest, float weight);
        void addCoordinates(string id, float x, float y);

        void printGraph();
        Graph generateGraph(int numVertices, int weightMin, int weightMax, double edgeProb);
};