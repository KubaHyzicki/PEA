#ifndef LINUXTIME_H
#define LINUXTIME_H
#include <iostream>
#include <chrono>
using namespace std;
//-------------------------------------------------------------------------

class linuxtime{
    chrono::steady_clock::time_point begining;
public:

    void start();


    void stop();

    int check();
};
#endif // LINUXTIME_H
