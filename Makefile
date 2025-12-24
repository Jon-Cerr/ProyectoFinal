MAIN = main.c
CC = gcc
APP = main.exe
WIN_FLAGS = -mwindows
GRAPHICS_SRC = .\src\graficos\graficos.c
GRAPHICS_OBJ = graficos.o
PERSONAJE_SRC = .\src\juego\personaje.c
PERSONAJE_OBJ = personaje.o
GRAPHICS_OBJ = graficos.o
JUEGO_SRC = .\src\juego\juego.c
JUEGO_OBJ = juego.o
SIMPLECONTROLLER_SRC = .\src\esp32\simplecontroller.c
SIMPLECONTROLLER_OBJ = simplecontroller.o
SERIAL_SRC = .\src\esp32\serial.c
SERIAL_OBJ = serial.o
WINMM_LIB=-lwinmm

run: $(APP)
	./$(APP)

$(APP): $(MAIN) $(GRAPHICS_OBJ) $(PERSONAJE_OBJ) $(JUEGO_OBJ) $(SIMPLECONTROLLER_OBJ) $(SERIAL_OBJ)
	$(CC) -o $(APP) $(MAIN) $(WIN_FLAGS) $(GRAPHICS_OBJ) $(WINMM_LIB) $(PERSONAJE_OBJ) $(JUEGO_OBJ) $(SIMPLECONTROLLER_OBJ) $(SERIAL_OBJ)
	
$(GRAPHICS_OBJ): $(GRAPHICS_SRC)
	$(CC) -c $(GRAPHICS_SRC) -o $(GRAPHICS_OBJ)

$(PERSONAJE_OBJ): $(PERSONAJE_SRC)
	$(CC) -c $(PERSONAJE_SRC) -o $(PERSONAJE_OBJ)

$(JUEGO_OBJ): $(JUEGO_SRC)
	$(CC) -c $(JUEGO_SRC) -o $(JUEGO_OBJ)

$(SIMPLECONTROLLER_OBJ): $(SIMPLECONTROLLER_SRC)
	$(CC) -c $(SIMPLECONTROLLER_SRC) -o $(SIMPLECONTROLLER_OBJ)

$(SERIAL_OBJ): $(SERIAL_SRC)
	$(CC) -c $(SERIAL_SRC) -o $(SERIAL_OBJ)

clean:
	rm -f *.o exe