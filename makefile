APP=mov.exe
MAIN=mov.c
GRAFICOS_C=graficos.c
GRAFICOS_H=graficos.h
GRAFICS_LIB=graficos.o
COMP=gcc
WINFLAGS=-mwindows
run: $(APP)
	 ./$(APP)
	 
$(APP): $(MAIN) $(GRAFICOS_H) $(GRAFICS_LIB)
	$(COMP) -o $(APP) $(GRAFICS_LIB) $(MAIN) $(WINFLAGS)

$(GRAFICS_L): $(GRAFICOS_H) $(GRAFICOS_C)
	$(COMP) -c $(GRAFICOS_C) -o $(GRAFICOS_LIB)
clean:
	del $(APP) $(GRAFICS_LIB)