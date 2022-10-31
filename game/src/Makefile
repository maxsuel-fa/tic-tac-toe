CC=g++
IDIR=../include
CFLAGS=-I$(IDIR) `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf

ODIR=obj

_DEPS=utils.hpp entities.hpp screen.hpp communication_handler.hpp
DEPS=$(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ = game.o utils.o entities.o screen.o communication_handler.o
OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))

all: test

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run:
	./test

clear:
	rm $(ODIR)/*.o

