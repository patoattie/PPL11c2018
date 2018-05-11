#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Programacion-I/pattie/Funciones/funciones.h"
#include "Propietarios.h"
#include "Automoviles.h"

int main()
{
    char seguir='s';
    int opcion=0;
    int puntoMenu;

    //Declaro array donde guardo los datos de la estructura Propietario
    ePropietario listaPropietarios[LIMITE_PROPIETARIOS];
    eAutomovil listaAutomoviles[LIMITE_AUTOMOVILES];

    //Inicializo el flag de estado junto con hardcodeo de datos
    ePropietario_hardcodeo(listaPropietarios, LIMITE_PROPIETARIOS);
    eAutomovil_hardcodeo(listaAutomoviles, LIMITE_AUTOMOVILES);

    while(seguir=='s')
    {
        limpiarPantalla();

        printf("1- Alta de propietario\n");
        printf("2- Modificacion de propietario\n");
        printf("3- Baja de propietario\n");
        printf("4- Listado de propietarios\n");
        printf("5- Ingreso de automovil\n");
        printf("6- Listado de automoviles\n\n");
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
                puntoMenu = eAutomovil_ingreso(listaAutomoviles, listaPropietarios, LIMITE_AUTOMOVILES, LIMITE_PROPIETARIOS);
                if(puntoMenu == 0)
                {
                    printf("\nIngreso de automovil OK");
                }
                break;
            case 6:
                puntoMenu = eAutomovil_mostrarListadoConOcupados(listaAutomoviles, listaPropietarios, LIMITE_AUTOMOVILES, LIMITE_PROPIETARIOS);
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
