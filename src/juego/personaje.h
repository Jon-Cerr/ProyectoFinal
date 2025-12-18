#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../graficos/graficos.h"

typedef struct
{
    int x, y;
    int vida;
    int estado;
    int frameActual;
    int totalFrames;
    Imagen **sprites;
    Imagen *animQuieto[4];
    Imagen *animCaminata[6];
} Personaje;

typedef enum {
    QUIETO,
    CAMINANDO_DER,
    CAMINANDO_IZQ,
} EstadoPersonaje;

/**
 * @brief Funcion que crea un personaje desde sus atributos hasta cada sprite que lo compone
 * 
 * @param personaje Puntero a la struct Personaje
 * @param estado Enumeracion que contiene los estados del personaje
 * @return Personaje* 
 */
Personaje *cargarPersonaje(Personaje *personaje, EstadoPersonaje estado);

void dibujarPersonaje(Personaje *personaje);

void cambiarEstado(Personaje *personaje);

void actualizarMovimiento(Personaje *personaje);

#endif