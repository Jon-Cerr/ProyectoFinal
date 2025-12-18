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

    personaje->x = 100;
    personaje->y = 400;
    personaje->vida = 100;
    personaje->estado = QUIETO; // quieto
    personaje->frameActual = 0;
    personaje->totalFrames = 4;
    personaje->sprites = (Imagen **)malloc(sizeof(Imagen *) * 15);

    for (int i = 0; i < 4; i++)
    {
        char nombreArchivo[100];
        sprintf(nombreArchivo, "./sprites/quieto/sub_quieto_%d.bmp", (i + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/quieto/sub_quieto_%d_mask.bmp", (i + 1));
        personaje->sprites[i] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        personaje->animQuieto[i] = personaje->sprites[i];
        if (personaje->sprites[i] == NULL)
        {
            printf("ERROR: No se encontró el archivo: %s\n", nombreArchivo);
        }
        else
        {
            printf("Cargado con éxito: %s\n", nombreArchivo);
        }
    }
    for (int j = 0; j < 6; j++)
    {
        char nombreArchivo[100];
        sprintf(nombreArchivo, "./sprites/camina/sub_camina_%d.bmp", (j + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/camina/sub_camina_%d_mask.bmp", (j + 1));
        personaje->sprites[j + 4] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        personaje->animCaminata[j] = personaje->sprites[j + 4];
        if (personaje->sprites[j + 4] == NULL)
        {
            printf("ERROR: No se encontró el archivo: %s\n", nombreArchivo);
        }
        else
        {
            printf("Cargado con éxito: %s\n", nombreArchivo);
        }
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
}

void cambiarEstado(Personaje *personaje)
{
    int teclaActual = ventana.teclaPresionada();
    int teclaActualSoltada = ventana.teclaSoltada();
    // detectar tecla de movimiento y cambiar estado del personaje y el frame actual
    if (teclaActual == TECLAS.LETRA_D && personaje->estado != CAMINANDO_DER)
    {
        personaje->estado = CAMINANDO_DER;
        personaje->frameActual = 0;
        personaje->totalFrames = 6;
    }
    else if ((teclaActualSoltada == TECLAS.LETRA_D) && personaje->estado != QUIETO)
    {
        personaje->estado = QUIETO;
        personaje->frameActual = 0;
        personaje->totalFrames = 4;
    }
    else if (teclaActual == TECLAS.LETRA_A && personaje->estado != CAMINANDO_IZQ)
    {
        personaje->estado = CAMINANDO_IZQ;
        personaje->frameActual = 0;
        personaje->totalFrames = 6;
    }
    else if ((teclaActualSoltada == TECLAS.LETRA_A) && personaje->estado != QUIETO)
    {
        personaje->estado = QUIETO;
        personaje->frameActual = 0;
        personaje->totalFrames = 4;
    }
}

void actualizarMovimiento(Personaje *personaje)
{
    cambiarEstado(personaje);
    personaje->frameActual = (personaje->frameActual + 1) % personaje->totalFrames;
    if (personaje->estado == CAMINANDO_DER)
    {
        if (!((personaje->x + 104) >= ventana.anchoVentana()))
        {
            personaje->x += 15;
        }
    }
    else if (personaje->estado == CAMINANDO_IZQ)
    {
        if (!(personaje->x <= 0 ))
        {
            personaje->x -= 15;
        }
    }
}