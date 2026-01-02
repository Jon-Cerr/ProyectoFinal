#include <stdio.h>
#include <stdlib.h>

#include "./personaje.h"
#include "./juego.h"

Personaje *cargarPersonaje(Personaje *personaje, EstadoPersonaje estado, const char *nombrePersonaje)
{
    if (personaje == NULL)
    {
        personaje = (Personaje *)malloc(sizeof(Personaje));
    }

    // Inicializar campos
    personaje->x = 100;
    personaje->y = 400;
    personaje->vida = 100;
    personaje->estado = QUIETO;
    personaje->frameActual = 0;
    personaje->totalFrames = 4;
    personaje->moviendoDerecha = false;
    personaje->moviendoIzquierda = false;
    personaje->controls.derecha = TECLAS.LETRA_D;
    personaje->controls.izquierda = TECLAS.LETRA_A;
    personaje->controls.golpe = TECLAS.LETRA_Q;
    personaje->controls.golpe2 = TECLAS.LETRA_E;
    personaje->controls.patada = TECLAS.LETRA_W;
    personaje->controls.defensa = TECLAS.LETRA_Z;
    personaje->defendiendo = false;
    personaje->fatalityGolpe = NULL;
    personaje->sprites = (Imagen **)malloc(sizeof(Imagen *) * 70);

    // Llenar la memoria reservada en NULL para evitar bugs
    for (int z = 0; z < 70; z++)
    {
        personaje->sprites[z] = NULL;
    }
    cargarSprites(personaje, nombrePersonaje);
    return personaje;
}

Personaje *cargarPersonaje2(Personaje *personaje, EstadoPersonaje estado, const char *nombrePersonaje)
{
    if (personaje == NULL)
    {
        personaje = (Personaje *)malloc(sizeof(Personaje));
    }

    // Inicializar campos
    personaje->x = 1000;
    personaje->y = 400;
    personaje->vida = 100;
    personaje->estado = QUIETO; // quieto
    personaje->frameActual = 0;
    personaje->totalFrames = 4;
    personaje->moviendoDerecha = false;
    personaje->moviendoIzquierda = false;
    personaje->controls.derecha = TECLAS.LETRA_D;
    personaje->controls.izquierda = TECLAS.LETRA_A;
    personaje->controls.golpe = TECLAS.LETRA_Q;
    personaje->controls.golpe2 = TECLAS.LETRA_E;
    personaje->controls.patada = TECLAS.LETRA_W;
    personaje->controls.defensa = TECLAS.LETRA_Z;
    personaje->controlsEsp32.defensaEsp32 = false;
    personaje->defendiendo = false;
    personaje->fatalityGolpe = NULL;
    personaje->sprites = (Imagen **)malloc(sizeof(Imagen *) * 70);

    // Llenar la memoria reservada en NULL para evitar bugs
    for (int z = 0; z < 70; z++)
    {
        personaje->sprites[z] = NULL;
    }
    cargarSprites(personaje, nombrePersonaje);
    return personaje;
}

void cargarSprites(Personaje *personaje, const char *nombrePersonaje)
{
    int indiceActual = 0;
    // Se llenan los arreglos de animaciones correspondientes y los sprites del personaje
    for (int indiceQuieto = 0; indiceQuieto < 4; indiceQuieto++)
    {
        char nombreArchivo[100];
        sprintf(nombreArchivo, "./sprites/quieto/%s_quieto_%d.bmp", nombrePersonaje, (indiceQuieto + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/quieto/%s_quieto_%d_mask.bmp", nombrePersonaje, (indiceQuieto + 1));
        personaje->sprites[indiceActual] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        if (personaje->sprites[indiceActual] == NULL)
        {
            ventana.muestraMensaje("No se pudieron cargar los sprites.");
            printf("ERROR: No se encontro el archivo: %s\n", nombreArchivo);
        }
        personaje->animQuieto[indiceQuieto] = personaje->sprites[indiceActual];
        indiceActual++;
    }

    for (int indiceCaminata = 0; indiceCaminata < 6; indiceCaminata++)
    {
        char nombreArchivo[100];
        sprintf(nombreArchivo, "./sprites/camina/%s_camina_%d.bmp", nombrePersonaje, (indiceCaminata + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/camina/%s_camina_%d_mask.bmp", nombrePersonaje, (indiceCaminata + 1));
        personaje->sprites[indiceActual] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        if (personaje->sprites[indiceActual] == NULL)
        {
            ventana.muestraMensaje("No se pudieron cargar los sprites.");
            printf("ERROR: No se encontro el archivo: %s\n", nombreArchivo);
        }
        personaje->animCaminata[indiceCaminata] = personaje->sprites[indiceActual];
        indiceActual++;
    }

    for (int indiceGolpe = 0; indiceGolpe < 3; indiceGolpe++)
    {
        char nombreArchivo[100];
        sprintf(nombreArchivo, "./sprites/golpe/%s_golpe_%d.bmp", nombrePersonaje, (indiceGolpe + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/golpe/%s_golpe_%d_mask.bmp", nombrePersonaje, (indiceGolpe + 1));
        personaje->sprites[indiceActual] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        if (personaje->sprites[indiceActual] == NULL)
        {
            ventana.muestraMensaje("No se pudieron cargar los sprites.");
            printf("ERROR: No se encontro el archivo: %s\n", nombreArchivo);
        }
        personaje->animGolpe[indiceGolpe] = personaje->sprites[indiceActual];
        indiceActual++;
    }

    for (int indiceGolpe2 = 0; indiceGolpe2 < 3; indiceGolpe2++)
    {
        char nombreArchivo[100];
        sprintf(nombreArchivo, "./sprites/golpe/golpe2/%s_golpe_%d.bmp", nombrePersonaje, (indiceGolpe2 + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/golpe/golpe2/%s_golpe_%d_mask.bmp", nombrePersonaje, (indiceGolpe2 + 1));
        personaje->sprites[indiceActual] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        if (personaje->sprites[indiceActual] == NULL)
        {
            ventana.muestraMensaje("No se pudieron cargar los sprites.");
            printf("ERROR: No se encontro el archivo: %s\n", nombreArchivo);
        }
        personaje->animGolpe2[indiceGolpe2] = personaje->sprites[indiceActual];
        indiceActual++;
    }

    for (int indicePatada = 0; indicePatada < 4; indicePatada++)
    {
        char nombreArchivo[100];
        sprintf(nombreArchivo, "./sprites/golpe/patada/%s_patada_%d.bmp", nombrePersonaje, (indicePatada + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/golpe/patada/%s_patada_%d_mask.bmp", nombrePersonaje, (indicePatada + 1));
        personaje->sprites[indiceActual] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        if (personaje->sprites[indiceActual] == NULL)
        {
            ventana.muestraMensaje("No se pudieron cargar los sprites.");
            printf("ERROR: No se encontro el archivo: %s\n", nombreArchivo);
        }
        personaje->animPatada[indicePatada] = personaje->sprites[indiceActual];
        indiceActual++;
    }

    for (int indiceGolpeado = 0; indiceGolpeado < 3; indiceGolpeado++)
    {
        char nombreArchivo[100];
        sprintf(nombreArchivo, "./sprites/golpeado/%s_golpeado_%d.bmp", nombrePersonaje, (indiceGolpeado + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/golpeado/%s_golpeado_%d_mask.bmp", nombrePersonaje, (indiceGolpeado + 1));
        personaje->sprites[indiceActual] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        if (personaje->sprites[indiceActual] == NULL)
        {
            ventana.muestraMensaje("No se pudieron cargar los sprites.");
            printf("ERROR: No se encontro el archivo: %s\n", nombreArchivo);
        }
        personaje->animGolpeado[indiceGolpeado] = personaje->sprites[indiceActual];
        indiceActual++;
    }

    for (int indiceDefensa = 0; indiceDefensa < 3; indiceDefensa++)
    {
        char nombreArchivo[100];
        sprintf(nombreArchivo, "./sprites/golpeado/%s_defensa_%d.bmp", nombrePersonaje, (indiceDefensa + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/golpeado/%s_defensa_%d_mask.bmp", nombrePersonaje, (indiceDefensa + 1));
        personaje->sprites[indiceActual] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        if (personaje->sprites[indiceActual] == NULL)
        {
            ventana.muestraMensaje("No se pudieron cargar los sprites.");
            printf("ERROR: No se encontro el archivo: %s\n", nombreArchivo);
        }
        personaje->animDefensa[indiceDefensa] = personaje->sprites[indiceActual];
        indiceActual++;
    }

    for (int indiceAbatido = 0; indiceAbatido < 7; indiceAbatido++)
    {
        char nombreArchivo[100];
        sprintf(nombreArchivo, "./sprites/abatido/%s_abatido_%d.bmp", nombrePersonaje, (indiceAbatido + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/abatido/%s_abatido_%d_mask.bmp", nombrePersonaje, (indiceAbatido + 1));
        personaje->sprites[indiceActual] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        if (personaje->sprites[indiceActual] == NULL)
        {
            ventana.muestraMensaje("No se pudieron cargar los sprites.");
            printf("ERROR: No se encontró el archivo: %s\n", nombreArchivo);
        }
        personaje->animAbatido[indiceAbatido] = personaje->sprites[indiceActual];
        indiceActual++;
    }
}

ControlesEsp32 *mapearControlesEsp32(Board *esp32, ControlesEsp32 *controlEsp)
{
    if (esp32 != NULL)
    {
        int lecturaDefensa = esp32->digitalRead(esp32, DEFENSA_ESP32);
        if (lecturaDefensa != 0 && lecturaDefensa != 1)
        {
            controlEsp->defensaEsp32 = false;
        }
        else
        {
            controlEsp->defensaEsp32 = (lecturaDefensa == 0);
        }
        controlEsp->derechaEsp32 = (esp32->digitalRead(esp32, DERECHA) == 0);
        controlEsp->izquierdaEsp32 = (esp32->digitalRead(esp32, IZQUIERDA) == 0);
        controlEsp->defensaEsp32 = (esp32->digitalRead(esp32, DEFENSA_ESP32) == 0);
        controlEsp->golpeEsp32 = (esp32->digitalRead(esp32, GOLPE1) == 0);
        controlEsp->golpe2Esp32 = (esp32->digitalRead(esp32, GOLPE2) == 0);
        controlEsp->patadaEsp32 = (esp32->digitalRead(esp32, PATADA) == 0);
    }
    return controlEsp;
}

void dibujarPersonaje(Personaje *personaje)
{
    // si el estado es quieto, se dibujan los sprites de "quieto"
    if (personaje->estado == QUIETO)
    {
        ventana.muestraImagenEscalada(personaje->x, personaje->y, 154, 190, personaje->animQuieto[personaje->frameActual]);
    }
    // si el estado es caminando, se dibujan los sprites de "caminando"
    else if (personaje->estado == CAMINANDO_DER || personaje->estado == CAMINANDO_IZQ)
    {
        ventana.muestraImagenEscalada(personaje->x, personaje->y, 154, 190, personaje->animCaminata[personaje->frameActual]);
    }
    // si el estado es golpeando, se dibujan los sprites de "golpeando"
    else if (personaje->estado == GOLPEANDO)
    {
        ventana.muestraImagenEscalada(personaje->x, personaje->y, 154, 190, personaje->animGolpe[personaje->frameActual]);
    }
    // si el estado es golpeando2, se dibujan los sprites de "golpeando2"
    else if (personaje->estado == GOLPEANDO2)
    {
        ventana.muestraImagenEscalada(personaje->x, personaje->y, 154, 190, personaje->animGolpe2[personaje->frameActual]);
    }
    // si el estado es pateando, se dibujan los sprites de "pateando"
    else if (personaje->estado == PATEANDO)
    {
        ventana.muestraImagenEscalada(personaje->x, personaje->y, 154, 190, personaje->animPatada[personaje->frameActual]);
    }
    // si el estado es GOLPEADO, se dibujan los sprites de "GOLPEADO"
    else if (personaje->estado == GOLPEADO)
    {
        ventana.muestraImagenEscalada(personaje->x, personaje->y, 154, 190, personaje->animGolpeado[personaje->frameActual]);
    }
    // si el estado es defensa, se dibujan los sprites de "defensa"
    else if (personaje->estado == DEFENSA)
    {
        ventana.muestraImagenEscalada(personaje->x, personaje->y, 154, 190, personaje->animDefensa[personaje->frameActual]);
    }
    // si el estado es ABATIDO, se dibujan los sprites de "ABATIDO"
    else if (personaje->estado == ABATIDO)
    {
        ventana.muestraImagenEscalada(personaje->x, personaje->y, 154, 190, personaje->animAbatido[personaje->frameActual]);
    }
}

void cambiarEstado(Personaje *personaje, int tecla, int teclaSoltada)
{
    if (personaje->vida <= 0)
    {
        personaje->moviendoDerecha = false;
        personaje->moviendoIzquierda = false;
        if (personaje->estado != ABATIDO)
        {
            personaje->estado = ABATIDO;
            personaje->frameActual = 0;
            personaje->totalFrames = 7;
        }
        return;
    }

    // deteccion de teclas para evitar colisiones con el main
    if (tecla == personaje->controls.derecha)
        personaje->moviendoDerecha = true;
    if (tecla == personaje->controls.izquierda)
        personaje->moviendoIzquierda = true;

    // desactivar caminata, al detectar una tecla soltada
    if (teclaSoltada == personaje->controls.derecha)
        personaje->moviendoDerecha = false;
    if (teclaSoltada == personaje->controls.izquierda)
        personaje->moviendoIzquierda = false;

    // activar defensa - activar bandera de defensa si la tecla defensa se presiona
    if (tecla == personaje->controls.defensa)
        personaje->defendiendo = true;

    // desactivar defensa - desactivar bandera de defensa si la tecla defensa se suelta
    if (teclaSoltada == personaje->controls.defensa)
        personaje->defendiendo = false;

    // bloquear flujo de ejecucion si el personaje esta siendo golpeado
    if (personaje->estado == GOLPEADO)
        return;

    // activar estado de defensa si la bandera defendiendo es true
    if (personaje->defendiendo)
    {
        personaje->estado = DEFENSA;
        personaje->totalFrames = 3;
        personaje->frameActual = 0;
        return;
    }

    // ignorar cualquier comportamiento mientras uno de estos 3 estados este activo
    if (personaje->estado == GOLPEANDO ||
        personaje->estado == GOLPEANDO2 ||
        personaje->estado == PATEANDO)
    {
        return;
    }

    // activacion de movimiento de acuerdo al control presionado, estado sera correspondiente a la tecla presionada y acorde al campo de la struct Controles, se resetean los frames actuales a 0 y se igualan el total de frames al total de sprites de cada animacion - arreglo
    if (tecla == personaje->controls.golpe)
    {
        personaje->estado = GOLPEANDO;
        personaje->frameActual = 0;
        personaje->totalFrames = 3;
        return;
    }

    if (tecla == personaje->controls.golpe2)
    {
        personaje->estado = GOLPEANDO2;
        personaje->frameActual = 0;
        personaje->totalFrames = 3;
        return;
    }

    if (tecla == personaje->controls.patada)
    {
        personaje->estado = PATEANDO;
        personaje->frameActual = 0;
        personaje->totalFrames = 4;
        return;
    }

    // detectar tecla de movimiento y cambiar estado del personaje y el frame actual, se cambia el estado correspondiente y se iguala el total de frames al total de sprites del arreglo correspondiente
    if (personaje->moviendoDerecha)
    {
        if (personaje->estado != CAMINANDO_DER)
        {
            personaje->estado = CAMINANDO_DER;
            personaje->totalFrames = 6;
        }
    }
    else if (personaje->moviendoIzquierda)
    {
        if (personaje->estado != CAMINANDO_IZQ)
        {
            personaje->estado = CAMINANDO_IZQ;
            personaje->totalFrames = 6;
        }
    }

    // si no se cumplio ninguna condicion anterior, el estado por defecto sera "QUIETO"
    else
    {
        personaje->estado = QUIETO;
        personaje->totalFrames = 4;
    }

    // SE IGUALA EL ESTADO A "QUIETO" PARA EVITAR INTERRUPCIONES EN EL MOVIMIENTOI
    if (!personaje->moviendoDerecha && !personaje->moviendoIzquierda)
    {
        if (personaje->estado != QUIETO)
        {
            personaje->estado = QUIETO;
            personaje->totalFrames = 4;
            personaje->frameActual = 0;
        }
    }
}

void actualizarMovimiento(Personaje *personaje, int tecla, int teclaSoltada)
{
    // cambiar el estado del personaje pasado desde el main, asi como la tecla presionada y soltada para evitar colisiones con el main
    cambiarEstado(personaje, tecla, teclaSoltada);
    personaje->frameActual++; // se incrementa el frame
    if (personaje->frameActual >= personaje->totalFrames)
    {
        if (personaje->estado == GOLPEANDO ||
            personaje->estado == GOLPEANDO2 ||
            personaje->estado == PATEANDO ||
            personaje->estado == GOLPEADO)
        {
            personaje->estado = QUIETO;
            personaje->totalFrames = 4;
        }
        personaje->frameActual = 0;
    }

    // limites en la pantalla para evitar que el personaje se desborde de la ventana
    if (personaje->estado == CAMINANDO_DER)
    {
        if (!((personaje->x + 104) >= ventana.anchoVentana()))
        {
            personaje->x += 15;
        }
    }
    else if (personaje->estado == CAMINANDO_IZQ)
    {
        if (!(personaje->x <= 0))
        {
            personaje->x -= 15;
        }
    }
}

void dibujarHUD(Personaje *personaje, int tecla, MenuSeleccion *menuSel)
{
    ventana.color(COLORES.ROJO);
    ventana.rectanguloRelleno(70, 50, 470, 80);

    ventana.color(COLORES.VERDE);
    ventana.rectanguloRelleno(70, 50, 70 + (personaje->vida * 4), 80);

    ventana.color(COLORES.BLANCO);
    ventana.rectangulo(70, 50, 470, 80);
    if (menuSel->selP1 == LIUKANG)
    {
        ventana.texto1(70, 100, "LIUKANG", 30, "Arial");
    }
    else if (menuSel->selP1 == SUBZERO)
    {
        ventana.texto1(70, 100, "SUB ZERO", 30, "Arial");
    }
}

void dibujarHUDP2(Personaje *personaje, int tecla, MenuSeleccion *menuSel)
{
    ventana.color(COLORES.ROJO);
    ventana.rectanguloRelleno(800, 50, 1200, 80);

    ventana.color(COLORES.VERDE);
    ventana.rectanguloRelleno(1200 - (personaje->vida * 4), 50, 1200, 80);

    ventana.color(COLORES.BLANCO);
    ventana.rectangulo(800, 50, 1200, 80);
    ventana.color(COLORES.BLANCO);
    if (menuSel->selP2 == SCORPION)
    {
        ventana.texto1(800, 100, "SCORPION", 30, "Arial");
    }
    else if (menuSel->selP2 == RAIDEN)
    {
        ventana.texto1(800, 100, "RAIDEN", 30, "Arial");
    }
}

void detectarColision(Personaje *personaje1, Personaje *personaje2, int tecla, MenuSeleccion *menuSel, EstadoJuego *estado)
{
    // distancia absoluta entre personaje1 y personaje2
    int distancia = abs(personaje1->x - personaje2->x);
    int minColision = 100; // colision minima para detectar el golpe
    // comparar distancias para hacer efectiva la colision
    if (distancia < minColision)
    {
        // verificcar que el personaje se encuentre en los siguientes estados para hacer valida la colision
        if (personaje1->estado == GOLPEANDO || personaje1->estado == GOLPEANDO2 || personaje1->estado == PATEANDO)
        {
            // solo se hara valido si la vida del personaje golpeado es mayor a 0, y si el personaje no se esta defendiendo para bajar la vida
            if (personaje2->vida > 0)
            {
                if (!(personaje2->defendiendo))
                {
                    // Si la colision es efectiva, se resta vida al personaje
                    personaje2->vida -= 1;
                    // si la vida del personaje es menor o igual a 0, el estado del personaje sera ABATIDO, la vida es de cero y se reinician los frames para la animacion de abatido, y suena el famoso "finish him"
                    if (personaje2->vida <= 0)
                    {
                        personaje2->vida = 0;
                        personaje2->estado = ABATIDO;
                        personaje2->frameActual = 0;
                        ventana.reproducirAudio("./assets/audio/finish.wav");
                    }
                    // si no se cumple lo anetrior (el personaje aun tiene vida) su estado sera de GOLPEADO para animar este estado
                    else
                    {
                        personaje2->estado = GOLPEADO;
                        personaje2->frameActual = 0;
                    }
                }
            }
        }
        if (personaje2->estado == GOLPEANDO || personaje2->estado == GOLPEANDO2 || personaje2->estado == PATEANDO)
        {
            if (personaje1->vida > 0)
            {
                if (!(personaje1->defendiendo))
                {
                    personaje1->vida -= 1;
                    if (personaje1->vida <= 0)
                    {
                        personaje1->vida = 0;
                        personaje1->estado = ABATIDO;
                        personaje1->frameActual = 0;
                        ventana.reproducirAudio("./assets/audio/finish.wav");
                        return;
                    }
                    else
                    {
                        personaje1->estado = GOLPEADO;
                        personaje1->frameActual = 0;
                    }
                }
            }
        }
    }

    // logica para el personaje 1 para activar el fatality
    if (personaje2->estado == ABATIDO && distancia < 150)
    {
        if (tecla == TECLAS.LETRA_Q)
        {
            cargarAnimacionFatality(personaje1, menuSel);
            *estado = ESTADO_FATALITY;
        }
    }
    // logica para el personaje 2 para activar el fatality
    if (personaje1->estado == ABATIDO && distancia < 150)
    {
        if (tecla == TECLAS.LETRA_U)
        {
            cargarAnimacionFatality(personaje2, menuSel);
            *estado = ESTADO_FATALITY;
        }
    }
}

void cargarSpritesFatality(Personaje *ganador, const char *nombreGanador)
{
    // para int numSpritesFatality
    for (int i = 0; i < ganador->fatalityGolpe->numSpritesFatality; i++)
    {
        char nombreArchivo[100];
        char nombreArchivoMask[100];
        sprintf(nombreArchivo, "./sprites/fatalitys/%s/%s_fatality_%d.bmp", nombreGanador, nombreGanador, (i + 1));
        sprintf(nombreArchivoMask, "./sprites/fatalitys/%s/%s_fatality_%d_mask.bmp", nombreGanador, nombreGanador, (i + 1));
        ganador->fatalityGolpe->personajeFatality[i] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        if (ganador->fatalityGolpe->personajeFatality[i] == NULL)
        {
            printf("Aviso: No se encontro el frame %d para el fatality de %s\n", i + 1, nombreGanador);
        }
    }
    // para int numSpritesAbatido
    for (int i = 0; i < ganador->fatalityGolpe->numSpritesAbatido; i++)
    {
        char nombreArchivo[100];
        char nombreArchivoMask[100];

        sprintf(nombreArchivo, "./sprites/fatalitys/%s/%s_fatality_golpe_%d.bmp", nombreGanador, nombreGanador, (i + 1));
        sprintf(nombreArchivoMask, "./sprites/fatalitys/%s/%s_fatality_golpe_%d_mask.bmp", nombreGanador, nombreGanador, (i + 1));
        ganador->fatalityGolpe->personajeAbatido[i] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);

        if (ganador->fatalityGolpe->personajeAbatido[i] == NULL)
        {
            printf("Aviso: No se encontro el frame %d para el fatality de %s\n", i + 1, nombreGanador);
        }
    }
    // para  int numSpritesTecnica
    for (int i = 0; i < ganador->fatalityGolpe->numSpritesTecnica; i++)
    {
        char nombreArchivo[100];
        char nombreArchivoMask[100];
        sprintf(nombreArchivo, "./sprites/fatalitys/%s/%s_fatality_tecnica_%d.bmp", nombreGanador, nombreGanador, (i + 1));
        sprintf(nombreArchivoMask, "./sprites/fatalitys/%s/%s_fatality_tecnica_%d_mask.bmp", nombreGanador, nombreGanador, (i + 1));
        ganador->fatalityGolpe->dibujoTecnica[i] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        if (ganador->fatalityGolpe->dibujoTecnica[i] == NULL)
        {
            printf("Aviso: No se encontro el frame %d para el fatality de %s\n", i + 1, nombreGanador);
        }
    }
}

void cargarAnimacionFatality(Personaje *ganador, MenuSeleccion *menuSel)
{
    // buffer para el nombre del ganador
    char nombreGanador[20];
    // se crea la memoria para las animaciones del fatality
    ganador->fatalityGolpe = (Fatality *)malloc(sizeof(Fatality));
    // Se inicializa el frameActual a 0 para iniciar la animacion
    ganador->fatalityGolpe->frameActual = 0;
    // condiciones para saber de que personaje se cargaran los frames y acorde a eso establecer el numero de frames
    // Para el personaje 1
    if (ganador == menuSel->datosJuego->personaje1)
    {
        if (menuSel->selP1 == LIUKANG)
        {
            ganador->fatalityGolpe->totalFrames = 12;
            sprintf(nombreGanador, "liu");
            ganador->fatalityGolpe->numSpritesAbatido = 8;
            ganador->fatalityGolpe->numSpritesFatality = 6;
            ganador->fatalityGolpe->numSpritesTecnica = 11;
            ganador->fatalityGolpe->coorXFatality = 400;
            ganador->fatalityGolpe->coorYFatality = 400;
        }
        else if (menuSel->selP1 == SUBZERO)
        {
            ganador->fatalityGolpe->totalFrames = 11;
            sprintf(nombreGanador, "sub");
            ganador->fatalityGolpe->numSpritesAbatido = 10;
            ganador->fatalityGolpe->numSpritesFatality = 5;
            ganador->fatalityGolpe->numSpritesTecnica = 4;
            ganador->fatalityGolpe->coorXFatality = 400;
            ganador->fatalityGolpe->coorYFatality = 400;
        }
    }
    // para el personaje 2
    else
    {
        if (menuSel->selP2 == SCORPION)
        {
            ganador->fatalityGolpe->totalFrames = 9;
            sprintf(nombreGanador, "scor");
            ganador->fatalityGolpe->numSpritesAbatido = 8;
            ganador->fatalityGolpe->numSpritesFatality = 8;
            ganador->fatalityGolpe->numSpritesTecnica = 8;
            ganador->fatalityGolpe->coorXFatality = 800;
            ganador->fatalityGolpe->coorYFatality = 400;
        }
        else if (menuSel->selP2 == RAIDEN)
        {
            ganador->fatalityGolpe->totalFrames = 16;
            sprintf(nombreGanador, "raiden");
            ganador->fatalityGolpe->numSpritesAbatido = 15;
            ganador->fatalityGolpe->numSpritesFatality = 10;
            ganador->fatalityGolpe->numSpritesTecnica = 7;
            ganador->fatalityGolpe->coorXFatality = 800;
            ganador->fatalityGolpe->coorYFatality = 400;
        }
    }

    // Reservar memoria para las imagenes acorde a los frames establecidos, Imagen** es de doble puntero pues son imagenes dinamicas
    ganador->fatalityGolpe->personajeFatality = (Imagen **)malloc(sizeof(Imagen *) * ganador->fatalityGolpe->totalFrames);
    ganador->fatalityGolpe->personajeAbatido = (Imagen **)malloc(sizeof(Imagen *) * ganador->fatalityGolpe->totalFrames);
    ganador->fatalityGolpe->dibujoTecnica = (Imagen **)malloc(sizeof(Imagen *) * ganador->fatalityGolpe->totalFrames);

    // Inciializar la memoria en NULL para evitar crasheos
    for (int z = 0; z < ganador->fatalityGolpe->totalFrames; z++)
    {
        ganador->fatalityGolpe->personajeFatality[z] = NULL;
        ganador->fatalityGolpe->personajeAbatido[z] = NULL;
        ganador->fatalityGolpe->dibujoTecnica[z] = NULL;
    }

    // Llenar o buscar los archivos bmp acorde al nombre del personaje/ganador y el nmumero de frames
    cargarSpritesFatality(ganador, nombreGanador);
}

void dibujarEscenaFatality(Personaje *ganador, Personaje *perdedor)
{
    // si falla la reserva de memoria, retornar NULL para evitar crasheos
    if (ganador->fatalityGolpe == NULL)
    {
        return;
    }
    // Inicializamos el frame al frame actual de la animacion del ganador
    int frame = ganador->fatalityGolpe->frameActual;
    if (frame < ganador->fatalityGolpe->totalFrames)
    {
        ventana.muestraImagenEscalada(ganador->fatalityGolpe->coorXFatality, ganador->fatalityGolpe->coorYFatality, 154, 190, ganador->fatalityGolpe->personajeFatality[frame]);
        if (frame >= 4)
        {
            ventana.muestraImagenEscalada(perdedor->x, perdedor->y, 154, 190, ganador->fatalityGolpe->dibujoTecnica[frame]);
        }
        if (frame >= 5)
        {
            ventana.muestraImagenEscalada(perdedor->x, perdedor->y, 130, 190, ganador->fatalityGolpe->personajeAbatido[frame]);
        }
        else
        {
            dibujarPersonaje(perdedor);
        }
    }
}

void liberarPersonajeMemoria(Personaje *personaje)
{
    if (personaje == NULL)
        return;
    if (personaje->sprites != NULL)
    {
        for (int i = 0; i < 70; i++)
        {
            if (personaje->sprites[i] != NULL)
            {
                ventana.eliminaImagen(personaje->sprites[i]);
                personaje->sprites[i] = NULL;
            }
        }
        free(personaje->sprites);
    }

    if (personaje->fatalityGolpe != NULL)
    {
        for (int i = 0; i < personaje->fatalityGolpe->totalFrames; i++)
        {
            if (personaje->fatalityGolpe->personajeFatality && personaje->fatalityGolpe->personajeFatality[i])
                ventana.eliminaImagen(personaje->fatalityGolpe->personajeFatality[i]);
            if (personaje->fatalityGolpe->personajeAbatido && personaje->fatalityGolpe->personajeAbatido[i])
                ventana.eliminaImagen(personaje->fatalityGolpe->personajeAbatido[i]);
            if (personaje->fatalityGolpe->dibujoTecnica && personaje->fatalityGolpe->dibujoTecnica[i])
                ventana.eliminaImagen(personaje->fatalityGolpe->dibujoTecnica[i]);
        }
        if (personaje->fatalityGolpe->personajeFatality)
            free(personaje->fatalityGolpe->personajeFatality);
        if (personaje->fatalityGolpe->personajeAbatido)
            free(personaje->fatalityGolpe->personajeAbatido);
        if (personaje->fatalityGolpe->dibujoTecnica)
            free(personaje->fatalityGolpe->dibujoTecnica);

        free(personaje->fatalityGolpe);
        personaje->fatalityGolpe = NULL;
    }

    free(personaje);
}