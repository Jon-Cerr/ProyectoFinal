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
    fondos->fondoInicio = ventana.creaImagen("./assets/img/fondoInicio.bmp");
    fondos->fondoStage = ventana.creaImagen("./assets/img/fondo_stage.bmp");
    return fondos;
}

void animacionPersonaje(Juego *juego, MenuSeleccion *menuSel, EstadoJuego *estado)
{
    actualizarMovimiento(juego->personaje1, juego->tecla, juego->teclaSoltada);
    dibujarPersonaje(juego->personaje1);
    actualizarMovimiento(juego->personaje2, juego->tecla, juego->teclaSoltada);
    dibujarPersonaje(juego->personaje2);
    dibujarHUD(juego->personaje1, juego->tecla, menuSel);
    dibujarHUDP2(juego->personaje2, juego->tecla, menuSel);
    detectarColision(juego->personaje1, juego->personaje2, juego->tecla, menuSel, estado);
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

void gameLoop(Juego *juego, MenuSeleccion *menuSel, EstadoJuego *estado)
{
    dibujarEscenario(juego->fondosJuego);
    animacionPersonaje(juego, menuSel, estado);
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
    retratosPersonajes->liuKangSeleccionado = ventana.creaImagen("./assets/img/liuKangSeleccionado.bmp");
    retratosPersonajes->scorpionSeleccionado = ventana.creaImagen("./assets/img/scorpionSeleccionado.bmp");
    retratosPersonajes->subZeroSeleccionado = ventana.creaImagen("./assets/img/subZeroSeleccionado.bmp");
    retratosPersonajes->raidenSeleccionado = ventana.creaImagen("./assets/img/raidenSeleccionado.bmp");
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

void menuLoop(MenuSeleccion *menuSel, EstadoJuego *estadoJuego)
{
    crearMenuSeleccion(menuSel->retrato);
    ventana.color(COLORES.BLANCO);
    int tecla = menuSel->datosJuego->tecla;
    if (tecla == TECLAS.LETRA_V)
    {
        *estadoJuego = ESTADO_PODIO;
    }
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
    if (menuSel->datosJuego->p1Listo || menuSel->datosJuego->p2Listo)
        animacionInicioPelea(menuSel);
    if (menuSel->datosJuego->p1Listo && menuSel->datosJuego->p2Listo)
    {
        menuSel->duracionTransicion--;
        if (menuSel->duracionTransicion % 20 > 10)
        {
            ventana.color(COLORES.ROJO);
            ventana.texto1(505, 55, "GET READY!", 50, "Arial");
            ventana.color(COLORES.BLANCO);
            ventana.texto1(500, 50, "GET READY!", 50, "Arial");
        }
        if (menuSel->duracionTransicion <= 0)
        {
            ventana.reproducirAudio(NULL);
            // jugador 1
            if (menuSel->selP1 == LIUKANG)
                menuSel->datosJuego->personaje1 = cargarPersonaje(menuSel->datosJuego->personaje1, *estadoJuego, "liu");
            else if (menuSel->selP1 == SUBZERO)
                menuSel->datosJuego->personaje1 = cargarPersonaje(menuSel->datosJuego->personaje1, *estadoJuego, "sub");

            // jugador 2
            if (menuSel->selP2 == SCORPION)
                menuSel->datosJuego->personaje2 = cargarPersonaje2(menuSel->datosJuego->personaje2, *estadoJuego, "scor");
            else if (menuSel->selP2 == RAIDEN)
                menuSel->datosJuego->personaje2 = cargarPersonaje2(menuSel->datosJuego->personaje2, *estadoJuego, "raiden");

            if (menuSel->datosJuego->personaje1)
                menuSel->datosJuego->personaje1->frameActual = 0;
            if (menuSel->datosJuego->personaje2)
                menuSel->datosJuego->personaje2->frameActual = 0;
            *estadoJuego = ESTADO_JUGANDO;
        }
    }
}

void animacionInicioPelea(MenuSeleccion *menuSel)
{
    if (menuSel->datosJuego->p1Listo)
    {
        if (menuSel->selP1 == LIUKANG)
        {
            ventana.muestraImagenEscalada(250, (ventana.altoVentana() / 2) - 100, 200, 250, menuSel->retrato->liuKangSeleccionado);
            ventana.texto1(250, (ventana.altoVentana() / 2) + 200, "LIUKANG", 40, "Arial");
        }
        else if (menuSel->selP1 == SUBZERO)
        {
            ventana.muestraImagenEscalada(250, (ventana.altoVentana() / 2) - 100, 200, 250, menuSel->retrato->subZeroSeleccionado);
            ventana.texto1(250, (ventana.altoVentana() / 2) + 200, "SUBZERO", 40, "Arial");
        }
    }
    if (menuSel->datosJuego->p2Listo)
    {
        if (menuSel->selP2 == SCORPION)
        {
            ventana.muestraImagenEscalada(830, (ventana.altoVentana() / 2) - 100, 200, 250, menuSel->retrato->scorpionSeleccionado);
            ventana.texto1(830, (ventana.altoVentana() / 2) + 200, "SCORPION", 40, "Arial");
        }
        else if (menuSel->selP2 == RAIDEN)
        {
            ventana.muestraImagenEscalada(830, (ventana.altoVentana() / 2) - 100, 200, 250, menuSel->retrato->raidenSeleccionado);
            ventana.texto1(830, (ventana.altoVentana() / 2) + 200, "RAIDEN", 40, "Arial");
        }
    }
}

void ejecutarLogicaFatality(Juego *juego, EstadoJuego *estado, MenuSeleccion *menuSel)
{
    if (juego->personaje1 == NULL || juego->personaje2 == NULL)
    {
        *estado = ESTADO_MENUSELECCION;
        return;
    }
    Personaje *ganador = (juego->personaje1->fatalityGolpe != NULL) ? juego->personaje1 : juego->personaje2;
    Personaje *perdedor = (ganador == juego->personaje1) ? juego->personaje2 : juego->personaje1;
    if (ganador->fatalityGolpe != NULL)
    {
        dibujarEscenaFatality(ganador, perdedor);   
        static int frames = 0;
        frames++;
        if (frames >= 6)
        {
            ganador->fatalityGolpe->frameActual++;
            frames = 0;
        }
        if (ganador->fatalityGolpe->frameActual >= ganador->fatalityGolpe->totalFrames)
        {
            char nombreGanador[20];
            if (ganador == juego->personaje1)
            {
                if (menuSel->selP1 == SUBZERO)
                    sprintf(nombreGanador, "Sub-Zero");
                else if (menuSel->selP1 == LIUKANG)
                    sprintf(nombreGanador, "Liu Kang");
            }
            else
            {
                if (menuSel->selP2 == SCORPION)
                    sprintf(nombreGanador, "Scorpion");
                else if (menuSel->selP2 == RAIDEN)
                    sprintf(nombreGanador, "Raiden");
            }

            juego->p1Listo = false;
            juego->p2Listo = false;
            menuSel->duracionTransicion = 50;
            *estado = ESTADO_MENUSELECCION;
            registrarVictoria(juego, nombreGanador);
            ganador->fatalityGolpe->frameActual = 0;
            juego->personaje1->vida = 100;
            juego->personaje2->vida = 100;
            if (*estado == ESTADO_MENUSELECCION)
            {
                ventana.reproducirAudio("assets/audio/audioPelea1.wav");
                liberarPersonajeMemoria(juego->personaje1);
                liberarPersonajeMemoria(juego->personaje2);
                juego->personaje1 = NULL;
                juego->personaje2 = NULL;
            }
        }
    }
}

void liberarImagenes(AssetsRetratos *retratosPersonajes)
{
    ventana.eliminaImagen(retratosPersonajes->liuKang);
    ventana.eliminaImagen(retratosPersonajes->scorpion);
    ventana.eliminaImagen(retratosPersonajes->subZero);
    ventana.eliminaImagen(retratosPersonajes->raiden);
    ventana.eliminaImagen(retratosPersonajes->fondoSeleccion);
    ventana.eliminaImagen(retratosPersonajes->cursorSelector);
    ventana.eliminaImagen(retratosPersonajes->cursorSelectorP2);
    ventana.eliminaImagen(retratosPersonajes->liuKangSeleccionado);
    ventana.eliminaImagen(retratosPersonajes->scorpionSeleccionado);
    ventana.eliminaImagen(retratosPersonajes->subZeroSeleccionado);
    ventana.eliminaImagen(retratosPersonajes->raidenSeleccionado);
}