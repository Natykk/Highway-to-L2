
OBJS	=  obj/map_jeu_entite.o obj/entite.o  obj/mapStruct.o obj/menu.o obj/inventaire.o obj/objet.o obj/chemin.o obj/mapBoss.o
SOURCE	= src/map_jeu_entite.c src/entite.c src/inventaire.c src/mapStruct.c src/menu.c src/objet.c src/chemin.c src/mapBoss.c
HEADER	= head/entite.h head/mapStruct.h head/objet.h head/objet_inv.h head/mapBoss.h
OUT	= bin/main
CC	 = gcc
FLAGS	 = -g3 -c -Wall -lm
SDLFLAGS= -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2main 
WINDOWS = -lmingw32
SDLROUTE = -L$(HOME)/SDL2/lib -I $(HOME)/SDL2/include


all: $(OBJS)
	gcc $(SDLROUTE) $(OBJS) $(SDLFLAGS) -lm -g -o $(OUT)


obj/entite.o: src/entite.c
	$(CC) $(FLAGS) $< -o $@

obj/inventaire.o: src/inventaire.c
	$(CC) $(FLAGS) $< -o $@

obj/mapBoss.o: src/mapBoss.c
	$(CC) $(FLAGS) $< -o $@

obj/mapStruct.o: src/mapStruct.c
	$(CC) $(FLAGS) $< -o $@

obj/objet.o: src/objet.c
	$(CC) $(FLAGS) $< -o $@

obj/chemin.o: src/chemin.c
	$(CC) $(FLAGS) $< -o $@

obj/map_jeu_entite.o: src/map_jeu_entite.c 
	$(CC) $(FLAGS) $(SDLROUTE) $(SDLFLAGS)  $< -o $@

obj/menu.o: src/menu.c
	$(CC) $(FLAGS) $(SDLROUTE) $(SDLFLAGS) $< -o $@



bin/main : obj/mapStruct.o obj/entite.o obj/map_jeu_entite.o
	gcc $(SDLROUTE) $(OBJS) $(SDLFLAGS) -g -o $(OUT) -lm


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
