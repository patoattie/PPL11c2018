#ifndef INGRESOS_H_INCLUDED
#define INGRESOS_H_INCLUDED

#define LIMITE_INGRESOS 200
#define TAM_PATENTE 10
#define TAM_MARCA 20
#define ALPHA_ROMEO 1
#define FERRARI 2
#define AUDI 3
#define OTRO 4

typedef struct
{
    int idIngreso;
    char patente[TAM_PATENTE];
    int marca;
    int idPropietario;
    int estado;
}eIngreso;

void eIngreso_init(eAutomovil[],int limite);
void eIngreso_hardcodeo(eAutomovil[],int limite);
int eIngreso_buscarPorId(eAutomovil[] ,int limite, int id);
int eIngreso_siguienteId(eAutomovil[] ,int limite);
int eIngreso_buscarLugarLibre(eAutomovil listado[],int limite);

void eIngreso_mostrarUno(eAutomovil parametro, char nombrePropietario[]);
void eIngreso_mostrarUnoConEstado(eAutomovil parametro, char nombrePropietario[]);
int eIngreso_mostrarListado(eAutomovil[], ePropietario[], int limiteAutomoviles, int limitePropietarios);
int eIngreso_mostrarListadoConOcupados(eAutomovil[], ePropietario[], int limiteAutomoviles, int limitePropietarios);

int eIngreso_alta(eAutomovil[] ,int limite);

void retornaMarca(int marca, char nombreMarca[]);


#endif // INGRESOS_H_INCLUDED
