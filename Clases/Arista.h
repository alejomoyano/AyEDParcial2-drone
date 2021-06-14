#ifndef PARCIAL_3_ARISTA_H
#define PARCIAL_3_ARISTA_H

#include "Vertice.h"

using namespace std;


class Arista{
private:
    Vertice inicio;
    Vertice final;
    int dist;

public:
    Arista();
    Arista(Vertice i, Vertice f);

    Vertice get_inicio();
    Vertice get_final();
    int get_dist();

    void set_inicio(Vertice aux);
    void set_final(Vertice aux);
    void set_dist(int aux);

};

Arista::Arista() {
    inicio = Vertice();
    final = Vertice();
    dist = 0;
}

Arista::Arista(Vertice i, Vertice f) {
    inicio = i;
    final = f;
    dist = i.calc_dist(f);

}

Vertice Arista::get_inicio() {
    return inicio;
}

Vertice Arista::get_final() {
    return final;
}

int Arista::get_dist() {
    return dist;
}

void Arista::set_inicio(Vertice aux) {
    inicio = aux;
}

void Arista::set_final(Vertice aux) {
    final = aux;
}

void Arista::set_dist(int aux) {
    dist = aux;
}


#endif //PARCIAL_3_ARISTA_H
