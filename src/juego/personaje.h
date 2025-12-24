#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../graficos/graficos.h"
struct MenuSeleccion;
typedef struct MenuSeleccion MenuSeleccion;

typedef struct {
    int derecha;
    int izquierda;
    int golpe;
    int golpe2;
    int patada;
    int defensa;
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
    bool defendiendo;
    Imagen **sprites;
    Imagen *animQuieto[4];
    Imagen *animCaminata[6];
    Imagen *animGolpe[3];
    Imagen *animGolpe2[3];
    Imagen *animPatada[4];
    Imagen *animGolpeado[3];
    Imagen *animDefensa[3];
    Imagen *animAbatido[7];
    Controles controls;
} Personaje;

typedef enum {
    QUIETO,
    CAMINANDO_DER,
    CAMINANDO_IZQ,
    GOLPEANDO,
    GOLPEANDO2,
    PATEANDO,
    GOLPEADO,
    DEFENSA,
    ABATIDO,
} EstadoPersonaje;

/**
 * @brief Funcion que crea un personaje desde sus atributos hasta cada sprite que lo compone
 * 
 * @param personaje Puntero a la struct Personaje
 * @param estado Enumeracion que contiene los estados del personaje
 * @return Personaje* 
 */
Personaje *cargarPersonaje(Personaje *personaje, EstadoPersonaje estado, const char *nombrePersonaje);

/**
 * @brief Funcion que crea un personaje desde sus atributos hasta cada sprite que lo compone
 * 
 * @param personaje Puntero a la struct Personaje
 * @param estado Enumeracion que contiene los estados del personaje
 * @return Personaje* 
 */
Personaje *cargarPersonaje2(Personaje *personaje, EstadoPersonaje estado, const char *nombrePersonaje);

/**
 * @brief Funcion que se encarga de llenar el puntero **sprites y los arreglos de animacion para cada personaje
 * 
 * @param personaje Puntero a la struct Personaje
 * @param nombrePersonaje Tipo de dato const char * que representa el nombre del personaje
 */
void cargarSprites(Personaje *personaje, const char *nombrePersonaje);

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

/**
 * @brief Funcion que se encarga ed dibujar la barra de vida del personaje de acuerdo al campo vida de la struct Personaje
 * 
 * @param personaje Puntero a la struct Personaje para acceder y modificar todos sus campos
 * @param tecla tipo de dato int que retorna o reciba el valor de la tecla presionada
 */
void dibujarHUD(Personaje *personaje, int tecla, MenuSeleccion *menuSel);

/**
 * @brief Funcion que se encarga ed dibujar la barra de vida del personaje de acuerdo al campo vida de la struct Personaje
 * 
 * @param personaje Puntero a la struct Personaje para acceder y modificar todos sus campos
 * @param tecla tipo de dato int que retorna o reciba el valor de la tecla presionada
 */
void dibujarHUDP2(Personaje *personaje, int tecla, MenuSeleccion *menuSel);


/**
 * @brief Funcion que detecta la colision de personaje1 y personaje2 acorde a sus coordenadas
 * 
 * @param personaje1 Puntero a la struct Personaje que recibe el puntero del mismo tipo desde el main y que recibe el valor de personaje1
 * @param personaje2 Puntero a la struct Personaje que recibe el puntero del mismo tipo desde el main y que recibe el valor de personaje2
 * @param tecla tipo de dato int que retorna o reciba el valor de la tecla presionada
 */
void detectarColision(Personaje *personaje1, Personaje *personaje2, int tecla);

#endif