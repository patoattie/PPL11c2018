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

void eEgreso_mostrarTicket(char nombrePropietario[], char patenteAutomovil[], char marcaAutomovil[], int horasEstadia, float precioEstadia)
{
    float importeEstadia = (float)horasEstadia * precioEstadia;
    printf("\nNombre del Propietario: %s\nPatente del Automovil: %s\nMarca del Automovil: %s\nValor de la Estadia: %5.2f", nombrePropietario, patenteAutomovil, marcaAutomovil, importeEstadia);

}

int eEgreso_alta(eEgreso listado[], int limite, int idIngreso, char nombrePropietario[], char patenteAutomovil[], char marcaAutomovil[], int horasEstadia, float precioEstadia)
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
            retorno = 0; //OK
            eEgreso_mostrarTicket(nombrePropietario, patenteAutomovil, marcaAutomovil, horasEstadia, precioEstadia);
            pausarEjecucion();
            listado[indice].idEgreso = eEgreso_siguienteId(listado,limite);
            listado[indice].idIngreso = idIngreso;
            listado[indice].importe = (float)horasEstadia * precioEstadia;
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
