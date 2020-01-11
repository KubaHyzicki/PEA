#include <iostream>
#include <fstream>
#include <string>
#include "interface.h"
#include "graph.h"
#include "dp.h"
#include "bf.h"
#include "time.h"
#include "linuxtime.h"
using namespace std;

//int main(int argc, char *argv[])
int main()
{
    string filename="testData10.txt";
//    interface pea(filename, "linux");

    graph g(filename);
    g.display();

    dp algDP(&g);
    algDP.findPath();
    algDP.showPath();

//    linuxtime *time;
//    time=new linuxtime();

//    time->start();
//    dp algDP(&g);
//    algDP.findPath();
//    algDP.showPath();
//    time->stop();

//    time->start();
//    bf algBF(&g);
//    algBF.findPath();
//    algBF.showPath();
//    time->stop();

    return 0;
}
