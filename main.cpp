#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "interface.h"
#include "graph.h"
#include "dp.h"
#include "genetic.h"
#include "bf.h"
#include "time.h"
#include "linuxtime.h"
using namespace std;

int main(int argc, char *argv[])
{
//    interface pea(filename, "linux");


    string filename="testDataX.txt";
    int sizeOfPopulation=10;
    int generationsAmount=5;
    int mixMutationsPerGen=1;
    int combineMutationsPerGen=8;

    if(argc > 1){
        filename=argv[1];
        sizeOfPopulation=atoi(argv[2]);
        generationsAmount=atoi(argv[3]);
        mixMutationsPerGen=(int)sizeOfPopulation*0.1;
        combineMutationsPerGen=(int)sizeOfPopulation*0.8;
    }
    if(argc > 4){
        mixMutationsPerGen=atoi(argv[4]);
        combineMutationsPerGen=atoi(argv[5]);
    }

    graph g(filename);
    g.display();

    linuxtime *time;
    time=new linuxtime();

//    dp correctOne(&g);
//    correctOne.findPath();

    genetic gen(&g, sizeOfPopulation, generationsAmount, mixMutationsPerGen, combineMutationsPerGen);
    time->start();
    gen.findPath();
    time->stop();

    return 0;
}
