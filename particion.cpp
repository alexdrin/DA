#include "particion.hpp"

//Crea la particion inicial
Particion:Particion(int n) : p(n, -1){}


int Particion::buscar(int i) const{
    while(p[i] >= 0){
        i = p[i]; //Subir al padre
    }
    return i;
}

int Particion::unir(int i, int j){
    if(p[i] < p[j]){
        p[j] = i;
    }else{
        if(p[i] == p[j] ){
            p[j] --;    
        }
        p[i] = j;
    }
}