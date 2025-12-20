#include <stdio.h>
#include <stdlib.h>
#include "./src/graficos/graficos.h"
#include "./src/juego/personaje.h"
#include "./src/juego/juego.h"

int main()
{
    ventana.tamanioVentana(1280, 720);
    ventana.tituloVentana("Mortal Kombat");
    ventana.cambiarIconoVentana();
    int tecla = ventana.teclaPresionada();
    int teclaSoltada = ventana.teclaSoltada();
    Personaje *subZero = NULL;
    Personaje *scorpio = NULL;
    EstadoPersonaje estado = QUIETO;    
    Imagen *fondoStage = crearFondoStage();
    subZero = cargarPersonaje(subZero, estado);
    subZero->frameActual = 0;
    scorpio = cargarPersonaje2(scorpio, estado);
    scorpio->frameActual = 0;
    while (tecla != TECLAS.ESCAPE)
    {
        tecla = ventana.teclaPresionada();
        teclaSoltada = ventana.teclaSoltada();
        ventana.limpiaVentana();
        dibujarEscenario(fondoStage);
        animacionPersonaje(subZero, scorpio, tecla, teclaSoltada);
        ventana.actualizaVentana();
        ventana.espera(50);
    }
    liberarPersonajeMemoria(subZero);
    liberarPersonajeMemoria(scorpio);
    ventana.eliminaImagen(fondoStage);
    ventana.cierraVentana();
    return 0;
}