#ifndef VUELO_DE_UN_DRONE_BITSET_H
#define VUELO_DE_UN_DRONE_BITSET_H


#include <iostream>
#include <string>
#include <bitset>
using namespace std;

class bitmap{
    public:
        bitset<3> M[3];
        void print();
        int count(); // cuenta los 1
    //definiendo and de conjuntos
        friend bitmap operator &(bitmap c1, bitmap c2);
    // definiendo or de conjuntos
        friend bitmap operator |(bitmap c1, bitmap c2); //operador or de conjunto
        friend bitmap operator <<(bitmap c1,int n); //shift a la izquierda
        friend bool operator ==(bitmap c1,bitmap c2);// compara si son iguales
};


bitmap operator &(bitmap c1, bitmap c2){
    bitmap c3;
        for(int i=0;i<7;i++)
            c3.M[i] = c1.M[i]&c2.M[i];
        return c3;
    }

    void bitmap::print(){
        int i,j;
        for(i=0;i<3;i++){
            cout<<endl;
            for(j=2;j>=0;j--)
                cout<<this->M[i][j]<<"  ";
        }
        cout<<endl;
    }

    int bitmap::count(){
        int c=0;
        for(int i=0;i<7;i++)
            c=c+M[i].count();
        return c;
    }

bitmap operator |(bitmap c1, bitmap c2){
    bitmap c3;
        for(int i=0;i<7;i++)
            c3.M[i]= c1.M[i]|c2.M[i];
        return c3;
    }

bitmap operator <<(bitmap c1, int n){
        for(int i=0;i<3;i++)
            c1.M[i]<<=n;
        return c1;
    }

    bool operator ==(bitmap c1, bitmap c2){
        for(int i=0;i<7;i++){
            for(int j=0;j<7;j++){
                if (c1.M[i][j]!=c2.M[i][j])
                    return false;
            }

        }
        return true;
    }

#endif //VUELO_DE_UN_DRONE_BITSET_H
