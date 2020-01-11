#ifndef DP_H
#define DP_H

#include <algorithm>
#include <tuple>
#include <map>
#include "graph.h"

struct storedPath{
    vector <int>path;
    int weight;
};

class dp{
public:
    graph *gr;
    int weightSum;
    vector<int> finalPath;
    map<vector <int>, storedPath> storedPathes;

    dp(graph *gr);

    void findPath();
    tuple<int, vector<int>> goNext(int vert, int visitId, vector <int>notVisited, graph* gr);
    void showPath();
};

#endif // DP_H
