#ifndef ALGORITMOS_TP1_COLA_H
#define ALGORITMOS_TP1_COLA_H

#include "Nodo.h"

/**
 * Clase que implementa una Cola genérica, ya que puede
 * almacenar cualquier tipo de dato T
 * @tparam T cualquier tipo de dato
 */
template<class T>
class Cola {
private:
    Nodo<T> *frente;

    Nodo<T> *fondo;

public:
    Cola();

//    ~Cola();  El destructor genera problemas si no existe constructor por copia

    int size();

    bool esVacia();

    void encolar(T dato);

    T verFrente();

    T desencolar();

    void vaciar();

};


/**
 * Constructor de la clase Cola
 * @tparam T
 */
template<class T>
Cola<T>::Cola() {
    fondo = frente = NULL;
}

///**
// * Destructor de la clase Cola, se encarga de liberar la memoria de todos los nodos
// * utilizados en la Cola
// * @tparam T
// */
//template<class T>
//Cola<T>::~Cola() {}

/**
 * Devuelve la cantidad de elementos de la Cola
 * @tparam T
 * @return cantidad de elementos
 */
template<class T>
int Cola<T>::size() {

    if(esVacia()){return 0;}
    Nodo<T> *aux = frente;
    int cont = 0; //para tener en cuenta el de fondo que lo salta
    while (aux != fondo) {
        cont++;
        aux = aux->getNext();
    }
    cont++;
    return cont;


}

/**
 * Responde si la Cola se encuentra Vacía
 * @tparam T
 * @return true si es vacía
 */
template<class T>
bool Cola<T>::esVacia() {
    return frente == NULL;
}

/**
 * Inserta un dato en la Cola
 * @tparam T
 * @param dato  dato a insertar
 */
template<class T>
void Cola<T>::encolar(T dato) {
    Nodo<T> *aux = new Nodo<T>(dato);

    if (fondo == NULL && frente == NULL) {  // La cola está vacía
        frente = fondo = aux;
    } else {
        fondo->setNext(aux);
        fondo = aux;
    }
}

/**
 * Muestra el primer dato de la Cola sin desencolarlo
 * @tparam T
 * @return primer dato en la Cola
 */
template<class T>
T Cola<T>::verFrente() {
    if(esVacia())
        throw 404;
    return frente->getDato();
}


/**
 * Obtener el dato de la Cola
 * @tparam T
 * @return dato almacenado en el nodo
 */
template<class T>
T Cola<T>::desencolar() {

    if (esVacia())
        throw 1;

    // Si no es vacia.
    T tmp;
    Nodo<T> *aux = frente;

    frente = frente->getNext();
    tmp = aux->getDato();
    delete aux;

    if (frente == NULL)
        fondo = frente;

    return tmp;
}

/**
 * Vaciamos y liberamos memoria.
 * @tparam T
 */
template<class T>
void Cola<T>::vaciar() {

    while(frente != NULL)
        desencolar();

}

#endif //ALGORITMOS_TP1_COLA_H