#include <iostream>
#include <fstream>
#include <bitset>
#include "Clases/Filter.h"
#include "Clases/bitmap.h"

using namespace std;

int main() {
    int j=0;
    string str;
    string line;

//    bitmap mapa;
//    Filter filtro=Filter(mapa);
     Filter filtro;

    int** pic = new int*[100];
    for (int i = 0; i < 100; ++i)
        pic[i] = new int[100];

    ifstream myFile("Pic.txt"); //Archivo con la foto

    // Mientras siga habiendo una linea por procesar
    while (getline(myFile, line)) {

        for (int i = 0; i < line.length(); ++i) { //generamos la matriz
            char pixel = line.at(i);
            if(pixel=='x' || pixel=='X') {//respresentamos las X con 2
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
    return 0;
}
