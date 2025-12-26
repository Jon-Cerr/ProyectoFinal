#include <stdio.h>
#include <stdlib.h>
#include "./src/graficos/graficos.h"
#include "./src/juego/personaje.h"
#include "./src/juego/juego.h"
#include "./src/esp32/simplecontroller.h"
#include "./src/juego/podio_marcadores.h"
#define DERECHA 15
#define IZQUIERDA 18
#define DEFENSA 19
#define GOLPE1 22
#define GOLPE2 23
#define PATADA 21

int main()
{
    ventana.tamanioVentana(1280, 720);
    ventana.tituloVentana("Mortal Kombat");
    ventana.cambiarIconoVentana();
    int tecla = ventana.teclaPresionada();
    int teclaSoltada = ventana.teclaSoltada();
    Personaje *jugador1 = NULL;
    Personaje *jugador2 = NULL;
    EstadoPersonaje estado = QUIETO;
    EstadoJuego estadoJuego = ESTADO_INICIO;
    Fondos *fondosJuego = crearFondos();
    Juego *juego = (Juego *)malloc(sizeof(Juego));
    juego->personaje1 = jugador1;
    juego->personaje2 = jugador2;
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
    menuSel->duracionTransicion = 50;
    cargarPodio(juego);
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

        else if (estadoJuego == ESTADO_JUGANDO)
        {
            gameLoop(juego, menuSel, &estadoJuego);
        }
        else if (estadoJuego == ESTADO_FATALITY)
        {
            dibujarEscenario(fondosJuego);
            ejecutarLogicaFatality(juego, &estadoJuego, menuSel);
        }
        else if (estadoJuego == ESTADO_PODIO)
        {
            mostrarMarcadores(&estadoJuego, juego);
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
    free(menuSel);
    free(fondosJuego);
    ventana.cierraVentana();
    return 0;
}