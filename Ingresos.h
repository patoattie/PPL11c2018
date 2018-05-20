#ifndef INGRESOS_H_INCLUDED
#define INGRESOS_H_INCLUDED

#define LIMITE_INGRESOS 200
#define INGRESADO 0
#define LIBRE 1
#define RETIRADO 2

typedef struct
{
    int idIngreso;
    int idAutomovil;
    int estado;
}eIngreso;

void eIngreso_init(eIngreso[],int limite);
int eIngreso_buscarPorId(eIngreso[] ,int limite, int id);
int eIngreso_buscarPorIdAutomovil(eIngreso[] ,int limite, int idAutomovil);
int eIngreso_siguienteId(eIngreso[] ,int limite);
int eIngreso_buscarLugarLibre(eIngreso listado[],int limite);

void eIngreso_mostrarUno(eIngreso parametro, char nombrePropietario[], char patente[], char marca[]);

int eIngreso_alta(eIngreso[] ,int limite, int idAutomovil);
int eIngreso_baja(eIngreso[] ,int limite, int idAutomovil);

#endif // INGRESOS_H_INCLUDED
