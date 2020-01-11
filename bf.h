#ifndef BF_H
#define BF_H

#include <algorithm>
#include <tuple>
#include "graph.h"

class bf{
public:
    graph *gr;
    int weightSum;
    vector<int> finalPath;

    bf(graph *gr);

    void findPath();
    tuple<int, vector<int>> goNext(int vert, int visitId, vector <int>path, vector <int>notVisited, graph* gr);
    void showPath();
};

#endif // BF_H
