#ifndef ALGORITMOS_TP1_PILA_H
#define ALGORITMOS_TP1_PILA_H

#include "Nodo.h"

/**
 * Clase que implementa una Pila generica, ya que puede
 * almacenar cualquier tipo de dato T
 * @tparam T cualquier tipo de dato
 */
template<class T>
class Pila {
private:
    Nodo<T> *inicio;
public:
    Pila();

//    ~Pila();  El destructor genera problemas si no existe un constructor por copia

    void push(T dato);

    int size();

    bool esVacia();

    T first();

    T peek();

    T pop();

    void desapilar();

};


/**
 * Constructor de la clase Pila
 * @tparam T
 */
template<class T>
Pila<T>::Pila() {
    inicio = NULL;
}


///**
// * Destructor de la clase Pila, se encarga de liberar la memoria de todos los nodos
// * utilizados en la Pila
// * @tparam T
// */
//template<class T>
//Pila<T>::~Pila() {
//   while (!esVacia()) {
//       pop();
//   }
//}


/**
 * Inserta un dato en la pila
 * @tparam T
 * @param dato  dato a insertar
 */
template<class T>
void Pila<T>::push(T dato) {
    Nodo<T> *aux = new Nodo<T>(dato, inicio);
    inicio = aux;
}

/**
 * Devuelve el tamaño de la pila
 * @tparam T
 * @return cantidad de elementos en la Pila
 */
template<class T>
int Pila<T>::size() {
    if(esVacia()){return 0;}
    Nodo<T> *aux = inicio;
    int cont = 0;

    while (aux != NULL) {
        cont++;
        aux = aux->getNext();
    }

    return cont;
}

/**
 * Responde si la pila se encuentra Vacía
 * @tparam T
 * @return true si es vacía
 */
template<class T>
bool Pila<T>::esVacia() {
    return inicio == NULL;
}

/**
 * Devuelve el primer dato almacenado en la pila
 * @tparam T
 * @return primer dato que fue almacenado en la pila
 */
template <class T>
T Pila<T>::first() {
    if(esVacia()){return 0;}
    Nodo<T> *aux = inicio;

    while (aux->getNext() != NULL) {
        aux = aux->getNext();
    }
    return aux->getDato();
}

/**
 * Devuelve el último dato almacenado en la pila, sin desapilarlo
 * @tparam T
 * @return último dato agregado a la Pila
 */
template<class T>
T Pila<T>::peek() {
    if (esVacia())
        throw 1;

    return inicio->getDato();
}

/**
 * Obtener el dato de la pila
 * @tparam T
 * @return dato almacenado en el nodo
 */
template<class T>
T Pila<T>::pop() {
    if (esVacia())
        throw 1;

    T dato = inicio->getDato();
    Nodo<T> *aux = inicio;

    inicio = inicio->getNext();
    delete aux;

    return dato;
}

/**
 * Desapila el último dato ingresado a la Pila
 * @tparam T
 */
template<class T>
void Pila<T>::desapilar() {
    if (esVacia())
        throw 1;

    Nodo<T> *aux = inicio;
    inicio = inicio->getNext();
    delete aux;

}


#endif //ALGORITMOS_TP1_PILA_H