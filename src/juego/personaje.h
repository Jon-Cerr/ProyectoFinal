#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../graficos/graficos.h"
struct MenuSeleccion;
typedef struct MenuSeleccion MenuSeleccion;

// estados del juego
typedef enum
{
    ESTADO_INICIO,
    ESTADO_MENUSELECCION,
    ESTADO_JUGANDO,
    ESTADO_FATALITY,
    ESTADO_PODIO,
} EstadoJuego;

// contiene la informacion de los controles para inicializar sus valores acorde al personaje que se crea
typedef struct
{
    int derecha;
    int izquierda;
    int golpe;
    int golpe2;
    int patada;
    int defensa;
} Controles;

// struct para almacemar el numero de sprites a crear por cada animacion
typedef struct {
     int numSpritesFatality; int numSpritesAbatido; int numSpritesTecnica;
} SpritesFatality;

// contiene punteros dobles a la struct Imagen de la libreria de graficos para generar imagenes dinamicas en ejecucion del programa para no usar arreglos estaticos
typedef struct
{
    Imagen **personajeFatality;
    Imagen **personajeAbatido;
    Imagen **dibujoTecnica;
    int totalFrames;
    int frameActual;
} Fatality;

// contiene todos los campos necesarios para la logica del personaje, asi como arreglos dinamicos (punteros dobles) para generar los sprites correspondientes
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
    Fatality *fatalityGolpe;
} Personaje;

// contiene los estados del personaje para manejar ciertos comportamientos y funciones 
typedef enum
{
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

typedef struct {
    char nombreGanador[20];
    int victorias;
} RegistroGanador;

/**
 * @brief Funcion que crea un personaje desde sus atributos hasta cada sprite que lo compone
 *
 * @param personaje Puntero a la struct Personaje
 * @param estado Enumeracion que contiene los estados del personaje
 * @param nombrePersonaje contiene la cadena de texto para crear los sprites acorde a la cadena pasada en la llamada a la funcion
 * @return Personaje*
 */
Personaje *cargarPersonaje(Personaje *personaje, EstadoPersonaje estado, const char *nombrePersonaje);

/**
 * @brief Funcion que crea un personaje desde sus atributos hasta cada sprite que lo compone
 *
 * @param personaje Puntero a la struct Personaje
 * @param estado Enumeracion que contiene los estados del personaje
 * @param nombrePersonaje contiene la cadena de texto para crear los sprites acorde a la cadena pasada en la llamada a la funcion
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
 * @brief Funcion que cambia el estado del personaje de acuerdo a las teclas presionadas y sus estados correspondientes
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
 * @param menuSel Puntero a la struct MenuSeleccion para acceder a sus campos y tomar los valores correspondientes para dibujar el HUD acorde a los mismos
 */
void dibujarHUD(Personaje *personaje, int tecla, MenuSeleccion *menuSel);

/**
 * @brief Funcion que se encarga ed dibujar la barra de vida del personaje de acuerdo al campo vida de la struct Personaje
 *
 * @param personaje Puntero a la struct Personaje para acceder y modificar todos sus campos
 * @param tecla tipo de dato int que retorna o reciba el valor de la tecla presionada
 * @param menuSel Puntero a la struct MenuSeleccion para acceder a sus campos y tomar los valores correspondientes para dibujar el HUD acorde a los mismos
 */
void dibujarHUDP2(Personaje *personaje, int tecla, MenuSeleccion *menuSel);

/**
 * @brief Funcion que detecta la colision de personaje1 y personaje2 acorde a sus coordenadas
 *
 * @param personaje1 Puntero a la struct Personaje que recibe el puntero del mismo tipo desde el main y que recibe el valor de personaje1
 * @param personaje2 Puntero a la struct Personaje que recibe el puntero del mismo tipo desde el main y que recibe el valor de personaje2
 * @param menuSel Puntero a la struct MenuSeleccion para acceder a sus campos y tomar los valores correspondientes para dibujar el HUD acorde a los mismos
 * @param estado Puntero a la enum EstadoJuego para leer los valores persistentes en la ejecucion del programa y cambiar su valor acorde a condiciones y fuinciones
 * @param tecla tipo de dato int que retorna o reciba el valor de la tecla presionada
 */
void detectarColision(Personaje *personaje1, Personaje *personaje2, int tecla, MenuSeleccion *menuSel, EstadoJuego *estado);

/**
 * @brief Funcion que se encarga de cargar la logica para la ejecucion del fatality para manejar los recursos de forma adecuada
 * 
 * @param ganador Puntero a la struct ganador que arroja los datos del personaje ganador pasado durante la ejecucion de detectarColision, que retorna el valor del personaje ganador
 * @param perdedor Puntero a la struct perdedor que arroja los datos del personaje perdedor pasado durante la ejecucion de detectarColision, que retorna el valor del personaje perdedor
 * @param menuSel Puntero a la struct MenuSeleccion para manejar y modificar directamente los campos del menu para realizar ciertas condiciones
 */
void cargarAnimacionFatality(Personaje *ganador, MenuSeleccion *menuSel);

/**
 * @brief Funcion que se encarga de cargar los aprites de la animacion del fatality acorde a cada personaje, pues cada uno tiene distintos numero de sprites
 * 
 * @param ganador puntero a la struct Personaje para acceder a los campos del ganador y modificarlos adecuadamente
 * @param nombreGanador tipo de dato que represente el nombre del ganador 
 * @param sprites Puntero a la struct SpritesFatality que contiene los campos para manejar el numero de sprites por cada animacion
 */
void cargarSpritesFatality(Personaje *ganador, const char *nombreGanador, SpritesFatality *sprites);

/**
 * @brief Funcion que se encarga de dibujar la escena del fatality accediendo a los campos de las structs Personaje acorde al ganador y el perdedor
 * 
 * @param ganador Puntero a la struct ganador que arroja los datos del personaje ganador pasado durante la ejecucion de detectarColision, que retorna el valor del personaje ganador
 * @param perdedor Puntero a la struct perdedor que arroja los datos del personaje perdedor pasado durante la ejecucion de detectarColision, que retorna el valor del personaje perdedor
 */
void dibujarEscenaFatality(Personaje *ganador, Personaje *perdedor);

#endif