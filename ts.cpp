#include "ts.h"

bool compareNeighbors(routeTS firstRoute, routeTS secondRoute){
    return firstRoute.weight > secondRoute.weight;
}

ts::ts(graph *gr, int iterStop, int maxSec, int defaultCadence, int maxBetterRouteFoundXItersAgo, int maxIterationsPerArea){
    srand (time(NULL));
    this->gr = gr;
    this->maxBetterRouteFoundXItersAgo=maxBetterRouteFoundXItersAgo;
    this->maxIterationsPerArea=maxIterationsPerArea;
    this->iterStop=iterStop;
    this->maxSec=maxSec;
    this->defaultCadence=defaultCadence;
}

void ts::showPath(vector <int>path){
    cout << path[0];
    if((int)path.size() > 1){
        for(int i=1;i<(int)path.size();i++){
            cout << " -> " << path[i];
        }
    }
    cout << endl;
    cout << "finalWeight=" << countPathWeight(path) << endl;
}

int ts::countPathWeight(vector <int>path){
    int lastCity=0;
    int weightSum=0;
    for(int i=0;i<(int)path.size();i++){
        weightSum+=this->gr->cities[lastCity][path[i]];
        lastCity=path[i];
    }
    weightSum+=this->gr->cities[lastCity][0];
    return weightSum;
}

routeTS ts::generateRandomRoute(){
    vector <int>vertices;
    for(int i=1;i<this->gr->verticesAmount;i++){
        vertices.push_back(i);
    }
    vector <int>path;
    int verId;
    path.push_back(0);
    while(vertices.size()>0){
        verId=rand()*100%vertices.size();
        path.push_back(vertices[verId]);
        vertices.erase(vertices.begin()+verId);
    }
    path.push_back(0);
    return routeTS{path,countPathWeight(path)};
}

vector <routeTS>ts::switchedCities(vector <int>path){
    vector <routeTS>routes;
    for(int i=1;i<(int)path.size()-2;i++){
        for(int i2=i+1;i2<(int)path.size()-1;i2++){
            vector <int>newPath=path;
            newPath.at(i2)=path[i];
            newPath.at(i)=path[i2];
            routes.push_back({newPath,countPathWeight(newPath)});
        }
    }
    return routes;
}

vector <routeTS>ts::turnedAroundArc(vector <int>path){
    vector <routeTS>routes;
    for(int i=1;i<(int)path.size()-2;i++){
        for(int i2=i+1;i2<(int)path.size()-1;i2++){
            vector <int>newPath;
            int vecPos=0;
            while(vecPos < i){
                newPath.push_back(path[vecPos++]);
            }
            for(vecPos=i2;vecPos>=i;vecPos--){
                newPath.push_back(path[vecPos]);
            }
            vecPos=i2+1;
            while(vecPos < (int)path.size()){
                newPath.push_back(path[vecPos++]);
            }
            routes.push_back({newPath,countPathWeight(newPath)});
        }
    }
    return routes;
}

vector <routeTS>ts::getNeighbors(vector <int>path){
    //2 alternatywne strategie...ale obracanie łuków jest do kitu(skuteczność) w porównaniu do zamiany miast... :/
//    vector <route>routes=switchedCities(path);
    vector <routeTS>routes=turnedAroundArc(path);
    sort(routes.begin(),routes.end(),compareNeighbors);
    return routes;
}

int ts::simplestCountMVal(vector <int>x, vector <int>y){
    return countPathWeight(x) - countPathWeight(y);
}

int ts::countMVal(vector <int>x, vector <int>y){
    return countPathWeight(x) - countPathWeight(y);
}

bool ts::criticalEvent(){
    if(this->betterRouteFoundXItersAgo >= this->maxBetterRouteFoundXItersAgo){
//        cout << "maxBetterRouteFoundXItersAgo" << endl;
        return true;
    }
    if(this->iterationPerArea >= this->maxIterationsPerArea){
//        cout << "maxIterationsPerArea" << endl;
        return true;
    }
    return false;
}

void ts::restart(){
    this->betterRouteFoundXItersAgo=0;
    this->iterationPerArea=0;
    this->currentRoute=generateRandomRoute();
//    showPath(this->bestRoute.path);
//    showPath(this->currentRoute.path);
    this->tabuCadences.clear();
    this->tabuPaths.clear();
}



void ts::findPath(){
    this->iteration = 0;
    linuxtime time;
    int iTabu;
    int iTime=1;
    this->currentRoute=generateRandomRoute();
    this->bestRoute=currentRoute;
//    showPath(this->currentRoute.path);

    vector <routeTS>neighbors=getNeighbors(this->currentRoute.path);
    routeTS bestOfNeighBors;

    time.start();
//    while(iteration++ < this->iterStop){
    while(time.check() < this->maxSec){
        neighbors=getNeighbors(this->currentRoute.path);
        do{
            bestOfNeighBors=neighbors.back();
            neighbors.pop_back();
        }while(count(this->tabuPaths.begin(),this->tabuPaths.end(),bestOfNeighBors.path));
        this->currentRoute = bestOfNeighBors;
//save in tabu:
        this->tabuPaths.push_back(this->currentRoute.path);
        this->tabuCadences.push_back(this->defaultCadence);
//release tabu
        iTabu=0;
        while((int)this->tabuCadences.size() > iTabu){
            this->tabuCadences[iTabu] -= 1;
            if(this->tabuCadences[iTabu] == 0){
                this->tabuCadences.erase(this->tabuCadences.begin()+iTabu);
                this->tabuPaths.erase(this->tabuPaths.begin()+iTabu);
            } else{
                iTabu++;
            }
        }

        if(bestOfNeighBors.weight < this->bestRoute.weight){
            this->bestRoute = bestOfNeighBors;
            this->betterRouteFoundXItersAgo=0;
        }else {
            this->betterRouteFoundXItersAgo++;
        }
//diversification if statement:
        if( this->criticalEvent() == true ){
            restart();
        }else{
            this->iterationPerArea++;
        }

        if(time.check() > iTime){
            cout<<"w="<<this->bestRoute.weight<<endl;
            iTime++;
        }
    }

    showPath(this->bestRoute.path);
}
