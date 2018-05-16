#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Programacion-I/pattie/Funciones/funciones.h"
#include "Egresos.h"

void eEgreso_init(eEgreso listado[],int limite)
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

void eEgreso_hardcodeo(eEgreso listado[],int limite)
{
    int i;
    int id[10]= {1,2,3,4,5,6,7,8,9,10};
    float importe[10]= {100,200,100,300,100,100,200,200,100,100};

    eEgreso_init(listado, limite);

    for(i = 0; i < 10; i++)
    {
        listado[i].idEgreso = id[i];
        listado[i].idIngreso = id[i];
        listado[i].importe = importe[i];
        listado[i].estado = INGRESADO;
    }
}
int eEgreso_buscarLugarLibre(eEgreso listado[],int limite)
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

int eEgreso_siguienteId(eEgreso listado[],int limite)
{
    int retorno = 0;
    int i;
    if(limite > 0 && listado != NULL)
    {
        for(i=0; i<limite; i++)
        {
            if(listado[i].estado == OCUPADO)
            {
                    if(listado[i].idEgreso>retorno)
                    {
                         retorno=listado[i].idEgreso;
                    }

            }
        }
    }

    return retorno+1; //Retorno el mayor ID más 1
}


int eEgreso_buscarPorId(eEgreso listado[] ,int limite, int id)
{
    int retorno = -1;
    int i;
    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(listado[i].estado == OCUPADO && listado[i].idEgreso == id)
            {
                retorno = i;
                //Hallé el elemento que buscaba y retorno su indice
                break;
            }
        }
    }
    return retorno;
}

int eEgreso_alta(eEgreso listado[], int limite, int idIngreso, int horasEstadia, float importeEstadia)
{
    int retorno = -1;
    int indice;

    if(limite > 0 && listado != NULL)
    {
        retorno = -2;
        //Busca lugar libre en el array
        indice = eEgreso_buscarLugarLibre(listado,limite);
        if(indice >= 0)
        {
            retorno = 0;
            //OK
            listado[indice].idEgreso = eEgreso_siguienteId(listado,limite);
            listado[indice].idIngreso = idIngreso;
            listado[indice].estado = OCUPADO;
        }
        else //retorno = -2
        {
            printf("No hay espacio suficiente para agregar datos\n");
        }
    }
    return retorno;
}

int eEgreso_devolverHorasEstadia(void)
{
    int horas;

    srand(time(NULL));

    horas = (rand()%24)+1;

    return horas ;

}
