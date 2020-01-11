#include "linuxtime.h"

void linuxtime::start(){
    begining = chrono::steady_clock::now();
}

void linuxtime::stop(){
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    auto elapsed = end - begining;
    cout << elapsed.count() << endl;
    cout<<"seconds: "<<chrono::duration_cast<chrono::seconds>(end-begining).count()<<endl;
    cout<<"miliseconds: "<<chrono::duration_cast<chrono::milliseconds>(end - begining).count()<<endl;
    cout<<"microseconds: "<<chrono::duration_cast<chrono::microseconds>(end - begining).count()<<endl;
    cout<<"nanoseconds: "<<chrono::duration_cast<chrono::nanoseconds>(end - begining).count()<<endl;
}
