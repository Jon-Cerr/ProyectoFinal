#ifndef JUEGO_H_
#define JUEGO_H_
#include "./personaje.h"

typedef struct {
    Imagen *fondoStage;
} Juego;

void dibujarEscenario(Imagen *fondoStage);
void animacionPersonaje(Personaje *personaje);
Imagen *crearFondoStage();
#endif