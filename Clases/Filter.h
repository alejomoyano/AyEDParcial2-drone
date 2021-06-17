#ifndef PARCIAL_3_FILTER_H
#define PARCIAL_3_FILTER_H

#include <iostream>
#include <bitset>
#include <vector>
#include "Arista.h"
#include "Vertice.h"
#include "bitmap.h"

using namespace std;

class Filter{
public:
    bitmap filtro;

    Filter();

    bool comparar(bitmap);

    void filtrado(int**);
    void filtrado_x(int**);
    void printMatriz(int**);

    vector<Vertice> vertices; //va almacenando los nodos que encuentra durante el filtrado
    vector<Arista>  barreras; //almacena las barreras encontradas durante el filtrado
};

Filter::Filter(){
    for (int i = 0; i < filtro.M->size(); ++i) {
        filtro.M[i].flip();
    }


}

/*
 * Metodo que realiza la operacion AND entre dos conjuntos
 * @param aux: bitmap a comparar con respecto al filtro de 3x3
 * @return true si son iguales, false si no lo son
 */
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



/*
 * Metodo que filtra las malezas
 * @param campo: matriz del campo
 */
void Filter::filtrado(int **campo){
    //el otro bitmap lleno de 1s ya es parámetro de la clase, "filtro"
    bitmap aux;
    int fila=1, columna=1;

    while(fila<99){
        int k=0;
        for(int i = fila-1; i<=fila+1; i++ ){ //pasamos a un bitmap para poder comparar
            bitset<3> baux;
            int p=2; //limite inverso del bitset
            for (int j = 0; j < 3; j++) {
                int s = campo[j][i];
                if(s==2) //si hay una barrera en esa posicion colocamos un 0 asi no molesta
                    s = 0;
                if(s==1)
                    baux.set(p);
                p--;
            }
            aux.M[k]=baux;
            k++;
        }

        while (columna<99){
            if(comparar(aux)){
                Vertice nodo = Vertice(fila,columna);
                //lo meto en el vector de vertices
                vertices.push_back(nodo);
                //paso a 0 esa parte de campo, solamente si fue filtrada
                for (int i = fila-1; i <= fila + 1; i++) {  //empiezo desde la fila anterior y paro en la siguiente
                    for (int j = columna-1; j <= columna +1 ; j++) { //empiezo desde la fila anterior y paro en la siguiente
                        campo[j][i]=0;
                    }
                }
                for (int i = 0; i < aux.M->size(); ++i) {
                    aux.M[i].flip(); //colocamos la matriz en 0 ya que fue filtrada
                }
                cout<<"Encontramos una mancha en ("<<fila<<","<<columna<<") Cambiamos a 0 el 3x3 en el campo y en el aux\n";
            }
            aux=aux<<1; //corremos 1 pos a la izq dejando la 3ra columna en 0
            int f=0;
            if((columna+2)<=99){ // colocamos la proxima columna a observar en la matriz aux para filtrar
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

}


/*
 * Metodo que filtra las barreas
 * @param campo: matriz del campo
 */
void Filter::filtrado_x(int **campo) {//barrido de la matriz para ver las x. Es una verguenza

    for (int i = 0; i < 100; ++i) { //es 100
        for (int j = 0; j < 100; ++j) { //es 100

            if(campo[j][i] == 2){
                vector<Vertice> b;
                int k = j; //para moverme a partir de las coordenadas actuales sin tocar los for
                int z = i; //para moverme a partir de las coordenadas actuales sin tocar los for
                int flag = 1; //empieza en 1 para arrancar el while por primera vez. en el while se pone a 0 y si hay cambios,
                //vuelve a 1,sino sale del while. es para casos límites donde se trabe con la k o la z.

                while(campo[k][z]==2 && flag == 1){
                    Vertice aux = Vertice(z,k);
                    b.push_back(aux);
                    flag = 0;
                    campo[k][z] = 0; //lo borro acá para que en próximas vueltas no lo vuelva a tener en cuenta
                    if(k!=0){ //caso de primer fila,no se puede ir una fila arriba
                        if(campo[k-1][z]==2){
                            k--;
                            flag = 1;
                        }
                    };

                    if(k!=99){ //caso de ultima fila,no se puede ir una fila más abajo. Es 99
                        if(campo[k+1][z]==2){
                            k++;
                            flag = 1;
                        }
                    };

                    if(z!=0){//caso límite de primer columna, no puede irse una columna a la izquierda
                        if(campo[k][z-1]==2){
                            z--;
                            flag = 1;
                        }
                    };

                    if(z!=99){ //Es 99. caso límite de ultima columna, no puede irse una columna a la derecha
                        if(campo[k][z+1]==2){
                            z++;
                            flag = 1;
                        }
                    }

                }
                if(b.size()>=4) { // si la barrera es de 4 o mas es tomada en cuentap
                    Vertice inicio = b.front();
                    Vertice final = b.back();
                    Arista barrera = Arista(inicio, final);
                    barreras.push_back(barrera);
                }
            }

        }
    }

}


/*
 * Metodo que imprime la matriz
 * @param campo: matriz del campo
 */
void Filter::printMatriz(int **campo) {
    for(int i=0;i<100;i++){
        cout<<endl;
        for(int j=0;j<100;j++)
            cout<<campo[j][i]<<" ";
    }
    cout<<endl;
}


#endif //PARCIAL_3_FILTER_H