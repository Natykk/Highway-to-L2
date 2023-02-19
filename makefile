map_jeu : 
	gcc -o bin/main src/map_jeu.c -L${HOME}/SDL2/lib -lSDL2 -I${HOME}/SDL2/include -lSDL2_image -g

menu : 
	gcc menu.c -ISDL2\include -LSDL2\lib -lmingw32  -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image -o main

all : mapStruct
mapStuct : mapStruct.o
	gcc -g -Wall mapStruct.o -o mapStruct

mapStruct.o : mapStruct.c mapStruct.h
	gcc -c mapStruct.c mapStruct.h