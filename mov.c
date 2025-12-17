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
    int movy=531;
    Imagen *patoverde = ventana.creaImagenConMascara("nadamask.bmp","nada.bmp");
    int tecla= ventana.teclaPresionada();
    srand(time(NULL));
    while (tecla != TECLAS.LETRA_N)
    {
    ventana.tituloVentana("Pruebas");
    ventana.tamanioVentana(800,600);
    ventana.limpiaVentana();
    ventana.colorFondo(COLORES.CYAN);
    ventana.actualizaVentana();
    ventana.espera(1);
    //ventana.muestraImagenEscalada(100,100,75,75,patoverde);
    ventana.limpiaVentana();
    ventana.actualizaVentana();
    ventana.espera(100);
    ventana.limpiaVentana();
    movx=rand()%(800-0+1);
    for (int i = movx; i < 730; i++)
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
    if (i > 729)
    {
        for (int j = i; movy > 0; j--)
        {
    patoverde=ventana.creaImagenConMascara("Patoverde0.bmp","Patoverde0mask.bmp");
    ventana.muestraImagenEscalada(j,movy,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde11.bmp","Patoverdemask11.bmp");
    ventana.muestraImagenEscalada(j--,movy--,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde22.bmp","Patoverdemask22.bmp");
    ventana.muestraImagenEscalada(j--,movy--,75,75,patoverde);
    ventana.eliminaImagen(patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde11.bmp","Patoverdemask11.bmp");
    ventana.muestraImagenEscalada(j--,movy--,75,75,patoverde);
    ventana.eliminaImagen(patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde0.bmp","Patoverde0mask.bmp");
    ventana.muestraImagenEscalada(j--,movy--,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    if (movy < 2)
    {
        for (int k = j; k > 0; k--)
        {
    patoverde=ventana.creaImagenConMascara("Patoverde0.bmp","Patoverde0mask.bmp");
    ventana.muestraImagenEscalada(k,movy,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde11.bmp","Patoverdemask11.bmp");
    ventana.muestraImagenEscalada(k--,movy++,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde22.bmp","Patoverdemask22.bmp");
    ventana.muestraImagenEscalada(k--,movy++,75,75,patoverde);
    ventana.eliminaImagen(patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde11.bmp","Patoverdemask11.bmp");
    ventana.muestraImagenEscalada(k--,movy++,75,75,patoverde);
    ventana.eliminaImagen(patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde0.bmp","Patoverde0mask.bmp");
    ventana.muestraImagenEscalada(k--,movy++,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    if (k < 2)
    {
        for (int l = k; movy < 730; l++)
        {
    patoverde=ventana.creaImagenConMascara("Patoverde.bmp","Patoverdemask.bmp");
    ventana.muestraImagenEscalada(l,movy,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde1.bmp","Patoverdemask1.bmp");
    ventana.muestraImagenEscalada(l++,movy++,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde2.bmp","Patoverdemask2.bmp");
    ventana.muestraImagenEscalada(l++,movy++,75,75,patoverde);
    ventana.eliminaImagen(patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde1.bmp","Patoverdemask1.bmp");
    ventana.muestraImagenEscalada(l++,movy++,75,75,patoverde);
    ventana.eliminaImagen(patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde.bmp","Patoverdemask.bmp");
    ventana.muestraImagenEscalada(l++,movy++,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    /*if (k < 0)
    {
     for (int m = k; l < 531; m++)
    {
    patoverde=ventana.creaImagenConMascara("Patoverde.bmp","Patoverdemask.bmp");
    ventana.muestraImagenEscalada(m,l,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde1.bmp","Patoverdemask1.bmp");
    ventana.muestraImagenEscalada(m++,l++,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde2.bmp","Patoverdemask2.bmp");
    ventana.muestraImagenEscalada(m++,l++,75,75,patoverde);
    ventana.eliminaImagen(patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde1.bmp","Patoverdemask1.bmp");
    ventana.muestraImagenEscalada(m++,l++,75,75,patoverde);
    ventana.eliminaImagen(patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde.bmp","Patoverdemask.bmp");
    ventana.muestraImagenEscalada(m++,l++,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();   
    }
    l=731;
    ventana.eliminaImagen(patoverde);
    //if (l == 531)
    //{
    //ventana.limpiaVentana();
    //patoverde=ventana.creaImagenConMascara("Patoverde4.bmp","Patoverde4mask");
    //ventana.muestraImagenEscalada(100,l,75,75,patoverde);
    //ventana.actualizaVentana();
    //ventana.espera(100);
    //ventana.eliminaImagen(patoverde);
    //ventana.actualizaVentana();
    //ventana.limpiaVentana();
    //}
    }*/
    }
    }
    }
    }   
    }
    }
    }
    movy=531;
}
    ventana.cierraVentana();
    return 0;
}
