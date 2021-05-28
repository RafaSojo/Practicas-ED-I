#ifndef LISTA_H
#define LISTA_H
#define MAX 30
#include <iostream>
#include "TTipos.h"

using namespace std;

class Lista {
 TPedido elementos[MAX]; //elementos de la lista
 int n; //nº de elementos que tiene la lista

public:
    Lista();
    Lista(TPedido pedido);
    bool esVacia();
    int longitud();
    /*void anadirIzq(TPedido pedido);
    void anadirDch(TPedido pedido);
    void eliminarIzq();
    void eliminarDch();
    TPedido observarIzq();
    TPedido observarDch();
    void concatenar(TPedido Lista[]);*/
    bool pertenece(TPedido pedido);
    void insertar(int i, TPedido pedido);
    void eliminar(int i);
    void modificar(int i, TPedido pedido);
    TPedido observar(int i);
    int posicion(TPedido pedido);
};

#endif // LISTA_H
