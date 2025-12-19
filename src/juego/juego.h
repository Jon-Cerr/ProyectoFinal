#ifndef JUEGO_H_
#define JUEGO_H_
#include "./personaje.h"

typedef struct {
    Imagen *fondoStage;
} Juego;

/**
 * @brief Funcion que dibuja el stage
 * 
 * @param fondoStage Puntero a la struct Juego que contiene un campo que apunta a la funcion Imagen de la libreria de graficos y que almacena el fondo
 */
void dibujarEscenario(Imagen *fondoStage);

/**
 * @brief Funcion que se encarga del dibujado del personaje
 * 
 * @param personaje Puntero a la struct personaje
 * @param tecla Valor de la tecla presionada
 * @param teclaSoltada Valor de la tecla soltada
 */
void animacionPersonaje(Personaje *personaje, int tecla, int teclaSoltada);

/**
 * @brief Funcion que crea la imagen del escenario
 * 
 * @return Imagen* 
 */
Imagen *crearFondoStage();
#endif