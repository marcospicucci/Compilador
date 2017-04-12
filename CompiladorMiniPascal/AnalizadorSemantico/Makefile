CC = gcc
CFLAGS = -Wall -g

SOURCES = lexico.c TablaDeSimbolos.c semantico.c sintactico.c main.c
MAIN = asemantico
OBJS = $(SOURCES:.c=.o)

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) 

.c.o:
		$(CC) $(CFLAGS) -c $<  -o $@

clean:
	-rm *.o asemantico

