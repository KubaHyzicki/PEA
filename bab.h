#ifndef BAB_H
#define BAB_H

#include "graph.h"

class bab{
public:
    graph *gr;
    int weightSum;
    bab(graph *gr);
    void findPath();
};

#endif // BAB_H
