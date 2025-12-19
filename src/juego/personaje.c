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
    personaje->sprites = (Imagen **)malloc(sizeof(Imagen *) * 45);

    // Llenar la memoria reservada en NULL para evitar bugs
    for (int z = 0; z < 45; z++)
    {
        personaje->sprites[z] = NULL;
    }
    int indiceActual = 0;
    
    // Se llenan los arreglos de animaciones correspondientes y los sprites del personaje
    for (int i = 0; i < 4; i++)
    {
        char nombreArchivo[100];
        sprintf(nombreArchivo, "./sprites/quieto/sub_quieto_%d.bmp", (i + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/quieto/sub_quieto_%d_mask.bmp", (i + 1));
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
        sprintf(nombreArchivo, "./sprites/camina/sub_camina_%d.bmp", (j + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/camina/sub_camina_%d_mask.bmp", (j + 1));
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
        sprintf(nombreArchivo, "./sprites/golpe/sub_golpe_%d.bmp", (k + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/golpe/sub_golpe_%d_mask.bmp", (k + 1));
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
        sprintf(nombreArchivo, "./sprites/golpe/golpe2/sub_golpe_%d.bmp", (l + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/golpe/golpe2/sub_golpe_%d_mask.bmp", (l + 1));
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
        sprintf(nombreArchivo, "./sprites/golpe/patada/sub_patada_%d.bmp", (m + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/golpe/patada/sub_patada_%d_mask.bmp", (m + 1));
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
    personaje->sprites = (Imagen **)malloc(sizeof(Imagen *) * 45);

    // Llenar la memoria reservada en NULL para evitar bugs
    for (int z = 0; z < 45; z++)
    {
        personaje->sprites[z] = NULL;
    }
    int indiceActual = 0;

    // Se llenan los arreglos de animaciones correspondientes y los sprites del personaje
    for (int i = 0; i < 4; i++)
    {
        char nombreArchivo[100];
        sprintf(nombreArchivo, "./sprites/quieto/scor_quieto_%d.bmp", (i + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/quieto/scor_quieto_%d_mask.bmp", (i + 1));
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
        sprintf(nombreArchivo, "./sprites/camina/scor_camina_%d.bmp", (j + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/camina/scor_camina_%d_mask.bmp", (j + 1));
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
        sprintf(nombreArchivo, "./sprites/golpe/scor_golpe_%d.bmp", (k + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/golpe/scor_golpe_%d_mask.bmp", (k + 1));
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
        sprintf(nombreArchivo, "./sprites/golpe/golpe2/scor_golpe_%d.bmp", (l + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/golpe/golpe2/scor_golpe_%d_mask.bmp", (l + 1));
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
        sprintf(nombreArchivo, "./sprites/golpe/patada/scor_patada_%d.bmp", (m + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/golpe/patada/scor_patada_%d_mask.bmp", (m + 1));
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
    return personaje;
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
    
    cambiarEstado(personaje, tecla, teclaSoltada);
    personaje->frameActual++;
    if (personaje->frameActual >= personaje->totalFrames)
    {
        if (personaje->estado == GOLPEANDO ||
            personaje->estado == GOLPEANDO2 ||
            personaje->estado == PATEANDO)
        {
            personaje->estado = QUIETO;
            personaje->totalFrames = 4;
        }
        personaje->frameActual = 0;
    }
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

void liberarPersonajeMemoria(Personaje *personaje)
{
    if (personaje == NULL)
    {
        return;
    }
    for (int i = 0; i < 45; i++)
    {
        if (personaje->sprites[i] != NULL)
        {
            ventana.eliminaImagen(personaje->sprites[i]);
        }
    }
    free(personaje->sprites);
    free(personaje);
}