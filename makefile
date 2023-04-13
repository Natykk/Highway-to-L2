# project name (generate executable with this name)
TARGETS  = map_jeu_entite

ifeq ($(OS),Windows_NT)
	CFLAGS   = -I.
	SDLROUTE = -I$(HOME)/SDL2/include -L$(HOME)/SDL2/lib
    LIBS = -lmingw32 -lm -lssl -lcrypto -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 
	del = del /Q
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CFLAGS   = -I.
		SDLROUTE = -I$(HOME)/SDL2/include -L$(HOME)/SDL2/lib
		LIBS = -lm -lssl -lcrypto -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 
		del = rm -f
	else
		SDLROUTE = -I$(HOME)/SDL2/include -L$(HOME)/SDL2/lib
		CFLAGS	= -I. -Wall -Wextra -I/usr/local/mac-dev-env/openssl-1.1.1a/include
		LFLAGS  = -I. -lm -L/usr/local/mac-dev-env/openssl-1.1.1a/lib -lssl -lcrypto
		LIBS 	= -lm -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 
		del 	= rm -f
	endif
endif


CC       = gcc -g3
# compiling flags here


LINKER   = gcc -g3
# linking flags here

# change these to proper directories where each file should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
TRGS	 := $(TARGETS:%=$(BINDIR)/%)

DIRS	 = $(OBJDIR) $(BINDIR) 

.PHONY: DIRS
all: $(DIRS) $(TRGS)

$(OBJDIR):
	mkdir $(OBJDIR)
$(BINDIR):
	mkdir $(BINDIR)

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
MAINS	 := $(TARGETS:%=$(OBJDIR)/%.o)
# Liste des fichiers .o sans ceux contenant un main
OBJS	 := $(filter-out $(MAINS),$(OBJECTS))


#$(BINDIR)/$(TARGET): $(OBJECTS)
$(TRGS): $(OBJECTS)
	@echo "Linking...$(OBJECTS)"
	@$(LINKER) $(SDLROUTE) $(subst $(BINDIR),$(OBJDIR),$@).o $(OBJS) $(LFLAGS) $(LIBS) -o $@ 
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(SDLROUTE) $(CFLAGS) $(LFLAGS) $(LIBS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

clean:
	@$(del) $(OBJECTS)
	@echo "Cleanup complete!"

remove: clean
	@$(del) $(BINDIR)/$(TARGETS)
	@echo "Executable removed!"
