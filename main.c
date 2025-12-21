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
    EstadoJuego estadoJuego = ESTADO_INICIO;
    Fondos *fondosJuego = crearFondos();
    subZero = cargarPersonaje(subZero, estado);
    subZero->frameActual = 0;
    scorpio = cargarPersonaje2(scorpio, estado);
    scorpio->frameActual = 0;
    Juego *juego = (Juego *)malloc(sizeof(Juego));
    juego->personaje1 = subZero;
    juego->personaje2 = scorpio;
    juego->fondosJuego = fondosJuego;
    juego->tecla = tecla;
    juego->teclaSoltada = teclaSoltada;
    juego->p1Listo = false;
    juego->p2Listo = false;
    iniciarJuego(juego, &estadoJuego);
    MenuSeleccion *menuSel = (MenuSeleccion *)malloc(sizeof(MenuSeleccion));
    menuSel->retrato = crearRetratos();
    menuSel->cursorP1 = (CursorSeleccion *)malloc(sizeof(CursorSeleccion));
    menuSel->cursorP2 = (CursorSeleccion *)malloc(sizeof(CursorSeleccion));
    menuSel->selP1 = LIUKANG;
    menuSel->selP2 = SCORPION;
    menuSel->datosJuego = juego;
    while (tecla != TECLAS.ESCAPE)
    {
        tecla = ventana.teclaPresionada();
        teclaSoltada = ventana.teclaSoltada();
        juego->tecla = tecla;
        juego->teclaSoltada = teclaSoltada;
        ventana.limpiaVentana();
        if (estadoJuego == ESTADO_MENUSELECCION)
        {
            menuLoop(menuSel, &estadoJuego);
        }

        if (estadoJuego == ESTADO_JUGANDO)
        {
            gameLoop(juego);
        }
        ventana.actualizaVentana();
        ventana.espera(50);
    }
    liberarPersonajeMemoria(juego->personaje1);
    liberarPersonajeMemoria(juego->personaje2);
    ventana.eliminaImagen(fondosJuego->fondoInicio);
    ventana.eliminaImagen(fondosJuego->fondoStage);
    free(juego);
    free(menuSel->cursorP1);
    free(menuSel->cursorP2);
    liberarImagenes(menuSel->retrato);
    free(menuSel->retrato);
    ventana.cierraVentana();
    return 0;
}