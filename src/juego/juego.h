#ifndef JUEGO_H_
#define JUEGO_H_
#include "./personaje.h"

//integrar imagenes/almacenar  punteros
typedef struct Fondos
{
    Imagen *fondoInicio;
    Imagen *fondoStage;
} Fondos;

typedef struct Personaje *personaje1;
typedef struct Personaje *personaje2;

//campos necesarios para el Juego, varios apuntan a otras structs
typedef struct
{
    Personaje *personaje1;
    Personaje *personaje2;
    int tecla;
    int teclaSoltada;
    Fondos *fondosJuego;
    int identificadorP1;
    int identificadorP2;
    bool p1Listo;
    bool p2Listo;
} Juego;

//estados del juego
typedef enum
{
    ESTADO_INICIO,
    ESTADO_MENUSELECCION,
    ESTADO_JUGANDO
} EstadoJuego;

//integrar imagenes/almacenar punteros de imagenes con los retratos de los personajes disponibles
typedef struct
{
    Imagen *liuKang;
    Imagen *scorpion;
    Imagen *subZero;
    Imagen *raiden;
    Imagen *liuKangSeleccionado;
    Imagen *scorpionSeleccionado;
    Imagen *subZeroSeleccionado;
    Imagen *raidenSeleccionado;
    Imagen *fondoSeleccion;
    Imagen *contenedorRetrato;
    Imagen *cursorSelector;
    Imagen *cursorSelectorP2;
} AssetsRetratos;

//struct que sirve para cambiar el cursor/selector de personajes y detectar su id
typedef struct
{
    int coorX;
    int coorY;
    int identificador;
} CursorSeleccion;

//enum que contiene los 4 personajes disponibles
typedef enum
{
    SUBZERO,
    SCORPION,
    RAIDEN,
    LIUKANG
} Personajes;

//struct que alamcena punteros a otras structs para mutar/cambiar estado dentro del menu y detectar selecciones de jugadoresa
typedef struct MenuSeleccion
{
    AssetsRetratos *retrato;
    CursorSeleccion *cursorP1;
    CursorSeleccion *cursorP2;
    Personajes selP1;
    Personajes selP2;
    Juego *datosJuego;
    int duracionTransicion;
} MenuSeleccion;

/**
 * @brief Funcion que dibuja el stage
 *
 * @param fondo Puntero a la struct Fondo que contiene un campo que apunta a la funcion Imagen de la libreria de graficos y que almacena el fondo
 */
void dibujarEscenario(Fondos *fondos);

/**
 * @brief Funcion que se encarga del dibujado del personaje
 *
 * @param juego Puntero a la struct juego que contiene los campos del mismo asi como punteros a otras structs
 */
void animacionPersonaje(Juego *juego, MenuSeleccion *menuSel);

/**
 * @brief Funcion que crea la imagen del escenario
 *
 * @return fondos*
 */
Fondos *crearFondos();

/**
 * @brief Funcion que inicia el juego en estado ESTADO_INICIO, que funge como un inicialiador de menu
 *
 * @param juego Struct de tipo puntero que apunta a todo Juego, que incluye campos de Fondo para la creacion de imaganes de los stages
 * @param estadoJuego Puntero a la enum EstadoJuego inicializada desde el main, para trabajar con el comportamiento de estados y pasar ed JUGANDO, a INICIO, y visceversa
 */
void iniciarJuego(Juego *juego, EstadoJuego *estadoJuego);

/**
 * @brief Funcion encargada ed iniciar el loop del juego, llamda desde el main
 *
 * @param juego Puntero a la struct Juego que contiene los campos de Personaje, Fondos entre otras mas
 */
void gameLoop(Juego *juego, MenuSeleccion *menuSel);

/**
 * @brief Funcion que instancia, inicialioza y crea los retratos de cada jugador asi como los cursores de seleccion
 * 
 * @return AssetsRetratos* 
 */
AssetsRetratos *crearRetratos();

/**
 * @brief Funcion que actualiza el cursor de seleccion para cada jugador, retornado la struct CursorSeleccion completa
 * 
 * @param personajeRet Puntero a la struct CursorSeleccion que accede a cada uno de sus campos y los cambia segun ciertas condiciones
 * @param personaje puntero al enum Personajes para acceder al personaje seleccionad y evitar variables complejas
 * @return CursorSeleccion* 
 */
CursorSeleccion *actualizarCursor(CursorSeleccion *personajeRet, Personajes *personaje);

/**
 * @brief Funcion que dibuja en pantalla el menu de seleccion de personakjes
 * 
 * @param retrato Puntero a la struct AssetsRetratos para acceder a cada imagen
 */
void crearMenuSeleccion(AssetsRetratos *retrato);

/**
 * @brief Funcion que dibuja el cursor de seleccion para cada jugador
 * 
 * @param cursorPersonaje Puntero a la struct CursorSeleccion
 * @param retratos Puntero a la struct AssetsRetratos
 * @param personaje Puntero al enum Personajes
 */
void dibujarCursor(CursorSeleccion *cursorPersonaje, AssetsRetratos *retratos, Personajes *personaje);

/**
 * @brief Funcion que inicia la pelea segun la eleccion de cada personaje
 * 
 * @param cursorPersonaje1 puntero al CursorSeleccion struct
 * @param cursorPersonaje2 puntero al CursorSeleccion struct 
 * @param juego PUNTERO A la struct JUEGO
 * @param tecla tecla presionada recibida desde el main
 * @return Juego* 
 */
Juego *iniciarPelea(CursorSeleccion *cursorPersonaje1, CursorSeleccion *cursorPersonaje2, Juego *juego, int tecla);

/**
 * @brief Funcion que se encarga de liberara de la memoria las imagenes creadas
 * 
 * @param retratosPersonajes Puntero a la struct AssetsRetratos
 */
void liberarImagenes(AssetsRetratos *retratosPersonajes);

/**
 * @brief Funcion que se encarga de ejecutar el loop del menu mientras el estadop sea ESTADO_MENUSELECCION
 * 
 * @param menuSel Puntero a la struct completa de MenuSeleccion
 * @param estadoJuego Pubntero a la enum EstadoJuego
 */
void menuLoop(MenuSeleccion *menuSel, EstadoJuego *estadoJuego);

/**
 * @brief Funcion que se encarga de inciar un timer para pasar el estado de juego ESTADO_JUGANDO
 * 
 * @param menuSel 
 */
void animacionInicioPelea(MenuSeleccion *menuSel);
#endif