/**
 * @file podio_marcadores.c
 * @author Alan Jonathan Cerritos Hernandez (alanchdez147@gmail.com) 2026640080
 * @author Ricardo Chaparro Zarco (ricardochzarco@gmail.com) 2026640302
 * @author Jesus Roque Lopez (jesusroquelopez22@gmail.com) 2026640210
 * @brief Archivo de funciones para podio_marcadores
 * @version 0.1
 * @date 2026-01-04
 * Proyecto Final
 * 
 */
#include "podio_marcadores.h"
void mostrarMarcadores(EstadoJuego *estadoJuego, Juego *juego)
{
    ventana.reproducirAudio(NULL);
    while (*estadoJuego == ESTADO_PODIO)
    {
        ventana.limpiaVentana();
        ventana.muestraImagenEscalada(0, 0, ventana.anchoVentana(), ventana.altoVentana(), juego->fondosJuego->fondoPodio);
        int posYInicial = 250;
        int separacionY = 60;

        ventana.color(COLORES.AMARILLO);
        ventana.texto1(ventana.anchoVentana() / 2 - 300, 100, "PODIO DE KOMBATIENTES", 50, "Arial");
        ventana.color(COLORES.BLANCO);

        for (int i = 0; i < 5; i++)
        {
            ventana.muestraTextoParametroInt(300, posYInicial + (i * separacionY), "%d.", 30, "Arial", i + 1);
            ventana.texto1(450, posYInicial + (i * separacionY), juego->nuevoRegistro[i].nombreGanador, 30, "Arial");
        }
        if (ventana.teclaPresionada() == TECLAS.LETRA_V)
            *estadoJuego = ESTADO_MENUSELECCION;
        ventana.actualizaVentana();
        ventana.espera(10);
    }
}

void registrarVictoria(Juego *juego, const char *nombreGanador)
{
    if (juego == NULL)
    {
        return;
    }

    for (int i = 4; i > 0; i--)
    {
        juego->nuevoRegistro[i] = juego->nuevoRegistro[i - 1];
    }
    sprintf(juego->nuevoRegistro[0].nombreGanador, "%s", nombreGanador);
    juego->nuevoRegistro[0].victorias = 1;
    FILE *archivoPodio = fopen("podio.bin", "wb");
    if (archivoPodio)
    {
        fwrite(juego->nuevoRegistro, sizeof(RegistroGanador), 5, archivoPodio);
        fclose(archivoPodio);
    }
}

void cargarPodio(Juego *juego)
{
    FILE *archivoPodio = fopen("podio.bin", "rb");
    if (archivoPodio != NULL)
    {
        fread(juego->nuevoRegistro, sizeof(RegistroGanador), 5, archivoPodio);
        fclose(archivoPodio);
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            sprintf(juego->nuevoRegistro[i].nombreGanador, "---");
            juego->nuevoRegistro[i].victorias = 0;
        }
        archivoPodio = fopen("podio.bin", "wb");
        if (archivoPodio != NULL)
        {
            fwrite(juego->nuevoRegistro, sizeof(RegistroGanador), 5, archivoPodio);
            fclose(archivoPodio);
        }
        else
        {
            printf("No se pudo guardar el podio.\n");
            exit(1);
        }
    }
}