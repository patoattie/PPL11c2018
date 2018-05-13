#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Programacion-I/pattie/Funciones/funciones.h"
#include "Ingresos.h"

void eIngreso_init(eIngreso listado[],int limite)
{
    int i;
    if(limite > 0 && listado != NULL)
    {
        for(i=0; i<limite; i++)
        {
            listado[i].estado= LIBRE;
            listado[i].idIngreso= 0;
        }
    }
}

void eIngreso_hardcodeo(eIngreso listado[],int limite)
{
    int i;
    int id[10]= {1,2,3,4,5,6,7,8,9,10};

    eIngreso_init(listado, limite);

    for(i = 0; i < 10; i++)
    {
        listado[i].idIngreso = id[i];
        listado[i].idAutomovil = id[i];
        listado[i].estado = INGRESADO;
    }
}
int eIngreso_buscarLugarLibre(eIngreso listado[],int limite)
{
    int retorno = -1;
    int i;
    int posicionLibre = -1; //Guarda la primer posicion con estado LIBRE que encuentra

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

        if(posicionLibre >= 0)
        {
            retorno = posicionLibre; //Retorno la primera posición con estado LIBRE
        }
    }

    return retorno;
}

int eIngreso_siguienteId(eIngreso listado[],int limite)
{
    int retorno = 0;
    int i;
    if(limite > 0 && listado != NULL)
    {
        for(i=0; i<limite; i++)
        {
            if(listado[i].estado == INGRESADO || listado[i].estado == RETIRADO)
            {
                    if(listado[i].idIngreso>retorno)
                    {
                         retorno=listado[i].idIngreso;
                    }

            }
        }
    }

    return retorno+1; //Retorno el mayor ID más 1
}


int eIngreso_buscarPorId(eIngreso listado[] ,int limite, int id)
{
    int retorno = -1;
    int i;
    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(listado[i].estado == INGRESADO && listado[i].idIngreso == id)
            {
                retorno = i;
                //Hallé el elemento que buscaba y retorno su indice
                break;
            }
        }
    }
    return retorno;
}

int eIngreso_alta(eIngreso listado[], int limite, int idAutomovil)
{
    int retorno = -1;
    int indice;

    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        //Busca lugar libre en el array
        indice = eIngreso_buscarLugarLibre(listado,limite);
        if(indice >= 0)
        {
            retorno = 0;
            //OK
            listado[indice].idIngreso = eIngreso_siguienteId(listado,limite);
            listado[indice].idAutomovil = idAutomovil;
            listado[indice].estado = INGRESADO;
        }
        else //retorno = -2
        {
            printf("No hay espacio suficiente para agregar datos\n");
        }
    }
    return retorno;
}
