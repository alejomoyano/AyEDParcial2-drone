#ifndef PARCIAL_3_GRAFO_H
#define PARCIAL_3_GRAFO_H

#include "Vertice.h"
#include "Arista.h"
#include "Filter.h"
#include "Cola.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <iomanip>
#include <cmath>
#define INFI  999

using namespace std;

class Grafo{
public:
    vector<vector<float>> grafo;
    vector<Arista> barreras;
    vector<Vertice> vertices;
    vector<Vertice> cicloH;
    float distancia=0;

    void grafos (vector<Vertice>*, vector<Arista>*b);
    void set_grafo();
//    void busquedaAmplitud();
    void busqueda();
};
/*
 * Metodo que setea los campos de la calse
 * @param a: vector con los vertices
 * @param b: vector con las aristas
 */
void Grafo::grafos(vector<Vertice>* a, vector<Arista>*b) {
    //copio el contenido de los nodos y agrego el punto de salida del drone
    Vertice inicio_drone = Vertice(1,1);
    vertices.push_back(inicio_drone);
    for (int k = 0; k < a->size(); ++k) {
        if(!(inicio_drone.igual(a->at(k)))){
            vertices.push_back(a->at(k));
        }
    }

    //copio el contenido de las barreras de x
    for (int z = 0; z < b->size(); ++z) {
        barreras.push_back(b->at(z));
    }

    //inicializo grafo con los pesos en 0
    int size = vertices.size();
    vector<float> aux;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            aux.push_back(0);
        }
        grafo.push_back(aux);
        aux.clear();
    }
}

/*
 * Metodo que setea la matriz de adyacencia
 */
void Grafo::set_grafo() {
    int size= vertices.size();
    int bar = barreras.size();
    //doble for porque tengo que comparar todos con todos
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {

            if(grafo[i][j]==0){ //evito la comparación si el nodo tiene INFI o algún valor
                if(i==j){ //consigo mismo, es infinita la distancia porque no tenemos nodos autoreferenciados
                    grafo.at(i).at(j) = INFI;
                }else{

                    Arista posible = Arista(vertices.at(i),vertices.at(j)); //considero la posible arista
                    int flag = 0; //me avisa si se cruzó con alguna de las barreras
                    for (int k = 0; k < bar; ++k) { //recorro barreras
                        if (posible.intersecta(barreras.at(k))){
                            flag=1;
                        }
                    }
                    if(flag==0){ //si no hubo intersección, pongo en la relacion correspondiente el peso de la arista
                        grafo.at(i).at(j) = posible.get_dist();
                    }
                }
            }
        }
    }
    cout<<endl<<endl;
    cout<<"------------------------------------------------------------------------------------------------"<<endl;
    cout<<"Matriz de Adyacencia: "<<endl<<endl;
    cout<<"       ";
    for(int h = 0; h < grafo.size(); h++){
        cout << setw(8) << h;
    }
    cout<<endl<<"------------------------------------------------------------------------------------------------"<<endl;
    for (int i = 0; i < grafo.size(); i++)
    {
        cout<<setw(4) << i<<"  |";
        for (int j = 0; j < grafo[i].size(); j++)
        {
            cout << setw(8) << grafo[i][j];
        }
        cout << endl<<endl;
    }
    cout<<"------------------------------------------------------------------------------------------------"<<endl;
}


/*
 * Metodo donde se aplica la busqueda de amplitud
 */
//void Grafo::busquedaAmplitud() {
//    Cola<Vertice> q; //va a guardar los vertices que entren en el ciclo(siempre los q estan a menor distancia entre ellos)
//    vertices.front().setMark(); // el primero es el 1,1. Se empieza por ese siempre
//    q.encolar(vertices.front());
//    cicloH.push_back(vertices.front()); //en este vector queda armado el menor ciclo Hamiltoneano
//    int k=0, f=0;
//    while(!q.esVacia()) {
//        for (int i = 0; i < vertices.size(); i++) { //esto es para saber que indice poner en la busqueda en la matriz
//            if (q.verFrente().igual(vertices[i])) {
//                f = i;
//            }
//        }
//        for (int g = 1; g < vertices.size(); g++) { //busco el menor de la fila(q no sea 0)
//            if (grafo[f][g]!=0 && grafo[f][g]!=INFI && !vertices[g].isMarked()) {
//                if (grafo[f][g] < grafo[f][k]) k = g;
//
//            }
//        }
//        if(!vertices[k].isMarked()) {
//            vertices[k].setMark(); //k va a ser el indice del vertice a menor distancia del primer vertice
//            q.encolar(vertices[k]);
//            cicloH.push_back(vertices.at(k));
//            distancia = distancia + grafo.at(f).at(k); //distancia que recorre el menor cicloH
//        }
//        q.desencolar();
//
//    }
//
//}

struct camino{
    vector<int> c; //contiene los indices de los vertices recorridos
    vector<bool> recorridos; //true si ya vio ese veritice
    double peso; //peso del camino
};

void Grafo::busqueda() {
    int counter=0;
    //Se va generando una cola con un recorrido por nivel de los vecinos del primer vertice
    Cola<camino> aux;
    camino inicio, ideal;
    ideal.peso=1000;
    for (int i = 0; i < vertices.size(); ++i) {//inicializamos el vector en false
        inicio.recorridos.push_back(false);
    }
    inicio.c.push_back(0);
    inicio.recorridos[0]=true;
    aux.encolar(inicio);
    int f=0; //indice de la fila de la matriz de adyacencias
    while (!(aux.esVacia())){

        camino i_camino = aux.desencolar();
        f=i_camino.c[i_camino.c.size()-1]; //para que cambie el indice de la matriz, antes no cambiaba
        for (int g = 1; g < vertices.size(); g++) {
            if (grafo[f][g]!=0 && grafo[f][g]!=INFI && i_camino.recorridos[g]!=1) {
                camino caux = i_camino;
                caux.c.push_back(g);
                caux.recorridos[g]=true;
                caux.peso += grafo[f][g];

                if(caux.c.size()==vertices.size()){
                    if(grafo[g][0]!=0 && grafo[g][0]!=INFI){
                        counter++;
                        if(ideal.peso>caux.peso)
                            ideal=caux;
                    }
                }
                else{
                    aux.encolar(caux);
                }
            }
        }
    }
        printf("El ciclo Hamiltoniano mas corto detectado tiene un peso de: %f.\n Cantidad de caminos encontrados: %i",ideal.peso,counter);
}




#endif //PARCIAL_3_GRAFO_H
