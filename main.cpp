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
    int** pic = new int*[20]; // Inicializamos la matriz que va a contener la imagen del campo. TODO iría 100
    for (int i = 0; i < 20; ++i)//iría 100
        pic[i] = new int[20];//iría 100

    ifstream myFile("Pic.txt"); //Archivo con la foto

    // Mientras siga habiendo una linea por procesar
    while (getline(myFile, line)) {

        for (int i = 0; i < line.length(); ++i) {// en este for generamos la matriz. Las x se representan con 2
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

    filtro.filtrado(pic); //filtrado de superficies a fumigar
    filtro.filtrado_x(pic); //filtrado de barreras

    vector<Vertice>* vertices = &filtro.vertices;
    vector<Arista>* barreras = &filtro.barreras;

    campo.grafos(vertices, barreras);
    campo.set_grafo();
    campo.busqueda();

    return 0;
}
