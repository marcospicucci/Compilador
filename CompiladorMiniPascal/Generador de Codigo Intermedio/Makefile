CC = gcc
CFLAGS = -Wall -g

SOURCES = lexico.c sintactico.c semantico.c TablaDeSimbolos.c generadorMepa.c main.c
MAIN = gencodint
OBJS = $(SOURCES:.c=.o)

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) 

.c.o:
		$(CC) $(CFLAGS) -c $<  -o $@

clean:
	-rm *.o gencodint traduccionMEPA.txt

