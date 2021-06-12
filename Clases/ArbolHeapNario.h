#ifndef PARCIAL2_ARBOLYHEAPNARIO_ARBOLHEAPNARIO_H
#define PARCIAL2_ARBOLYHEAPNARIO_ARBOLHEAPNARIO_H

#include <iostream>
#include <fstream>
#include "NodoHeap.h"
#include "Cola.h"
#include "Pila.h"

using namespace std;

/**
*En el arbol se guarda la raiz junto a las funciones para agregar y ordenar los NodoHeap.
* También se encarga del ordenamiento final y la generación del archivo de salida.
*/
template<class T>
class ArbolHeapNario {
private:
    int n; // Cantidad de Nodos Hijos que puede tener la raíz y cada Nodo

    NodoHeap<T> *raiz;

    Cola<NodoHeap<T>*> cola; // Cola donde se agregan los Nodos y se arman las relaciones Padre-Hijos
    Pila<NodoHeap<T>*> pila; // Pila que agrega cada valor de tal manera que se accedan a sus posiciones en el Arbol
    NodoHeap<T> *primer_pila; // primer elemento que se agrega a la pila, sin importar intercambios

    // Comparaciones y Swaps durante el armado de la Heap
    int comp_presort = 0;
    int swap_presort = 0;

    // Comparaciones y Swaps durante el ordenamiento final de la Heap
    int swap = 0;
    int comp = 0;

    // Cantidad inicial y final del texto fuente
    int size_inicial=0;
    int size_final=0;

public:
    ArbolHeapNario(int orden);

    void put(T dato);

    // Método de comparación para Armado de Heap
    void comparar(NodoHeap<T>* nodoNuevo,NodoHeap<T>* nodob );

    // Método de ordenamiento final de Heap
    void heapsort();

    //Método de generación de archivo de salida
    void print_arbol();
    void print_alfabetico(NodoHeap<T>* root);

};

/**
 *Constructor de Arbol
 * @tparam T
 * @param número de nodos
*/
template<class T>
ArbolHeapNario<T>::ArbolHeapNario(int orden) {
    n = orden;
    raiz = nullptr;
}

/**
 *Agregamos los datos al arbol: si es el primero, lo ponemos como raiz y
 * luego usamos la cola para agregar los hijos formando un arbol balanceado
 * @tparam T
 * @param dato a ingresar al Arbol
*/
template<class T>
void ArbolHeapNario<T>::put(T dato) {

    size_inicial++; // Esté la palabra repetida o no, se tiene en cuenta para el tamaño inicial del texto;

    if (raiz == nullptr) {
        raiz = new NodoHeap<T>(dato);
        cola.encolar(raiz);
        pila.push(raiz);
        primer_pila = raiz; // Aquí queda guardada la dirección del nodo que ingresa primero a la pila
        size_final++; // Aumento el contador de elementos finales

    }
    else {
        //-------------------------------------------------- DESCOMENTAR PARA CONSIDERAR REPETICIONES
        /*
        NodoHeap<T>* a = raiz->buscarDato(dato); // Corroboro si la palabra no fue agregada anteriormente
        if (a!= nullptr){ // La palabra ya fue agregada
            a->sumarRepeticion();
            //Aumento en 1 la variable "repeticiones" del Nodo que contiene el dato y
            // no se agrega al arbol ni se tiene en cuenta en los contadores del tamaño del texto

        }
        else{
            // Si la palabra no está repetida, ingresa al Arbol y se tiene en cuenta
            // para el tamaño final del text
            */
        // -------------------------------------------------------------------------------------------


            size_final++;

            NodoHeap<T> *aux = cola.verFrente(); // Se necesita el Nodo Padre actual que todavía puede tener Nodos Hijos
            NodoHeap<T> *nodoNuevo = new NodoHeap<T>(dato); // Puntero a NodoHeap que contiene el dato ingresado

            comparar(nodoNuevo, aux); // Realiza la comparación entre ellos y recursivamente hacia la raíz del Arbol

            // El NodoHeap con el dato menor, se configura como hijo del NodoHeap que tenía el dato mayor
            aux->putHijo(nodoNuevo);
            nodoNuevo->setPadre(aux);

            cola.encolar(nodoNuevo);
            pila.push(nodoNuevo);

            // Si el tamaño del vector que contiene a los Nodos Hijos es igual a la cantidad de nodos permitidas
            // dicho Nodo Padre se descola, y ahora queda como primero el nuevo Nodo Padre a completar
            if(aux->getCantidadHijos() == n)
                cola.desencolar();

    }
}

/**
 * Genera un archivo de salida que cuenta con la list de palabras ordenadas alfabéticamente
 * junto con su cantidad de repeticiones y la cantidad de comparaciones y swaps realizadas
 * realizadas en el armado y ordenamiento de la Heap
 * @tparam T
 * @param punteros a NodoHeap que inician la comparación recursiva junto con punteros a los
 * parámetros comp y swap
*/
template<class T>
void ArbolHeapNario<T>::comparar(NodoHeap<T> *nodoNuevo, NodoHeap<T> *nodob) {
    int* c;
    int* s;
    c = &comp_presort;
    s = &swap_presort;
    nodoNuevo->comparar(nodob,c,s);//Es un metodo de NodoHeap
}

/**
 * Se realiza el ordenamiento final de la Heap ya armada
 * @tparam T
*/
template<class T>
void ArbolHeapNario<T>::heapsort() {
    int* c;
    int* s;
    c = &comp;
    s = &swap;
    // Mientras no quede solamente un NodoHeap en la Pila, puedo realizar comparaciones
    while(!(pila.size()==1)) {

        // Se toma el NodoHeap que actualmente es la raíz del arbol con el último NodoHeap Hijo
        // con el que se pueda comparar e intercambiar, y se intercambian, aumentando en 1 el
        // contador de intercambios del Arbol
        NodoHeap<T>* first = pila.first();
        NodoHeap<T>* temp = pila.peek();
        swap++;
        temp->swap_dato(first);
        //temp->swap_repeticion(first); --------------------DESCOMENTAR PARA CONSIDERAR REPETICIONES

        // Temp es ahora el último Nodo Hoja que puede ser considerado para comparaciones, pero
        // se activa su flag de desapilado y se quita de la Pila
        temp->setNoPila();
        pila.desapilar();

        // Teniendo la nueva raíz del Arbol, se procede a hacer las comparaciones con los
        // Nodos Hijos asociados a esa posición, modificando a través de punteros las variables
        // "comp" y "swap" correspondientes a estos movimientos durante el ordenamiento
        vector<NodoHeap<T>*> children = first->getHijos();
        first->comparar_sort(children,c,s);
    }
    // Una vez que se compararon los n-1 elementos de la pila, se termina de desapilar el último
    // elemento, activando el flag correspondiente y terminando con el ordenamiento
    pila.first()->setNoPila();
    pila.desapilar();
    cout << "El arbol esta ordenado alfabeticamente." <<endl;
}


/**
 * Le brindo el puntero de inicio al método de generación del archivo de
 * salida para que empiece imprimiendo el menor dato del Arbol
 * @tparam T
*/
template<class T>
void ArbolHeapNario<T>::print_arbol() {
    print_alfabetico(raiz);
}

/**
 * Genera un archivo de salida que cuenta con la list de palabras ordenadas alfabéticamente
 * junto con su cantidad de repeticiones y la cantidad de comparaciones y swaps realizadas
 * realizadas en el armado y ordenamiento de la Heap
 * @tparam T
 * @param puntero a raíz del Arbol
*/
template<class T>
void ArbolHeapNario<T>::print_alfabetico(NodoHeap<T> *root) {

    //Se va generando una cola con un recorrido por nivel del Arbol, iniciando por la raíz
    Cola<NodoHeap<T>*> aux;
    aux.encolar(root);

    //Se general el archivo de salida para poder ir agregando lo que sea necesario
    ofstream salida;
    string nombre = "Ordenado - n = " + to_string(n) + ".txt" ;

    salida.open(nombre.c_str(), ios::out);

    if(salida.fail()){
        cout<<"No se pudo generar el archivo."<<endl;
    }
    salida<<"--------------------------------------------------------------------------------"<<endl;
    salida<<"Lista de palabras ordenadas alfabeticamente"<<endl;

    salida<<"Cantidad de palabras del texto inicial: "<<size_inicial<<". "<<endl;

    salida<<"Cantidad de nodos definidos: "<<n<<". "<<endl;
    salida<<"--------------------------------------------------------------------------------"<<endl;
    salida<<"Cant. de swaps para armado de Heap N-Aria: "<<swap_presort<<". "<<endl;
    salida<<"Cant. de comparaciones para armado de Heap N-Aria: "<<comp_presort<<". "<<endl;
    salida<<"--------------------------------------------------------------------------------"<<endl<<endl;

    while (!(aux.esVacia())){
        int size = aux.size();

        while(size>0){
            NodoHeap<T>* i_raiz = aux.desencolar();

            salida<<i_raiz->getDato()<<endl;
            cout<<i_raiz->getDato()<<endl;

            //-------------------------------------------------- DESCOMENTAR PARA CONSIDERAR REPETICIONES

            //if(i_raiz->getRepeticion()==1){
            //    cout<<" - No se repite. "<<endl;
            //    salida<<" - No se repite. "<<endl;
            //} else {
            //    cout<<" - "<<i_raiz->getRepeticion()<<" repeticiones. "<<endl;
            //    salida<<" - "<<i_raiz->getRepeticion()<<" repeticiones. "<<endl;
            //}
            // -------------------------------------------------------------------------------------------

            vector<NodoHeap<T>*> children = i_raiz->getHijos();
            if(!(children.empty())){
                for(int i = 0; i < children.size(); i++){
                    aux.encolar(children.at(i));
                }
                size--;
            } else{
                size--;
            }
        }
        salida<<endl<<endl;
    }
    //DESCOMENTAR PARA CONSIDERAR REPETICIONES
    //salida<<"--------------------------------------------------------------------------------"<<endl;
    //salida<<"Cantidad final de palabras (sin tener en cuenta repeticiones): "<<size_final<<". "<<endl;

    salida<<"--------------------------------------------------------------------------------"<<endl;
    salida<<"Cant. de swaps para sort de Heap: "<<swap<<". "<<endl;
    salida<<"Cant. de comparaciones para sort de Heap: "<<comp<<". "<<endl;
    salida<<"--------------------------------------------------------------------------------"<<endl;

    salida<<"Cant. de swaps TOTALES: "<<swap_presort + swap<<". "<<endl;
    salida<<"Cant. de comparaciones TOTALES: "<<comp_presort + comp<<". "<<endl;
    salida<<"--------------------------------------------------------------------------------"<<endl;

    cout<<"Cant. de swaps TOTALES: "<<swap_presort + swap<<". "<<endl;
    cout<<"Cant. de comparaciones TOTALES: "<<comp_presort + comp<<". "<<endl;

    salida.close();
}




#endif //PARCIAL2_ARBOLYHEAPNARIO_ARBOLHEAPNARIO_H