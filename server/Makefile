CC=g++
IDIR=../include
CFLAGS=-I$(IDIR)

ODIR=obj

_DEPS=utils.hpp
DEPS=$(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ = main.o
OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))

all: server

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run:
	./server