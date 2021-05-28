#ifndef COLA_H
#define COLA_H

#define MAX 30
#include <iostream>
#include "TTipos.h"

class Cola {
    TPedido elementos[MAX]; //elementos de la cola
    int inicio;
    int fin; // principio y fin de la cola
public:
    Cola(); // constructor de la clase
    void encolar(TPedido pedido);
    void desencolar();
    TPedido primero();
    bool esVacia();
    int longitud();
};

#endif // COLA_H
