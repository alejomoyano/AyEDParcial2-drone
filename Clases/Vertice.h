
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
    bool mark;

public:
    Vertice();
    Vertice (int x, int y);

    int get_x();
    int get_y();
    bool isMarked();

    void set_x(int aux);
    void set_y(int aux);
    void set_xy(int,int);
    void setMark();

    float calc_dist(Vertice aux);
    bool igual (Vertice aux);


};

Vertice::Vertice() {
    x = 0;
    y = 0;
    mark=0;
}

Vertice::Vertice(int x, int y) {
    this->x = x;
    this->y = y;
    mark=0;
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

float Vertice::calc_dist(Vertice aux) {
    int x1 = x;
    int y1 = y;
    int x2 = aux.get_x();
    int y2 = aux.get_y();

    float distancia = roundf(sqrt(abs(pow(x2-x1,2) + pow(y2-y1,2)))*100)/100;

    return distancia;
}

void Vertice::set_xy(int x, int y) {
    set_x(x);
    set_y(y);
}

bool Vertice::igual(Vertice aux) {
    int x1 = x;
    int y1 = y;
    int x2 = aux.get_x();
    int y2 = aux.get_y();

    if(x1 == x2 && y1 == y2){
        return true;
    }else{
        return false;
    }
}

bool Vertice::isMarked() {
    return mark;
}

void Vertice::setMark() {
    mark=1;
}


#endif //PARCIAL_3_VERTICE_H
