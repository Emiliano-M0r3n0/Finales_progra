/**
 * @file main.c
 * @author Jose Luis Cruz (jlcruz@ipn.mx)
 * @brief Mi primer programa
 * @version 0.1
 * @date 2025-12-01
 *
 * @copyright Copyright (c) 2025
 *
 */
/**#include "graficos.h"
 * 
#include "simplecontroller.h"

int main()
{
    Imagen *cafe1 = ventana.creaImagenConMascara("cafe1_0.bmp", "cafe1_1.bmp");

    bool fullscreen = false;
    bool dir_der = false;
    bool dir_izq = false;
    bool dir_up = false;
    bool dir_down = false;

    int coordx = 400;
    int coordy = 300;

    ventana.tituloVentana("Prueba_1");
    ventana.tamanioVentana(800,600);

    int tecla = ventana.teclaPresionada();

    while (tecla != TECLAS.ESCAPE)
    {
      tecla = ventana.teclaPresionada();
      
      if(tecla == TECLAS.ARRIBA) dir_up = true;
      if(tecla == TECLAS.ABAJO) dir_down = true;
      if(tecla == TECLAS.DERECHA) dir_der = true;
      if(tecla == TECLAS.IZQUIERDA) dir_izq = true;
      
      if(dir_up) coordy -= 10;
      if(dir_down) coordy += 10;
      if(dir_der) coordx += 10;
      if(dir_izq) coordx -= 10;
      
      if (tecla == TECLAS.ENTER)
      {
        fullscreen = !fullscreen;
        ventana.pantallaCompleta(fullscreen);
      }

      ventana.limpiaVentana();

      ventana.colorFondoRGB(135,206,235);

      ventana.muestraImagen(coordx,coordy,cafe1);
      
      ventana.actualizaVentana();

      int tmp = ventana.teclaSoltada();

      if (tmp == TECLAS.DERECHA) dir_der = false;
      if (tmp == TECLAS.IZQUIERDA) dir_izq = false;
      if (tmp == TECLAS.ARRIBA) dir_up = false;
      if (tmp == TECLAS.ABAJO) dir_down = false;

      ventana.espera(1);  
    }

    ventana.cierraVentana();

    return 0;
}*/


/**
 * @file main.c
 * @author Jose Luis Cruz (jlcruz@ipn.mx)
 * @brief Mi primer programa
 * @version 0.1
 * @date 2025-12-01
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "graficos.h"
#include "simplecontroller.h"
#include <windows.h>
#include <mmsystem.h>
#define BTN 4
#define JX 15
#define JY 2
#define MTR 13

#define AJUSTE_X 0.047
#define AJUSTE_Y 0.049

int main()
{
    Imagen *trex = ventana.creaImagenConMascara("cafe1_0.bmp", "cafe1_1.bmp");
    Board *esp32 = connectDevice("COM6", B115200);
    esp32->pinMode(esp32, JX, INPUT);
    esp32->pinMode(esp32, JY, INPUT);
    esp32->pinMode(esp32, BTN, INPUT_PULLUP);
    esp32->pinMode(esp32, MTR, OUTPUT);

    int rx = 400, ry = 300;
    int movx, movy;
    bool btn = false;
    float jx, jy;
    bool vivo = true;

    ventana.tituloVentana("Hola Windows :D");

    ventana.tamanioVentana(800, 600);

    int tecla = ventana.teclaPresionada();
    bool fs = false;

    while (tecla != TECLAS.ESCAPE)
    {
        btn = esp32->digitalRead(esp32, BTN);
        jx = esp32->analogRead(esp32, JX);
        jy = esp32->analogRead(esp32, JY);

        //Calibracion del joystick
        jx -= AJUSTE_X;
        if (jx >= 0)
            movx = (int)(jx * (10.0 / (1.0 - AJUSTE_X)));
        else
            movx = (int)(jx * (11.0 / AJUSTE_X));

        jy -= AJUSTE_Y;
        if (jy >= 0)
            movy = (int)(jy * (10.0 / (1.0 - AJUSTE_Y)));
        else
            movy = (int)(jy * (11.0 / AJUSTE_Y));

        ventana.imprimeEnConsola("(%f, %f) - %i | %i, %i\n", jx, jy, btn, movx, movy);

        //Seguro para evitar que se mueva
        if (movx != 5 && movy != 5)
        {
            rx += movx;
            ry += movy; 
        }

        //Limites de la pantalla
        if (rx >= ventana.anchoVentana() - 100)
        {
            rx = ventana.anchoVentana() - 100;
        }
        if (rx <= 100)
        {
            rx = 100;
        }
        if (ry >= ventana.altoVentana() - 100)
        {
            ry = ventana.altoVentana() - 100;
        }
        if (ry <= 100)
        {
            ry = 100;
        }

        tecla = ventana.teclaPresionada();
        //ventana.raton(&rx, &ry);

        // ventana.imprimeEnConsola("X=%i - Y=%i\n", rx, ry);

        if (tecla == TECLAS.ENTER)
        {
            fs = !fs;
            ventana.pantallaCompleta(fs);
        }

        ventana.limpiaVentana(); // Borra


        if(!btn) {
            ventana.texto1(rx, ry, "Piyum!!", 50, "MV Boli");
            ventana.colorRGB(234,23,42);
            esp32->digitalWrite(esp32, MTR, true);
            PlaySound("shot-duckhunt.wav",NULL,SND_FILENAME | SND_ASYNC);
        } else {
            esp32->digitalWrite(esp32, MTR, false);
        }

        ventana.colorFondo(COLORES.VERDE); // Dibujamos
               
        // ventana.muestraImagenEscalada(coordx, coordy, 100, 100, trex);

        ventana.colorRGB(234,23,42);
        ventana.circulo(rx, ry, 20);
        ventana.linea(rx - 10, ry, rx - 30, ry);
        ventana.linea(rx + 10, ry, rx + 30, ry);
        ventana.linea(rx, ry - 10, rx, ry - 30);
        ventana.linea(rx, ry + 10, rx, ry + 30);

        ventana.actualizaVentana(); // Mostramos

        int tmp = ventana.teclaSoltada();

        ventana.espera(1);
    }

    ventana.cierraVentana();

    return 0;
}