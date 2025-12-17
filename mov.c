/**
 * @file mov.c
 * @author Willliam Isai Gonzalez Cabrera
 *         2026640133
 * @brief movimiento de pato
 * @version 0.1
 * @date 2025-12-09
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"graficos.h"
int main()
{
    int movx;
    int movy;
    int limitx;
    int limity;
    int x, y;
    Imagen *patoverde = ventana.creaImagenConMascara("nadamask.bmp","nada.bmp");
    int tecla= ventana.teclaPresionada();
    srand(time(NULL));

    //Configuracion de la ventana
    ventana.tituloVentana("Pruebas");
    ventana.tamanioVentana(x,y);
    ventana.limpiaVentana();
    ventana.colorFondo(COLORES.CYAN);
    ventana.actualizaVentana();
    ventana.espera(1);
    ventana.limpiaVentana();
    ventana.actualizaVentana();
    ventana.espera(1);
    ventana.limpiaVentana();

    //Posiciones Iniciales
    movx = 80 + rand()%(ventana.anchoVentana()-159);
    movy = ventana.altoVentana() - 85;

    //Limites de la pantalla
    limitx = ventana.anchoVentana() - 75;
    limity = ventana.altoVentana() - 75;

    //Primer ciclo de movimiento
    for (int i = movx; i < limitx; i++)
    {
    patoverde=ventana.creaImagenConMascara("Patoverde.bmp","Patoverdemask.bmp");
    ventana.muestraImagenEscalada(i,movy--,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde1.bmp","Patoverdemask1.bmp");
    ventana.muestraImagenEscalada(i++,movy--,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde2.bmp","Patoverdemask2.bmp");
    ventana.muestraImagenEscalada(i++,movy--,75,75,patoverde);
    ventana.eliminaImagen(patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde1.bmp","Patoverdemask1.bmp");
    ventana.muestraImagenEscalada(i++,movy--,75,75,patoverde);
    ventana.eliminaImagen(patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde.bmp","Patoverdemask.bmp");
    ventana.muestraImagenEscalada(i++,movy--,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    }
    ventana.cierraVentana();
    return 0;
}
