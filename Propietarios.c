#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Programacion-I/pattie/Funciones/funciones.h"
#include "Propietarios.h"

#define OCUPADO 0
#define LIBRE 1
#define BAJA 2

void ePropietario_init(ePropietario listado[],int limite)
{
    int i;
    if(limite > 0 && listado != NULL)
    {
        for(i=0; i<limite; i++)
        {
            listado[i].estado= LIBRE;
            listado[i].idPropietario= 0;
        }
    }
}

void ePropietario_hardcodeo(ePropietario listado[],int limite)
{
    int i;
    int id[4]= {1,2,3,4};
    char nombre[4][20]= {"Juan","Luis","Maria","Jose"};
    char tarjeta[4][20]= {"111-111","222-222","333-333","444-444"};
    char direccion[4][20]= {"mitre","urquiza","belgrano","alsina"};

    ePropietario_init(listado, limite);

    for(i = 0; i < 4; i++)
    {
        listado[i].idPropietario = id[i];
        strcpy(listado[i].nombreApellido, nombre[i]);
        strcpy(listado[i].direccion, direccion[i]);
        strcpy(listado[i].numeroTarjeta, tarjeta[i]);
        listado[i].estado = OCUPADO;
    }
}
int ePropietario_buscarLugarLibre(ePropietario listado[],int limite)
{
    int retorno = -1;
    int i;
    int posicionLibre = -1; //Guarda la primer posicion con estado LIBRE que encuentra
    int posicionBaja = -1; //Guarda la primer posicion con estado BAJA que encuentra

    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(listado[i].estado == LIBRE)
            {
                posicionLibre = i;
                break;
            }
        }

        if(posicionLibre < 0) //No hay posiciones con estado LIBRE, busco la primer posición con estado BAJA
        {
            for(i=0;i<limite;i++)
            {
                if(listado[i].estado == BAJA)
                {
                    posicionBaja = i;
                    break;
                }
            }

            if(posicionBaja >= 0)
            {
                retorno = posicionBaja; //Retorno la primera posición con estado BAJA
            }
        }
        else
        {
            retorno = posicionLibre; //Retorno la primera posición con estado LIBRE
        }
    }

    return retorno;
}

int ePropietario_siguienteId(ePropietario listado[],int limite)
{
    int retorno = 0;
    int i;
    if(limite > 0 && listado != NULL)
    {
        for(i=0; i<limite; i++)
        {
            if(listado[i].estado == OCUPADO || listado[i].estado == BAJA) //Tengo en cuenta las bajas lógicas para no duplicar id al rehabilitar
            {
                    if(listado[i].idPropietario>retorno)
                    {
                         retorno=listado[i].idPropietario;
                    }

            }
        }
    }

    return retorno+1; //Retorno el mayor ID más 1
}


int ePropietario_buscarPorId(ePropietario listado[] ,int limite, int id)
{
    int retorno = -1;
    int i;
    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(listado[i].estado == OCUPADO && listado[i].idPropietario == id)
            {
                retorno = i;
                //Hallé el elemento que buscaba y retorno su indice
                break;
            }
        }
    }
    return retorno;
}

void ePropietario_mostrarUno(ePropietario parametro)
{
     printf("\n %d - %s - %s - %s", parametro.idPropietario, parametro.nombreApellido, parametro.direccion, parametro.numeroTarjeta);

}

void ePropietario_mostrarUnoConEstado(ePropietario parametro)
{
    switch(parametro.estado)
    {
    case LIBRE: //No muestro las posiciones con estado LIBRE porque contienen basura
        break;
    case BAJA:
        printf("\n %d - %s - %s - %s - %s", parametro.idPropietario, parametro.nombreApellido, parametro.direccion, parametro.numeroTarjeta, "[BAJA]");
        break;
    case OCUPADO:
        printf("\n %d - %s - %s - %s", parametro.idPropietario, parametro.nombreApellido, parametro.direccion, parametro.numeroTarjeta);
        break;
    default:
        printf("\n %d - %s - %s - %s - %s", parametro.idPropietario, parametro.nombreApellido, parametro.direccion, parametro.numeroTarjeta, "[N/A]");
        break;
    }
}

int ePropietario_mostrarListadoConOcupados(ePropietario listado[],int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && listado != NULL)
    {
        retorno = 0;
        for(i=0; i<limite; i++)
        {
            if(listado[i].estado==OCUPADO)
            {
                retorno = 1;
                //Se muestra al menos un elemento del array
                ePropietario_mostrarUno(listado[i]);
            }
        }

        if(retorno == 0)
        {
            printf("\n*** NO HAY ELEMENTOS PARA MOSTRAR ***");
        }
    }
    return retorno;
}

int ePropietario_mostrarListado(ePropietario listado[],int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && listado != NULL)
    {
        retorno = 0;
        for(i=0; i<limite; i++)
        {
            if(listado[i].estado==BAJA || listado[i].estado==OCUPADO)
            {
                retorno = 1;
                //Se muestra al menos un elemento del array
                ePropietario_mostrarUnoConEstado(listado[i]);
            }
        }

        if(retorno == 0)
        {
            printf("\n*** NO HAY ELEMENTOS PARA MOSTRAR ***");
        }
    }
    return retorno;
}

int ePropietario_alta(ePropietario listado[],int limite)
{
    int retorno = -1;
    ePropietario temporario;
    int indice;
    char confirma[3];

    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        //Busca lugar libre en el array
        indice = ePropietario_buscarLugarLibre(listado,limite);
        if(indice >= 0)
        {
            retorno = -3;
            //Campos con valores iniciales calculados
            temporario.idPropietario = ePropietario_siguienteId(listado,limite);
            temporario.estado = OCUPADO;

            retorno = -4;
            //Campos con valores pedidos al usuario
            do
            {
                pedirString("Ingrese nombre y apellido del propietario: ", temporario.nombreApellido, TAM_NOMBRE_APELLIDO);
                if(strcmp(temporario.nombreApellido, "") == 0)
                {
                    printf("El dato es obligatorio, por favor reingrese\n");
                }
            } while(strcmp(temporario.nombreApellido, "") == 0);

            do
            {
                pedirString("Ingrese direccion del propietario: ", temporario.direccion, TAM_DIRECCION);
                if(strcmp(temporario.direccion, "") == 0)
                {
                    printf("El dato es obligatorio, por favor reingrese\n");
                }
            } while(strcmp(temporario.direccion, "") == 0);

            do
            {
                pedirString("Ingrese numero de tarjeta de credito del propietario: ", temporario.numeroTarjeta, TAM_TARJETA);
                if(strcmp(temporario.numeroTarjeta, "") == 0)
                {
                    printf("El dato es obligatorio, por favor reingrese\n");
                }
            } while(strcmp(temporario.numeroTarjeta, "") == 0);

            retorno = -5;
            //Confirmación de la acción por parte del usuario
            do
            {
                printf("\nSe va a dar de alta:");
                ePropietario_mostrarUno(temporario);
                pedirString("\nConfirma esta accion? (S/N): ", confirma, 3);
                if(stricmp(confirma, "S") != 0 && stricmp(confirma, "N") != 0)
                {
                    printf("Debe ingresar S o N. Por favor reingrese\n");
                }
            } while(stricmp(confirma, "S") != 0 && stricmp(confirma, "N") != 0);

            if(stricmp(confirma, "S") == 0)
            {
                retorno = 0;
                //OK
                listado[indice] = temporario;
            }
            else //retorno = -5
            {
                printf("Accion cancelada por el usuario\n");
            }
        }
        else //retorno = -2
        {
            printf("No hay espacio suficiente para agregar datos\n");
        }
    }
    return retorno;
}

int ePropietario_baja(ePropietario listado[],int limite)
{
    int retorno = -1;
    int indice;
    int muestraListado;
    int id;
    char confirma[3];
    int cancelaAccion = 0;

    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        do
        {
            muestraListado = ePropietario_mostrarListadoConOcupados(listado, limite);

            switch(muestraListado)
            {
            case 0:
                printf("\nNo hay propietarios para dar de baja"); //retorno = -2
                break;
            case 1:
                id = pedirEnteroSinValidar("\nIngrese ID del propietario a dar de baja: ");
                indice = ePropietario_buscarPorId(listado, limite, id);
                if(indice < 0)
                {
                    printf("No se encontro el ID ingresado. Por favor reingrese\n");
                }
                else
                {
                    retorno = -3;
                    //Confirmación de la acción por parte del usuario
                    do
                    {
                        printf("\nSe va a dar de baja:");
                        ePropietario_mostrarUno(listado[indice]);
                        pedirString("\nConfirma esta accion? (S/N): ", confirma, 3);
                        if(stricmp(confirma, "S") != 0 && stricmp(confirma, "N") != 0)
                        {
                            printf("Debe ingresar S o N. Por favor reingrese\n");
                        }
                    } while(stricmp(confirma, "S") != 0 && stricmp(confirma, "N") != 0);

                    if(stricmp(confirma, "S") == 0)
                    {
                        retorno = 0;
                        //OK
                        listado[indice].estado = BAJA;
                    }
                    else //retorno = -3
                    {
                        printf("Accion cancelada por el usuario\n");
                        cancelaAccion = 1;
                    }
                }

                break;
            default:
                printf("\Error al listar...\n"); //retorno = -2
                break;
            }
        } while(indice < 0 && muestraListado == 1 && cancelaAccion == 0);
    }

    return retorno;
}

int ePropietario_modificacion(ePropietario listado[],int limite)
{
    int retorno = -1;
    int indice;
    int muestraListado;
    ePropietario temporario;
    char confirma[3];
    int cancelaAccion = 0;

    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        do
        {
            muestraListado = ePropietario_mostrarListadoConOcupados(listado, limite);

            switch(muestraListado)
            {
            case 0:
                printf("\nNo hay propietarios para modificar"); //retorno = -2
                break;
            case 1:
                temporario.idPropietario = pedirEnteroSinValidar("\nIngrese ID del propietario a modificar: ");
                indice = ePropietario_buscarPorId(listado, limite, temporario.idPropietario);
                if(indice < 0)
                {
                    printf("No se encontro el ID ingresado. Por favor reingrese\n");
                }
                else
                {
                    temporario = listado[indice];

                    retorno = -3;
                    //Modificación de campos
                    do
                    {
                        pedirString("Ingrese numero de tarjeta de credito del propietario: ", temporario.numeroTarjeta, TAM_TARJETA);
                        if(strcmp(temporario.numeroTarjeta, "") == 0)
                        {
                            printf("El dato es obligatorio, por favor reingrese\n");
                        }
                    } while(strcmp(temporario.numeroTarjeta, "") == 0);

                    retorno = -4;
                    //Confirmación de la acción por parte del usuario
                    do
                    {
                        printf("\nSe va a modificar:");
                        ePropietario_mostrarUno(listado[indice]);
                        printf("\nPor:");
                        ePropietario_mostrarUno(temporario);
                        pedirString("\nConfirma esta accion? (S/N): ", confirma, 3);
                        if(stricmp(confirma, "S") != 0 && stricmp(confirma, "N") != 0)
                        {
                            printf("Debe ingresar S o N. Por favor reingrese\n");
                        }
                    } while(stricmp(confirma, "S") != 0 && stricmp(confirma, "N") != 0);

                    if(stricmp(confirma, "S") == 0)
                    {
                        retorno = 0;
                        //OK
                        listado[indice] = temporario;
                    }
                    else //(retorno = -3 || retorno = -4)
                    {
                        printf("Accion cancelada por el usuario\n");
                        cancelaAccion = 1;
                    }
                }

                break;
            default:
                printf("\Error al listar...\n"); //retorno = -2
                break;
            }
        } while(indice < 0 && muestraListado == 1 && cancelaAccion == 0);
    }

    return retorno;
}
