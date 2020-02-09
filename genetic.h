#ifndef GENETIC_H
#define GENETIC_H

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

class genetic{
public:
    graph *gr;
    routeSA *routes;
    vector <int>citiesDefault;
    int sizeOfPopulation;
    int generationsAmount;
    int mixMutationsPerGen;
    int combineMutationsPerGen;

    genetic(graph *gr, int sizeOfPopulation, int generationsAmount, int mixMutationsPerGen, int combineMutationsPerGen);

    void findPath();

    routeSA generateRandomRoute();
    routeSA generateRandomRouteEnd(vector <int>partialPath);
//used first half of one of them and second half is the order of cities from second
    routeSA combineRoutes(vector <int>firstPath, vector <int>secondPath);
//replace two random cities position on path
    routeSA mixRoute(vector <int>path);
    int countPathWeight(vector <int>path);

    void showPath(vector <int>path);
    void printPopulation(vector <routeSA>population);
};
#endif // GENETIC_H
