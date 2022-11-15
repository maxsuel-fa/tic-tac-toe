CC=g++
IDIR=../include
CFLAGS=-I$(IDIR) -pthread

ODIR=obj

_DEPS=player_handler.hpp communication_handler.hpp utils.hpp
DEPS=$(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ =server.o player_handler.o communication_handler.o utils.o
OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))

all: server

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run:
	./server
