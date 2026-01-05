/**
 * @file main.c
 * @author Alan Jonathan Cerritos Hernandez (alanchdez147@gmail.com) 2026640080
 * @author Ricardo Chaparro Zarco (ricardochzarco@gmail.com) 2026640302
 * @author Jesus Roque Lopez (jesusroquelopez22@gmail.com) 2026640210
 * @brief Archivo main del proyecto 
 * @version 0.1
 * @date 2026-01-04
 * Proyecto Final
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "./src/graficos/graficos.h"
#include "./src/juego/personaje.h"
#include "./src/juego/juego.h"
#include "./src/esp32/simplecontroller.h"
#include "./src/juego/podio_marcadores.h"
#define DERECHA 22
#define IZQUIERDA 23
#define DEFENSA_ESP32 21
#define GOLPE1 19
#define GOLPE2 18
#define PATADA 15

int main()
{
    ventana.tamanioVentana(1280, 720);
    ventana.tituloVentana("Mortal Kombat");
    ventana.cambiarIconoVentana();
    int tecla = ventana.teclaPresionada();
    int teclaSoltada = ventana.teclaSoltada();
    Board *esp32 = connectDevice("COM3", B115200);

    if (esp32 != NULL)
    {
        esp32->pinMode(esp32, DERECHA, INPUT_PULLUP);
        esp32->pinMode(esp32, IZQUIERDA, INPUT_PULLUP);
        esp32->pinMode(esp32, DEFENSA_ESP32, INPUT_PULLUP);
        esp32->pinMode(esp32, GOLPE1, INPUT_PULLUP);
        esp32->pinMode(esp32, GOLPE2, INPUT_PULLUP);
        esp32->pinMode(esp32, PATADA, INPUT_PULLUP);
        ventana.espera(10);
    }
    else
    {
        ventana.muestraMensaje("Error al conectar con el ESP32. Verifique si el control esta conectado.");
    }
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
    juego->timerTransicionAMenu = 150;
    MenuSeleccion *menuSel = (MenuSeleccion *)malloc(sizeof(MenuSeleccion));
    menuSel->retrato = crearRetratos();
    menuSel->cursorP1 = (CursorSeleccion *)malloc(sizeof(CursorSeleccion));
    menuSel->cursorP2 = (CursorSeleccion *)malloc(sizeof(CursorSeleccion));
    menuSel->selP1 = LIUKANG;
    menuSel->selP2 = SCORPION;
    menuSel->datosJuego = juego;
    menuSel->duracionTransicion = 50;
    iniciarJuego(juego, &estadoJuego);
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
            gameLoop(juego, menuSel, &estadoJuego, esp32);
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