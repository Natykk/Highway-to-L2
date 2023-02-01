map_jeu : 
	gcc map_jeu.c -ISDL2\include -LSDL2\lib -lmingw32  -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image -o main

menu : 
	gcc menu.c -ISDL2\include -LSDL2\lib -lmingw32  -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image -o main


all : mapStruct
mapStuct : mapStruct.o
	gcc -g -Wall mapStruct.o -o mapStruct

mapStruct.o : mapStruct.c mapStruct.h
	gcc -c mapStruct.c mapStruct.h