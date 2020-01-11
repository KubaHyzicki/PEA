#include "interface.h"

interface::interface(string filename, string system){
    this->gr=new graph(filename);
    if (system == "linux"){
        this->time=new linuxtime;
    } else {
        cout << "No system specified! Returning..." << endl;
        return;
    }
    while(this->mainLoop());
}

interface::~interface(){
    delete this->gr;
    delete this->time;
}

bool interface::mainLoop(){
    for(;;){
        cout<<messMain << endl;
        cin>>input;
        switch(input){
        case 0:{
            return 0;
        }
        case 1:{
            cout<<endl;
            gr->display();
            cout<<endl;
            return 1;
        }
        case 2:{
            bf alg(this->gr);
            cout << endl;
            time->start();
            alg.findPath();
            time->stop();
            cout << endl;
            alg.showPath();
            cout << endl;
            return 1;
        }
        case 3:{
            dp alg(this->gr);
            cout << endl;
            time->start();
            alg.findPath();
            time->stop();
            cout << endl;
            alg.showPath();
            cout << endl;
            return 1;
        }
        default:{
            continue;
        }
        }
        time->stop();
        return 1;
    }
}
