
#ifndef PARCIAL_3_VERTICE_H
#define PARCIAL_3_VERTICE_H
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

class Vertice{
private:
    int x;
    int y;

public:
    Vertice();
    Vertice (int x, int y);

    int get_x();
    int get_y();

    void set_x(int aux);
    void set_y(int aux);

    int calc_dist(Vertice aux);


};

Vertice::Vertice() {
    x = 0;
    y = 0;
}

Vertice::Vertice(int x, int y) {
    this->x = x;
    this->y = y;
}

int Vertice::get_x() {
    return x;
}

int Vertice::get_y() {
    return y;
}

void Vertice::set_x(int aux) {
    x = aux;
}

void Vertice::set_y(int aux) {
    y = aux;
}

int Vertice::calc_dist(Vertice aux) {
    int x1 = x;
    int y1 = y;
    int x2 = aux.get_x();
    int y2 = aux.get_y();

    float distancia = sqrt(abs(pow(x2-x1,2) + pow(y2-y1,2)));

    return round(distancia); //supuestamente no se permitian decimales, los pesos tenian que ser enteros
}


#endif //PARCIAL_3_VERTICE_H
