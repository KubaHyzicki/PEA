#include "dp.h"

dp::dp(graph *gr){
    this->gr=gr;
}

void dp::showPath(){
    cout << this->finalPath[0];
    if((int)this->finalPath.size() > 1){
        for(int i=1;i<(int)this->finalPath.size();i++){
            cout << " -> " << this->finalPath[i];
        }
    }
    cout << endl;
    cout << "finalWeight=" << this->weightSum << endl;
}

void print(vector <int>path){
    cout << path[0];
    if((int)path.size() > 1){
        for(int i=1;i<(int)path.size();i++){
            cout << " -> " << path[i];
        }
    }
    cout << endl;
}

void printNotVisited(vector <int>notVisited){
    if((int)notVisited.size() == 0){
        cout << "no more!" << endl;
        return;
    }
    cout << notVisited[0];
    if((int)notVisited.size() > 1){
        for(int i=1;i<(int)notVisited.size();i++){
            cout << ", " << notVisited[i];
        }
    }
    cout << endl;
}

tuple<int, vector<int>> dp::goNext(int vert, int visitId, vector <int>notVisited, graph* gr){

    //odwiedzamy dane miasto
    notVisited.erase(notVisited.begin()+visitId);

    int weight=0;
    int newWeight=0;
    vector <int>newPath,returnPath;

    //klucz główny dla zapamiętanych sytuacji=[nieodwiedzone_miasta,miasto_startowe]
    vector <int>storedArg=notVisited;
    storedArg.push_back(vert);

    //najgłębsze odchłanie algorytmu(droga powrotna)
    if(notVisited.empty()){
        int returnWeight=gr->cities[vert][0];
        returnPath.push_back(vert);
        returnPath.push_back(0);
        return make_tuple(returnWeight, returnPath);
    }

    //jeśli dana sytuacja już wystąpiła, skorzystaj z gotowych wyników
    if(this->storedPathes.find(storedArg) != this->storedPathes.end()){
        weight=this->storedPathes[storedArg].weight;
        returnPath=this->storedPathes[storedArg].path;
        print(returnPath);
        for(int i=0;i<(int)notVisited.size();i++) cout << notVisited[i];
//        cout << "ciastko" << endl;            //do zliczania ilości razy gdy korzystamy z gotowych wyników
    }
    //jeśli nie, przejdź ją
    else{
        storedPath pathToStore;
        for(int newVisitId=0; newVisitId < (int)notVisited.size(); newVisitId++){
            tie(newWeight, newPath)=goNext(notVisited[newVisitId], newVisitId, notVisited, gr);
            print(newPath);
            newWeight=newWeight+gr->cities[vert][notVisited[newVisitId]];
            if(newWeight<weight || weight==0){
                weight=newWeight;
                returnPath=newPath;
            }

        }
        //zapamiętaj najlepsze rozwiązanie w danej sytuacji
        {
            pathToStore.path=returnPath;
            pathToStore.weight=weight;
            this->storedPathes[storedArg]=pathToStore;
        }
    }

    //dodaj wierzchołek do ścieżki
    returnPath.insert(returnPath.begin(),vert);
    return make_tuple(weight, returnPath);
}

void dp::findPath(){
    graph *gr=this->gr;
    vector <int>notVisited;
    for(int i=0;i<gr->getVerticesAmount();i++)
        notVisited.push_back(i);
    tie(this->weightSum, this->finalPath) = goNext(0, 0, notVisited, gr);
}
