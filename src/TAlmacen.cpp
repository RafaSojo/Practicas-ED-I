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


// seekg lectura
// seekp escritura


bool TAlmacen::AbrirAlmacen(Cadena pNomFiche){

    if(EstaAbierto())
        return false;

    FicheProductos.open(pNomFiche, ios::in|ios::out|ios::binary);

    /* actualizar datos clase*/

    FicheProductos.read((char*)&NProduc, sizeof(NProduc));
    FicheProductos.read((char*)&Nombre, sizeof(Nombre));
    FicheProductos.read((char*)&Direccion, sizeof(Direccion));


  /*  cout << "-----";
    cout << endl << "Numero productos: " << NProduc;
    cout << endl << "Nombre: " << Nombre;
    cout << endl << "Dirección: " << Direccion;

    cout << endl;*/


    return !FicheProductos.fail();
}

bool TAlmacen::CerrarAlmacen(){

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

    int offset = sizeof(NProduc) + sizeof(Nombre) + sizeof(Direccion) + (sizeof(producto) * pPos) ;
    FicheProductos.seekg(offset);
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
    FicheProductos.seekp(offset);
    FicheProductos.write((char*) &pProduc, sizeof(TProducto));

    // Actualizo número de productos
    NProduc++;
    FicheProductos.seekp(0);
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
    FicheProductos.seekp(offset);
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





