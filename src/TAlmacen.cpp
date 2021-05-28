#include <iostream>
#include "TAlmacen.h"
#include "TTipos.h"

/* Constructor */
TAlmacen::TAlmacen()
{
    NProduc = -1;
    strcpy(Nombre, " ");
    strcpy(Direccion, " ");
}

/* Destructor */
TAlmacen::~TAlmacen()
{
    if(FicheProductos.is_open())
        FicheProductos.close();
}


bool TAlmacen::AbrirAlmacen(Cadena pNomFiche){

    if(EstaAbierto())
        return false;

    FicheProductos.open(pNomFiche, ios::in|ios::out|ios::binary);

    /* actualizar datos clase*/
    FicheProductos.read((char*)&NProduc, sizeof(NProduc));
    FicheProductos.read((char*)&Nombre, sizeof(Nombre));
    FicheProductos.read((char*)&Direccion, sizeof(Direccion));

    return !FicheProductos.fail();
}

bool TAlmacen::CerrarAlmacen(){

    // vaciar lista y cola
    for(int i=0; i < Envios.longitud(); i++)
        Envios.eliminar(i);

    for(int i=0; i < Pedidos.longitud(); i++)
        Pedidos.desencolar();

     FicheProductos.close();
     return FicheProductos.is_open();

}

bool TAlmacen::EstaAbierto(){
    return FicheProductos.is_open();
}

int TAlmacen::NProductos(){
    return NProduc;
}

void TAlmacen::DatosAlmacen(Cadena pNombAlmacen, Cadena pDirAlmacen){
    strcpy(pNombAlmacen, Nombre);
    strcpy(pDirAlmacen, Direccion);
}




TProducto TAlmacen::ObtenerProducto(int pPos){
    TProducto producto;

    if(pPos >= NProduc){
            strcpy(producto.CodProd, "NULO");
        return producto;
    }

    int offset = sizeof(NProduc) + sizeof(Nombre) + sizeof(Direccion) + (sizeof(producto) * pPos);
    FicheProductos.seekg(offset, ios::beg);
    FicheProductos.read((char*)&producto, sizeof(producto));

    return producto;

}

 bool TAlmacen::CrearAlmacen(Cadena pNomFiche){

    // creamos el fichero
    FicheProductos.open(pNomFiche, ios::out|ios::binary);
    FicheProductos.close();
    FicheProductos.clear();

    // Lo volvemos a abrir
    FicheProductos.open(pNomFiche, ios::in|ios::out|ios::binary);

    return FicheProductos.is_open();

 }


 bool TAlmacen::CrearAlmacen(Cadena pNombAlmacen, Cadena pDirAlmacen, Cadena pNomFiche){

    strcpy(Nombre, pNombAlmacen);
    strcpy(Direccion, pDirAlmacen);
    NProduc = 0;

    // Creamos el fichero y comprobamos si se ha creado correctamente
    if(!CrearAlmacen(pNomFiche))
        return false;

    // Añade al fichero las cabeceras
    FicheProductos.write((char*)&NProduc, sizeof(NProduc));
    FicheProductos.write((char*)Nombre, sizeof(Nombre));
    FicheProductos.write((char*)Direccion, sizeof(Direccion));


     return true;
 }


 //Dado un producto, lo busca en el fichero y si no lo encuentra lo añade al final del fichero.
//Devuelve true si se ha añadido el producto.
    bool TAlmacen::AnadirProducto(TProducto pProduc){

    if(BuscarProducto(pProduc.CodProd) != -1)
        return false;

    // Añadimos al fichero el producto
    int offset = sizeof(NProduc) + sizeof(Nombre) + sizeof(Direccion) + (sizeof(TProducto) * NProduc) ;
    FicheProductos.seekp(offset, ios::beg);
    FicheProductos.write((char*) &pProduc, sizeof(TProducto));

    // Actualizo número de productos
    NProduc++;
    FicheProductos.seekp(0, ios::beg);
    FicheProductos.write((char*)&NProduc, sizeof(NProduc));


    return true;
    }


int TAlmacen::BuscarProducto(Cadena codigoProducto){

    TProducto producto;
    for(int i=0;i<NProduc; i++){
        producto = ObtenerProducto(i);
        if(strcmp(producto.CodProd, codigoProducto) == 0)
            return i;
    }
    return -1;

}



bool TAlmacen::ActualizarProducto(int pPos, TProducto pProduc){

    if(BuscarProducto(pProduc.CodProd) == -1)
        return false;

    int offset = sizeof(NProduc) + sizeof(Nombre) + sizeof(Direccion) + (sizeof(TProducto) * pPos) ;
    FicheProductos.seekp(offset, ios::beg);
    FicheProductos.write((char*) &pProduc, sizeof(TProducto));

    return true;

}


bool TAlmacen::EliminarProducto(int pPos){

    TProducto ultimoProducto = ObtenerProducto(NProduc - 1);

    // comprobar si existe un producto
    if(strcmp(ultimoProducto.CodProd, "NULO") == 0)
        return false;

    ActualizarProducto(pPos, ultimoProducto);

    NProduc--;

    return true;

}


//Método que carga la lista de envíos a partir del nombre del fichero que se le pasa por parámetro.
//El fichero tiene una sucesión de elementos de tipo TPedido.
bool TAlmacen::CargarListaEnvios(Cadena Nomf){

    fstream ficheroEnvios;

    TPedido pedidoAux;

    ficheroEnvios.open(Nomf, ios::in|ios::out|ios::binary);

    if(!ficheroEnvios.fail())
        return false;

    while(!ficheroEnvios.eof()){
        ficheroEnvios.read((char*)&pedidoAux, sizeof(TPedido));
        Envios.anadirDch(pedidoAux);
    }

    return !ficheroEnvios.fail();
}


//Método que carga la cola de pedidos a partir del nombre del fichero que se le pasa por parámetro.
//El fichero tiene una sucesión de elementos de tipo TPedido.
bool TAlmacen::CargarColaPedidos(Cadena Nomf){

    fstream ficheroPedidos;

    TPedido pedidoAux;

    ficheroPedidos.open(Nomf, ios::in|ios::out|ios::binary);

    if(!ficheroPedidos.fail())
        return false;

    while(!ficheroPedidos.eof()){
        ficheroPedidos.read((char*)&pedidoAux, sizeof(TPedido));
        Pedidos.encolar(pedidoAux);
    }

    return !ficheroPedidos.fail();

}

// Añadirá un nuevo pedido a la cola de pedidos.
void TAlmacen::AñadirPedido (TPedido p){
    Pedidos.encolar(p);
}

 //Método que atiende los pedidos del producto en cuestión pendientes de suministrar con la cantidad
 //comprada por el almacén, los incorpora a la lista de Envíos, eliminando de la cola de pedidos los
 //pedidos atendidos.
 //Si algún pedido es atendido parcialmente por que se acabe el producto, la cola se modificará
 //modificando y dejando pendiente la cantidad correspondiente, introduciendo en la lista de Envios
 //la cantidad que se puede suministrar.
 //Si el producto comprado excede de la cantidad pendiente de servir en los pedidos, la cantidad
 //sobrante, entra en el Almacén.
 bool TAlmacen::AtenderPedidos(Cadena CodProd,int cantidadcomprada){
    //to-do


}

// Muestra el contenido completo, con todos los datos de los productos leídos del almacén, de la cola
// si CodProd es '' o muestra los pedidos del Codprod pasado con todos sus datos del almacén.
void TAlmacen::ListarPedidosCompleto(Cadena CodProd){



}


// Muestra la cantidad pendiente de cada tipo de producto si CodProd es '' o del producto concreto
// que se pase por parámetro.
void TAlmacen::ListarCantidadesPendientes(Cadena CodProd){

    int longitud = Pedidos.longitud();
    TPedido pedido;

    for(int i=0; i < longitud; i++){
        pedido = Pedidos.primero();
        if(strcmp(CodProd, "") == 0 || strcmp(CodProd, pedido.CodProd)){
            cout << endl << "Cód Producto: " << pedido.CodProd << ", Cantidad: " << pedido.CantidadPed << ", Fichero: " << pedido.Nomtienda;
        }
        Pedidos.desencolar();
        Pedidos.encolar(pedido);
    }



}


//Se encarga de meter en la lista de envíos, de forma ordenada, por nombre del fichero de tienda, el
//pedido a enviar.
bool TAlmacen::InsertarEnvios(TPedido p){

}


//Se encarga de sacar de la lista los envíos que tienen por destino la tienda que se le pasa por
//parámetro mostrando por pantalla los envíos que van en el camión.
bool TAlmacen::SalidaCamionTienda(Cadena NomTienda){

}

//Si recibe Nomtienda a '' muestra por pantalla todo el contenido de la lista de envíos.
//Si se le pasa el nombre de una tienda muestra por pantalla los envíos a dicha tienda.
void TAlmacen::ListarListaEnvios(Cadena Nomtienda){

}


//Método que vuelca en el fichero nomf la cola de pedidos.
bool TAlmacen::SalvarColaPedidos(Cadena Nomf){

}


//Método que vuelca en el fichero nomf la lista de envíos.
bool TAlmacen::SalvarListaEnvios(Cadena Nomf){

}










