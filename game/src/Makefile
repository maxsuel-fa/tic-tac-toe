CC=g++
IDIR=../include
CFLAGS=-I$(IDIR) `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf

ODIR=obj

_DEPS=utils.hpp entities.hpp screen.hpp game_gi.hpp communication_handler.hpp game_engine.hpp
DEPS=$(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ = game.o utils.o entities.o screen.o game_gi.o communication_handler.o game_engine.o
OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))

all: test

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run:
	./test

clear:
	rm $(ODIR)/*.o & rm test

