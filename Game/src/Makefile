CC=gcc
IDIR=../include
CFLAGS=-I$(IDIR)

ODIR=obj

_DEPS=game.h
DEPS=$(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ = main.o game.o
OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))

all: game_exe

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

game_exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run:
	./game_exe

clear:
	rm -f ./obj/*.o


