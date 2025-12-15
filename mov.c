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
#include"graficos.h"
int main()
{
    int movx;
    int movy;
    Imagen *patoverde = ventana.creaImagenConMascara("nadamask.bmp","nada.bmp");
    int tecla= ventana.teclaPresionada();
    while (tecla != TECLAS.LETRA_N)
    {
    ventana.tituloVentana("Pruebas");
    ventana.tamanioVentana(800,600);
    ventana.limpiaVentana();
    ventana.colorFondo(COLORES.CYAN);
    ventana.actualizaVentana();
    ventana.espera(1);
    ventana.muestraImagenEscalada(100,100,75,75,patoverde);
    ventana.limpiaVentana();
    ventana.actualizaVentana();
    ventana.espera(100);
    ventana.limpiaVentana();
    for (int i = 0; i < 531; i++)
    {
    patoverde=ventana.creaImagenConMascara("Patoverde.bmp","Patoverdemask.bmp");
    ventana.muestraImagenEscalada(i,i,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde1.bmp","Patoverdemask1.bmp");
    ventana.muestraImagenEscalada(i++,i++,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde2.bmp","Patoverdemask2.bmp");
    ventana.muestraImagenEscalada(i++,i++,75,75,patoverde);
    ventana.eliminaImagen(patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde1.bmp","Patoverdemask1.bmp");
    ventana.muestraImagenEscalada(i++,i++,75,75,patoverde);
    ventana.eliminaImagen(patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde.bmp","Patoverdemask.bmp");
    ventana.muestraImagenEscalada(i++,i++,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    if (i == 530)
    {
        for (int j = i; j > 0; j--)
        {
    patoverde=ventana.creaImagenConMascara("Patoverde.bmp","Patoverdemask.bmp");
    ventana.muestraImagenEscalada(i,j,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde1.bmp","Patoverdemask1.bmp");
    ventana.muestraImagenEscalada(i++,j--,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde2.bmp","Patoverdemask2.bmp");
    ventana.muestraImagenEscalada(i++,j--,75,75,patoverde);
    ventana.eliminaImagen(patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde1.bmp","Patoverdemask1.bmp");
    ventana.muestraImagenEscalada(i++,j--,75,75,patoverde);
    ventana.eliminaImagen(patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde.bmp","Patoverdemask.bmp");
    ventana.muestraImagenEscalada(i++,j--,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    if (i >= 727)
    {
        for (int k = i; k > 0; k--)
        {
    patoverde=ventana.creaImagenConMascara("Patoverde.bmp","Patoverdemask.bmp");
    ventana.muestraImagenEscalada(k,j,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde1.bmp","Patoverdemask1.bmp");
    ventana.muestraImagenEscalada(k--,j--,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde2.bmp","Patoverdemask2.bmp");
    ventana.muestraImagenEscalada(k--,j--,75,75,patoverde);
    ventana.eliminaImagen(patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde1.bmp","Patoverdemask1.bmp");
    ventana.muestraImagenEscalada(k--,j--,75,75,patoverde);
    ventana.eliminaImagen(patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde.bmp","Patoverdemask.bmp");
    ventana.muestraImagenEscalada(k--,j--,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    if (j == 1)
    {
        for (int l = j; l < 730; l++)
        {
    patoverde=ventana.creaImagenConMascara("Patoverde.bmp","Patoverdemask.bmp");
    ventana.muestraImagenEscalada(k,l,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde1.bmp","Patoverdemask1.bmp");
    ventana.muestraImagenEscalada(k--,l++,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde2.bmp","Patoverdemask2.bmp");
    ventana.muestraImagenEscalada(k--,l++,75,75,patoverde);
    ventana.eliminaImagen(patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde1.bmp","Patoverdemask1.bmp");
    ventana.muestraImagenEscalada(k--,l++,75,75,patoverde);
    ventana.eliminaImagen(patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patoverde.bmp","Patoverdemask.bmp");
    ventana.muestraImagenEscalada(k--,l++,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(25);
    ventana.limpiaVentana();
    if (k < 0)
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
    }
    }
    }
    }
    }   
    }
    }
    }
}
    ventana.cierraVentana();
    return 0;
}
