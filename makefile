# Nombre del archivo ejecutable
TARGET = duckhunt.exe

# Archivos de fuente
SRCS = main.c graficos.c

# Objetos (se generan automáticamente a partir de SRCS)
OBJS = $(SRCS:.c=.o)

# Compilador
CC = gcc

# Banderas del compilador
# -mwindows evita que se abra una consola extra al iniciar el juego
CFLAGS = -Wall -std=c99

# Librerías de Windows necesarias:
# gdi32: Para funciones de dibujo y bitmaps
# winmm: Para la reproducción de sonidos (PlaySound)
LIBS = -lgdi32 -lwinmm

# Regla principal
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

# Regla para compilar archivos .c a .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos temporales
clean:
	del /f $(OBJS) $(TARGET)