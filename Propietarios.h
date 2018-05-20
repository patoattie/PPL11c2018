#ifndef PROPIETARIOS_H_INCLUDED
#define PROPIETARIOS_H_INCLUDED

#define TAM_NOMBRE_APELLIDO 100
#define TAM_DIRECCION 50
#define TAM_TARJETA 50
#define LIMITE_PROPIETARIOS 200
#define OCUPADO 0
#define LIBRE 1
#define BAJA 2

typedef struct
{
    int idPropietario;
    char nombreApellido[TAM_NOMBRE_APELLIDO];
    char direccion[TAM_DIRECCION];
    char numeroTarjeta[TAM_TARJETA];
    int estado;
}ePropietario;

void ePropietario_init(ePropietario[],int limite);
void ePropietario_hardcodeo(ePropietario[],int limite);
int ePropietario_buscarPorId(ePropietario[] ,int limite, int id);
int ePropietario_siguienteId(ePropietario[] ,int limite);
int ePropietario_buscarLugarLibre(ePropietario listado[],int limite);

void ePropietario_mostrarUno(ePropietario parametro);
void ePropietario_mostrarUnoConEstado(ePropietario parametro);
int ePropietario_mostrarListado(ePropietario[] ,int limite);
int ePropietario_mostrarListadoConOcupados(ePropietario[] ,int limite);

int ePropietario_alta(ePropietario[] ,int limite);
int ePropietario_modificacion(ePropietario[] ,int limite);

#endif // PROPIETARIOS_H_INCLUDED
