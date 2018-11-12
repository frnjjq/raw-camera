CC=gcc
CFLAGS=-Wall -Wextra -Ofast -march=native-fopt-info-vec
LDFLAGS=
LIB=-lv4l2 -lSDL2

SOURCES=capture.c player.c main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=rawcam

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o $@ $(LDFLAGS) $(OBJECTS) $(LIB) 

clean :
	rm -f $(EXECUTABLE) *.o
