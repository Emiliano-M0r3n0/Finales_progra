/*
 * main.c - Clon de Duck Hunt usando graficos.h
 * Requiere enlazar con winmm (ej: gcc main.c graficos.c -o duckhunt -lwinmm -lgdi32)
 */

#include "graficos.h"
#include "simplecontroller.h"
#include "serial.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Incluimos mmsystem.h para PlaySound. windows.h ya lo incluye graficos.h pero lo necesitamos para los flags SND_
#include <mmsystem.h>

// --- Constantes (Defines en lugar de Enums) ---
#define ANCHO_VENTANA 800 
#define ALTO_VENTANA 600
#define SUELO_Y 450

// Estados del juego
#define ESTADO_MENU 0
#define ESTADO_INTRO_RONDA 1
#define ESTADO_JUGANDO 2
#define ESTADO_PATO_CAYENDO 3
#define ESTADO_PERRO_REACCION 4
#define ESTADO_GAMEOVER 5

// Configuración
#define PATOS_POR_RONDA 10
#define BALAS_MAX 3

// --- Macros para Sonido (API de Windows estándar) ---
// Reproduce en bucle (fondo) asíncronamente
#define PLAY_LOOP(archivo) PlaySound(archivo, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP)
// Reproduce una vez asíncronamente (efectos)
#define PLAY_SFX(archivo) PlaySound(archivo, NULL, SND_FILENAME | SND_ASYNC)
// Detiene cualquier sonido
#define STOP_SOUND() PlaySound(NULL, 0, 0)

#define BTN 4
#define JX 15
#define JY 2
#define MTR 13

#define AJUSTE_X 0.047
#define AJUSTE_Y 0.049

// --- Variables Globales de Recursos ---
Imagen *imgPortada;
// Animación del pato volando horizontal (usando nombres de las imagenes)
Imagen *imgPatoVuelo[3]; // Patoverde1, Patoverde2, Patoverde3
Imagen *imgPatoSube[3];  // Reutilizamos o necesitamos sprites diagonales (simplificado: usaremos los mismos)
Imagen *imgPatoTiro;     // Patobalaceado
Imagen *imgPatoCae[2];   // Patocaido, Patoverde4 (usado como frame de caída)

Imagen *imgPerroBusca[2]; // Perro, Perro1
Imagen *imgPerroAtrapa;   // Atrapado
Imagen *imgPerroRie;      // No vi imagen de risa, usaremos Perro1 como placeholder o Atrapado sin pato si existiera.

// --- Variables del Juego ---
int estadoActual = ESTADO_MENU;
int score = 0;
int highScore = 0;
int ronda = 1;
int patosGolpeadosRonda = 0;
int patosLanzadosRonda = 0;
int balasRestantes = BALAS_MAX;

// Variables del Pato actual
float patoX, patoY;
float patoVX, patoVY;
int patoAnimFrame = 0;
int patoAnimTimer = 0;
bool patoMirandoDerecha = true;

// Variables auxiliares
int timerGeneral = 0;
bool puedeDisparar = true;
char bufferTexto[100]; // Para sprintf

// --- Declaración de Funciones ---
void cargarRecursos();
void liberarRecursos();
void cargarHighScore();
void guardarHighScore();
void iniciarRonda();
void lanzarPato();
void actualizarJuego();
void dibujarJuego();
void manejarInputJuego();

// ==========================================
// Función Principal
// ==========================================
int main() {
    srand(time(NULL)); // Semilla para aleatoriedad

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

    ventana.tamanioVentana(ANCHO_VENTANA, ALTO_VENTANA);
    ventana.tituloVentana("Duck Hunt C");
    ventana.colorFondoRGB(52, 152, 219); // Color cielo azul

    cargarRecursos();
    cargarHighScore();

    PLAY_LOOP("Voicy_Duck_Hunt_Intro.wav");

    int fpsTimer = 0;

    // Bucle principal del juego
    while (1) {
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

        // Control básico de tiempo para animaciones (aprox 30 FPS)
        ventana.espera(33);
        fpsTimer++;
        patoAnimTimer++;
        timerGeneral++;

        ventana.limpiaVentana();

        // Máquina de estados principal
        switch (estadoActual) {
            case ESTADO_MENU:
                ventana.muestraImagenEscalada(0, 0, ANCHO_VENTANA, ALTO_VENTANA, imgPortada);
                ventana.colorRGB(255, 255, 255);
                ventana.texto1(ANCHO_VENTANA / 2 - 100, ALTO_VENTANA - 150, "PRESIONA ENTER PARA JUGAR", 24, "Arial");
                sprintf(bufferTexto, "HIGH SCORE: %d", highScore);
                ventana.texto(ANCHO_VENTANA / 2 - 50, ALTO_VENTANA - 100, bufferTexto);

                if (ventana.teclaPresionada() == TECLAS.ENTER) {
                    score = 0;
                    ronda = 1;
                    iniciarRonda();
                }
                break;

            case ESTADO_INTRO_RONDA:
                dibujarJuego();
                ventana.colorRGB(255, 255, 255);
                sprintf(bufferTexto, "RONDA %d", ronda);
                ventana.texto1(ANCHO_VENTANA / 2 - 50, ALTO_VENTANA / 2, bufferTexto, 36, "Arial");
                
                if (timerGeneral > 60) { // Espera 2 segundos aprox
                    lanzarPato();
                }
                break;

            case ESTADO_JUGANDO:
                manejarInputJuego();
                actualizarJuego();
                dibujarJuego();
                break;

            case ESTADO_PATO_CAYENDO:
                // Lógica simple de caída
                patoY += 8;
                // Animación de caída rápida
                 if (patoAnimTimer % 5 == 0) patoAnimFrame = !patoAnimFrame;

                dibujarJuego();

                if (patoY > SUELO_Y) {
                    PLAY_SFX("Voicy_Duck_Drop.wav");
                    timerGeneral = 0;
                    // Decidir si sale el perro a reír o a mostrar el pato
                    estadoActual = ESTADO_PERRO_REACCION;
                }
                break;
            
            case ESTADO_PERRO_REACCION:
                dibujarJuego();
                 // Mostrar perro con pato si se cazó
                if(patosGolpeadosRonda > 0 && patoY > SUELO_Y) { // Condición simple para mostrar perro feliz
                     ventana.muestraImagen(patoX, SUELO_Y - ventana.altoImagen(imgPerroAtrapa) + 20, imgPerroAtrapa);
                } else {
                    // Aquí iría la animación del perro riendo si fallaste el pato
                     ventana.muestraImagen(ANCHO_VENTANA/2, SUELO_Y - ventana.altoImagen(imgPerroBusca[0]), imgPerroBusca[0]); // Placeholder
                }


                if(timerGeneral > 60) { // Esperar a que el perro termine
                    if (patosLanzadosRonda < PATOS_POR_RONDA) {
                        lanzarPato();
                    } else {
                        // Fin de la ronda
                        if (patosGolpeadosRonda >= 6) { // Mínimo para pasar
                            ronda++;
                            PLAY_SFX("Voicy_Next_Round.wav");
                            iniciarRonda();
                        } else {
                             PLAY_SFX("Voicy_Lose_Sound_1.wav");
                            estadoActual = ESTADO_GAMEOVER;
                        }
                    }
                }
                break;

            case ESTADO_GAMEOVER:
                dibujarJuego();
                ventana.colorRGB(255, 0, 0);
                ventana.texto1(ANCHO_VENTANA / 2 - 100, ALTO_VENTANA / 2, "GAME OVER", 48, "Arial");
                ventana.colorRGB(255, 255, 255);
                ventana.texto(ANCHO_VENTANA / 2 - 80, ALTO_VENTANA / 2 + 60, "Presiona ESPACIO para Menu");

                if (score > highScore) {
                    highScore = score;
                    guardarHighScore();
                    PLAY_SFX("Voicy_High_Score.wav");
                }

                if (ventana.teclaPresionada() == TECLAS.ESPACIO) {
                    estadoActual = ESTADO_MENU;
                    PLAY_LOOP("Voicy_Duck_Hunt_Intro.wav");
                }
                break;
        }

        // Dibujar la mira del ratón
        int mX, mY;
        if(ventana.raton(&mX, &mY)) {
             ventana.colorRGB(255, 0, 0);
             ventana.circulo(mX, mY, 10);
             ventana.linea(mX-15, mY, mX+15, mY);
             ventana.linea(mX, mY-15, mX, mY+15);
        }

        ventana.actualizaVentana();

        // Salir con ESC
        if (ventana.teclaPresionada() == TECLAS.ESCAPE) {
            break;
        }
    }

    STOP_SOUND();
    liberarRecursos();
    return 0;
}

// ==========================================
// Funciones de Lógica del Juego
// ==========================================

void iniciarRonda() {
    patosLanzadosRonda = 0;
    patosGolpeadosRonda = 0;
    timerGeneral = 0;
    estadoActual = ESTADO_INTRO_RONDA;
    STOP_SOUND(); // Parar música del menú
}

void lanzarPato() {
    patosLanzadosRonda++;
    balasRestantes = BALAS_MAX;
    
    // Posición inicial aleatoria en el suelo
    patoX = rand() % (ANCHO_VENTANA - 100) + 50;
    patoY = SUELO_Y;

    // Velocidad aleatoria basada en la ronda
    float velocidadBase = 4.0f + ronda;
    patoVX = (rand() % 2 == 0 ? 1 : -1) * velocidadBase; // Izquierda o derecha
    patoVY = -velocidadBase; // Siempre hacia arriba al inicio

    patoMirandoDerecha = (patoVX > 0);
    estadoActual = ESTADO_JUGANDO;
    
    PLAY_SFX("Voicy_Duck_Hunt_Intro_No_Bark.wav"); // Sonido corto de inicio
}

void manejarInputJuego() {
    int mX, mY;
    ventana.raton(&mX, &mY);

    if (ventana.ratonBotonIzquierdo()) {
        if (puedeDisparar && balasRestantes > 0) {
            PLAY_SFX("Voicy_Gun_Shot.wav");
            balasRestantes--;
            puedeDisparar = false; // Evitar ametralladora

            // Chequear colisión simple (caja rectangular)
            int anchoPato = ventana.anchoImagen(imgPatoVuelo[0]);
            int altoPato = ventana.altoImagen(imgPatoVuelo[0]);

            // Ajuste básico porque el sprite puede tener espacios transparentes
            if (mX > patoX + 10 && mX < patoX + anchoPato - 10 &&
                mY > patoY + 10 && mY < patoY + altoPato - 10) {
                
                // PATO DADO
                score += 100 * ronda;
                patosGolpeadosRonda++;
                estadoActual = ESTADO_PATO_CAYENDO;
                PLAY_SFX("Voicy_Duck_Falling.wav");
            }
        }
    } else {
        puedeDisparar = true; // Resetear el gatillo cuando se suelta el botón
    }
}

void actualizarJuego() {
    patoX += patoVX;
    patoY += patoVY;

    // Rebotar en las paredes
    if (patoX <= 0 || patoX >= ANCHO_VENTANA - ventana.anchoImagen(imgPatoVuelo[0])) {
        patoVX = -patoVX;
        patoMirandoDerecha = (patoVX > 0);
    }
    if (patoY <= 0) {
        patoVY = -patoVY;
    }

    // Si el pato se escapa por arriba o por los lados muy alto
    if (patoY > ALTO_VENTANA + 50 || (patoY < -50 && timerGeneral > 200)) {
         // Pato escapado
         timerGeneral = 0;
         estadoActual = ESTADO_PERRO_REACCION;
         PLAY_SFX("Voicy_Dog_Laughing.wav");
    }

    // Animación de vuelo
    if (patoAnimTimer % 4 == 0) { // Cambiar frame cada 4 ciclos
        patoAnimFrame = (patoAnimFrame + 1) % 3;
    }
}

void dibujarJuego() {
    // 1. Dibujar Suelo/Pasto
    ventana.colorRGB(34, 139, 34); // Verde pasto
    ventana.rectanguloRelleno(0, SUELO_Y, ANCHO_VENTANA, ALTO_VENTANA);
    ventana.colorRGB(139, 69, 19); // Marrón tierra
    ventana.rectanguloRelleno(0, SUELO_Y + 40, ANCHO_VENTANA, ALTO_VENTANA);

    // 2. Dibujar Pato según estado
    if (estadoActual == ESTADO_JUGANDO) {
        // Nota: MiniWin no tiene función nativa para invertir imagen (flip horizontal).
        // Se usaría el sprite correspondiente a la dirección si estuviera disponible.
        // Usaremos el mismo sprite para simplificar, idealmente tendrías "Patoverde_izq.bmp".
        ventana.muestraImagen((int)patoX, (int)patoY, imgPatoVuelo[patoAnimFrame]);
    } else if (estadoActual == ESTADO_PATO_CAYENDO) {
        if(patoVY < 0) { // Momento inicial del impacto
             ventana.muestraImagen((int)patoX, (int)patoY, imgPatoTiro);
             patoVY = 1; // Empezar a caer
        } else {
             ventana.muestraImagen((int)patoX, (int)patoY, imgPatoCae[patoAnimFrame % 2]);
        }
    }

    // 3. Dibujar UI (Interfaz)
    ventana.colorRGB(255, 255, 255);
    ventana.rectanguloRelleno(50, ALTO_VENTANA - 80, 200, ALTO_VENTANA - 30); // Fondo UI score
    ventana.colorRGB(0, 0, 0);
    sprintf(bufferTexto, "SCORE: %06d", score);
    ventana.texto(60, ALTO_VENTANA - 70, bufferTexto);
    sprintf(bufferTexto, "R: %d  BALAS: %d", ronda, balasRestantes);
    ventana.texto(60, ALTO_VENTANA - 50, bufferTexto);
}

// ==========================================
// Funciones de Carga/Guardado y Recursos
// ==========================================

void cargarHighScore() {
    FILE *fp = fopen("highscore.dat", "rb");
    if (fp) {
        // Usamos fseek solo para demostrar su uso, aunque aquí un simple fread bastaría
        fseek(fp, 0, SEEK_SET);
        fread(&highScore, sizeof(int), 1, fp);
        fclose(fp);
    } else {
        highScore = 0;
    }
}

void guardarHighScore() {
    FILE *fp = fopen("highscore.dat", "wb");
    if (fp) {
        fwrite(&highScore, sizeof(int), 1, fp);
        fclose(fp);
    }
}

// Helper macro para cargar imágenes con máscara de forma segura
#define CARGAR_IMG_MASK(ptr, nombre, mask) \
    ptr = ventana.creaImagenConMascara(nombre, mask); \
    if (ptr == NULL) { printf("Error cargando %s o %s\n", nombre, mask); exit(1); }

void cargarRecursos() {
    // Portada (sin máscara necesaria, pero la función lo requiere, usamos la misma)
    imgPortada = ventana.creaImagen("Portada.bmp");
    
    // Patos volando
    CARGAR_IMG_MASK(imgPatoVuelo[0], "Patoverde1.bmp", "Patoverdemask.bmp");
    CARGAR_IMG_MASK(imgPatoVuelo[1], "Patoverde2.bmp", "Patoverdemask1.bmp"); // Asumo nombre de mascara basado en la imagen
    CARGAR_IMG_MASK(imgPatoVuelo[2], "Patoverde3.bmp", "Patoverde3mask.bmp");

    // Pato disparado y cayendo
    CARGAR_IMG_MASK(imgPatoTiro, "Patobalaceado.bmp", "Patobalaceadomask.bmp");
    CARGAR_IMG_MASK(imgPatoCae[0], "Patocaido.bmp", "Patocaidomask.bmp");
    CARGAR_IMG_MASK(imgPatoCae[1], "Patoverde4.bmp", "Patoverde4mask.bmp"); // Usando este como segundo frame de caída

    // Perro
    CARGAR_IMG_MASK(imgPerroBusca[0], "Perro.bmp", "Perromask.bmp");
    CARGAR_IMG_MASK(imgPerroBusca[1], "Perro1.bmp", "Perro1mask.bmp");
    CARGAR_IMG_MASK(imgPerroAtrapa, "Atrapado.bmp", "Atrapadomask.bmp");
    
    // Nota: Faltan máscaras exactas para algunas imágenes en los pantallazos.
    // He asumido nombres lógicos (ej. Patoverde2 -> Patoverdemask1.bmp según tu imagen).
    // Si falla la carga, verifica los nombres exactos de tus archivos BMP.
}

void liberarRecursos() {
    ventana.eliminaImagen(imgPortada);
    for(int i=0; i<3; i++) ventana.eliminaImagen(imgPatoVuelo[i]);
    ventana.eliminaImagen(imgPatoTiro);
    ventana.eliminaImagen(imgPatoCae[0]);
    ventana.eliminaImagen(imgPatoCae[1]);
    ventana.eliminaImagen(imgPerroBusca[0]);
    ventana.eliminaImagen(imgPerroBusca[1]);
    ventana.eliminaImagen(imgPerroAtrapa);
}