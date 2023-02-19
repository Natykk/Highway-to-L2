# Variables pour les dossiers
SRCDIR = src
OBJDIR = obj
BINDIR = bin
DOCDIR = doc
HEADDIR = head

# Variables Utiles pour la compilation
COMPIL = gcc
OBJ = $(OBJDIR)/entite.o $(OBJDIR)/inventaire.o $(OBJDIR)/objet.o 
CFLAGS = -Wall -g
EXEC = prog

#Création des dossiers
$(SRCDIR):
	mkdir -p $(SRCDIR)
$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)
$(DOCDIR):
	mkdir -p $(DOCDIR)
$(HEADDIR):
	mkdir -p $(HEADDIR)

# Compilation
$(OBJDIR)/objet.o: $(SRCDIR)/objet.c $(HEADDIR)/objet.h
	$(COMPIL) $(CFLAGS) -c  $< -o $@

$(OBJDIR)/entite.o: $(SRCDIR)/entite.c $(HEADDIR)/entite.h
	$(COMPIL) $(CFLAGS) -c  $< -o $@

$(OBJDIR)/inventaire.o: $(SRCDIR)/inventaire.c
	$(COMPIL) $(CFLAGS) -c  $< -o $@

$(BINDIR)/$(EXEC): $(OBJ)
	$(COMPIL) $(CFLAGS) $^ -o $@


# Execution du Makefile
all: $(SRCDIR) $(BINDIR) $(DOCDIR) $(HEADDIR) $(BINDIR)/$(EXEC)

# Commandes Utilitaires
clean:
	-rm -rf $(OBJDIR)/*

mrproper:
	-rm -rf $(BINDIR)/*
	-rm -rf $(DOCDIR)/*
	-rm -rf $(OBJDIR)/*