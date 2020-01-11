#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include "linuxtime.h"
#include "graph.h"
#include "dp.h"
#include "bf.h"

using namespace std;

class interface{
public:
    linuxtime *time;
    graph *gr;
    int input;
    string messMain="0-exit\n"
                    "1-display graph\n"
                    "2-BruteForce\n"
                    "3-Dynamic Programming Algorithm\n";
//                "2-init graph, load from file\n";

    interface(string filename, string system);

    ~interface();

    bool mainLoop();

    void noDirect(int mode);
};

#endif // INTERFACE_H
