#ifndef GRAPH_H
#define GRAPH_H

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;



class graph{
public:
    vector<vector<int>> cities;



    int edgesAmount, verticesAmount, startVerticle, endVerticle;
    string filename;
    graph(string filename);

    ~graph();

    bool file_read_line(ifstream &file, int tab[], int size);

    void sterna_file_read_graph(string filename);

    void file_read_graph(string filename);

    void showMatrix();

    void display();

    void showFileData();

    int vecToCity(int vecNumber);

    int cityToVec(int cityNumber);

    int getVerticesAmount();
};
#endif // GRAPH_H
