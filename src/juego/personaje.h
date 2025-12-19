#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../graficos/graficos.h"

typedef struct {
    int derecha;
    int izquierda;
    int golpe;
    int golpe2;
    int patada;
} Controles;

typedef struct
{
    int x, y;
    int vida;
    int estado;
    int frameActual;
    int totalFrames;
    bool moviendoDerecha;
    bool moviendoIzquierda;
    Imagen **sprites;
    Imagen *animQuieto[4];
    Imagen *animCaminata[6];
    Imagen *animGolpe[3];
    Imagen *animGolpe2[3];
    Imagen *animPatada[4];
    Controles controls;
} Personaje;

typedef enum {
    QUIETO,
    CAMINANDO_DER,
    CAMINANDO_IZQ,
    GOLPEANDO,
    GOLPEANDO2,
    PATEANDO
} EstadoPersonaje;

/**
 * @brief Funcion que crea un personaje desde sus atributos hasta cada sprite que lo compone
 * 
 * @param personaje Puntero a la struct Personaje
 * @param estado Enumeracion que contiene los estados del personaje
 * @return Personaje* 
 */
Personaje *cargarPersonaje(Personaje *personaje, EstadoPersonaje estado);

/**
 * @brief Funcion que crea un personaje desde sus atributos hasta cada sprite que lo compone
 * 
 * @param personaje Puntero a la struct Personaje
 * @param estado Enumeracion que contiene los estados del personaje
 * @return Personaje* 
 */
Personaje *cargarPersonaje2(Personaje *personaje, EstadoPersonaje estado);

/**
 * @brief Funcion que dibuja al personaje en base a sus estados
 * 
 * @param personaje Puntero a la struct Personaje para acceder y modificar todos sus campos
 */
void dibujarPersonaje(Personaje *personaje);

/**
 * @brief Funcion que cambia el estado del personaje de acuerdo a las teclas presionadas
 * 
 * @param personaje Puntero a la struct Personaje para acceder y modificar todos sus campos
 * @param tecla El valor de la tecla presionada
 * @param teclaSoltada El valor de la tecla soltada
 */
void cambiarEstado(Personaje *personaje, int tecla, int teclaSoltada);

/**
 * @brief Funcion que delimita hasta donde se puede mover el personaje y que cambia sus estados y los frames a mostrar
 * 
 * @param personaje Puntero a la struct Personaje para acceder y modificar todos sus campos
 * @param tecla El valor de la tecla presionada
 * @param teclaSoltada El valor de la tecla soltada
 */
void actualizarMovimiento(Personaje *personaje, int tecla, int teclaSoltada);

/**
 * @brief Funcion que libera toda la memoria dinamica reservada para los sprites del personaje asi como a los mismos
 * 
 * @param personaje Puntero a la struct Personaje para acceder y modificar todos sus campos
 */
void liberarPersonajeMemoria(Personaje *personaje);

#endif