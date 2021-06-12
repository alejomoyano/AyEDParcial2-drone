#include <iostream>
#include <fstream>

using namespace std;

int main() {
    string str;
    string line;
    ifstream myFile("Pic.txt");    // Archivo con la foto

    // Mientras siga habiendo una linea por procesar
    while (getline(myFile, line)) {
        for (int i = 0; i < line.length(); ++i) {
            line.at(i); //char en la posicion i, en el string
        }
    }

    myFile.close();
    return 0;
}
