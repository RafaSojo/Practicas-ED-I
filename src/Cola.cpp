#include "Cola.h"

Cola::Cola(){
    inicio = 0;
    fin = -1;
}

void Cola::encolar(TPedido pedido){
    if( (fin + 1) < MAX){
        elementos[++fin] = pedido;

    }
}

void Cola::desencolar(){

    for(int i = inicio; i < fin; i++){
        elementos[i] = elementos[i + 1];
    }
        fin--;

}

TPedido Cola::primero(){
    return elementos[inicio];
}

bool Cola::esVacia(){
    return fin == -1;
}

int Cola::longitud(){
    return fin + 1;
}
