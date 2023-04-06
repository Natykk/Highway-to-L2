
# CC = gcc

# CFLAGS = -g3

# SDLROUTE = -I$(HOME)/SDL2/include -L$(HOME)/SDL2/lib

# WINDOWS = -lmingw32

# LIBS = -lm -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 

# SRCS =  src/competence.c src/entite.c src/mapStruct.c src/objet.c src/chemin.c src/mapBoss.c src/arbre.c src/inv_SDL.c src/menu_cpt.c src/inventaire.c

# HEADERS = head/competence.h head/entite.h head/mapStruct.h head/objet.h head/chemin.h head/mapBoss.h  head/arbre.h head/inv_SDL.h head/menu_cpt.h head/map_jeu_entite.h head/inventaire.h

# OBJS = $(SRCS:src/%.c=obj/%.o)

# OUT = bin/main

# obj/%.o: src/%.c $(HEADERS)
# 	$(CC) $(CFLAGS) $(SDLROUTE) -c $< -o $@

# $(OUT): $(OBJS)
# 	$(CC) $(CFLAGS) $(SDLROUTE) $(OBJS) $(LIBS) -o $(OUT)

# all: $(OUT)

# clean:
# 	rm -rf obj\*.o
# 	rm -rf bin\*.exe

# run: $(OUT)
# 	.\$(OUT)

# gdb : $(OUT)
# 	gdb $(OUT)

# valgrind: $(OUT)
# 	valgrind $(OUT)


# valgrind_leakcheck: $(OUT)
# 	valgrind --leak-check=full $(OUT)

# valgrind_extreme: $(OUT)
# 	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes $(OUT)



# project name (generate executable with this name)
TARGETS  = menu_cpt

SDLROUTE = -I$(HOME)/SDL2/include -L$(HOME)/SDL2/lib
LIBS = -lm -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -g3

CC       = gcc -g3
# compiling flags here
CFLAGS   = -I.

LINKER   = gcc -g3
# linking flags here
LFLAGS   = -I. -lm

# change these to proper directories where each file should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
TRGS	 := $(TARGETS:%=$(BINDIR)/%)

DIRS	 = $(OBJDIR) $(BINDIR) 

.PHONY: DIRS
all: $(DIRS) $(TRGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
MAINS	 := $(TARGETS:%=$(OBJDIR)/%.o)
# Liste des fichiers .o sans ceux contenant un main
OBJS	 := $(filter-out $(MAINS),$(OBJECTS))
rm       = rm -f


#$(BINDIR)/$(TARGET): $(OBJECTS)
$(TRGS): $(OBJECTS)
	@echo "Linking...$(OBJECTS)"
	@$(LINKER) $(SDLROUTE) $(subst $(BINDIR),$(OBJDIR),$@).o $(OBJS) $(LFLAGS) $(LIBS) -o $@ 
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(SDLROUTE) $(CFLAGS) $(LFLAGS) $(LIBS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

remove: clean
	@$(rm) $(BINDIR)/$(TARGETS)
	@echo "Executable removed!"



