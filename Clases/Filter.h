#ifndef PARCIAL_3_FILTER_H
#define PARCIAL_3_FILTER_H

#include <iostream>
#include <bitset>
#include <vector>
#include "Arista.h"
#include "Vertice.h"
#include "bitmap.h"
#include "Pila.h"

using namespace std;

struct coordenada {
    int x,y;
    char type;
};

class Filter{
public:
    bitmap filtro;
    vector<Vertice> vertices; //va almacenando los nodos que encuentra durante el filtrado
    vector<Arista>  barreras;

    Filter();

    bool comparar(bitmap);

    void filtrado(int**);
    void filtrado_x(int**);
    Vertice encontrarPosiciones(bool, int, int, int **);
    void printMatriz(int**);


};


Filter::Filter(){
    for (int i = 0; i < filtro.M->size(); ++i) {
        filtro.M[i].flip();//inicializamos el filtro con 1s
    }

}

/*
 * Metodo que compara (and) el filtro con otro bitmap
 * @param aux bitmap a comparar
 * @return true si es igual, false si no lo es
 */
bool Filter::comparar(bitmap aux){ //funciona joya
    bool flag=true;
    bitset<3> equal;
    for(int i=0;i<3;i++) {
        equal = aux.M[i] & filtro.M[i];
        if (equal.count() != 3)
            flag = false;
    }
    return flag;
}

/*
 * Metodo que realiza el filtrado de conjutnos de 3x3 de 1s
 * @param campo: matriz de enteros que representa la imagen del campo
 */
void Filter::filtrado(int **campo){
    //el otro bitmap lleno de 1s ya es parámetro de la clase, "filtro"
    bitmap aux;
    int fila=1, columna=1;

    while(fila<19){ //es 99
        //inicio el bitmap aux de vuelta en cada fila nueva
        int k=0;
        for(int i = fila-1; i<=fila+1; i++ ){//FUNCIONA ASHEI
            bitset<3> baux;
            int p=2; //limite inverso del bitset
            for (int j = 0; j < 3; j++) { //ver diagrama de matriz en excel
                int s = campo[j][i];
                if(s==2)
                    s = 0;
                if(s==1)
                    baux.set(p);
                p--;
            }
            aux.M[k]=baux;
            k++;
        }

        while (columna<19){ // es 99
            if(comparar(aux)){
                //creo un vertice con las coordenadas de campo en donde aux se está fijando
                Vertice nodo = Vertice(fila,columna);
                //lo meto en el vector de vertices
                vertices.push_back(nodo);
                //paso a 0 esa parte de campo, solamente si coincide que son todos 1
                for (int i = fila-1; i <= fila + 1; i++) {  //empiezo desde la fila anterior y paro en la siguiente
                    for (int j = columna-1; j <= columna +1 ; j++) { //empiezo desde la fila anterior y paro en la siguiente
                        campo[j][i]=0;
                    }
                }
                for (int i = 0; i < aux.M->size(); ++i) {
                    aux.M[i].flip();
                }
                cout<<"Encontramos una mancha en ("<<fila<<","<<columna<<") Cambiamos a 0 el 3x3 en el campo y en el aux\n";
            }
            aux=aux<<1; //corremos 1 pos a la izq dejando la 3ra columna en 0
            int f=0;
            if((columna+2)<=19){ //es 99
                for(int k=fila-1;k<=fila+1;k++) {
                    int s = campo[columna+2][k];
                    if(s==2)
                        s = 0;
                    if(s==1)
                        aux.M[f].set(0);
                    f++;
                }
            }
            columna++;
        }
        columna = 1; //resetea de vuelta a columna 1 para ubicar correctamente el aux en 3*3
        fila++;
    }
    cout<<"\nMatriz luego de filtrado de manchas"<<endl;
    printMatriz(campo);
}


/*
 * Metodo que filtra las x de la matriz campo
 * @param campo: matriz de enteros que representa la imagen del campo
 */
void Filter::filtrado_x(int **campo) {//barrido de la matriz para ver las x. Es una verguenza
    int size=0;
    vector<coordenada> posiciones;

    for (int i = 0; i < 20; ++i) { //es 100
        for (int j = 0; j < 20; ++j) { //es 100
            if(campo[j][i] == 2 && posiciones.empty()){
                Vertice inicio, final;
                inicio.set_xy(j,i);
                campo[j][i] = 0;
                if(campo[j+1][i]){
                    final = encontrarPosiciones(true,j,i,campo); //true para indicar que se mueva por el eje x
                    size = final.get_x()-inicio.get_x();//calculamos la cantidad de x que encontramos
                }
                if(campo[j][i+1]) {
                    final = encontrarPosiciones(false, j, i, campo); //false para indicar que se mueva por el eje y
                    size = final.get_y()-inicio.get_y();//calculamos la cantidad de x que encontramos
                }
                if(size>=3){//deben ser 4 o mas x para considerarla barrera
                    j=final.get_x();
                    i=final.get_y();
                    Arista barrera = Arista(inicio,final);
                    barreras.push_back(barrera);
                }
            }
        }
    }
    cout<<"\nMatriz luego de filtrado de barreras"<<endl;
    printMatriz(campo);
    cout<<"\n----------------------------------\n";
}

/*
 * Metodo auxiliar para el filtrado de las x. Encuentra en que direccion estan las x que quedan
 * @param side: true si avanzamos hacia la derecha, false si lo hacemos para abajo
 * @param j: indica la columna de la 1ra x
 * @param i: indica la fila de la 1ra x
 * @param campo: matriz de enteros que representa la imagen del campo
 * @return Vertice con las coordenadas de la ultima x encontrada en esa barrera
 */
Vertice Filter::encontrarPosiciones(bool side, int j, int i,int **campo){
    Vertice final;
    bool flag=true;
    int posx,posy;
    if(side){//nos movemos por el eje x
        while(flag){
            j++;
            if(campo[j][i]==2 && j!=20){
                campo[j][i]=0;
                posx=j;
                posy=i;
            }
            else
                flag=false;
        }
    }
    else{ // nos movemos por el eje y
        while(flag){
            i++;
            if(campo[j][i]==2 && i!=20){
                campo[j][i]=0;
                posx=j;
                posy=i;
            }
            else
                flag=false;
        }
    }

    final.set_xy(posx,posy);

    return final;
}

/*
 * Metodo para imprimir la matriz campo
 * @param campo: matriz de enteros que representa la imagen del campo
 */
void Filter::printMatriz(int **campo) {
    for(int i=0;i<20;i++){
        cout<<endl;
        for(int j=0;j<20;j++)
            cout<<campo[j][i]<<" ";
    }
    cout<<endl;
}


#endif //PARCIAL_3_FILTER_H