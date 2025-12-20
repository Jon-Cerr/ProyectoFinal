#include <stdio.h>
#include <stdlib.h>

#include "../graficos/graficos.h"
#include "./personaje.h"

Personaje *cargarPersonaje(Personaje *personaje, EstadoPersonaje estado)
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
    personaje->sprites = (Imagen **)malloc(sizeof(Imagen *) * 60);

    // Llenar la memoria reservada en NULL para evitar bugs
    for (int z = 0; z < 60; z++)
    {
        personaje->sprites[z] = NULL;
    }
    int indiceActual = 0;

    const char *nombrePersonaje = "sub";
    cargarSprites(personaje, nombrePersonaje);
    return personaje;
}

Personaje *cargarPersonaje2(Personaje *personaje, EstadoPersonaje estado)
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
    personaje->controls.derecha = TECLAS.LETRA_L;
    personaje->controls.izquierda = TECLAS.LETRA_J;
    personaje->controls.golpe = TECLAS.LETRA_U;
    personaje->controls.golpe2 = TECLAS.LETRA_O;
    personaje->controls.patada = TECLAS.LETRA_I;
    personaje->controls.defensa = TECLAS.LETRA_M;
    personaje->defendiendo = false;
    personaje->sprites = (Imagen **)malloc(sizeof(Imagen *) * 60);

    // Llenar la memoria reservada en NULL para evitar bugs
    for (int z = 0; z < 60; z++)
    {
        personaje->sprites[z] = NULL;
    }
    const char *nombrePersonaje = "scor";
    cargarSprites(personaje, nombrePersonaje);
    return personaje;
}

void cargarSprites(Personaje *personaje, const char *nombrePersonaje)
{
    int indiceActual = 0;
    // Se llenan los arreglos de animaciones correspondientes y los sprites del personaje
    for (int i = 0; i < 4; i++)
    {
        char nombreArchivo[100];
        sprintf(nombreArchivo, "./sprites/quieto/%s_quieto_%d.bmp", nombrePersonaje, (i + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/quieto/%s_quieto_%d_mask.bmp", nombrePersonaje, (i + 1));
        personaje->sprites[indiceActual] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        if (personaje->sprites[indiceActual] == NULL)
        {
            printf("ERROR: No se encontró el archivo: %s\n", nombreArchivo);
        }
        else
        {
            printf("Cargado con éxito: %s\n", nombreArchivo);
        }
        personaje->animQuieto[i] = personaje->sprites[indiceActual];
        indiceActual++;
    }

    for (int j = 0; j < 6; j++)
    {
        char nombreArchivo[100];
        sprintf(nombreArchivo, "./sprites/camina/%s_camina_%d.bmp", nombrePersonaje, (j + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/camina/%s_camina_%d_mask.bmp", nombrePersonaje, (j + 1));
        personaje->sprites[indiceActual] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        if (personaje->sprites[indiceActual] == NULL)
        {
            printf("ERROR: No se encontró el archivo: %s\n", nombreArchivo);
        }
        else
        {
            printf("Cargado con éxito: %s\n", nombreArchivo);
        }
        personaje->animCaminata[j] = personaje->sprites[indiceActual];
        indiceActual++;
    }

    for (int k = 0; k < 3; k++)
    {
        char nombreArchivo[100];
        sprintf(nombreArchivo, "./sprites/golpe/%s_golpe_%d.bmp", nombrePersonaje, (k + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/golpe/%s_golpe_%d_mask.bmp", nombrePersonaje, (k + 1));
        personaje->sprites[indiceActual] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        if (personaje->sprites[indiceActual] == NULL)
        {
            printf("ERROR: No se encontró el archivo: %s\n", nombreArchivo);
        }
        else
        {
            printf("Cargado con éxito: %s\n", nombreArchivo);
        }
        personaje->animGolpe[k] = personaje->sprites[indiceActual];
        indiceActual++;
    }

    for (int l = 0; l < 3; l++)
    {
        char nombreArchivo[100];
        sprintf(nombreArchivo, "./sprites/golpe/golpe2/%s_golpe_%d.bmp", nombrePersonaje, (l + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/golpe/golpe2/%s_golpe_%d_mask.bmp", nombrePersonaje, (l + 1));
        personaje->sprites[indiceActual] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        if (personaje->sprites[indiceActual] == NULL)
        {
            printf("ERROR: No se encontró el archivo: %s\n", nombreArchivo);
        }
        else
        {
            printf("Cargado con éxito: %s\n", nombreArchivo);
        }
        personaje->animGolpe2[l] = personaje->sprites[indiceActual];
        indiceActual++;
    }

    for (int m = 0; m < 4; m++)
    {
        char nombreArchivo[100];
        sprintf(nombreArchivo, "./sprites/golpe/patada/%s_patada_%d.bmp", nombrePersonaje, (m + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/golpe/patada/%s_patada_%d_mask.bmp", nombrePersonaje, (m + 1));
        personaje->sprites[indiceActual] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        if (personaje->sprites[indiceActual] == NULL)
        {
            printf("ERROR: No se encontró el archivo: %s\n", nombreArchivo);
        }
        else
        {
            printf("Cargado con éxito: %s\n", nombreArchivo);
        }
        personaje->animPatada[m] = personaje->sprites[indiceActual];
        indiceActual++;
    }

    for (int n = 0; n < 3; n++)
    {
        char nombreArchivo[100];
        sprintf(nombreArchivo, "./sprites/golpeado/%s_golpeado_%d.bmp", nombrePersonaje, (n + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/golpeado/%s_golpeado_%d_mask.bmp", nombrePersonaje, (n + 1));
        personaje->sprites[indiceActual] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        if (personaje->sprites[indiceActual] == NULL)
        {
            printf("ERROR: No se encontró el archivo: %s\n", nombreArchivo);
        }
        else
        {
            printf("Cargado con éxito: %s\n", nombreArchivo);
        }
        personaje->animGolpeado[n] = personaje->sprites[indiceActual];
        indiceActual++;
    }

    for (int o = 0; o < 3; o++)
    {
        char nombreArchivo[100];
        sprintf(nombreArchivo, "./sprites/golpeado/%s_defensa_%d.bmp", nombrePersonaje, (o + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/golpeado/%s_defensa_%d_mask.bmp", nombrePersonaje, (o + 1));
        personaje->sprites[indiceActual] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        if (personaje->sprites[indiceActual] == NULL)
        {
            printf("ERROR: No se encontró el archivo: %s\n", nombreArchivo);
        }
        else
        {
            printf("Cargado con éxito: %s\n", nombreArchivo);
        }
        personaje->animDefensa[o] = personaje->sprites[indiceActual];
        indiceActual++;
    }
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
}

void cambiarEstado(Personaje *personaje, int tecla, int teclaSoltada)
{
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

void actualizarVida(Personaje *personaje, int tecla)
{
    if (tecla == TECLAS.LETRA_U || tecla == TECLAS.LETRA_I || tecla == TECLAS.LETRA_O)
    {
        if (personaje->vida > 0)
        {
            personaje->vida -= 2;
        }
    }
}

void dibujarHUD(Personaje *personaje, int tecla)
{
    ventana.color(COLORES.ROJO);
    ventana.rectanguloRelleno(70, 50, 470, 80);

    ventana.color(COLORES.VERDE);
    ventana.rectanguloRelleno(70, 50, 70 + (personaje->vida * 4), 80);

    ventana.color(COLORES.BLANCO);
    ventana.rectangulo(70, 50, 470, 80);
}

void actualizarVidaP2(Personaje *personaje, int tecla)
{
    if (tecla == TECLAS.LETRA_Q || tecla == TECLAS.LETRA_W || tecla == TECLAS.LETRA_E)
    {
        if (personaje->vida > 0)
        {
            personaje->vida -= 2;
        }
    }
}

void dibujarHUDP2(Personaje *personaje, int tecla)
{
    ventana.color(COLORES.ROJO);
    ventana.rectanguloRelleno(800, 50, 1200, 80);

    ventana.color(COLORES.VERDE);
    ventana.rectanguloRelleno(1200 - (personaje->vida * 4), 50, 1200, 80);

    ventana.color(COLORES.BLANCO);
    ventana.rectangulo(800, 50, 1200, 80);
}

void detectarColision(Personaje *personaje1, Personaje *personaje2, int tecla)
{
    // distancia absoluta entre personaje1 y personaje2
    int distancia = abs(personaje1->x - personaje2->x);
    int minColision = 150; // colision minima para detectar el golpe
    if (distancia < minColision)
    {
        if (personaje1->estado == GOLPEANDO || personaje1->estado == GOLPEANDO2 || personaje1->estado == PATEANDO)
        {
            if (personaje2->vida > 0)
            {
                if (!(personaje2->defendiendo))
                {
                    personaje2->estado = GOLPEADO;
                    personaje2->frameActual = 0;
                    personaje2->vida -= 1;
                }
            }
        }
        if (personaje2->estado == GOLPEANDO || personaje2->estado == GOLPEANDO2 || personaje2->estado == PATEANDO)
        {
            if (personaje1->vida > 0)
            {
                if (!(personaje1->defendiendo))
                {
                    personaje1->estado = GOLPEADO;
                    personaje1->frameActual = 0;
                    personaje1->vida -= 1;
                }
            }
        }
    }
}

void liberarPersonajeMemoria(Personaje *personaje)
{
    if (personaje == NULL)
    {
        return;
    }
    for (int i = 0; i < 60; i++)
    {
        if (personaje->sprites[i] != NULL)
        {
            ventana.eliminaImagen(personaje->sprites[i]);
        }
    }
    free(personaje->sprites);
    free(personaje);
}