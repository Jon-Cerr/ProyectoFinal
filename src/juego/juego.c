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
    if (fondoStage == NULL)
    {
        ventana.muestraMensaje("No se pudo cargar el fondo");
    }
    else
    {
        ventana.muestraMensaje("Todo fino!");
        printf("Fondo cargado con exito.\n");
    }
    return fondoStage;
}

void animacionPersonaje(Personaje *personaje1, Personaje *personaje2, int tecla, int teclaSoltada)
{
    actualizarMovimiento(personaje1, tecla, teclaSoltada);
    dibujarPersonaje(personaje1);
    actualizarMovimiento(personaje2, tecla, teclaSoltada);
    dibujarPersonaje(personaje2);
    dibujarHUD(personaje1, tecla);
    dibujarHUDP2(personaje2, tecla);
    detectarColision(personaje1, personaje2, tecla);
}

void gameLoop(Imagen *fondoStage, Personaje *personaje, int tecla, int teclaSoltada)
{
    dibujarEscenario(fondoStage);
    // animacionPersonaje(personaje, tecla, teclaSoltada);
    // animacionPersonaje(personaje, tecla, teclaSoltada);
}