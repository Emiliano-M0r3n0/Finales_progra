#include<stdio.h>
#include"graficos.h"
#define GRAVEDAD 10
int main()
{
    Imagen *patoverde=ventana.creaImagenConMascara("Patobalaceado.bmp","Patobalaceadomask.bmp");
    Imagen *Perro=ventana.creaImagenConMascara("Atrapado.bmp","Atrapadomask.bmp");
    while (1)
    {
        ventana.tituloVentana("POW");
        ventana.tamanioVentana(700,700);
        ventana.limpiaVentana();
        ventana.colorFondo(COLORES.CYAN);
        ventana.actualizaVentana();
        ventana.espera(1);
        ventana.limpiaVentana();
        ventana.creaImagenConMascara("Patobalaceado.bmp","Patobalaceadomask.bmp");
        ventana.muestraImagenEscalada(100,0,75,75,patoverde);
        ventana.actualizaVentana();
        ventana.espera(1000);
        ventana.limpiaVentana();
        for (int i = 0; i < 600; i++)
    {
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patocaido.bmp","Patocaidomask.bmp");
    ventana.muestraImagenEscalada(100,(GRAVEDAD)*i,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(200);
    ventana.limpiaVentana();
    patoverde=ventana.creaImagenConMascara("Patocaido0.bmp","Patocaidomask0.bmp");
    ventana.muestraImagenEscalada(100,(GRAVEDAD)*i,75,75,patoverde);
    ventana.actualizaVentana();
    ventana.espera(200);
    ventana.limpiaVentana();
    i++;
    if (i > 100)
    {
        for (int j = 670; j > 600; j--)
        {
        ventana.limpiaVentana();
        ventana.muestraImagenEscalada(100,j,125,105,Perro);
        ventana.actualizaVentana();
        ventana.espera(1);
        ventana.limpiaVentana();

        }
        for (int z = 600; z < 700; z++)
        {
        ventana.limpiaVentana();
        ventana.muestraImagenEscalada(100,z,125,105,Perro);
        ventana.actualizaVentana();
        ventana.espera(1);
        ventana.limpiaVentana();
        i=900;
        }
        
    }
    }
    patoverde=ventana.creaImagenConMascara("Patobalaceado.bmp","Patobalaceadomask.bmp");
    }
    
    return 0;
}
