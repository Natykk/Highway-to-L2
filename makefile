
OBJS	=  obj/map_jeu_entite.o obj/entite.o  obj/mapStruct.o 
SOURCE	= src/map_jeu_entite.c src/entite.c src/inventaire.c src/mapStruct.c src/menu.c src/objet.c
HEADER	= head/entite.h head/mapStruct.h head/objet.h head/objet_inv.h
OUT	= bin/main.exe
CC	 = gcc
FLAGS	 = -g3 -c -Wall
SDLFLAGS= -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2main
WINDOWS = -lmingw32
SDLROUTE = -L SDL2/lib -I SDL2/include


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)


obj/entite.o: src/entite.c
	$(CC) $(FLAGS) $< 
obj/inventaire.o: src/inventaire.c
	$(CC) $(FLAGS) $<

obj/mapStruct.o: src/mapStruct.c
	$(CC) $(FLAGS)  $< 

obj/objet.o: src/objet.c
	$(CC) $(FLAGS) $< 

obj/map_jeu_entite.o: src/map_jeu_entite.c 
	$(CC) -c $(SDLROUTE) $(SDLFLAGS)  $< 



bin/main.exe : obj/mapStruct.o obj/entite.o obj/map_jeu_entite.o
	gcc -L SDL2/lib -I SDL2/include mapStruct.o entite.o map_jeu_entite.o  -lSDL2main -lSDL2 $(WINDOWS) -lSDL2_image -g -o $(OUT)


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)


gdb : $(OUT)
	gdb $(OUT)


valgrind: $(OUT)
	valgrind $(OUT)


valgrind_leakcheck: $(OUT)
	valgrind --leak-check=full $(OUT)

valgrind_extreme: $(OUT)
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes $(OUT)
