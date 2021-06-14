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

    vector<Vertice> vertices; //va almacenando los nodos que encuentra durante el filtrado
    vector<Arista>  barreras;
};

Filter::Filter(){
    for (int i = 0; i < filtro.M->size(); ++i) {
        filtro.M[i].flip();
    }
    //filtro.print(); era para ver si

}

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




void Filter::filtrado(int **campo){
    //el otro bitmap lleno de 1s ya es parámetro de la clase, "filtro"
    bitmap aux;

    int fila=1;
    int columna=1;

    while(fila<19){ //es 99
        //inicio el bitmap aux de vuelta en cada fila nueva
        int p=2; //limite inverso del bitset
        for (int j = 0; j < 3; j++) { //ver diagrama de matriz en excel
            aux.M[fila-1][p]=campo[fila-1][j];
            p--;
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
                        campo[i][j]=0;
                    }
                }
            }
            aux=aux<<1; //corremos 1 pos a la izq dejando la 3ra columna en 0
            if((columna+2)<=19){ //es 99
                for(int k=fila-1;k<=fila+1;k++) {
                    aux.M[k][0]=campo[0][columna+2];
                }
            }
            columna++;
        }
        columna = 1; //resetea de vuelta a columna 1 para ubicar correctamente el aux en 3*3
        fila++;
    }
    //print campo
    cout<<"Matriz luego de filtrado"<<endl;
    for(int i=0;i<20;i++){
        cout<<endl;
        for(int j=0;j<20;j++)
            cout<<campo[i][j]<<"  ";
    }
}

void Filter::filtrado_x(int **campo) {//barrido de la matriz para ver las x. Es una verguenza

    for (int i = 0; i < 20; ++i) { //es 100
        for (int j = 0; j < 20; ++j) { //es 100

            if(campo[i][j] == 2){
                vector<Vertice> b;
                int k = i; //para moverme a partir de las coordenadas actuales sin tocar los for
                int z = j; //para moverme a partir de las coordenadas actuales sin tocar los for
                int flag = 1; //empieza en 1 para arrancar el while por primera vez. en el while se pone a 0 y si hay cambios,
                //vuelve a 1,sino sale del while. es para casos límites donde se trabe con la k o la z.

                while(campo[k][z]==2 && flag == 1){
                    flag = 0;
                    campo[k][z] = 0; //lo borro acá para que en próximas vueltas no lo vuelva a tener en cuenta
                    if(k!=0){ //caso de primer fila,no se puede ir una fila arriba
                        if(campo[k-1][z]==2){
                            k--;
                            flag = 1;
                        }
                    };

                    if(k!=19){ //caso de ultima fila,no se puede ir una fila más abajo. Es 99
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

                    if(z!=19){ //Es 99. caso límite de ultima columna, no puede irse una columna a la derecha
                        if(campo[k][z+1]==2){
                            z++;
                            flag = 1;
                        }
                    }

                    Vertice aux = Vertice(k,z);
                    b.push_back(aux);
                }
                Vertice inicio = b.front();
                Vertice final = b.back();
                Arista barrera = Arista(inicio,final);
                barreras.push_back(barrera);

                /*
                Vertice i_barrera = Vertice(i,j);
                campo[i][j] = 0; //lo paso a 0 para que en otra pasada no se vuelva a tener en cuenta
                int k, z;//para guardar la siguiente direccion por la que sigue la barrera
                //comparo cada pixel de alrededor (menos diagonales) y el que sea x, guardo sus coordenadas en k y z


                //i tiene que ser distinto de 0
                if(campo[i-1][j]==2){
                    k = i-1;
                    z = j;
                };

                //i no puede ser 99
                if(campo[i+1][j]==2){
                    k = i+1;
                    z = j;
                };

                //j no puede ser 0
                if(campo[i][j-1]==2){
                    k = i;
                    z = j-1;
                };

                //j no puede ser 99
                if(campo[i][j+1]==2){
                    k = i;
                    z = j+1;
                }

                while(campo[k][z]==2){
                    campo[k][z]=0;
                    if(k==i){
                        if(z == j-1){
                            z--;
                        } else{
                            z++;
                        }
                    };
                    if(z==j){
                        if(k == i-1){
                            k--;
                        } else {
                            k++;
                        }
                    }
                }
                Vertice f_barrera = Vertice(k,z);
                Arista barrera = Arista(i_barrera, f_barrera);
                barreras.push_back(barrera);
                 */
            }

        }
    }
    cout<<"Matriz luego de filtrado"<<endl;
    for(int i=0;i<20;i++){
        cout<<endl;
        for(int j=0;j<20;j++)
            cout<<campo[i][j]<<"  ";
    }
}


#endif //PARCIAL_3_FILTER_H
