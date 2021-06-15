#include <iostream>
#include <fstream>
#include <bitset>
#include "Clases/Filter.h"
#include "Clases/bitmap.h"
#include "Clases/Vertice.h"

using namespace std;

int main() {
    int j=0;
    string str;
    string line;
    Filter filtro;
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
                cout<<pic[i][j];
            }
            else{
                int casted = (int)pixel-48;
                pic[i][j]= casted;
                cout<<pic[i][j];
            }
        }
        cout<<endl;
        j++;
    }

    myFile.close();

    //la matriz queda vacía y no se pasa como parámetro a las otras funciones
    filtro.filtrado(pic);
    filtro.filtrado_x(pic);


    return 0;
}
