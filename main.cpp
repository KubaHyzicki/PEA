#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "time.h"
#include "linuxtime.h"
#include "interface.h"
#include "graph.h"
#include "string"
//#include "dp.h"
//#include "genetic.h"
//#include "bf.h"
#include "sa.h"
#include "ts.h"

using namespace std;

int main(int argc, char *argv[])
{
//    interface pea(filename, "linux");

    string algName = argv[7];
    linuxtime time=linuxtime();

//################################################################################################
    if(argc == 8 && (algName == "sa")){
        cout << "Testing simulated annealing" << endl;
        string filename=argv[1];
        int temp = atoi(argv[2]);
        int tempMin = atoi(argv[3]);
        int iterStop = atoi(argv[4]);
        int maxSec = atoi(argv[5]);
        double alpha = atof(argv[6]);

        graph g(filename);

        sa simulatedAnnealing(&g, temp, tempMin, iterStop, maxSec, alpha);
        time.start();
        simulatedAnnealing.findPath();
        time.stop();
    }else
//################################################################################################

//################################################################################################
    if(argc == 8 && (algName == "ts")){
        cout << "Testing tabu search" << endl;
        string filename=argv[1];
        int iterStop = atoi(argv[2]);
        int maxSec = atoi(argv[3]);
        int defaultCadence = atoi(argv[4]);
        int maxBetterRouteFoundXItersAgo = atoi(argv[5]);
        int maxIterationsPerArea = atoi(argv[6]);

        graph g(filename);

        ts tabuSearch(&g, iterStop, maxSec, defaultCadence, maxBetterRouteFoundXItersAgo, maxIterationsPerArea);
        time.start();
        tabuSearch.findPath();
        time.stop();
    }else
//################################################################################################
    if(true){
        cout << "no algorithm chosen" << endl;
    }
    return 0;
}
