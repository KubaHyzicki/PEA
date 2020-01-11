#include "graph.h"

graph::graph(string filename){
    this->filename=filename;
    this->file_read_graph(filename);
}

graph::~graph(){    //usunięte, jako iż Vector sam dba o zwalnianie pamięci
//    int vecWidth=this->verticesAmount;
//    for(int i=0;i<this->cities.size();i++){
//        for(int i2=0;i2<this->cities[i].size();i2++){
//            delete[] this->cities[i][i2];
//        }
//        delete[] this->cities[i];
//    }
//    delete[] this->cities;
}

//pierwsza wersja ładowania grafu, format niezgodny z tym w opisie projektu(funkcja pomocnicza)
bool graph::file_read_line(ifstream &file, int tab[], int size){
    string s;
    getline(file, s);

    if(file.fail() || s.empty())
        return(false);

    istringstream in_ss(s);

    for(int i = 0; i < size; i++) {
        in_ss >> tab[i];
        if(in_ss.fail())
        return(false);
    }
    return(true);
}

//pierwsza wersja ładowania grafu, format niezgodny z tym w opisie projektu
void graph::sterna_file_read_graph(string file_name) {
    ifstream file;
    int tab[4];
    file.open(file_name.c_str());

    int edge_start, edge_end, edge_weight;

    if(file.is_open()) {
        if(file_read_line(file, tab, 4)) {
            this->edgesAmount = tab[0];
            this->verticesAmount = tab[1];
            this->startVerticle = tab[2];
            this->endVerticle = tab[3];
//create vector
            for(int i = 0;i < edgesAmount; i++){
                this->cities.push_back(vector <int>());
                for(int i2 = 0;i2 < edgesAmount; i2++){
                    this->cities[i].push_back(0);
                }
            }
//init vector
            for(int i = 0; i < this->edgesAmount; i++) {
                if(file_read_line(file, tab, 3)) {
                    edge_start = tab[0];
                    edge_end = tab[1];
                    edge_weight = tab[2];
                    this->cities[this->cityToVec(edge_start)][this->cityToVec(edge_end)]=edge_weight;
                }
                else {
                    cout << "File error - READ EDGE" << endl;
                    break;
                }
            }
        }
        else{
            cout << "File error - READ INFO" << endl;
            file.close();
        }
    }
    else
        cout << "File error - OPEN" << endl;
}

void graph::file_read_graph(string filename){
    ifstream file;
    string line;
    int weight;

    file.open(filename.c_str());

    if(file.is_open()){
        getline(file,line);
        istringstream in_ss(line);
        in_ss >> this->verticesAmount;
        //create vector
        for(int i = 0;i < this->verticesAmount; i++){
            this->cities.push_back(vector <int>());
            for(int i2 = 0;i2 < this->verticesAmount; i2++){
                this->cities[i].push_back(0);
            }
        }
        //init vector
        for(int vecNr=0; vecNr < this->verticesAmount;vecNr++){
            getline(file, line);
            istringstream in_ss(line);
            for(int i = 0; i < this -> verticesAmount; i++) {
                in_ss >> weight;
                this->cities[vecNr][i]=weight;
            }
        }
        //nadpisz odległości wierzchołków do nich samych(na wszelki wypadek)
        for(int i = 0;i < this->verticesAmount; i++){
            this->cities[i][i]=0;
        }
    }

    file.close();

}

void graph::display(){
    //oprawa graficzna
    cout<<"Display graph:"<<endl;
    int vecWidth=this->verticesAmount;
    int len;
    for(int i=0;i<vecWidth;i++){
        for(int i2=0;i2<vecWidth;i2++){
            len=to_string(this->cities[i][i2]).length();
            cout << cities[i][i2];
            for(int i3=0;i3<5-len;i3++) cout << " ";
        }
        cout << endl;
    }
}

//wyjaśnienie następnych 2 metod: wszystkie tablice/wektory mają numerację zawsze od 0, miasta od 1
int graph::vecToCity(int vecNumber){
    return vecNumber+1;
}

int graph::cityToVec(int cityNumber){
    return cityNumber-1;
}

void graph::showFileData(){
    string line;
    ifstream file (this->filename);
    if (file.is_open())
    {
      while ( getline (file,line) )
      {
        cout << line << endl;
      }
      file.close();
    }
}

int graph::getVerticesAmount(){
    return this->verticesAmount;
}
