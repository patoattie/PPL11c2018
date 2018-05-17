#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Programacion-I/pattie/Funciones/funciones.h"
#include "Propietarios.h"
#include "Automoviles.h"
#include "Ingresos.h"
#include "Egresos.h"

int eAutomovil_mostrarListado(eAutomovil[], ePropietario[], int limiteAutomoviles, int limitePropietarios);
int eAutomovil_ingreso(eAutomovil[], ePropietario[], int limiteAutomoviles, int limitePropietarios);
int eAutomovil_egreso(eAutomovil[], ePropietario[], eIngreso[], int limiteAutomoviles, int limitePropietarios, int limiteIngresos);
int eIngreso_mostrarListado(eIngreso[], ePropietario[], eAutomovil[], int limiteAutomoviles, int limitePropietarios, int limiteIngresos);
float eEgreso_devolverPrecioEstadia(int marca);
void eIngreso_hardcodeo(eIngreso[], eAutomovil[], int limiteIngresos, int limiteAutomoviles);
void eEgreso_hardcodeo(eEgreso[], eIngreso[], eAutomovil[], int limiteEgresos, int limiteIngresos, int limiteAutomoviles);

int main()
{
    char seguir='s';
    int opcion=0;
    int puntoMenu;
    int idAutomovil;
    int idIngreso;
    int posicionIngreso;
    int posicionAutomovil;
    int posicionPropietario;
    int horasEstadia;
    float precioEstadia;
    char nombrePropietario[TAM_NOMBRE_APELLIDO];
    char marcaAutomovil[TAM_MARCA];
    char patenteAutomovil[TAM_PATENTE];

    //Declaro array donde guardo los datos de la estructura Propietario
    ePropietario listaPropietarios[LIMITE_PROPIETARIOS];
    eAutomovil listaAutomoviles[LIMITE_AUTOMOVILES];
    eIngreso listaIngresos[LIMITE_INGRESOS];
    eEgreso listaEgresos[LIMITE_EGRESOS];

    //Inicializo el flag de estado junto con hardcodeo de datos
    ePropietario_hardcodeo(listaPropietarios, LIMITE_PROPIETARIOS);
    eAutomovil_hardcodeo(listaAutomoviles, LIMITE_AUTOMOVILES);
    eIngreso_hardcodeo(listaIngresos, listaAutomoviles, LIMITE_INGRESOS, LIMITE_AUTOMOVILES);
    eEgreso_hardcodeo(listaEgresos, listaIngresos, listaAutomoviles, LIMITE_EGRESOS, LIMITE_INGRESOS, LIMITE_AUTOMOVILES);

    while(seguir=='s')
    {
        limpiarPantalla();

        printf("1- Alta de propietario\n");
        printf("2- Modificacion de propietario\n");
        printf("3- Baja de propietario\n");
        printf("4- Listado de propietarios\n");
        printf("5- Ingreso de automovil\n");
        printf("6- Egreso de automovil\n");
        printf("7- Listado de automoviles\n\n");
        printf("9- Salir\n");

        scanf("%d",&opcion);

        switch(opcion)
        {
            case 1:
                puntoMenu = ePropietario_alta(listaPropietarios, LIMITE_PROPIETARIOS);
                if(puntoMenu == 0)
                {
                    printf("\nAlta de propietario OK");
                }
                break;
            case 2:
                puntoMenu = ePropietario_modificacion(listaPropietarios, LIMITE_PROPIETARIOS);
                if(puntoMenu == 0)
                {
                    printf("\nModificacion de propietario OK");
                }
                break;
            case 3:
                puntoMenu = ePropietario_baja(listaPropietarios, LIMITE_PROPIETARIOS);
                if(puntoMenu == 0)
                {
                    printf("\nBaja de propietario OK");
                }
                break;
            case 4:
                puntoMenu = ePropietario_mostrarListadoConOcupados(listaPropietarios, LIMITE_PROPIETARIOS);
                if(puntoMenu == 0)
                {
                    printf("\nListado de propietarios OK");
                }
                break;
            case 5:
                idAutomovil = eAutomovil_ingreso(listaAutomoviles, listaPropietarios, LIMITE_AUTOMOVILES, LIMITE_PROPIETARIOS);
                if(idAutomovil > 0)
                {
                    posicionAutomovil = eAutomovil_buscarPorId(listaAutomoviles, LIMITE_AUTOMOVILES, idAutomovil);
                    puntoMenu = eIngreso_alta(listaIngresos, LIMITE_INGRESOS, idAutomovil);
                    if(puntoMenu == 0)
                    {
                        listaAutomoviles[posicionAutomovil].estado = ESTACIONADO;
                        printf("\nIngreso de automovil OK");
                    }
                }
                else
                {
                    printf("\nNo se pudo obtener un ID de automovil para ingresar. Por favor reintente");
                }
                break;
            case 6:
                idIngreso = eAutomovil_egreso(listaAutomoviles, listaPropietarios, listaIngresos, LIMITE_AUTOMOVILES, LIMITE_PROPIETARIOS, LIMITE_INGRESOS);
                if(idIngreso > 0)
                {
                    posicionIngreso = eIngreso_buscarPorId(listaIngresos, LIMITE_INGRESOS, idIngreso);
                    if(posicionIngreso >= 0)
                    {
                        posicionAutomovil = eAutomovil_buscarPorIdEstacionados(listaAutomoviles, LIMITE_AUTOMOVILES, listaIngresos[posicionIngreso].idAutomovil);
                        if(posicionAutomovil >= 0)
                        {
                            posicionPropietario = ePropietario_buscarPorId(listaPropietarios, LIMITE_PROPIETARIOS, listaAutomoviles[posicionAutomovil].idPropietario);
                            if(posicionPropietario >= 0)
                            {
                                strcpy(nombrePropietario, listaPropietarios[posicionPropietario].nombreApellido);
                                strcpy(patenteAutomovil, listaAutomoviles[posicionAutomovil].patente);
                                eAutomovil_retornaMarca(listaAutomoviles[posicionAutomovil].marca, marcaAutomovil);
                                horasEstadia = eEgreso_devolverHorasEstadia();
                                precioEstadia = eEgreso_devolverPrecioEstadia(listaAutomoviles[posicionAutomovil].marca);
                                puntoMenu = eEgreso_alta(listaEgresos, LIMITE_EGRESOS, idIngreso, nombrePropietario, patenteAutomovil, marcaAutomovil, horasEstadia, precioEstadia);
                                if(puntoMenu == 0)
                                {
                                    listaAutomoviles[posicionAutomovil].estado = NO_ESTACIONADO;
                                    listaIngresos[posicionIngreso].estado = RETIRADO;
                                    printf("\nEgreso de automovil OK");
                                }
                            }
                        }
                    }
                }
                else
                {
                    printf("\nNo se pudo obtener un ID de automovil para egresar. Por favor reintente");
                }
                break;
            case 7:
                puntoMenu = eAutomovil_mostrarListado(listaAutomoviles, listaPropietarios, LIMITE_AUTOMOVILES, LIMITE_PROPIETARIOS);
                if(puntoMenu == 0)
                {
                    printf("\nListado de automoviles OK");
                }
                break;
            case 9:
                seguir = 'n';
                break;
            default:
                printf("\nOpcion no contemplada, por favor vuelva a elegir");
                break;
        }

        if(seguir=='s')
        {
            printf("\n");
            pausarEjecucion();
        }
    }

    return 0;
}

int eAutomovil_mostrarListado(eAutomovil listaAutomoviles[], ePropietario listaPropietarios[], int limiteAutomoviles, int limitePropietarios)
{
    int retorno = -1;
    int i;
    int posicionPropietario;

    if(limiteAutomoviles > 0 && listaAutomoviles != NULL && listaPropietarios != NULL)
    {
        retorno = 0;
        for(i=0; i<limiteAutomoviles; i++)
        {
            if(listaAutomoviles[i].estado==NO_ESTACIONADO || listaAutomoviles[i].estado==ESTACIONADO)
            {
                retorno = 1;

                posicionPropietario = ePropietario_buscarPorId(listaPropietarios, limitePropietarios, listaAutomoviles[i].idPropietario);
                //Se muestra al menos un elemento del array
                eAutomovil_mostrarUnoConEstado(listaAutomoviles[i], listaPropietarios[posicionPropietario].nombreApellido);
            }
        }

        if(retorno == 0)
        {
            printf("\n*** NO HAY ELEMENTOS PARA MOSTRAR ***");
        }
    }
    return retorno;
}

int eAutomovil_ingreso(eAutomovil listaAutomoviles[], ePropietario listaPropietarios[], int limiteAutomoviles, int limitePropietarios)
{
    int idPropietario;
    int indicePropietario;
    int idAutomovil = 0;
    int indiceAutomovil;
    int ingresoAutomovil;
    int limiteEstacionados;
    int muestraListado;

    limiteEstacionados = eAutomovil_validarLimiteEstacionados(listaAutomoviles, LIMITE_AUTOMOVILES);
    if(limiteEstacionados < 0)
    {
        printf("\nNo hay lugar disponible para ingresar automoviles");
    }
    else
    {
        do
        {
            muestraListado = ePropietario_mostrarListadoConOcupados(listaPropietarios, LIMITE_PROPIETARIOS);

            switch(muestraListado)
            {
            case 0:
                printf("\nNo hay propietarios para hacer ingresos"); //retorno = -2
                break;
            case 1:
                idPropietario = pedirEnteroSinValidar("\nIngrese ID del propietario a hacer el ingreso: ");
                indicePropietario = ePropietario_buscarPorId(listaPropietarios, LIMITE_PROPIETARIOS, idPropietario);
                if(indicePropietario < 0)
                {
                    printf("No se encontro el ID ingresado. Por favor reingrese\n");
                }
                break;
            default:
                printf("\Error al listar...\n"); //retorno = -2
                break;
            }
        } while(indicePropietario < 0 && muestraListado == 1);

        do
        {
            muestraListado = eAutomovil_mostrarListadoPropietario(listaAutomoviles, LIMITE_AUTOMOVILES, idPropietario, listaPropietarios[indicePropietario].nombreApellido);

            if(muestraListado == 1)
            {
                idAutomovil = pedirEnteroSinValidar("\nIngrese ID del automovil del propietario a hacer el ingreso, o 0 para ingresar un nuevo automovil: ");
            }
            else
            {
                printf("\n"); //Hago retorno de carro para separar mensajes en pantalla en caso que no haya automóviles
            }

            /*
            Si el propietario ya tiene automóviles ingresados pero quiere ingresar uno nuevo
            ==> el if entra por idAutomovil == 0
            Pero si el propietario no tiene ningún automóvil ingresado el sistema va a pedir directamente
            que el operador ingrese un automóvil para el propietario
            ==> el if entra por muestraListado == 0 ya que dicha función devuelve cero si no hay automóviles para mostrar
            */
            if(idAutomovil == 0 || muestraListado == 0)
            {
                ingresoAutomovil = eAutomovil_alta(listaAutomoviles, LIMITE_AUTOMOVILES, idPropietario, listaPropietarios[indicePropietario].nombreApellido);
                if(ingresoAutomovil == 0)
                {
                    indiceAutomovil = eAutomovil_ultimoIngresado(listaAutomoviles, LIMITE_AUTOMOVILES);
                    idAutomovil = listaAutomoviles[indiceAutomovil].idAutomovil;
                    printf("\nAlta de automovil OK");
                }
                else
                {
                    indiceAutomovil = -1;
                    printf("Por favor reingrese\n");
                }
            }
            else
            {
                indiceAutomovil = eAutomovil_buscarPorId(listaAutomoviles, LIMITE_AUTOMOVILES, idAutomovil);
                if(indiceAutomovil < 0)
                {
                    printf("No se encontro el ID ingresado. Por favor reingrese\n");
                }
            }
        } while(indiceAutomovil < 0 && muestraListado == 1);
    }

    return idAutomovil;
}

int eIngreso_mostrarListado(eIngreso listaIngresos[], ePropietario listaPropietarios[], eAutomovil listaAutomoviles[], int limiteIngresos, int limitePropietarios, int limiteAutomoviles)
{
    int retorno = -1;
    int i;
    int posicionAutomovil;
    int posicionPropietario;
    char nombrePropietario[TAM_NOMBRE_APELLIDO];
    char patente[TAM_PATENTE];
    char marca[TAM_MARCA];

    if(limiteIngresos > 0 && listaIngresos != NULL)
    {
        retorno = 0;
        for(i=0; i<limiteIngresos; i++)
        {
            if(listaIngresos[i].estado==INGRESADO)
            {
                //Busco el ID del Automóvil en la entidad correspondiente
                posicionAutomovil = eAutomovil_buscarPorIdEstacionados(listaAutomoviles, limiteAutomoviles, listaIngresos[i].idAutomovil);
                if(posicionAutomovil >= 0) //Si encuentro el ID del Automóvil
                {
                    posicionPropietario = ePropietario_buscarPorId(listaPropietarios, limitePropietarios, listaAutomoviles[posicionAutomovil].idPropietario);
                    if(posicionPropietario >= 0) //Si encuentro el ID del Propietario
                    {
                        retorno = 1;
                        strcpy(nombrePropietario, listaPropietarios[posicionPropietario].nombreApellido); //Nombre del Propietario
                        strcpy(patente, listaAutomoviles[posicionAutomovil].patente); //Patente del Automóvil
                        eAutomovil_retornaMarca(listaAutomoviles[posicionAutomovil].marca, marca); //Marca del Automóvil

                        //Se muestra al menos un elemento del array
                        eIngreso_mostrarUno(listaIngresos[i], nombrePropietario, patente, marca);
                    }
                }

            }
        }

        if(retorno == 0)
        {
            printf("\n*** NO HAY ELEMENTOS PARA MOSTRAR ***");
        }
    }
    return retorno;
}

int eAutomovil_egreso(eAutomovil listaAutomoviles[], ePropietario listaPropietarios[], eIngreso listaIngresos[], int limiteAutomoviles, int limitePropietarios, int limiteIngresos)
{
    int idIngreso;
    int indiceIngreso;
    int muestraListado;

    do
    {
        muestraListado = eIngreso_mostrarListado(listaIngresos, listaPropietarios, listaAutomoviles, limiteIngresos, limitePropietarios, limiteAutomoviles);

        switch(muestraListado)
        {
        case 0:
            printf("\nNo hay propietarios para hacer egresos"); //retorno = -2
            break;
        case 1:
            idIngreso = pedirEnteroSinValidar("\nIngrese ID del ingreso, para efectuar su salida: ");
            indiceIngreso = eIngreso_buscarPorId(listaIngresos, LIMITE_INGRESOS, idIngreso);
            if(indiceIngreso < 0)
            {
                printf("No se encontro el ID ingresado. Por favor reingrese\n");
            }
            break;
        default:
            printf("\Error al listar...\n"); //retorno = -2
            break;
        }
    } while(indiceIngreso < 0 && muestraListado == 1);

    return idIngreso;
}


float eEgreso_devolverPrecioEstadia(int marca)
{
    float precioEstadia;

    switch(marca)
    {
    case ALPHA_ROMEO:
        precioEstadia = IMPORTE_ALPHA_ROMEO;
        break;
    case FERRARI:
        precioEstadia = IMPORTE_FERRARI;
        break;
    case AUDI:
        precioEstadia = IMPORTE_AUDI;
        break;
    default:
        precioEstadia = IMPORTE_OTRO;
    }

    return precioEstadia;
}

void eIngreso_hardcodeo(eIngreso listaIngresos[], eAutomovil listaAutomoviles[], int limiteIngresos, int limiteAutomoviles)
{
    int i;
    int id[10]= {1,2,3,4,5,6,7,8,9,10};
    int posicionAutomovil;

    eIngreso_init(listaIngresos, limiteIngresos);

    for(i = 0; i < 10; i++)
    {
        listaIngresos[i].idIngreso = id[i];
        listaIngresos[i].idAutomovil = id[i];
        listaIngresos[i].estado = INGRESADO;
        //Cambio estado en la entidad Automovil
        posicionAutomovil = eAutomovil_buscarPorId(listaAutomoviles, limiteAutomoviles, listaIngresos[i].idAutomovil);
        listaAutomoviles[posicionAutomovil].estado = ESTACIONADO;
    }
}

void eEgreso_hardcodeo(eEgreso listaEgresos[], eIngreso listaIngresos[], eAutomovil listaAutomoviles[], int limiteEgresos, int limiteIngresos, int limiteAutomoviles)
{
    int i;
    int id[10]= {1,2,3,4,5,6,7,8,9,10};
    float importe[10]= {100,200,100,300,100,100,200,200,100,100};
    int posicionIngreso;
    int posicionAutomovil;

    eEgreso_init(listaEgresos, limiteEgresos);

    for(i = 0; i < 10; i++)
    {
        listaEgresos[i].idEgreso = id[i];
        listaEgresos[i].idIngreso = id[i];
        listaEgresos[i].importe = importe[i];
        listaEgresos[i].estado = OCUPADO;
        //Cambio estado en la entidad Ingreso
        posicionIngreso = eIngreso_buscarPorId(listaIngresos, limiteIngresos, listaEgresos[i].idIngreso);
        listaIngresos[posicionIngreso].estado = RETIRADO;
        //Cambio estado en la entidad Automovil
        posicionAutomovil = eAutomovil_buscarPorIdEstacionados(listaAutomoviles, limiteAutomoviles, listaIngresos[posicionIngreso].idAutomovil);
        listaAutomoviles[posicionAutomovil].estado = NO_ESTACIONADO;
    }
}
