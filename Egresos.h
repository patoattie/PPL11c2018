#ifndef EGRESOS_H_INCLUDED
#define EGRESOS_H_INCLUDED

#define LIMITE_EGRESOS 200
#define OCUPADO 0
#define LIBRE 1
#define IMPORTE_ALPHA_ROMEO 150
#define IMPORTE_FERRARI 175
#define IMPORTE_AUDI 200
#define IMPORTE_OTRO 250

typedef struct
{
    int idEgreso;
    int idIngreso;
    float importe;
    int estado;
}eEgreso;

void eEgreso_init(eEgreso[],int limite);
int eEgreso_buscarPorId(eEgreso[] ,int limite, int id);
int eEgreso_siguienteId(eEgreso[] ,int limite);
int eEgreso_buscarLugarLibre(eEgreso listado[],int limite);

void eEgreso_mostrarTicket(int horasEstadia, float precioEstadia);

int eEgreso_alta(eEgreso[] ,int limite, int idIngreso, int horasEstadia, float precioEstadia);
int eEgreso_devolverHorasEstadia(void);

#endif // EGRESOS_H_INCLUDED

