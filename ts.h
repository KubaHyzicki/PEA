#ifndef TS_H
#define TS_H

#include <algorithm>
#include <tuple>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "graph.h"
#include "linuxtime.h"

struct routeTS{
    vector <int>path;
    int weight;
};

class ts{
public:
    graph *gr;
    vector <vector<int>>tabuPaths;
//{} to głupi workaround, bo inaczej dodanie czegokolwiek do tego konkretnego wektora wyrzucało błędy z pointerem przy zwalnianiu pamięci...to niby to jakoś naprawia
    vector <int>tabuCadences{};
    int betterRouteFoundXItersAgo=0;
    int maxBetterRouteFoundXItersAgo=20;
    int iteration=0;
    int iterationPerArea=0;
    int maxIterationsPerArea=50;
    routeTS currentRoute;
    routeTS bestRoute;
    int iterStop=100;
    int defaultCadence=1;
    int maxSec=10;

    ts(graph *gr, int iterStop, int maxSec, int defaultCadence, int maxBetterRouteFoundXItersAgo, int maxIterationsPerArea);

    void findPath();

    int countPathWeight(vector <int>path);
    routeTS generateRandomRoute();
//definicje sąsiedstwa:
    vector <routeTS>switchedCities(vector <int>path);
    vector <routeTS>turnedAroundArc(vector <int>path);
//można je zmieniać w:
    vector <routeTS>getNeighbors(vector <int>path);

    int countMVal(vector <int>x, vector <int>y);
    int simplestCountMVal(vector <int>x, vector <int>y);
    bool criticalEvent();
    void restart();

    void showPath(vector <int>path);
};

#endif // TS_H
