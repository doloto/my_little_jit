CC=gcc
CFLAGS=-Wall -c
LDFLAGS=
SOURCES=smc.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=smc

all: exec
exec: $(SOURCES) $(EXECUTABLE)
debug: CFLAGS += -g
debug: exec
		
$(EXECUTABLE): $(OBJECTS) 
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
		$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o smc

