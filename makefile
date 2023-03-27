CC = gcc

CFLAGS = -g3

SDLROUTE = -ISDL2/include -LSDL2/lib

WINDOWS = -lmingw32

LIBS = -lm -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 

SRCS = src/entite.c src/mapStruct.c src/menu.c src/objet.c src/chemin.c src/mapBoss.c src/arbre.c src/inv_SDL.c src/menu_cpt.c src/map_jeu_entite.c src/inventaire.c

HEADERS = head/entite.h head/mapStruct.h head/menu.h head/objet.h head/chemin.h head/mapBoss.h head/arbre.h head/inv_SDL.h head/menu_cpt.h head/map_jeu_entite.h head/inventaire.h

OBJS = $(SRCS:src/%.c=obj/%.o)

OUT = bin/main.exe

obj/%.o: src/%.c
	$(CC) $(CFLAGS) $(SDLROUTE) -c $< -o $@

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) $(SDLROUTE) $(OBJS) $(LIBS) $(WINDOWS) -o $(OUT)

all: $(OUT)

clean:
	del obj\*.o
	del bin\*.exe

run: $(OUT)
	.\$(OUT)

gdb : $(OUT)
	gdb $(OUT)


valgrind: $(OUT)
	valgrind $(OUT)


valgrind_leakcheck: $(OUT)
	valgrind --leak-check=full $(OUT)

valgrind_extreme: $(OUT)
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes $(OUT)
