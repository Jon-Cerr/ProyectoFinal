#ifndef PODIO_MARCADORES_H
#define PODIO_MARCADORES_H

#include "personaje.h"
#include "../graficos/graficos.h"
struct Juego; 
typedef struct Juego Juego;

/**
 * @brief Funcion que se encarga de dibujar en pantalla el marcador-podio con los datos de los ganadores
 * 
 * @param estadoJuego Puntero a la enum EstadoJuego para acceder y modificar directamente el estado del juego
 * @param juego Puntero a la struct Juego para acceder y modificar los campos de dicha struct para poder leer los datos
 */
void mostrarMarcadores(EstadoJuego *estadoJuego, Juego *juego);

/**
 * @brief Funcion que se encarga de cargar el archivo binario. Lo crea si no existe y simplemente lo lee si ya existe
 * 
 * @param juego Puntero a la struct Juego para acceder a todos los campos del juego para poder leer y escirbir dentro del archivo binario
 */
void cargarPodio(Juego *juego);

/**
 * @brief Funcion que se encarga de cargar en memoria y en el archivo el nombre del personaje que gano en la ronda
 * 
 * @param juego Puntero a la struct Juego para acceder a todos los campos del juego para poder leer y escirbir dentro del archivo binario
 * @param nombreGanador Tipo de dato char que representa el nombre del ganador
 */
void registrarVictoria(Juego *juego, const char *nombreGanador);

#endif