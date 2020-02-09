#include "sa.h"

sa::sa(graph *gr, int temp, int tempMin, int iterStop, int maxSec, double alpha){
    srand (time(NULL));
    this->gr = gr;
    this->temp = (double)temp;
    this->tempMin = tempMin;
    this->iterStop = iterStop;
    this->alpha = alpha;
    this->maxSec = maxSec;
}

void sa::showPath(vector <int>path){
    cout << path[0];
    if((int)path.size() > 1){
        for(int i=1;i<(int)path.size();i++){
            cout << " -> " << path[i];
        }
    }
    cout << endl;
    cout << "finalWeight=" << countPathWeight(path) << endl;
}

int sa::countPathWeight(vector <int>path){
    int lastCity=0;
    int weightSum=0;
    for(int i=0;i<(int)path.size();i++){
        weightSum+=this->gr->cities[lastCity][path[i]];
        lastCity=path[i];
    }
    weightSum+=this->gr->cities[lastCity][0];
    return weightSum;
}

routeSA sa::generateRandomRoute(){
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
    return routeSA{path,countPathWeight(path)};
}

routeSA sa::switchCities(routeSA r){
    int firstID=1+rand()%(r.path.size()-2);
    int secondID=firstID;
    while(secondID == firstID){
        secondID=1+rand()%(r.path.size()-2);
    }
    int backupSecondID=r.path[secondID];
    r.path.at(secondID)=r.path[firstID];
    r.path.at(firstID)=backupSecondID;
    r.weight=countPathWeight(r.path);
    return r;
}

routeSA sa::turnAroundArc(routeSA r){
    int firstID=1+rand()%(r.path.size()-3);
    int secondID=firstID;
    while(secondID <= firstID){
        secondID=2+rand()%(r.path.size()-3);
    }
    routeSA r_changed;
    int i=0;
    while(i < firstID){
        r_changed.path.push_back(r.path[i++]);
    }
    for(i=secondID;i>=firstID;i--){
        r_changed.path.push_back(r.path[i]);
    }
    i=secondID+1;
    while(i < (int)r.path.size()){
        r_changed.path.push_back(r.path[i++]);
    }
    r_changed.weight=countPathWeight(r_changed.path);
    return r_changed;
}

bool sa::toAcceptRandomized(int weight){
//wzór: min{1,exp(-(f(x)-f(x0))/Ti)} -> min{1,exp(currentWeight-weight)/currentTemp)}
//ale w symulowanym wyżarzaniu im mniejsza waga typ lepiej co jest równoznaczne z weight=-f(x), więc:
//P(x0,x)=min{1,exp(weight-currentWeight)/currentTemp)}
    double probability = exp((double)(this->currentRoute.weight-weight)/this->temp);
//    cout << this->currentRoute.weight << "-" << weight << "=" << this->currentRoute.weight-weight << endl;
//probability=min(1,probability):
    if(probability>1){
        probability=1;
    }
    double randThrow = (double)rand()/RAND_MAX;
//    cout << probability << " > " << randThrow << " -> " << (probability > randThrow) << endl;
    return probability > randThrow;
}

bool sa::toAccept(routeSA r){
    if(r.weight < this->currentRoute.weight){
        saveBest(r);
        return true;
    }
    else if(toAcceptRandomized(r.weight)){
        return true;
    }
    return false;
}

void sa::saveBest(routeSA r){
    if(r.weight < this->bestRoute.weight){
        bestRoute=r;
    }
}


void sa::findPath(){
    int iter = 0;
    linuxtime time;
    this->currentRoute=generateRandomRoute();
    this->bestRoute=currentRoute;
    routeSA candidate;
    int iTime=1;
//    showPath(this->currentRoute.path);

    time.start();
//    while((temp > tempMin) && (iter++ < this->iterStop) && time.check() < this->maxSec){
//    while((iter++ < this->iterStop) && time.check() < this->maxSec){
    while(time.check() < this->maxSec){
//2 alternatywne strategie...ale obracanie łuków jest do kitu(skuteczność) w porównaniu do zamiany miast... :/
        candidate=switchCities(this->currentRoute);
//        candidate=turnAroundArc(this->currentRoute);
        if(toAccept(candidate)){
            this->currentRoute=candidate;
//            cout << "to accept: ";
//            showPath(candidate.path);
        }
        else{
//            cout << "to not accept: ";
//            showPath(candidate.path);
        }
        this->temp*=this->alpha;
//        cout << "temp: " << temp << " " << tempMin << endl;
//co sekundę wyświetla obecne najlepsze rozwiązanie
        if(time.check() > iTime){
            cout<<"w="<<this->bestRoute.weight<<endl;
            iTime++;
        }
    }

    cout<<"Best found: ";
    showPath(this->bestRoute.path);
}
