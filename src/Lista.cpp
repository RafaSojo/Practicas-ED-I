#include "Lista.h"
#include "TTipos.h"

Lista::Lista(){
    n = 0;
}

Lista::Lista(TPedido pedido){
    n=1;
    elementos[0] = pedido;
}

void Lista::insertar(int i, TPedido pedido){
    int postabla;

    postabla = i - 1;

    if (n < MAX){

        for(int x=n; x >= postabla; x--)
            elementos[x+1] = elementos[x];

        elementos[postabla] = pedido;
        n++;
    }

}

void Lista::eliminar(int i){
    int postabla;
    postabla = i - 1;
    while (postabla<n-1){
        elementos[postabla] = elementos[postabla + 1];
        postabla++;
    }
    n--;
}

void Lista::modificar(int i, TPedido pedido){
    elementos[i - 1] = pedido;
}

TPedido Lista::observar(int i){
    return elementos[i - 1];
}

bool Lista::esVacia(){
    return n == 0;
}

int Lista::posicion(TPedido pedido){
    /*int i = 0;
    while(strcmp(elementos[i].CodProd, pedido.CodProd) != 0 && (i < n)){
        i++;
    }

    if( strcmp(elementos[i].CodProd, pedido.CodProd) == 0 ){
        return i + 1;
    }
    else
        return -1;*/
    for(int i=0; i < longitud(); i++)
        if(strcmp(elementos[i].CodProd, pedido.CodProd) == 0)
            return i + 1;


    return -1;
}

int Lista::longitud(){
    return n;
}


void Lista::anadirIzq(TPedido pedido){
    insertar(1, pedido);
}

void Lista::anadirDch(TPedido pedido){
    insertar(n + 1, pedido);
}

void Lista::eliminarIzq(){
    for(int i = 0; i < n - 1; i++){
        elementos[i] = elementos[i + 1];
    }
    n--;
}

void Lista::eliminarDch(){
    n--;
}

TPedido Lista::observarIzq(){
    return observar(1);
}

TPedido Lista::observarDch(){
    return observar(n);
}

void Lista::concatenar(TPedido Lista[]){

   // for(int i = 1; i <= lista.longitud(); i++){
     //   insertar(n + 1, Lista.observar(i));
    //}
}

bool Lista::pertenece(TPedido pedido){
    return (posicion(pedido) != -1);
}
