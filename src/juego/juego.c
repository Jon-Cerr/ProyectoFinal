#include "../graficos/graficos.h"
#include "./juego.h"

void dibujarEscenario(Fondos *fondos)
{
    if (fondos->fondoStage != NULL)
    {
        ventana.muestraImagenEscalada(0, 0, ventana.anchoVentana(), ventana.altoVentana(), fondos->fondoStage);
    }
}

Fondos *crearFondos()
{
    Fondos *fondos = (Fondos *)malloc(sizeof(Fondos));
    if (fondos == NULL)
    {
        ventana.muestraMensaje("No se pudieron cargar los fondos.");
    }
    fondos->fondoInicio = ventana.creaImagen("assets/img/fondoInicio.bmp");
    fondos->fondoStage = ventana.creaImagen("assets/img/fondo_stage.bmp");
    return fondos;
}

void animacionPersonaje(Juego *juego)
{
    actualizarMovimiento(juego->personaje1, juego->tecla, juego->teclaSoltada);
    dibujarPersonaje(juego->personaje1);
    actualizarMovimiento(juego->personaje2, juego->tecla, juego->teclaSoltada);
    dibujarPersonaje(juego->personaje2);
    dibujarHUD(juego->personaje1, juego->tecla);
    dibujarHUDP2(juego->personaje2, juego->tecla);
    detectarColision(juego->personaje1, juego->personaje2, juego->tecla);
}

void iniciarJuego(Juego *juego, EstadoJuego *estadoJuego)
{
    int startButon = juego->tecla;
    if (*estadoJuego == ESTADO_INICIO)
    {
        ventana.reproducirAudio("assets/audio/inicio.wav");
    }
    while (*estadoJuego == ESTADO_INICIO)
    {
        juego->tecla = ventana.teclaPresionada();
        ventana.limpiaVentana();
        if (juego->fondosJuego->fondoInicio != NULL)
        {
            ventana.muestraImagenEscalada(0, 0, ventana.anchoVentana(), ventana.altoVentana(), juego->fondosJuego->fondoInicio);
        }
        else
        {
            ventana.muestraMensaje("ERROR: No se pudo cargar fondoInicio\n");
        }
        ventana.actualizaVentana();
        ventana.espera(10);
        if (juego->tecla == TECLAS.ESPACIO)
        {
            ventana.reproducirAudio(NULL);
            *estadoJuego = ESTADO_MENUSELECCION;
            ventana.reproducirAudio("assets/audio/audioPelea1.wav");
        }
        if (juego->tecla == TECLAS.ESCAPE)
        {
            ventana.reproducirAudio(NULL);
            exit(0);
        }
    }
}

void gameLoop(Juego *juego)
{
    dibujarEscenario(juego->fondosJuego);
    animacionPersonaje(juego);
}

AssetsRetratos *crearRetratos()
{
    AssetsRetratos *retratosPersonajes = (AssetsRetratos *)malloc(sizeof(AssetsRetratos));
    if (retratosPersonajes == NULL)
    {
        ventana.muestraMensaje("Imposible crear retratos de personajes.");
    }
    retratosPersonajes->liuKang = ventana.creaImagen("./assets/img/liuKangRetrato.bmp");
    retratosPersonajes->scorpion = ventana.creaImagen("./assets/img/scorpionRetrato.bmp");
    retratosPersonajes->subZero = ventana.creaImagen("./assets/img/subZeroRetrato.bmp");
    retratosPersonajes->raiden = ventana.creaImagen("./assets/img/raidenRetrato.bmp");
    retratosPersonajes->fondoSeleccion = ventana.creaImagen("./assets/img/fondoSeleccion.bmp");
    retratosPersonajes->contenedorRetrato = ventana.creaImagen("./assets/img/contenedorRetrato.bmp");
    retratosPersonajes->cursorSelector = ventana.creaImagenConMascara("./assets/img/cursorSelector.bmp", "./assets/img/cursorSelectorMask.bmp");
    retratosPersonajes->cursorSelectorP2 = ventana.creaImagenConMascara("./assets/img/cursorSelectorP2.bmp", "./assets/img/cursorSelectorMask.bmp");
    return retratosPersonajes;
}

CursorSeleccion *actualizarCursor(CursorSeleccion *personajeRet, Personajes *personaje)
{
    if (*personaje == LIUKANG)
    {
        personajeRet->identificador = 0;
        personajeRet->coorX = 100;
        personajeRet->coorY = 170;
    }
    else if (*personaje == SUBZERO)
    {
        personajeRet->identificador = 1;
        personajeRet->coorX = 100;
        personajeRet->coorY = 330;
    }
    else if (*personaje == SCORPION)
    {
        personajeRet->identificador = 2;
        personajeRet->coorX = 1080;
        personajeRet->coorY = 170;
    }
    else if (*personaje == RAIDEN)
    {
        personajeRet->identificador = 3;
        personajeRet->coorX = 1080;
        personajeRet->coorY = 330;
    }

    return personajeRet;
}

void crearMenuSeleccion(AssetsRetratos *retrato)
{
    ventana.muestraImagen(0, 0, retrato->fondoSeleccion);
    ventana.muestraImagenEscalada(100, 170, 100, 150, retrato->liuKang);
    ventana.muestraImagenEscalada(100, 330, 100, 150, retrato->subZero);
    ventana.muestraImagenEscalada(1080, 170, 100, 150, retrato->scorpion);
    ventana.muestraImagenEscalada(1080, 330, 100, 150, retrato->raiden);
    ventana.muestraImagenEscalada(1080, 500, 100, 150, retrato->contenedorRetrato);
    ventana.muestraImagenEscalada(100, 500, 100, 150, retrato->contenedorRetrato);
}

void dibujarCursor(CursorSeleccion *cursorPersonaje, AssetsRetratos *retratos, Personajes *personaje)
{
    if (*personaje == LIUKANG || *personaje == SUBZERO)
    {
        ventana.muestraImagenEscalada(cursorPersonaje->coorX, cursorPersonaje->coorY, 100, 150, retratos->cursorSelector);
    }
    else if (*personaje == SCORPION || *personaje == RAIDEN)
    {
        ventana.muestraImagenEscalada(cursorPersonaje->coorX, cursorPersonaje->coorY, 100, 150, retratos->cursorSelectorP2);
    }
}

Juego *iniciarPelea(CursorSeleccion *cursorPersonaje1, CursorSeleccion *cursorPersonaje2, Juego *juego, int tecla)
{
    if (tecla == TECLAS.LETRA_Q)
    {
        juego->identificadorP1 = cursorPersonaje1->identificador;
        juego->p1Listo = true;
    }
    if (tecla == TECLAS.LETRA_U)
    {
        juego->identificadorP2 = cursorPersonaje2->identificador;
        juego->p2Listo = true;
    }

    return juego;
}

void liberarImagenes(AssetsRetratos *retratosPersonajes)
{
    ventana.eliminaImagen(retratosPersonajes->liuKang);
    ventana.eliminaImagen(retratosPersonajes->scorpion);
    ventana.eliminaImagen(retratosPersonajes->subZero);
    ventana.eliminaImagen(retratosPersonajes->raiden);
    ventana.eliminaImagen(retratosPersonajes->fondoSeleccion);
    ventana.eliminaImagen(retratosPersonajes->contenedorRetrato);
    ventana.eliminaImagen(retratosPersonajes->cursorSelector);
    ventana.eliminaImagen(retratosPersonajes->cursorSelectorP2);
}

void menuLoop(MenuSeleccion *menuSel, EstadoJuego *estadoJuego)
{
    crearMenuSeleccion(menuSel->retrato);
    ventana.color(COLORES.BLANCO);
    int tecla = menuSel->datosJuego->tecla;
    if (!(menuSel->datosJuego->p1Listo))
    {
        if (tecla == TECLAS.LETRA_S)
        {
            menuSel->selP1 = SUBZERO;
        }
        if (tecla == TECLAS.LETRA_W)
        {
            menuSel->selP1 = LIUKANG;
        }
    }
    if (!(menuSel->datosJuego->p2Listo))
    {
        if (tecla == TECLAS.LETRA_K)
        {
            menuSel->selP2 = RAIDEN;
        }
        if (tecla == TECLAS.LETRA_I)
        {
            menuSel->selP2 = SCORPION;
        }
    }
    actualizarCursor(menuSel->cursorP1, &(menuSel->selP1));
    actualizarCursor(menuSel->cursorP2, &(menuSel->selP2));
    dibujarCursor(menuSel->cursorP1, menuSel->retrato, &(menuSel->selP1));
    dibujarCursor(menuSel->cursorP2, menuSel->retrato, &(menuSel->selP2));
    iniciarPelea(menuSel->cursorP1, menuSel->cursorP2, menuSel->datosJuego, tecla);
    if (menuSel->datosJuego->p1Listo && menuSel->datosJuego->p2Listo)
    {
        ventana.reproducirAudio(NULL);
        *estadoJuego = ESTADO_JUGANDO;
    }
}