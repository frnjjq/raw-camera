CC=gcc
CFLAGS=-Wall -Wextra -Ofast
LDFLAGS= -lv4l2

SOURCES=capture.c main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=rawcam

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o $@ $(LDFLAGS) $(OBJECTS) $(LIB) 

clean :
	rm -f $(EXECUTABLE) *.o