#ifndef SA_H
#define SA_H

#include <algorithm>
#include <tuple>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "graph.h"
#include "linuxtime.h"


struct routeSA{
    vector <int>path;
    int weight;
};

class sa{
public:
    graph *gr;

    double temp;
    int tempMin;
    int iterStop;
    double alpha;
    int maxSec;

    routeSA currentRoute;
    routeSA bestRoute;

    sa(graph *gr, int temp, int tempMin, int iterStop, int maxSec, double alpha);

    void findPath();

    int countPathWeight(vector <int>path);
    routeSA generateRandomRoute();
//definicje sąsiedstwa:
    routeSA switchCities(routeSA r);
    routeSA turnAroundArc(routeSA r);

    bool toAccept(routeSA r);
    bool toAcceptRandomized(int weight);
    void saveBest(routeSA r);

    void showPath(vector <int>path);
};

#endif // SA_H
