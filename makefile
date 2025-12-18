CC = gcc
CFLAGS = -Wall -O2 -std=c99
LIBS = -lgdi32 -lwinmm -luser32 -lcomdlg32
TARGET = DuckHunt.exe
SRCS = main.c graficos.c simplecontroller.c serial.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q $(OBJS) $(TARGET)