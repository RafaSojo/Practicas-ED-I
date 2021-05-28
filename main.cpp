#include <iostream>
#include "TAlmacen.h"
#include "TTipos.h"
#include "TTienda.h"
#include "Cola.h" //Fichero de definición de la cola de pedidos
#include "Lista.h" //Fichero de definición de la lista de envios

#include <Windows.h>
#include <cstdio>

#include <cmath>

/*
    cola -> FIFO (pedidos)
    lista -> ??? (envios)

*/

using namespace std;


// Funciones
void mostrarCabeceraPrincipal(Cadena nombreAlmacen, Cadena nombreTienda);
void motrarCabeceraAlmacen(Cadena nombreAlmacen);
void mostrarCabeceraTienda(Cadena nombreTienda);
void mostrarCabeceraPedidos();
void mostrarCabeceraEnvios();

void mostrarCabeceraPrincipal(Cadena nombreAlmacen, Cadena nombreTienda){

    cout << "----- Menú Principal ----- ";
    cout << nombreAlmacen << ", "<< nombreTienda << endl;

    cout << endl << "1.- Gestión del Almacenes.";
    cout << endl << "2.- Gestión de la Tienda.";
    cout << endl << "3.- Reposición de Productos en Tienda.";
    cout << endl << "0.- Salir";
    cout << endl << "> ";

}

void mostrarCabeceraAlmacen(Cadena nombreAlmacen){

    cout << endl << "----- Menú Almacenes ----- ";
    cout << nombreAlmacen << endl;

    cout << endl << "1.- Crear un almacén vacío.";
    cout << endl << "2.- Abrir un fichero de almacén.";
    cout << endl << "3.- Cerrar un almacén.";
    cout << endl << "4.- Listar productos del almacén.";
    cout << endl << "5.- Añadir un producto.";
    cout << endl << "6.- Actualizar un producto.";
    cout << endl << "7.- Consultar un producto.";
    cout << endl << "8.- Eliminar un producto.";
    cout << endl << "*9.- Gestión de pedidos.";
    cout << endl << "*10.- Gestión de envios.";
    cout << endl << "0.- Salir";
    cout << endl << "> ";

}

void mostrarCabeceraTienda(Cadena nombreTienda){

    cout << endl << endl << endl << "----- Menú Tienda ----- ";
    cout << nombreTienda << endl;

    cout << endl << "1.- Crear una tienda vacía.";
    cout << endl << "2.- Abrir un ficher o tienda.";
    cout << endl << "3.- Cerrar la tienda.";
    cout << endl << "4.- Actualizar el fichero tienda.";
    cout << endl << "5.- Listar productos de la tienda.";
    cout << endl << "6.- Añadir un estante.";
    cout << endl << "7.- Actualizar un estante.";
    cout << endl << "8.- Consultar un estante.";
    cout << endl << "9.- Eliminar un estante.";
    cout << endl << "0.- Salir";
    cout << endl << "> ";

}

void mostrarCabeceraPedidos(){

    cout << endl << endl << endl << "----- Gestión de Pedidos ----- ";

    cout << endl << "1.- Cargar pedidos de fichero.";
    cout << endl << "2.- Añadir pedido.";
    cout << endl << "3.- Atender pedidos.";
    cout << endl << "4.- Listar pedidos completos de todos los productos.";
    cout << endl << "5.- Lista pedidos de un producto.";
    cout << endl << "6.- Listar todas las cantidades pendientes.";
    cout << endl << "7.- Lista cantidades pendientes de un producto.";
    cout << endl << "8.- Guardar pedidos a fichero.";
    cout << endl << "0.- Salir";
    cout << endl << "> ";

}

void mostrarCabeceraEnvios(){

    cout << endl << endl << endl << "----- Gestión de Envíos ----- ";

    cout << endl << "1.- Cargar envíos de fichero.";
    cout << endl << "2.- Insertar un nuevo envío.";
    cout << endl << "3.- Reparto de envíos a tienda.";
    cout << endl << "4.- Listar todos ols envíos.";
    cout << endl << "5.- Listar los envíos a una tienda.";
    cout << endl << "6.- Guardar envíos a fichero.";
    cout << endl << "0.- Salir";
    cout << endl << "> ";

}


int main()
{
    // Para que se vean tildes y caracteres extraños:
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    //Cadena fichero = "Almacen.dat";
    TAlmacen almacen;
    TProducto producto;

    TTienda tienda;
    TEstante estante;

    Cadena nombreAlmacen;
    strcpy(nombreAlmacen, " *almacen no abierto* ");

    Cadena nombreTienda;
    strcpy(nombreTienda, " *tienda no abierta* ");


    Cadena direccionAlmacen;
    Cadena ficheroAlmacen;

    Cadena ficheroTienda;
    Cadena direccionTienda;

    int posicionProducto;
    int posicionEstante;

    Cadena opcionModificar;
    Cadena codigoProducto;
    Cadena nombreProducto;
    Cadena descripcionProducto;
    float precioProducto;
    int cantidadProducto;
    int dia;
    int mes;
    int anyo;

    int codigoEstante;
    float porcentajeOcupacion;

    TFecha fecha;

    int opcion_menu;
    int opcion_submenu;
    int opcion_subsubmenu;

    do
    {
        mostrarCabeceraPrincipal(nombreAlmacen, nombreTienda);
        cin >> opcion_menu;

        switch(opcion_menu)
        {

        case 1:
            /* Menu almacenes*/
            do
            {
                mostrarCabeceraAlmacen(nombreAlmacen);
                cin >> opcion_submenu;
                switch(opcion_submenu)
                {
                case 1:
                    /* Crear un almacen vacio */
                    if(almacen.EstaAbierto())
                        almacen.CerrarAlmacen();

                    cin.ignore();

                    cout << endl << "\tIntroduce el nombre del almacén > ";
                    cin.getline(nombreAlmacen, sizeof(Cadena));

                    cout << endl << "\tIntroduce la dirección del almacén > ";
                    cin.getline(direccionAlmacen, sizeof(Cadena));

                    cout << endl << "\tIntroduce el nombre del fichero del almacén > ";
                    cin.getline(ficheroAlmacen, sizeof(Cadena));


                    if(almacen.CrearAlmacen(nombreAlmacen, direccionAlmacen, ficheroAlmacen))
                        cout << endl << "\tAlmacén creado correctamente." << endl;
                    else
                        cout << endl << "\tOcurrió un error al crear el almacén" << endl;


                    break;

                case 2:
                    /* Abrir un fichero de almacén. */

                    cout << endl << "Introduzca el fichero del almacen: "<< endl << "> ";

                    cin >> ficheroAlmacen;

                    cout << endl << ficheroAlmacen;

                    if(!almacen.AbrirAlmacen(ficheroAlmacen))
                        break;
                    almacen.DatosAlmacen(nombreAlmacen, direccionAlmacen);

                    break;

                case 3:
                    /* Cerrar un almacen */
                    almacen.CerrarAlmacen();
                    strcpy(nombreAlmacen, " *almacen no abierto* ");
                    break;

                case 4:
                    /* Listar productos almacen */
                    if(!almacen.EstaAbierto()){
                        cout << endl << "No hay ningún almacen abierto" << endl;
                        break;
                    }
                        cout << endl << "Hay un total de: " << almacen.NProductos() << " productos";
                        cout << endl << "Lista de productos:" << endl;
                        cout << endl << "Codigo \t\tCantidad \tNombre \t\t\tPrecio \tDescripcion \tCaducidad" << endl;


                        // Para hacer la visualización mejor-> cout.flags(ios::left) y cout.width(tamaño asignación)
                        for(int i=0; i<almacen.NProductos(); i++){
                                producto = almacen.ObtenerProducto(i);
                                cout << producto.CodProd << "\t\t" << producto.Cantidad << "\t\t" << producto.NombreProd << "\t\t";
                                cout << producto.Precio << "\t" << producto.Descripcion << "\t" << producto.Caducicidad.Dia << "/" << producto.Caducicidad.Mes << "/" << producto.Caducicidad.Anyo  << endl;
                        }
                    break;
                case 5:
                    /* Añadir un producto */

                    if(!almacen.EstaAbierto()){
                        cout << endl << "No hay ningún almacen abierto" << endl;
                        break;
                    }

                    cout << endl << "Introduce el código del producto > ";
                    cin >> std::skipws >> producto.CodProd;

                    cin.ignore();

                    cout << endl << "Introduce el nombre del producto > ";
                    cin.getline(producto.NombreProd, sizeof(Cadena));

                    cout << endl << "Introduce la descripción del producto > ";
                    cin.getline(producto.Descripcion, sizeof(Cadena));

                    cout << endl << "Introduce el dia de la caducidad del producto > ";
                    cin >> fecha.Dia;

                    cout << endl << "Introduce el mes de la caducidad del producto > ";
                    cin >> fecha.Mes;

                    cout << endl << "Introduce el año de la caducidad del producto > ";
                    cin >> fecha.Anyo;

                    producto.Caducicidad = fecha;

                    cout << endl << "Introduce el precio del producto > ";
                    cin >> producto.Precio;

                    cout << endl << "Introduce la cantidad del producto > ";
                    cin >> producto.Cantidad;

                    if(almacen.AnadirProducto(producto))
                        cout << endl << "Se añadió correctamente." << endl;
                    else
                        cout << endl << "Ocurrió un error. Es posible que el producto ya exista." << endl;

                    break;
                case 6:
                    /* Actualizar un producto */

                    if(!almacen.EstaAbierto()){
                        cout << endl << "No hay ningún almacen abierto" << endl;
                        break;
                    }

                    cout << endl << "Introduce el código del producto >> ";
                    cin >> codigoProducto;

                    posicionProducto = almacen.BuscarProducto(codigoProducto);

                    if(posicionProducto == -1){
                        cout << endl << "El código introducido no coincide con ningún producto";
                        break;
                    }

                    producto = almacen.ObtenerProducto(posicionProducto);

                    cout << endl << "Indica qué es lo que quieres cambiar";
                    cout << endl << "(introduce \"n\" para no modificarlo y \"s\" para sí modificarlo)";

                    // To-Do: hacer más eficiente
                    cout << endl << "\tNombre (" << producto.NombreProd << ") >";
                    cin >> std::skipws >> opcionModificar;
                    if(strcmp(opcionModificar, "n") != 0){
                        cout << "\tIntroduce el valor > ";
                        cin.ignore();
                        cin.getline(producto.NombreProd, sizeof(Cadena));
                    }

                    cout << endl << "\tDescripción (" << producto.Descripcion << ") >";
                    cin >> std::skipws >> opcionModificar;
                    if(strcmp(opcionModificar, "n") != 0){
                        cout << "\tIntroduce el valor > ";
                        cin.ignore();
                        cin.getline(producto.Descripcion, sizeof(Cadena));
                    }


                    cout << endl << "\tPrecio (" << producto.Precio << ") >";
                    cin >> std::skipws >> opcionModificar;
                    if(strcmp(opcionModificar, "n") != 0){
                        cout << "\tIntroduce el valor > ";
                        cin >> producto.Precio;
                    }

                    cout << endl << "\tCantidad (" << producto.Cantidad << ") >";
                    cin >> std::skipws >> opcionModificar;
                    if(strcmp(opcionModificar, "n") != 0){
                        cout << "\tIntroduce el valor > ";
                        cin >> producto.Cantidad;
                    }


                      cout << endl << "\tFecha Caducidad (" << producto.Caducicidad.Dia << "/" << producto.Caducicidad.Mes << "/" << producto.Caducicidad.Anyo << ") >";
                    cin >> std::skipws >> opcionModificar;
                    if(strcmp(opcionModificar, "n") != 0){
                        cout << endl << "\tIntroduce el dia de la caducidad del producto > ";
                        cin >> fecha.Dia;

                        cout << endl << "\tIntroduce el mes de la caducidad del producto > ";
                        cin >> fecha.Mes;

                        cout << endl << "\tIntroduce el año de la caducidad del producto > ";
                        cin >> fecha.Anyo;
                        producto.Caducicidad = fecha;
                    }

                    if(almacen.ActualizarProducto(posicionProducto, producto))
                        cout << endl << "Producto modificado correctamente";
                    else
                        cout << endl << "Ocurrió un error";


                    break;
                case 7:
                    /* Consultar un producto */

                    if(!almacen.EstaAbierto()){
                        cout << endl << "No hay ningún almacen abierto" << endl;
                        break;
                    }

                    cout << endl << "Introduce el código del producto >> ";
                    cin >> codigoProducto;

                    posicionProducto = almacen.BuscarProducto(codigoProducto);

                    if(posicionProducto == -1){
                        cout << endl << "El código introducido no coincide con ningún producto";
                        break;
                    }
                    producto = almacen.ObtenerProducto(posicionProducto);

                    cout << endl << "El producto tiene los siguientes datos:";
                    cout << endl << "\tCódigo: " << producto.CodProd;
                    cout << endl << "\tNombre: " << producto.NombreProd;
                    cout << endl << "\tDescripción: " << producto.Descripcion;
                    cout << endl << "\tPrecio: " << producto.Precio;
                    cout << endl << "\tCantidad: " << producto.Cantidad;
                    cout << endl << "\tFecha caducidad: " << producto.Caducicidad.Dia << "/" << producto.Caducicidad.Mes << "/" << producto.Caducicidad.Anyo << endl;


                    break;
                case 8:
                    /* Eliminar un producto */

                    if(!almacen.EstaAbierto()){
                        cout << endl << "No hay ningún almacen abierto" << endl;
                        break;
                    }

                    cout << endl << "Introduce el código del producto >> ";
                    cin >> codigoProducto;

                    posicionProducto = almacen.BuscarProducto(codigoProducto);

                    if(posicionProducto == -1){
                        cout << endl << "El código introducido no coincide con ningún producto";
                        break;
                    }

                    almacen.EliminarProducto(posicionProducto);

                    break;

                case 9:
                    /* Gestión de pedidos */

                    do{
                        mostrarCabeceraPedidos();

                        cin >> opcion_subsubmenu;
                        switch(opcion_subsubmenu)
                        {
                            case 1:
                                /* Cargar pedidos de fichero */

                                break;

                            case 2:
                                /* Añadir pedido */

                                break;

                            case 3:
                                /* Atender pedidos */

                                break;

                            case 4:
                                /* Listar pedidos completos de todos los productos */

                                break;

                            case 5:
                                /* Listar pedidos de un producto */

                                break;

                            case 6:
                                /* Listar todas las cantidades pendientes */

                                break;

                            case 7:
                                /* Listar cantidades pendientes de un producto */

                                break;

                            case 8:
                                /* Guardar pedidos a fichero */

                                break;


                            case 0:
                                break;
                            default:
                                cout << endl << "No se ha seleccionado ninguna opción válida" << endl << endl;
                        }

                    }while(opcion_subsubmenu != 0);

                    break;


                case 10:
                    /* Gestión de envíos */
                    do{
                        mostrarCabeceraEnvios();
                        cin >> opcion_subsubmenu;
                        switch(opcion_subsubmenu)
                        {
                            case 1:
                                /* Cargar envios de fichero */

                                break;

                            case 2:
                                /* Insertar un nuevo envio */

                                break;

                            case 3:
                                /* Reparto de envíos a tienda */

                                break;

                            case 4:
                                /* Listar todos los envíos */

                                break;

                            case 5:
                                /* Listar los envíos a una tienda */

                                break;

                            case 6:
                                /* Guardar envios a fichero */

                                break;

                            case 0:
                                break;
                            default:
                                cout << endl << "No se ha seleccionado ninguna opción válida" << endl << endl;
                        }

                    }while(opcion_subsubmenu != 0);

                    break;

                case 0:
                    break;
                default:
                    cout << endl << "No se ha seleccionado ninguna opción válida" << endl << endl;
                }

            }
            while(opcion_submenu != 0);

            break;
        case 2:
            /* Menú Tienda */
            do
            {

                mostrarCabeceraTienda(nombreTienda);
                cin >> opcion_submenu;
                switch(opcion_submenu)
                {
                case 1:
                    /* Crear una tienda vacía */

                    cin.ignore();
                    cout << endl << "\tIntroduce el nombre de la tienda > ";
                    cin.getline(nombreTienda, sizeof(Cadena));

                    cout << endl << "\tIntroduce la dirección del almacen > ";
                    cin.getline(direccionTienda, sizeof(Cadena));

                    cout << endl << "\tIntroduce el fichero de la tienda > ";
                    cin.getline(ficheroTienda, sizeof(Cadena));

                    if(tienda.CrearTienda(nombreTienda, direccionTienda, ficheroTienda))
                        cout << endl << "\tTienda creada correctamente." << endl;
                    else
                        cout << endl << "\tOcurrió un error." << endl;

                    break;
                case 2:
                    /* Abrir un fichero tienda */
                    cout << endl << "Introduzca el fichero de la tienda: "<< endl << "> ";

                    cin >> ficheroTienda;

                    tienda.AbrirTienda(ficheroTienda);

                    tienda.DatosTienda(nombreTienda, direccionTienda);
                    break;
                case 3:
                    /* Cerrar la tienda */
                    if(!tienda.EstaAbierta()){
                        cout << endl << "No hay ninguna tienda abierta" << endl;
                        break;
                    }

                    if(tienda.CerrarTienda())
                        cout << endl << "Tienda cerrada correctamente.";
                    else
                        cout << endl << "Ocurrió un error al cerrar la tienda";

                    strcpy(nombreTienda, " *tienda no abierta*");

                    break;

                case 4:
                    /* Actualizar el fichero tienda */
                    if(!tienda.EstaAbierta()){
                        cout << endl << "No hay ninguna tienda abierta" << endl;
                        break;
                    }
                    tienda.GuardarTienda();
                    break;

                case 5:
                    /* Listar productos de la tienda */
                    if(!tienda.EstaAbierta()){
                        cout << endl << "No hay ninguna tienda abierta" << endl;
                        break;
                    }

                    cout << endl << "Hay un total de: " << tienda.NoEstantes() << " estantes";
                    cout << endl << "Lista de Estantes:" << endl;
                    cout << endl << "Codigo \t\tCod. Producto \tCapacidad \tNº Productos \tPosición" << endl;


                    // Para hacer la visualización mejor-> cout.flags(ios::left) y cout.width(tamaño asignación)
                    for(int i=0; i < tienda.NoEstantes(); i++){
                            //FicheProductos.read((char*)&producto, sizeof(producto));
                            estante = tienda.ObtenerEstante(i);
                            cout << estante.CodEstante << "\t\t" << estante.CodProd << "\t\t" << estante.Capacidad << "\t\t";
                            cout << estante.NoProductos << "\t\t" << estante.Posicion << endl;
                    }

                    break;
                case 6:
                    /* Añadir un estante */
                    if(!tienda.EstaAbierta()){
                        cout << endl << "No hay ninguna tienda abierta" << endl;
                        break;
                    }
                    if(!almacen.EstaAbierto()){
                        cout << endl << "No hay ningún almacen abierto" << endl;
                        break;
                    }

                    cout << endl << "\tIntroduce el código del estante > ";
                    cin >> estante.CodEstante;

                    if(tienda.BuscarEstante(estante.CodEstante) != -1){
                        cout << endl << "El código de estante ya existe.";
                        cout << endl << "Abortando creación de estante...";
                        break;
                    }

                    cout << endl << "\tIntroduce el código del producto > ";
                    cin >> estante.CodProd;

                    posicionProducto = almacen.BuscarProducto(estante.CodProd);
                    if(posicionProducto == -1){
                        cout << endl << "No existe ningún producto con ese código.";
                        cout << endl << "Abortando creación de estante...";
                        break;
                    }


                    producto = almacen.ObtenerProducto(posicionProducto);

                    cout << endl << "\tIntroduce la capacidad > ";
                    cin >> estante.Capacidad;

                    estante.NoProductos = estante.Capacidad+1;
                    do{
                        cout << endl << "\tIntroduce el número de productos (tiene que ser menor de " << estante.Capacidad << ") > ";
                        cin >> estante.NoProductos;

                        if(estante.NoProductos > estante.Capacidad){
                            estante.NoProductos = estante.Capacidad;
                            cout << endl << "\tSe ha introduce más productos que la capacidad. Se ha limitado al máximo: " << estante.NoProductos;
                        }
                    }while(estante.NoProductos>estante.Capacidad);


                    cout << endl << "\tIntroduce la posición > ";
                    cin >> estante.Posicion;

                    // Quitamos los productos solicitados del almacen (los que se pueda)
                    if(estante.NoProductos > producto.Cantidad){
                        estante.NoProductos = producto.Cantidad;
                        producto.Cantidad = 0;
                    }else{
                        producto.Cantidad = producto.Cantidad - estante.NoProductos;
                    }

                    almacen.ActualizarProducto(posicionProducto, producto);

                    if(tienda.AnadirEstante(estante))
                        cout << endl << "\tEstante añadido exitosamente.";
                    else
                        cout << endl << "\tOcurrió un error al añadir el estante.";

                    break;
                case 7:
                    /* Actualizar un estante */
                    if(!tienda.EstaAbierta()){
                        cout << endl << "No hay ninguna tienda abierta" << endl;
                        break;
                    }
                    if(!almacen.EstaAbierto()){
                        cout << endl << "No hay ningún almacen abierto" << endl;
                        break;
                    }


                    cout << endl << "\tIntroduce el código de estante > ";
                    cin >> codigoEstante;

                    posicionEstante = tienda.BuscarEstante(codigoEstante);
                    if(posicionEstante == -1){
                        cout << endl << "\tEl código introducido no se corresponde con ningún estante";
                    }else{
                        estante = tienda.ObtenerEstante(posicionEstante);


                        cout << endl << "\tEn el estante actualmente hay " << estante.NoProductos << "/" << estante.Capacidad;
                        cout << endl << "\t¿Quiere actualizarlo? s/n > ";

                        cin >> opcionModificar;
                        if(strcmp(opcionModificar, "n")){
                            cout << endl << "\tAbortando...";
                            break;
                        }
                        // mostrar por pantalla el numero de productos que hay en el estante y pedir confirmación

                        posicionProducto = almacen.BuscarProducto(estante.CodProd);

                        if(posicionProducto == -1){
                            cout << endl << "\tEl producto con código " << estante.CodProd << " no existe en el almacén";
                        }else{

                            cout << endl << "\tIntroduce la cantidad a reponer > ";
                            cin >> cantidadProducto;

                            producto = almacen.ObtenerProducto(posicionProducto);

                            if(cantidadProducto < estante.NoProductos){
                                // Mueve la cantidad al almacen

                                producto.Cantidad += estante.NoProductos - cantidadProducto;
                                almacen.ActualizarProducto(posicionProducto, producto);

                                estante.NoProductos -= cantidadProducto;
                                tienda.ActualizarEstante(posicionEstante, estante);

                                cout << endl << "\tSe ha quitado " << cantidadProducto << " productos para ponerlos en el almacén";


                            }else{
                                // mover desde almacen a tienda
                                if((cantidadProducto + estante.NoProductos) > estante.Capacidad ){
                                    // limitamos el número de productos que se pueden reponer
                                    //cantidadProducto =  cantidadProducto - (cantidadProducto + estante.NoProductos - estante.Capacidad);
                                    cantidadProducto = estante.Capacidad;
                                    //producto.Cantidad -= cantidadProducto;
                                    cout << endl << "\tSe ha introducido un número de productos mayor que la capacidad. Se ha limitado a " << cantidadProducto;
                                }

                                if(cantidadProducto > producto.Cantidad){
                                    cantidadProducto = producto.Cantidad;
                                    cout << endl << "\tEn el almacén no hay tantos productos. Se ha limitado a " << cantidadProducto;
                                    //producto.Cantidad = 0;
                                }

                                // calculamos cuanto falta para llenar el estante
                                if(cantidadProducto > (estante.Capacidad - estante.NoProductos)){
                                    cantidadProducto = estante.Capacidad - estante.NoProductos;
                                    cout << endl << "\tNo caben tantos productos en el estante. Se ha limitado a " << cantidadProducto;
                                }

                                producto.Cantidad -= cantidadProducto;
                                estante.NoProductos += cantidadProducto;

                                almacen.ActualizarProducto(posicionProducto, producto);
                                tienda.ActualizarEstante(posicionEstante, estante);

                                cout << endl << "\tSe ha repuesto " << cantidadProducto << " productos";

                            }

                        }

                    }

                    break;
                case 8:
                    /* Consultar un estante */
                    if(!tienda.EstaAbierta()){
                        cout << endl << "No hay ninguna tienda abierta" << endl;
                        break;
                    }

                    cout << endl << "\tIntroduce el código de estante > ";
                    cin >> codigoEstante;

                    posicionEstante = tienda.BuscarEstante(codigoEstante);
                    if(posicionEstante == -1){
                        cout << endl << "\tEl código introducido no se corresponde con ningún estante";
                    }else{
                        estante = tienda.ObtenerEstante(posicionEstante);
                        cout << endl << "\tDatos del estante: ";
                        cout << endl << "\t\tCódigo estante: " << estante.CodEstante;
                        cout << endl << "\t\tCódigo producto: " << estante.CodProd;
                        cout << endl << "\t\tCapacidad: " << estante.Capacidad;
                        cout << endl << "\t\tNº Productos: " << estante.NoProductos;
                        cout << endl << "\t\tPosición: " << estante.Posicion;
                    }

                    break;
                case 9:
                    /* Eliminar un estante */
                    if(!tienda.EstaAbierta()){
                        cout << endl << "No hay ninguna tienda abierta" << endl;
                        break;
                    }
                    if(!almacen.EstaAbierto()){
                        cout << endl << "No hay ningún almacen abierto" << endl;
                        break;
                    }

                    cout << endl << "\tIntroduce el código de estante > ";
                    cin >> codigoEstante;

                    posicionEstante = tienda.BuscarEstante(codigoEstante);
                    if(posicionEstante == -1){
                        cout << endl << "\tEl código introducido no se corresponde con ningún estante";
                    }else{
                        estante = tienda.ObtenerEstante(posicionEstante);
                        posicionProducto = almacen.BuscarProducto(estante.CodProd);

                        if(posicionProducto == -1){
                            cout << endl << "\tEl producto que se va a eliminar no está en el almacén, por lo tanto se desechará sin guardarlo.";
                        }else{
                            producto = almacen.ObtenerProducto(posicionProducto);
                            producto.Cantidad += estante.NoProductos;
                            almacen.ActualizarProducto(posicionProducto, producto);
                        }

                        if(tienda.EliminarEstante(posicionEstante))
                            cout << endl << "\tEstante eliminado correctamente.";
                        else
                            cout << endl << "\tOcurrió un error.";
                    }


                    break;
                case 0:
                    break;
                default:
                    cout << endl << "No se ha seleccionado ninguna opción válida" << endl << endl;
                }

            }
            while(opcion_submenu != 0);

            break;
        case 3:
            /* Reponer productos en tienda */
                if(!tienda.EstaAbierta()){
                        cout << endl << "No hay ninguna tienda abierta" << endl;
                        break;
                }
                if(!almacen.EstaAbierto()){
                        cout << endl << "No hay ningún almacen abierto" << endl;
                        break;
                }

                for(int i=0; i < tienda.NoEstantes(); i++){
                    estante = tienda.ObtenerEstante(i);

                    posicionProducto = almacen.BuscarProducto(estante.CodProd);

                    cout << endl << "\tCódigo estante: " << estante.CodEstante;
                    cout << endl << "\tCapacidad: " << estante.Capacidad;


                    if(posicionProducto != -1){
                            producto = almacen.ObtenerProducto(posicionProducto);
                            cout << endl << "\tProducto: " << producto.NombreProd;

                            switch(tienda.ReponerEstante(i, producto)){
                            case 0:
                                cout << endl << "\tError. Posición de producto incorrecta.";
                                break;

                            case 1:
                                cout << endl << "\tSe ha repuesto el estante correctamente.";
                                break;

                            case 2:
                                cout << endl << "\tSe ha repuesto el estante parcialmente.";
                                break;

                            default:
                                cout << endl << "\tOcurrió un error.";
                                break;

                            }
                            almacen.ActualizarProducto(posicionProducto, producto);

                    }else{
                        cout << endl << "\tEl producto no está en el almacen.";
                    }

                    porcentajeOcupacion = estante.NoProductos * 100 / estante.Capacidad;
                    cout << endl << "\tEl estante está lleno al " << round(porcentajeOcupacion) << "%." << endl;
                }

            break;
        case 0:
            break;
        default:
            cout << endl << "No se ha seleccionado ninguna opción válida" << endl << endl;

        }

    }
    while(opcion_menu != 0);
    return 0;
}
