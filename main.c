#include "graficos.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Definiciones de pantalla
#define ANCHO 800
#define ALTO 600

// Estados del Juego
typedef enum { MENU, INICIO_PERRO, JUGANDO, PATO_CAYENDO, GAME_OVER } Estado;

// Estructura para el Pato
typedef struct {
    float x, y;
    float vx, vy;
    int frame;
    bool vivo;
} Pato;

void reproducirSonido(const char* archivo) {
    // Requiere -lwinmm al compilar
    PlaySoundA(archivo, NULL, SND_FILENAME | SND_ASYNC);
}

int main() {
    ventana.tamanioVentana(ANCHO, ALTO);
    ventana.tituloVentana("Duck Hunt Remake");
    srand(time(NULL));

    // Carga de Recursos (Basado en tus archivos)
    Imagen* imgFondo = ventana.creaImagenConMascara("Portada.bmp", "Portadamask.bmp");
    Imagen* imgPato[3];
    imgPato[0] = ventana.creaImagenConMascara("Patoverde1.bmp", "Patoverdemask1.bmp");
    imgPato[1] = ventana.creaImagenConMascara("Patoverde2.bmp", "Patoverdemask2.bmp");
    imgPato[2] = ventana.creaImagenConMascara("Patoverde.bmp", "Patoverdemask.bmp");
    
    Imagen* imgCaido = ventana.creaImagenConMascara("Patocaido.bmp", "Patocaidomask.bmp");
    Imagen* imgPerro = ventana.creaImagenConMascara("Perro.bmp", "Perromask.bmp");
    Imagen* imgAtrapado = ventana.creaImagenConMascara("Atrapado.bmp", "Atrapadomask.bmp");

    // Variables de Juego
    Estado estadoActual = MENU;
    Pato pato = {100, 400, 7.0, -5.0, 0, true};
    int puntos = 0;
    int timer = 0;
    int animPerroX = 0;

    while (true) {
        int mx, my;
        bool click = ventana.ratonBotonIzquierdo();
        ventana.raton(&mx, &my);

        if (ventana.teclaPresionada() == TECLAS.ESCAPE) break;

        ventana.limpiaVentana();
        ventana.muestraImagenEscalada(0, 0, ANCHO, ALTO, imgFondo);

        switch (estadoActual) {
            case MENU:
                ventana.color(COLORES.BLANCO);
                ventana.texto1(ANCHO/2 - 100, ALTO/2, "DUCK HUNT", 50, "Arial");
                ventana.texto(ANCHO/2 - 120, ALTO/2 + 60, "Presiona ENTER para comenzar");
                if (ventana.teclaPresionada() == TECLAS.ENTER) {
                    reproducirSonido("Voicy_Duck Hunt Intro.wav");
                    estadoActual = INICIO_PERRO;
                    animPerroX = 0;
                }
                break;

            case INICIO_PERRO:
                // Animación del perro caminando al inicio
                ventana.muestraImagen(animPerroX, 420, imgPerro);
                animPerroX += 4;
                if (animPerroX > 300) {
                    estadoActual = JUGANDO;
                    pato.x = 400; pato.y = 450; pato.vivo = true;
                }
                break;

            case JUGANDO:
                // Animación de vuelo del pato
                pato.x += pato.vx;
                pato.y += pato.vy;
                if (pato.x < 0 || pato.x > ANCHO - 60) pato.vx *= -1;
                if (pato.y < 0 || pato.y > ALTO - 250) pato.vy *= -1;

                pato.frame = (pato.frame + 1) % 30;
                ventana.muestraImagen((int)pato.x, (int)pato.y, imgPato[pato.frame/10]);

                if (click) {
                    reproducirSonido("Voicy_GunShot.wav");
                    if (mx > pato.x && mx < pato.x + 60 && my > pato.y && my < pato.y + 60) {
                        pato.vivo = false;
                        estadoActual = PATO_CAYENDO;
                        puntos += 100;
                        reproducirSonido("Voicy_HighScore.wav");
                    }
                }
                break;

            case PATO_CAYENDO:
                ventana.muestraImagen((int)pato.x, (int)pato.y, imgCaido);
                pato.y += 10;
                if (pato.y > 420) {
                    timer++;
                    ventana.muestraImagen(pato.x, 400, imgAtrapado); // Perro sale con el pato
                    if (timer > 40) {
                        pato.y = 450; pato.x = rand() % 600;
                        pato.vivo = true;
                        timer = 0;
                        estadoActual = JUGANDO;
                    }
                }
                break;
        }

        // Interfaz (UI)
        char buffer[30];
        sprintf(buffer, "SCORE: %06d", puntos);
        ventana.color(COLORES.BLANCO);
        ventana.texto2(20, 550, buffer, 30, "Consolas", false, true, false);

        ventana.actualizaVentana();
        ventana.espera(20);
    }

    // Liberar memoria
    ventana.eliminaImagen(imgFondo);
    ventana.eliminaImagen(imgPerro);
    ventana.eliminaImagen(imgAtrapado);
    for(int i=0; i<3; i++) ventana.eliminaImagen(imgPato[i]);
    
    return 0;
}