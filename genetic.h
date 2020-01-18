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


struct route{
    vector <int>path;
    int weight;
};

class genetic{
public:
    graph *gr;
    route *routes;
    vector <int>citiesDefault;
    int sizeOfPopulation;
    int generationsAmount;
    int mixMutationsPerGen;
    int combineMutationsPerGen;

    genetic(graph *gr, int sizeOfPopulation, int generationsAmount, int mixMutationsPerGen, int combineMutationsPerGen);

    void findPath();

    route generateRandomRoute();
    route generateRandomRouteEnd(vector <int>partialPath);
//used first half of one of them and second half is the order of cities from second
    route combineRoutes(vector <int>firstPath, vector <int>secondPath);
//replace two random cities position on path
    route mixRoute(vector <int>path);
    int countPathWeight(vector <int>path);

    void showPath(vector <int>path);
    void printPopulation(vector <route>population);
};
#endif // GENETIC_H
