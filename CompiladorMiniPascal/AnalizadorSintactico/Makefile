CC = gcc
CFLAGS = -Wall -g

SOURCES = lexico.c sintactico.c main.c
MAIN = asintactico
OBJS = $(SOURCES:.c=.o)

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) 

.c.o:
		$(CC) $(CFLAGS) -c $<  -o $@

clean:
	-rm *.o asintactico

