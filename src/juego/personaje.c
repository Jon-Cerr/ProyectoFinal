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
    personaje->controls.derecha = TECLAS.LETRA_L;
    personaje->controls.izquierda = TECLAS.LETRA_J;
    personaje->controls.golpe = TECLAS.LETRA_U;
    personaje->controls.golpe2 = TECLAS.LETRA_O;
    personaje->controls.patada = TECLAS.LETRA_I;
    personaje->controls.defensa = TECLAS.LETRA_M;
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

    for (int p = 0; p < 7; p++)
    {
        char nombreArchivo[100];
        sprintf(nombreArchivo, "./sprites/abatido/%s_abatido_%d.bmp", nombrePersonaje, (p + 1));
        char nombreArchivoMask[100];
        sprintf(nombreArchivoMask, "./sprites/abatido/%s_abatido_%d_mask.bmp", nombrePersonaje, (p + 1));
        personaje->sprites[indiceActual] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        if (personaje->sprites[indiceActual] == NULL)
        {
            ventana.muestraMensaje("No se pudieron cargar los sprites.");
            printf("ERROR: No se encontró el archivo: %s\n", nombreArchivo);
        }
        else
        {
            printf("Cargado con éxito: %s\n", nombreArchivo);
        }
        personaje->animAbatido[p] = personaje->sprites[indiceActual];
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
    //comparar distancias para hacer efectiva la colision
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
                    personaje2->vida -= 10;
                    if (personaje2->vida <= 0)
                    {
                        personaje2->vida = 0;
                        personaje2->estado = ABATIDO;
                        personaje2->frameActual = 0;
                        ventana.reproducirAudio("./assets/audio/finish.wav");
                    }
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
                    personaje1->vida -= 10;
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

    //logica para el personaje 1 para activar el fatality
    if (personaje2->estado == ABATIDO && distancia < 150)
    {
        if (tecla == TECLAS.LETRA_Q)
        {
            cargarAnimacionFatality(personaje1, personaje2, menuSel);
            *estado = ESTADO_FATALITY;
        }
    }
    //logica para el personaje 2 para activar el fatality
    if (personaje1->estado == ABATIDO && distancia < 150)
    {
        if (tecla == TECLAS.LETRA_U)
        {
            cargarAnimacionFatality(personaje2, personaje1, menuSel);
            *estado = ESTADO_FATALITY;
        }
    }
}

void cargarAnimacionFatality(Personaje *ganador, Personaje *perdedor, MenuSeleccion *menuSel)
{
    // buffer para el nombre del ganador
    char nombreGanador[20];
    // se crea la memoria para las animacones del fatality
    ganador->fatalityGolpe = (Fatality *)malloc(sizeof(Fatality));
    ganador->fatalityGolpe->frameActual = 0;
    //condiciones para saber de que personaje se cargaran los frames y acoerde a eso establecer el numero de frames
    if (menuSel->selP1 == LIUKANG)
    {
        ganador->fatalityGolpe->totalFrames = 16;
        sprintf(nombreGanador, "liu");
    }
    else if (menuSel->selP1 == SUBZERO)
    {
        ganador->fatalityGolpe->totalFrames = 16;
        sprintf(nombreGanador, "sub");
    }
    if (menuSel->selP2 == SCORPION)
    {
        ganador->fatalityGolpe->totalFrames = 8;
        sprintf(nombreGanador, "scor");
    }
    else if (menuSel->selP2 == RAIDEN)
    {
        ganador->fatalityGolpe->totalFrames = 16;
        sprintf(nombreGanador, "raiden");
    }

    // reservar memoria para las imagenes acorde a los frames establecidos, Imagen** es de doble puntero pues son imagenes dinamicas
    ganador->fatalityGolpe->personajeFatality = (Imagen **)malloc(sizeof(Imagen *) * ganador->fatalityGolpe->totalFrames);
    ganador->fatalityGolpe->personajeAbatido = (Imagen **)malloc(sizeof(Imagen *) * ganador->fatalityGolpe->totalFrames);
    ganador->fatalityGolpe->dibujoTecnica = (Imagen **)malloc(sizeof(Imagen *) * ganador->fatalityGolpe->totalFrames);

    // inciializar la memoria en NULL para evitar crasheos
    for (int z = 0; z < ganador->fatalityGolpe->totalFrames; z++)
    {
        ganador->fatalityGolpe->personajeFatality[z] = NULL;
        ganador->fatalityGolpe->personajeAbatido[z] = NULL;
        ganador->fatalityGolpe->dibujoTecnica[z] = NULL;
    }

    // llenar o buscar los archivos bmp acorde al nombre del personaje/ganador y el nmumero de frames
    for (int i = 0; i < ganador->fatalityGolpe->totalFrames; i++)
    {
        char nombreArchivo[100];
        char nombreArchivoMask[100];
        sprintf(nombreArchivo, "./sprites/fatalitys/%s/%s_fatality_%d.bmp", nombreGanador, nombreGanador, (i + 1));
        sprintf(nombreArchivoMask, "./sprites/fatalitys/%s/%s_fatality_%d_mask.bmp", nombreGanador, nombreGanador, (i + 1));
        ganador->fatalityGolpe->personajeFatality[i] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        sprintf(nombreArchivo, "./sprites/fatalitys/%s/%s_fatality_golpe_%d.bmp", nombreGanador, nombreGanador, (i + 1));
        sprintf(nombreArchivoMask, "./sprites/fatalitys/%s/%s_fatality_golpe_%d_mask.bmp", nombreGanador, nombreGanador, (i + 1));
        ganador->fatalityGolpe->personajeAbatido[i] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        sprintf(nombreArchivo, "./sprites/fatalitys/%s/%s_fatality_tecnica_%d.bmp", nombreGanador, nombreGanador, (i + 1));
        sprintf(nombreArchivoMask, "./sprites/fatalitys/%s/%s_fatality_tecnica_%d_mask.bmp", nombreGanador, nombreGanador, (i + 1));
        ganador->fatalityGolpe->dibujoTecnica[i] = ventana.creaImagenConMascara(nombreArchivo, nombreArchivoMask);
        if (ganador->fatalityGolpe->personajeFatality[i] == NULL)
        {
            printf("Aviso: No se encontro el frame %d para el fatality de %s\n", i + 1, nombreGanador);
        }
    }
}

void dibujarEscenaFatality(Personaje *ganador, Personaje *perdedor)
{
    // si falla la reserva de memoria, retornar NULL para evitar crasheos
    if (ganador->fatalityGolpe == NULL)
    {
        return;
    }
    //inicializamos el frame al frame actual de la animacion del ganador
    int frame = ganador->fatalityGolpe->frameActual;
    if (frame < ganador->fatalityGolpe->totalFrames)
    {
        ventana.muestraImagenEscalada(ganador->x, ganador->y, 154, 190, ganador->fatalityGolpe->personajeFatality[frame]);
        if (frame >= 4)
        {
            ventana.muestraImagenEscalada(perdedor->x - 80, perdedor->y, 154, 190, ganador->fatalityGolpe->dibujoTecnica[frame]);
        }
        if (frame >= 5)
        {
            ventana.muestraImagenEscalada(perdedor->x - 50, perdedor->y, 130, 190, ganador->fatalityGolpe->personajeAbatido[frame]);
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