#include "genetic.h"

bool compareRoutes(route firstRoute, route secondRoute){
    return firstRoute.weight < secondRoute.weight;
}

genetic::genetic(graph *gr, int sizeOfPopulation, int generationsAmount, int mixMutationsPerGen, int combineMutationsPerGen){
    srand (time(NULL));
    this->gr=gr;
    this->sizeOfPopulation = sizeOfPopulation;
    this->generationsAmount = generationsAmount;
    this->mixMutationsPerGen = mixMutationsPerGen;
    this->combineMutationsPerGen = combineMutationsPerGen;
    for(int i=1;i<this->gr->verticesAmount;i++){
        this->citiesDefault.push_back(i);
    }
}

void genetic::showPath(vector <int>path){
    cout << path[0];
    if((int)path.size() > 1){
        for(int i=1;i<(int)path.size();i++){
            cout << " -> " << path[i];
        }
    }
    cout << endl;
    cout << "finalWeight=" << countPathWeight(path) << endl;
}

int genetic::countPathWeight(vector <int>path){
    int lastCity=0;
    int weightSum=0;
    for(int i=0;i<(int)path.size();i++){
        weightSum+=this->gr->cities[lastCity][path[i]];
        lastCity=path[i];
    }
    weightSum+=this->gr->cities[lastCity][0];
    return weightSum;
}

void genetic::printPopulation(vector <route>population){
    for(int i=0;i<(int)population.size();i++){
        showPath(population[i].path);
    }
}

route genetic::generateRandomRoute(){
    vector <int>vertices=this->citiesDefault;
    vector <int>path;
    int verId;
    path.push_back(0);
    while(vertices.size()>0){
        verId=rand()*100%vertices.size();
        path.push_back(vertices[verId]);
        vertices.erase(vertices.begin()+verId);
    }
    path.push_back(0);
    return route{path,countPathWeight(path)};
}

route genetic::combineRoutes(vector <int>path, vector <int>secondPath){
    int halfRoutLength=ceil(path.size()/2);
    while(path.size()>halfRoutLength){
        path.pop_back();
    }
    while(secondPath.size()>0){
        if(!(find(path.begin(), path.end(),secondPath[0]) != path.end())){
            path.push_back(secondPath[0]);
        }
        secondPath.erase(secondPath.begin());
    }
    path.push_back(0);
    return route{path,countPathWeight(path)};
}

route genetic::mixRoute(vector <int>path){
    int firstID=1+rand()%(path.size()-2);
    int secondID=firstID;
    while(secondID == firstID){
        secondID=1+rand()%(path.size()-2);
    }
    int backupSecondID=path[secondID];
    path.at(secondID)=path[firstID];
    path.at(firstID)=backupSecondID;
    return route{path,countPathWeight(path)};
}

void genetic::findPath(){
//intit population
    vector <route>population;
    for(int i=0;i<(int)this->sizeOfPopulation;i++){
//hmm no w sumie nic się nie powinno stać jeśli nie będę pomijał powtórzeń
//        if(!(find(population.begin(), population.end(),rt) != population.end())){
//        route rt=generateRandomRoute();
//            i--;
//            continue;
//        }
        population.push_back(generateRandomRoute());
    }

//mutating within generations
    for(int i_generation=0;i_generation<generationsAmount;i_generation++){

//mix route mutation
        for(int i_mixMutation=0;i_mixMutation<this->mixMutationsPerGen;i_mixMutation++){
            population.push_back(mixRoute(population[rand()%this->sizeOfPopulation].path));
        }

//combine routes mutation
        for(int i_combineMutation=0;i_combineMutation<this->combineMutationsPerGen;i_combineMutation++){
            int firstID = rand() % this->sizeOfPopulation;
            int secondID = firstID;
            while(secondID == firstID){
                secondID = rand() % this->sizeOfPopulation;
            }
            population.push_back(combineRoutes(population[firstID].path,population[secondID].path));
        }

//sort and remove worst results
        sort(population.begin(), population.end(), compareRoutes);
        while(population.size()>this->sizeOfPopulation){
            population.pop_back();
        }
    }

    //finalPrint
//    printPopulation(population);

    cout << "bestSolution:" << endl;
    showPath(population[0].path);
}
