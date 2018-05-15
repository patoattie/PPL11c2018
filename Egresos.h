#ifndef EGRESOS_H_INCLUDED
#define EGRESOS_H_INCLUDED

#define LIMITE_EGRESOS 200
#define OCUPADO 0
#define LIBRE 1

typedef struct
{
    int idEgreso;
    int idIngreso;
    float importe;
    int estado;
}eEgreso;

void eEgreso_init(eEgreso[],int limite);
void eEgreso_hardcodeo(eEgreso[],int limite);
int eEgreso_buscarPorId(eEgreso[] ,int limite, int id);
int eEgreso_siguienteId(eEgreso[] ,int limite);
int eEgreso_buscarLugarLibre(eEgreso listado[],int limite);

int eEgreso_alta(eEgreso[] ,int limite, int idIngreso);
int eEgreso_devolverHorasEstadia(void);

#endif // EGRESOS_H_INCLUDED

