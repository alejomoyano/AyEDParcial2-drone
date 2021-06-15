#ifndef PARCIAL_3_ARISTA_H
#define PARCIAL_3_ARISTA_H

#include "Vertice.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cmath>

using namespace std;


class Arista{
private:
    Vertice inicio;
    Vertice final;
    float dist;

public:
    Arista();
    Arista(Vertice i, Vertice f);

    Vertice get_inicio();
    Vertice get_final();
    float get_dist();

    void set_inicio(Vertice aux);
    void set_final(Vertice aux);
    void set_dist(float aux);

    bool intersecta(Arista aux);
    bool mismo_segmento(Vertice p, Vertice q, Vertice r);
    int orientacion(Vertice p, Vertice q, Vertice r);

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

float Arista::get_dist() {
    return dist;
}

void Arista::set_inicio(Vertice aux) {
    inicio = aux;
}

void Arista::set_final(Vertice aux) {
    final = aux;
}

void Arista::set_dist(float aux) {
    dist = aux;
}


bool Arista::mismo_segmento(Vertice p, Vertice q, Vertice r) {
    int p_x = p.get_x();
    int p_y = p.get_y();
    int q_x = q.get_x();
    int q_y = q.get_y();
    int r_x = r.get_x();
    int r_y = r.get_y();

    if (q_x <= max(p_x, r_x) && q_x >= min(p_x, r_x) && q_y <= max(p_y, r_y) && q_y >= min(p_y, r_y)) {
        return true;
    } else{
        return false;
    }
}

int Arista::orientacion(Vertice p, Vertice q, Vertice r) {

    int p_x = p.get_x();
    int p_y = p.get_y();
    int q_x = q.get_x();
    int q_y = q.get_y();
    int r_x = r.get_x();
    int r_y = r.get_y();

    int val = (q_y - p_y) * (r_x - q_x) - (q_x - p_x) * (r_y - q_y);

    if (val == 0) return 0;  // colinear

    if(val > 0) return 1;// clock or counterclock wise
    else return 2;
}


bool Arista::intersecta(Arista aux) {
    Vertice p1 = this->inicio;
    Vertice q1 = this->final;
    Vertice p2 = aux.inicio;
    Vertice q2 = aux.final;

    // Encuentra las 4 orientaciones necesarias para casos generales y excepciones
    int o1 = orientacion(p1, q1, p2);
    int o2 = orientacion(p1, q1, q2);
    int o3 = orientacion(p2, q2, p1);
    int o4 = orientacion(p2, q2, q1);

    // Caso general
    if (o1 != o2 && o3 != o4)
        return true;

    // Casos especiales
    // p1, q1 y p2 son colineales and p2 está en el segmento p1q1
    if (o1 == 0 && mismo_segmento(p1, p2, q1)) return true;

    // p1, q1 y q2 son colineales y q2 está en el segmento p1q1
    if (o2 == 0 && mismo_segmento(p1, q2, q1)) return true;

    // p2, q2 y p1 son colineales y p1 está en el segmento p2q2
    if (o3 == 0 && mismo_segmento(p2, p1, q2)) return true;

    // p2, q2 y q1 son colineales y q1 está en el segmento p2q2
    if (o4 == 0 && mismo_segmento(p2, q1, q2)) return true;

    return false; // No se obtiene ningún caso anterior
}


#endif //PARCIAL_3_ARISTA_H
