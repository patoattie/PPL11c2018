#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Programacion-I/pattie/Funciones/funciones.h"
#include "Propietarios.h"
#include "Automoviles.h"
#include "Ingresos.h"

int eAutomovil_mostrarListado(eAutomovil[], ePropietario[], int limiteAutomoviles, int limitePropietarios);
int eAutomovil_ingreso(eAutomovil[], ePropietario[], int limiteAutomoviles, int limitePropietarios);

int main()
{
    char seguir='s';
    int opcion=0;
    int puntoMenu;
    int idAutomovil;

    //Declaro array donde guardo los datos de la estructura Propietario
    ePropietario listaPropietarios[LIMITE_PROPIETARIOS];
    eAutomovil listaAutomoviles[LIMITE_AUTOMOVILES];
    eIngreso listaIngresos[LIMITE_INGRESOS];

    //Inicializo el flag de estado junto con hardcodeo de datos
    ePropietario_hardcodeo(listaPropietarios, LIMITE_PROPIETARIOS);
    eAutomovil_hardcodeo(listaAutomoviles, LIMITE_AUTOMOVILES);
    eIngreso_hardcodeo(listaIngresos, LIMITE_INGRESOS);

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
                    puntoMenu = eIngreso_alta(listaIngresos, LIMITE_INGRESOS, idAutomovil);
                    if(puntoMenu == 0)
                    {
                        printf("\nIngreso de automovil OK");
                    }
                }
                else
                {
                    printf("\nNo se pudo obtener un ID de automovil para ingresar. Por favor reintente");
                }
                break;
            case 6:
                idAutomovil = eAutomovil_ingreso(listaAutomoviles, listaPropietarios, LIMITE_AUTOMOVILES, LIMITE_PROPIETARIOS);
                if(idAutomovil > 0)
                {
                    puntoMenu = eIngreso_alta(listaIngresos, LIMITE_INGRESOS, idAutomovil);
                    if(puntoMenu == 0)
                    {
                        printf("\nIngreso de automovil OK");
                    }
                }
                else
                {
                    printf("\nNo se pudo obtener un ID de automovil para ingresar. Por favor reintente");
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
        printf("\nNo hay lugar disponible para estacionar automoviles");
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

            switch(muestraListado)
            {
            case 0:
                printf("\nNo hay automoviles para hacer ingresos"); //retorno = -2
                break;
            case 1:
                idAutomovil = pedirEnteroSinValidar("\nIngrese ID del automovil del propietario a hacer el ingreso, o 0 para ingresar un nuevo automovil: ");
                if(idAutomovil == 0)
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
                break;
            default:
                printf("\Error al listar...\n"); //retorno = -2
                break;
            }

            if(indiceAutomovil >= 0)
            {
                listaAutomoviles[indiceAutomovil].estado = ESTACIONADO;
            }
        } while(indiceAutomovil < 0 && muestraListado == 1);
    }

    return idAutomovil;
}
