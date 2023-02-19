all : prog

prog : entite.o inventaire.o objet.o
	gcc -g entite.o inventaire.o objet.o  -o prog

entite.o : entite.c entite.h
	gcc -Wall -g -c entite.c entite.h  

inventaire.o : inventaire.c
	gcc -Wall -g -c inventaire.c 

objet.o : objet.c objet.h
	gcc -Wall -g -c objet.c objet.h 

clean : 
	rm *.o