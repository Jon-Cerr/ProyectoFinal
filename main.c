#include <stdio.h>
#include <stdlib.h>
#include "./src/graficos/graficos.h"
#include "./src/juego/personaje.h"
#include "./src/juego/juego.h"

int main()
{
    ventana.tamanioVentana(1280, 720);
    ventana.tituloVentana("Mortal Kombat");
    int tecla = ventana.teclaPresionada();
    Personaje *subZero = NULL;
    EstadoPersonaje estado = QUIETO;
    Imagen *fondoStage = crearFondoStage();
    subZero = cargarPersonaje(subZero, estado);
    subZero->frameActual = 0;
    while (tecla != TECLAS.ESCAPE)
    {
        tecla = ventana.teclaPresionada();
        ventana.limpiaVentana();
        dibujarEscenario(fondoStage);
        animacionPersonaje(subZero);
        ventana.actualizaVentana();
        ventana.espera(100);
    }
    ventana.eliminaImagen(fondoStage);
    ventana.cierraVentana();
    return 0;
}