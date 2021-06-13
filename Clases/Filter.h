#ifndef PARCIAL_3_FILTER_H
#define PARCIAL_3_FILTER_H

#include <iostream>
#include <bitset>
#include "conjunto.h"
#include "bitmap.h"

using namespace std;

class Filter{
public:
    bitmap filtro;

    Filter();

    bool comparar(bitmap);

    void filtrado(int**);
};

Filter::Filter(){
    for (int i = 0; i < filtro.M->size(); ++i) {
        filtro.M[i].flip();
    }
//    this->filtro=filtro;
    filtro.print();

}

bool Filter::comparar(bitmap aux){
    bool flag=true;
    bitset<3> equal;
    for(int i=0;i<3;i++) {
        equal = aux.M[i] & filtro.M[i];
        if (equal.count() != 3)
            flag = false;
    }
    return flag;
}

void Filter::filtrado(int **campo){
//    bool comparacion;
    int fila=0, columna=3;
    bitmap aux;
    for (int i = 0; i < 3; ++i) {//inicializamos el bitmap auxilizar. Cuidado porque se recorren re raro los bitmaps
        int p=0; //limite inverso
        for (int j = 2; j <= 0; --j) {
            aux.M[i].set(p)=campo[i][j];
            p++;
        }
    }

    while(fila<99 && columna<99){
        if(comparar(aux)){
            //TODO array de posiciones y struct, poner todo en 0
        }
        aux=aux<<1; //corremos 1 pos a la izq dejando la 3ra columna en 0
        for(int k=0;k<3;k++) {
            aux.M[2].set(k)=campo[k][columna];
        }
        columna++;
    }
}

#endif //PARCIAL_3_FILTER_H
