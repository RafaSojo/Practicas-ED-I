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

    FicheProductos.open(pNomFiche, ios::in|ios::binary);

    /* actualizar datos clase*/
    FicheProductos.read((char*)&NProduc, sizeof(NProduc));
    FicheProductos.read((char*)&Nombre, sizeof(Nombre));
    FicheProductos.read((char*)&Direccion, sizeof(Direccion));

    return !FicheProductos.fail();
}

bool TAlmacen::CerrarAlmacen(){

    // vaciar lista y cola
    /*for(int i=0; i < Envios.longitud(); i++)
        Envios.eliminar(i);

    for(int i=0; i < Pedidos.longitud(); i++)
        Pedidos.desencolar();*/

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

    // A??ade al fichero las cabeceras
    FicheProductos.write((char*)&NProduc, sizeof(NProduc));
    FicheProductos.write((char*)Nombre, sizeof(Nombre));
    FicheProductos.write((char*)Direccion, sizeof(Direccion));


     return true;
 }


 //Dado un producto, lo busca en el fichero y si no lo encuentra lo a??ade al final del fichero.
//Devuelve true si se ha a??adido el producto.
    bool TAlmacen::AnadirProducto(TProducto pProduc){

    if(BuscarProducto(pProduc.CodProd) != -1)
        return false;

    // A??adimos al fichero el producto
    int offset = sizeof(NProduc) + sizeof(Nombre) + sizeof(Direccion) + (sizeof(TProducto) * NProduc) ;
    FicheProductos.seekp(offset, ios::beg);
    FicheProductos.write((char*) &pProduc, sizeof(TProducto));

    // Actualizo n??mero de productos
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


//M??todo que carga la lista de env??os a partir del nombre del fichero que se le pasa por par??metro.
//El fichero tiene una sucesi??n de elementos de tipo TPedido.
bool TAlmacen::CargarListaEnvios(Cadena Nomf){


    fstream ficheroEnvios;
    TPedido pedidoAux;
    ficheroEnvios.open(Nomf, ios::in|ios::binary);

    if(ficheroEnvios.fail())
        return false;

    // Reseteamos lista de envios
    for(int i=0; i<Envios.longitud(); i++)
        Envios.eliminar(0);

    int i = 0;

    while(!ficheroEnvios.eof()){
        ficheroEnvios.read((char*)&pedidoAux, sizeof(TPedido));

        Envios.insertar(i, pedidoAux);
        i++;

    }

    return !ficheroEnvios.fail();
}


//M??todo que carga la cola de pedidos a partir del nombre del fichero que se le pasa por par??metro.
//El fichero tiene una sucesi??n de elementos de tipo TPedido.
bool TAlmacen::CargarColaPedidos(Cadena Nomf){

    fstream ficheroPedidos;

    TPedido pedidoAux;

    ficheroPedidos.open(Nomf, ios::in|ios::binary);

    if(ficheroPedidos.fail())
        return false;

    while(!ficheroPedidos.eof()){
        ficheroPedidos.read((char*)&pedidoAux, sizeof(TPedido));
        Pedidos.encolar(pedidoAux);
    }

    return !ficheroPedidos.fail();

}

// A??adir?? un nuevo pedido a la cola de pedidos.
void TAlmacen::AnadirPedido (TPedido p){
    Pedidos.encolar(p);
}

 //M??todo que atiende los pedidos del producto en cuesti??n pendientes de suministrar con la cantidad
 //comprada por el almac??n, los incorpora a la lista de Env??os, eliminando de la cola de pedidos los
 //pedidos atendidos.
 //Si alg??n pedido es atendido parcialmente por que se acabe el producto, la cola se modificar??
 //modificando y dejando pendiente la cantidad correspondiente, introduciendo en la lista de Envios
 //la cantidad que se puede suministrar.
 //Si el producto comprado excede de la cantidad pendiente de servir en los pedidos, la cantidad
 //sobrante, entra en el Almac??n.
 bool TAlmacen::AtenderPedidos(Cadena CodProd, int cantidadcomprada){

    TPedido pedidoAux;
    TPedido envioAux;
    TProducto productoAux;

    int cantidadEnvio;

    for(int i=0; i < Pedidos.longitud(); i++){

        pedidoAux = Pedidos.primero();
        // comprobamos el c??digo de producto
        if(strcmp(pedidoAux.CodProd, CodProd) == 0){

            if(cantidadcomprada - pedidoAux.CantidadPed >= 0){
                // creamos pedido y restamos cantidad al total
                cantidadEnvio = pedidoAux.CantidadPed;
                cantidadcomprada -= cantidadEnvio;

                envioAux.CantidadPed = cantidadEnvio;
                strcpy(envioAux.CodProd, pedidoAux.CodProd);
                strcpy(envioAux.Nomtienda, pedidoAux.Nomtienda);

                Envios.anadirIzq(envioAux);

            }else{

                if(cantidadcomprada > 0){
                    // crea envio parcial
                    cantidadEnvio = cantidadcomprada;
                    cantidadcomprada -= cantidadEnvio;

                    envioAux.CantidadPed = cantidadEnvio;
                    strcpy(envioAux.CodProd,pedidoAux.CodProd);
                    strcpy(envioAux.Nomtienda,pedidoAux.Nomtienda);

                    Envios.anadirIzq(envioAux);

                    pedidoAux.CantidadPed -= cantidadEnvio;

                    Pedidos.encolar(pedidoAux);

                }else{
                    // No se puede crear envio
                    Pedidos.encolar(pedidoAux);
                }
            }

        }else{
            Pedidos.encolar(pedidoAux);
        }

        Pedidos.desencolar();

    }

    if(cantidadcomprada > 0){
        // Si hay excendete
        int posicionProducto = BuscarProducto(CodProd);
        productoAux = ObtenerProducto(posicionProducto);
        productoAux.Cantidad += cantidadcomprada;

        ActualizarProducto(posicionProducto, productoAux);
    }

    return true;

}

// Muestra el contenido completo, con todos los datos de los productos le??dos del almac??n, de la cola
// si CodProd es '' o muestra los pedidos del Codprod pasado con todos sus datos del almac??n.
void TAlmacen::ListarPedidosCompleto(Cadena CodProd){

    if(Pedidos.esVacia()){
        cout << endl << "La cola de pedidos est?? vac??a.";
        return;
    }

    int longitud = Pedidos.longitud();
    TPedido pedido;

    for(int i=0; i < longitud; i++){
        pedido = Pedidos.primero();
        if(strcmp(CodProd, "") == 0 || strcmp(CodProd, pedido.CodProd) == 0){
            cout << endl << "C??d Producto: " << pedido.CodProd << ", Cantidad: " << pedido.CantidadPed << ", Fichero: " << pedido.Nomtienda;
        }
        Pedidos.desencolar();
        Pedidos.encolar(pedido);
    }

}


// Muestra la cantidad pendiente de cada tipo de producto si CodProd es '' o del producto concreto
// que se pase por par??metro.
void TAlmacen::ListarCantidadesPendientes(Cadena CodProd){

    if(Pedidos.esVacia()){
        cout << endl << "La cola de pedidos est?? vac??a.";
        return;
    }

    int longitud = Pedidos.longitud();
    TPedido pedido;

    TPedido pedidoAux;
    Lista listaAux;
    int posicion;


    for(int i=0; i < longitud ; i++){
        pedido = Pedidos.primero();

        if(strcmp(CodProd, "") == 0 || strcmp(CodProd, pedido.CodProd) == 0){

            posicion = listaAux.posicion(pedido);

            if(posicion == -1){
                listaAux.anadirDch(pedido);
            }else{
                pedidoAux = listaAux.observar(posicion);
                pedidoAux.CantidadPed += pedido.CantidadPed;

                listaAux.modificar(posicion, pedidoAux);
            }
        }

        Pedidos.encolar(pedido);
        Pedidos.desencolar();

    }

    // en este momento tenemos listaAux con la suma de todos los envios
    for(int i=0; i < listaAux.longitud(); i++){
        pedidoAux = listaAux.observar(i + 1);
        cout << endl << "C??d Producto: " << pedidoAux.CodProd << ", Cantidad: " << pedidoAux.CantidadPed << ", Fichero: " << pedidoAux.Nomtienda;
    }


}


//Se encarga de meter en la lista de env??os, de forma ordenada, por nombre del fichero de tienda, el
//pedido a enviar.
bool TAlmacen::InsertarEnvios(TPedido p){

    TPedido pedidoAux;
    int posicion = 0;

    // Calcular posici??n de insertar
    for(int i=0; i < Envios.longitud(); i++){
        pedidoAux = Envios.observar(i);
        if(strcmp(pedidoAux.Nomtienda, p.Nomtienda) < 0)
            posicion = i;
    }

    Envios.insertar(posicion+1, p);

    return true;

}


//Se encarga de sacar de la lista los env??os que tienen por destino la tienda que se le pasa por
//par??metro mostrando por pantalla los env??os que van en el cami??n.
bool TAlmacen::SalidaCamionTienda(Cadena NomTienda){

    TPedido pedidoAux;
    Lista listaNueva;

    cout << endl << "\tPedidos hacia " << NomTienda << ":";
    cout << endl << "C??digo Producto\tCantidad\tNombre tienda";

    for(int i=0; i < Envios.longitud(); i++){
        pedidoAux = Envios.observar(i+1);

        if(strcmp(pedidoAux.Nomtienda, NomTienda) == 0)
            cout << endl << pedidoAux.CodProd << "\t" << pedidoAux.Nomtienda << "\t" << pedidoAux.CantidadPed;
        else
            listaNueva.anadirDch(pedidoAux);
    }

    Envios = listaNueva;

    return true;

}

//Si recibe Nomtienda a '' muestra por pantalla todo el contenido de la lista de env??os.
//Si se le pasa el nombre de una tienda muestra por pantalla los env??os a dicha tienda.
void TAlmacen::ListarListaEnvios(Cadena Nomtienda){

    TPedido pedido;

    cout << endl << "Lista de envios: ";

    for(int i=0; i < Envios.longitud(); i++){
        pedido = Envios.observar(i);

        /*cout << endl << Nomtienda;
        cout << endl << pedido.Nomtienda;*/
        if(strcmp(Nomtienda, "") == 0 || strcmp(Nomtienda, pedido.Nomtienda) == 0){
            // muestra todo el contenido de la lista de envios
            cout << endl << "\tPedido: " << i+1;
            cout << endl << "\t\tProducto: " << pedido.CodProd;
            cout << endl << "\t\tCantidad: " << pedido.CantidadPed;
            cout << endl << "\t\tFichero tienda: " << pedido.Nomtienda;
        }
    }

}


//M??todo que vuelca en el fichero nomf la cola de pedidos.
bool TAlmacen::SalvarColaPedidos(Cadena Nomf){

    int longitud = Pedidos.longitud();
    TPedido pedido;

    fstream ficheroPedidos;
    ficheroPedidos.open(Nomf, ios::in|ios::out|ios::binary);

    ficheroPedidos.seekp(0, ios::beg);

    for(int i=0; i < longitud; i++){
        pedido = Pedidos.primero();

        ficheroPedidos.write((char*) &pedido, sizeof(TPedido));

        Pedidos.desencolar();
        Pedidos.encolar(pedido);
    }

    return true;
}


//M??todo que vuelca en el fichero nomf la lista de env??os.
bool TAlmacen::SalvarListaEnvios(Cadena Nomf){


    int longitud = Envios.longitud();
    TPedido pedido;

    fstream ficheroPedidos;
    ficheroPedidos.open(Nomf, ios::in|ios::out|ios::binary);

    ficheroPedidos.seekp(0, ios::beg);

    for(int i=0; i < longitud; i++){
        pedido = Envios.observar(i);
        ficheroPedidos.write((char*) &pedido, sizeof(TPedido));
    }

    return true;

}










