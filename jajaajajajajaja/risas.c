#include <stdio.h>
#include "graficos.h"
int main()
{
    Imagen *perro;
    while (1)
    {
    ventana.tituloVentana("perro riendo");
    ventana.tamanioVentana(800,700);
    ventana.limpiaVentana();
    ventana.colorFondo(COLORES.CYAN);
    ventana.actualizaVentana();
    ventana.espera(1);
    for (int i = 700; i > 600; i--)
    {
        // i=600
    perro=ventana.creaImagenConMascara("Perro.bmp","Perromask.bmp");
    ventana.muestraImagenEscalada(340,i--,100,100,perro);
    ventana.actualizaVentana();
    ventana.espera(40);
    ventana.limpiaVentana();
    perro=ventana.creaImagenConMascara("Perro1.bmp","Perro1mask.bmp");
    ventana.muestraImagenEscalada(340,i--,100,100,perro);
    ventana.actualizaVentana();
    ventana.espera(40);
    ventana.limpiaVentana();
    if (i < 600)
    {
        for (int p = 0; p < 10; p++)
    {
        perro=ventana.creaImagenConMascara("Perro.bmp","Perromask.bmp");
    ventana.muestraImagenEscalada(340,i,100,100,perro);
    ventana.actualizaVentana();
    ventana.espera(40);
    ventana.limpiaVentana();
    perro=ventana.creaImagenConMascara("Perro1.bmp","Perro1mask.bmp");
    ventana.muestraImagenEscalada(340,(i-1),100,100,perro);
    ventana.actualizaVentana();
    ventana.espera(40);
    ventana.limpiaVentana();
    }
        for (int j = 600; j < 700; j++)
    {
        // i=600
    ventana.limpiaVentana();
    perro=ventana.creaImagenConMascara("Perro.bmp","Perromask.bmp");
    ventana.muestraImagenEscalada(340,j++,100,100,perro);
    ventana.actualizaVentana();
    ventana.espera(40);
    ventana.limpiaVentana();
    perro=ventana.creaImagenConMascara("Perro1.bmp","Perro1mask.bmp");
    ventana.muestraImagenEscalada(340,j++,100,100,perro);
    ventana.actualizaVentana();
    ventana.espera(40);
    ventana.limpiaVentana();
    }
    }
    }
    }
    return 0;
}
