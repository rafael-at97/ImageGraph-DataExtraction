# Remember to run 'export LD_LIBRARY_PATH=/usr/local/lib/opencv'

CC=g++
CFLAGS=-Wall -ansi $(shell pkg-config --cflags opencv4)
LDFLAGS=$(shell pkg-config --libs opencv4)

EXTRA_CFLAGS+="-std=c++11"

SRC= $(wildcard *.cpp)
OBJ= $(SRC:.c=.o)

all: $(OBJ)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(LDFLAGS) $(SRC)

$(OBJ):
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c $(SRC)
