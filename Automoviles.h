#ifndef AUTOMOVILES_H_INCLUDED
#define AUTOMOVILES_H_INCLUDED

#include "Propietarios.h"

#define LIMITE_AUTOMOVILES 20
#define TAM_PATENTE 20
#define TAM_MARCA 20
#define ALPHA_ROMEO 1
#define FERRARI 2
#define AUDI 3
#define OTRO 4

typedef struct
{
    int idAutomovil;
    char patente[TAM_PATENTE];
    int marca;
    int idPropietario;
    int estado;
}eAutomovil;

void eAutomovil_init(eAutomovil[],int limite);
void eAutomovil_hardcodeo(eAutomovil[],int limite);
int eAutomovil_buscarPorId(eAutomovil[] ,int limite, int id);
int eAutomovil_siguienteId(eAutomovil[] ,int limite);
int eAutomovil_buscarLugarLibre(eAutomovil listado[],int limite);

void eAutomovil_mostrarUno(eAutomovil parametro, char nombrePropietario[]);
void eAutomovil_mostrarUnoConEstado(eAutomovil parametro, char nombrePropietario[]);
int eAutomovil_mostrarListado(eAutomovil[], ePropietario[], int limiteAutomoviles, int limitePropietarios);
int eAutomovil_mostrarListadoConOcupados(eAutomovil[], ePropietario[], int limiteAutomoviles, int limitePropietarios);

int eAutomovil_ingreso(eAutomovil listaAutomoviles[], ePropietario listaPropietarios[], int limiteAutomoviles, int limitePropietarios);
int eAutomovil_egreso(eAutomovil[] ,int limite);

void retornaMarca(int marca, char nombreMarca[]);

#endif // AUTOMOVILES_H_INCLUDED
