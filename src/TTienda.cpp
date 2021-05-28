#include "TTienda.h"
#include "Cola.h" //Fichero de definición de la cola de pedidos
#include "Lista.h" //Fichero de definición de la lista de envios

/* Constructor */
TTienda::TTienda()
{
    strcpy(Nombre, "");
    strcpy(Direccion, "");
    strcpy(NomFiche, "");

    TEstante *Estantes = new TEstante[4];

    NEstan = -1;
    Tamano = 4;
}

/* Destructor */
TTienda::~TTienda()
{
    CerrarTienda();
    delete Estantes;
}


//Devuelve los atributos nombre y dirección por parámetro.
void TTienda::DatosTienda(Cadena pNombTienda, Cadena pDirTienda){
    strcpy(pNombTienda, Nombre);
    strcpy(pDirTienda, Direccion);
}





//Abre un fichero y lo carga a memoria. Si ya había un fichero previamente cargado, guardará los datos
//de la tienda y procederá a cargar el nuevo fichero. Si el fichero es el mismo que el que está en
//memoria, eliminará los datos y procederá a cargar nuevamente los datos del fichero. Devolverá true
//si se ha podido cargar el fichero.
 bool TTienda::AbrirTienda(Cadena pNomFiche){

    if(EstaAbierta())
        GuardarTienda();


    strcpy(NomFiche, pNomFiche);

    // Abrimos el fichero
    fstream FicheroTienda;
    FicheroTienda.open(pNomFiche, ios::in|ios::out|ios::binary);

    // Leemos la cabecera
    FicheroTienda.read((char*)&Nombre, sizeof(Cadena));
    FicheroTienda.read((char*)&Direccion, sizeof(Cadena));

    //cout << endl << "#DEBUG# Nombre: " << Nombre;
    //cout << endl << "#DEBUG# Dirección: " << Direccion;

    //calcular el tamaño
    NEstan = 0;


    TEstante estanteAux;
    while(!FicheroTienda.eof()){
        FicheroTienda.read((char*)&estanteAux, sizeof(TEstante));
        NEstan++;
    }



    // calcular el tamaño del vector
    float resto = NEstan % 4;
    if (resto == 0)
        Tamano = NEstan;
    else
        Tamano = NEstan + 4 - resto;

    Estantes = new TEstante[Tamano];

    // Cargamos los estantes del fichero
    int offset =  sizeof(Nombre) + sizeof(Direccion);
    FicheroTienda.clear();
    FicheroTienda.seekg(offset);

    for(int i=0;i<NEstan;i++){
        FicheroTienda.read((char*)&estanteAux, sizeof(TEstante));
        Estantes[i] = estanteAux;
    }

    // Ordenamos los estantes
    OrdenarProductos();


    FicheroTienda.close();

    return true;

 }




 void TTienda::OrdenarProductos(){

    bool cambios = true;
    TEstante estante1,estante2,estanteAux;

    //int nCambios = 0;

while(cambios){
        cambios = false;
        for(int i = 0; i<NEstan-1;i++){


            estante1 = Estantes[i];
            estante2 = Estantes[i+1];

            if(strcmp(estante1.CodProd,estante2.CodProd) == 1){
           // if(estante1.CodEstante > estante2.CodEstante){
                cambios = true;
                estanteAux = estante2;
                Estantes[i+1] = Estantes[i];
                Estantes[i] = estanteAux;
                //nCambios++;
            }

            if(strcmp(estante1.CodProd,estante2.CodProd) == 0){

                 if(estante1.Posicion > estante2.Posicion){
                    cambios = true;
                    estanteAux = estante2;
                    Estantes[i+1] = Estantes[i];
                    Estantes[i] = estanteAux;
                    //nCambios++;
                 }
            }

        }//for

    }//while

 }




  TEstante TTienda::ObtenerEstante(int pPos){
    return Estantes[pPos];
  }



  bool TTienda::EstaAbierta(){
    return NEstan != -1;
  }


  int TTienda::NoEstantes(){
    return NEstan;
  }

int TTienda::BuscarEstante(int pCodEstante){

    for (int i=0;i<NEstan;i++)
        if (Estantes[i].CodEstante == pCodEstante)
            return i;

    return -1;
 }

 bool TTienda::EliminarEstante(int pPos){
    NEstan--;
    Estantes[pPos] = Estantes[NEstan];
    OrdenarProductos();
    return true;

 }




bool TTienda::AnadirEstante(TEstante pEstante){
    // Si es igual se necesita aunmentar el tamaño
    if(NEstan == Tamano){
        cout << endl << "#debug: NEstan y Tamano son iguales.. aumentando el tamaño";
        Tamano += 4;
        TEstante* estanteriaAux = new TEstante[Tamano];
        for(int i=0;i<NEstan;i++)
            estanteriaAux[i] = Estantes[i];

        delete Estantes;

        Estantes = estanteriaAux;

        /*Estantes = new TEstante[Tamano];
        for(int i=0;i<NEstan;i++)
            Estantes[i] = estanteriaAux[i];*/
    }

    Estantes[NEstan] = pEstante;

    NEstan++;

    OrdenarProductos();

    return true;

}


bool TTienda::GuardarTienda(){

    fstream FicheroTienda;

    FicheroTienda.open(NomFiche, ios::in|ios::out|ios::binary);
    FicheroTienda.write((char*)&Nombre, sizeof(Cadena));
    FicheroTienda.write((char*)&Direccion, sizeof(Cadena));

    for(int i=0;i<NEstan;i++)
        FicheroTienda.write((char*)&Estantes[i], sizeof(TEstante));
    FicheroTienda.close();
    return true;
}


bool TTienda::CerrarTienda(){
    GuardarTienda();
    return true;
}


bool TTienda::ActualizarEstante(int pPos, TEstante pEstante){

    Estantes[pPos] = pEstante;
    return true;

}


//Dada la posición de un estante y un producto del almacén, actualizará el número de productos del
//estante a su máxima capacidad si hay suficientes unidades en el producto, en caso contrario se
//añadirán al estante la totalidad de unidades que estén en el producto del almacén. El mismo número
//de unidades añadidas en el estante deben reducirse del producto. Se debe verificar previamente que
//la posición sea correcta. El método devuelve:
// 0 si la posición es incorrecta.
// 1 si se ha repuesto unidades hasta llegar a la capacidad máxima del estante.
 // 2 si no se ha completado el estante al completo.
int TTienda::ReponerEstante(int pPos, TProducto &pProduc){

    if(pPos < 0 || pPos >= NEstan)
        return 0;

    TEstante estante = ObtenerEstante(pPos);

    if(strcmp(estante.CodProd, pProduc.CodProd) != 0)
        return 0;

    // todo-> cantidad real
    if(estante.Capacidad > pProduc.Cantidad){
        estante.NoProductos = pProduc.Cantidad;
        pProduc.Cantidad = 0;
        return 2;
    }else{
        pProduc.Cantidad = pProduc.Cantidad - estante.Capacidad;
        return 1;
    }

}



bool TTienda::CrearTienda(Cadena pNombTienda, Cadena pDirTienda, Cadena pNomFiche){
    strcpy(Nombre, pNombTienda);
    strcpy(Direccion, pDirTienda);
    strcpy(NomFiche, pNomFiche);

    NEstan = 0;
    Tamano = 4;

    Estantes = new TEstante[Tamano];

    return true;

}


