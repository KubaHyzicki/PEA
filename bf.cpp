#include "bf.h"

bf::bf(graph *gr){
    this->gr=gr;
}

void bf::showPath(){
    cout << this->finalPath[0];
    if((int)this->finalPath.size() > 1){
        for(int i=1;i<(int)this->finalPath.size();i++){
            cout << " -> " << this->finalPath[i];
        }
    }
    cout << endl;
    cout << "finalWeight=" << this->weightSum << endl;
}

tuple<int, vector<int>> bf::goNext(int vert, int visitId, vector <int>path, vector <int>notVisited, graph* gr){

    path.push_back(vert);
    notVisited.erase(notVisited.begin()+visitId);
    int weight=0;
    int newWeight;
    vector <int>newPath,returnPath;

    if(notVisited.empty()){
        int returnWeight=gr->cities[vert][0];
        path.push_back(0);
        return make_tuple(returnWeight, path);
    }

    for(int newVisitId=0; newVisitId < (int)notVisited.size(); newVisitId++){
        tie(newWeight, newPath)=goNext(notVisited[newVisitId], newVisitId, path, notVisited, gr);
        newWeight=newWeight+gr->cities[vert][notVisited[newVisitId]];
        if(newWeight<weight || weight==0){
            weight=newWeight;
            returnPath=newPath;
        }

    }

    return make_tuple(weight, returnPath);
}

void bf::findPath(){
    graph *gr=this->gr;
    vector <int>path;
    vector <int>notVisited;
    for(int i=0;i<gr->getVerticesAmount();i++)
        notVisited.push_back(i);
    tie(this->weightSum, this->finalPath) = goNext(0, 0, path, notVisited, gr);
}
