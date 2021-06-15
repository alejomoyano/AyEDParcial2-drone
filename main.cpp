#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include "Clases/Filter.h"
#include "Clases/bitmap.h"
#include "Clases/Vertice.h"
#include "Clases/Grafo.h"

using namespace std;

int main() {
    int j=0;
    string str;
    string line;
    Filter filtro;
    Grafo campo;
    int** pic = new int*[20]; //iría 100
    for (int i = 0; i < 20; ++i)//iría 100
        pic[i] = new int[20];//iría 100

    ifstream myFile("Pic.txt"); //Archivo con la foto

    // Mientras siga habiendo una linea por procesar
    while (getline(myFile, line)) {

        for (int i = 0; i < line.length(); ++i) { //generamos la matriz
            char pixel = line.at(i);
            if(pixel=='x' || pixel=='X') {//representamos las X con 2
                pic[i][j] = 2;
                cout<<pic[i][j]<<" ";
            }
            else{
                int casted = (int)pixel-48;
                pic[i][j]= casted;
                cout<<pic[i][j]<<" ";
            }
        }
        cout<<endl;
        j++;
    }

    myFile.close();

    filtro.filtrado(pic);
    filtro.filtrado_x(pic);
    vector<Vertice>* vertices = &filtro.vertices;
    vector<Arista>* barreras = &filtro.barreras;

    campo.grafos(vertices, barreras);
    campo.set_grafo();
/*
    Vertice a1 = Vertice(1,1);
    Vertice a2 = Vertice(6,16);
    Vertice b1 = Vertice(5,11);
    Vertice b2 = Vertice(8,11);

    Arista a = Arista(a1,a2);
    Arista b = Arista(b1,b2);

    cout<<a.intersecta(b)<<endl;
*/



    return 0;
}
