#ifndef ALGORITMOS_TP2_NODO_H
#define ALGORITMOS_TP2_NODO_H

#include <iostream>
#include <vector>


using namespace std;

/**
 * Clase que implementa un tipo de Nodo específico, que puede
 * almacenar cualquier tipo de dato T.
 * @tparam T
 */
template<class T>
class NodoHeap {
private:
    T dato;

    //-------------------------------------------------- DESCOMENTAR PARA CONSIDERAR REPETICIONES
    // int repeticiones = 1; // Cada palabra correspondiente al nodo comienza con 1 repetición.
    //-------------------------------------------------------------------------------------------

    NodoHeap<T> *padre;

    vector<NodoHeap<T>*> hijos;

    bool nopila = false; // Flag para determinar, en el ordenamiento final, si ya está en su posición final

public:
    NodoHeap(T d);
    NodoHeap(const NodoHeap<T> &nh);

    // Métodos correspondientes al dato del Nodo
    T getDato(){return dato;};
    void setDato(T nuevo);

    //-------------------------------------------------- DESCOMENTAR PARA CONSIDERAR REPETICIONES
    //int getRepeticion();
    //void sumarRepeticion();
    //void setRepeticiones(int nuevo);
    //NodoHeap<T>* buscarDato(T c);
    //NodoHeap<T>* buscarDatoEnHijos(T t);
    //-------------------------------------------------------------------------------------------

    // Métodos correspondientes al Nodo Padre
    void setPadre(NodoHeap<T> *nodo) {padre = nodo;};
    NodoHeap<T>* getPadre() {return padre;};

    // Métodos correspondientes al vector de Nodos Hijos
    void putHijo(NodoHeap<T> *nodo);
    vector<NodoHeap<T>*> getHijos();
    int getCantidadHijos();

    // Métodos correspondientes al flag de Ordenamiento Final
    bool desapilado();
    void setNoPila();

    // Métodos de comparación entre Nodos
    void comparar(NodoHeap<T>* nodob, int* c, int* s);
    void comparar_sort(vector<NodoHeap<T>*> children, int* c, int*s);
    void swap_dato(NodoHeap<T>* nodob);

    //void swap_repeticion(NodoHeap<T>* nodob); -------------DESCOMENTAR PARA CONSIDERAR REPETICIONES


};

/**
 * Constructor. Inicializa el puntero a padre en null.
 * @tparam T
 * @param d
 */
template<class T>
NodoHeap<T>::NodoHeap(T d) {
    dato = d;
    padre = nullptr;
}

/**
 * Constructor por copia
 * @tparam T
 * @param puntero constante del cuál quiero extraer información
 */
template<class T>
NodoHeap<T>::NodoHeap(const NodoHeap<T> &nh) {
    //repeticiones = nh.repeticiones;
    dato = nh.dato;
    padre = nh.padre;
    hijos = nh.hijos;
}

/**
 * Reemplaza el dato de un nodo con otro valor nuevo
 * @tparam T
 * @param dato nuevo
 */
template<class T>
void NodoHeap<T>::setDato(T nuevo) {
    dato = nuevo;
}


/**
 * Suma en 1 la cantidad actual de repeticiones del dato
 * @tparam T

template<class T>
void NodoHeap<T>::sumarRepeticion() {
    repeticiones++;
}
*/

/**
 * Busca en un nodo dado el dato c, y si no lo encuentra
 * busca en su vector Hijos
 * @tparam T
 * @param dato a buscar
 * @return

template<class T>
NodoHeap<T> *NodoHeap<T>::buscarDato(T c) {
    if(dato == c){
        return this;
    } else {
        return this->buscarDatoEnHijos(c);
    }
}*/

/**
 * Funcion recursiva de busqueda
 * @tparam T
 * @param dato
 * @return dirección del Nodo que contiene ese dato (un puntero)

template<class T>
NodoHeap<T>* NodoHeap<T>::buscarDatoEnHijos(T t) {
    NodoHeap<T> *aux;
    for(int i=0; i<getCantidadHijos(); i++){
        NodoHeap<T>* a=hijos.at(i);
        aux = a->buscarDato(t);
        if(aux != nullptr)
            return aux;
    }
    return nullptr;
}*/

/**
 * Devuelve el valor actual de repeticiones de una palabra
 * @tparam T
 * @return cantidad

template<class T>
int NodoHeap<T>::getRepeticion() {
    return repeticiones;
}*/

/**
 * Método para swap de Nodos - modifica el valor de la variable "repeticiones"
 * @tparam T
 * @param dato nuevo

template<class T>
void NodoHeap<T>::setRepeticiones(int nuevo) {
    repeticiones = nuevo;
}*/

/**
 * Método para cambiar entre dos Nodos su variable "comp"
 * @tparam T
 * @param puntero a nodo con el que se quiere intercambiar

template<class T>
void NodoHeap<T>::swap_repeticion(NodoHeap<T> *nodob) {
    int aux = this->getRepeticion();
    this->setRepeticiones(nodob->getRepeticion());
    nodob->setRepeticiones(aux);
}*/

/**
 * Inserta un nuevo Nodo Hijo al vector
 * @tparam T
 * @param puntero al nodo que se quiere insertar
 */
template<class T>
void NodoHeap<T>::putHijo(NodoHeap<T> *nodo) {
    hijos.push_back(nodo);
}

/**
 * Devuelve el vector que contiene a los Nodos Hijos
 * @tparam T
 * @return vector
 */
template<class T>
vector<NodoHeap<T> *> NodoHeap<T>::getHijos() {
    return hijos;
}

/**
 * Devuelve el tamaño actual del vector Hijos
 * @tparam T
 * @return
 */
template<class T>
int NodoHeap<T>::getCantidadHijos() {
    return hijos.size();
}

/**
 * Verifica si el Nodo ya está en posición fija del ordenamiento final
 * o si puede ser utilizado para comparar con el Nodo Padre;
 * @tparam T
 * @return true si ya es Nodo Hoja fijo
 */
template<class T>
bool NodoHeap<T>::desapilado() {
    return nopila;
}

/**
 * Activa la variable "nopila", indicando que el Nodo ya fue ordenado y
 * no tiene que ser comparado en futuras comparaciones
 * @tparam T
 */
template<class T>
void NodoHeap<T>::setNoPila() {
    if(!nopila){
        nopila = true;
    }
}


/**
 * Método de comparacion para armado de Heap - Compara dos Nodos para
 * determinar cuál tiene el dato mayor. Repite recursivamente en el caso de
 * que haya un intercambio, para comparar entre el nuevo dato y el que contiene
 * el Nodo Padre del Nodo que fue reemplazado.
 * @tparam T
 * @param vector a comparar, punteros a variables "comp" y "swap" del Arbol
 */
template<class T>
void NodoHeap<T>::comparar(NodoHeap<T> *nodob, int *c, int*s) {
    if(nodob!= nullptr) { // Si es nulo, significa que hemos llegado a la raíz del Arbol
        T dato_h = this->getDato();
        T dato_p = nodob->getDato();

        *c = *c +1; // Aumento en 1 la variable "comp" del Arbol

        if (dato_p<dato_h) { // Se realiza el intercambio de información entre los Nodos, continua comparando
            this->swap_dato(nodob);
            //this->swap_repeticion(nodob);   DESCOMENTAR PARA CONSIDERAR REPETICIONES

            *s = *s + 1; // Aumento en 1 la variable "swap" del Arbol
            // Comparo el nuevo Nodo con el Nodo Padre del reemplazado, manteniendo los puntos a comp y swap
            nodob->comparar(nodob->getPadre(), c, s);
        }
    }
}

/**
 * Método de comparacion "arriba-abajo" - Compara un nodo Padre y cambia
 * solamente con el Nodo Hijo cuyo dato sea mayor. Repite recursivamente
 * con el Nodo Hijo con el que hizo el swap.
 * @tparam T
 * @param vector de Nodos Hijos, punteros a variables "comp" y "swap" del Arbol
 */
template<class T>
void NodoHeap<T>::comparar_sort(vector<NodoHeap<T>*> children, int *c, int*s) {
    T posible_raiz; // Retengo el dato del Nodo que es candidato a ser raíz
    int k= -1; // Variable auxiliar para determinar en qué posición del vector se encuentra el Nodo Hijo a intercambiar

    if(!(children.empty())) {
        // Se compara con los hijos para determinar el que contiene el dato mayor
        for (int i = 0; i < children.size(); i++) {
            if (!(children.at(i)->desapilado())) { // Revisa si no es un nodo que no tiene que ser considerado
                *c = *c + 1; // Suma en 1 la variable comp del Arbol

                if (this->getDato() < children.at(i)->getDato()) { // El dato del Hijo es mayor
                    if(posible_raiz < children.at(i)->getDato()){ // Compara el dato de este Nodo con la posible raíz
                        posible_raiz = children.at(i)->getDato(); // Si es mayor, guarda su valor para usar como referencia
                        k=i; // Asigno a la variable k la posición del nodo con el que se tiene que hacer el intercambio
                    }
                }
            }
            else{
                break;
            }
        }
    }

    if(k != -1){ // Hubo intercambio
        // Se realiza el intercambio con el Nodo Hijo en la posición determinada por k
        this->swap_dato(children.at(k));
        //this->swap_repeticion(children.at(k));----------DESCOMENTAR PARA CONSIDERAR REPETICIONES

        *s = *s + 1; // Suma en 1 la variable swap del Nodo a devolver

        // Ahora, realizamos la comparación con el Nodo que posee el dato mayor
        //  y los Nodos Hijos de esa posición
        children.at(k)->comparar_sort(children.at(k)->getHijos(),c,s);
    }
}

/**
 * Método para cambiar entre dos Nodos su variable "swap"
 * @tparam T
 * @param puntero a nodo con el que se quiere intercambiar
 */
template<class T>
void NodoHeap<T>::swap_dato(NodoHeap<T> *nodob) {
    T aux = this->getDato();
    this->setDato(nodob->getDato());
    nodob->setDato(aux);

}


#endif //ALGORITMOS_TP2_NODO_H