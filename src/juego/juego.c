#include "../graficos/graficos.h"
#include "./juego.h"

void dibujarEscenario(Imagen *fondoStage)
{
    if (fondoStage != NULL)
    {
        ventana.muestraImagenEscalada(0, 0, ventana.anchoVentana(), ventana.altoVentana(), fondoStage);
    }
}

Imagen *crearFondoStage()
{
    Imagen *fondoStage = ventana.creaImagen("assets/img/fondo_stage.bmp");
    if (fondoStage == NULL) {
        ventana.muestraMensaje("No se pudo cargar el fondo");
    } else {
        ventana.muestraMensaje("Todo fino!");
        printf("Fondo cargado con exito.\n");
    }
    return fondoStage;
}

void animacionPersonaje(Personaje *personaje)
{
    actualizarMovimiento(personaje);
    dibujarPersonaje(personaje);
}