CC = gcc
CFLAGS = -Wall -g

SOURCES = lexico.c main.c
MAIN = alexico
OBJS = $(SOURCES:.c=.o)

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) 

.c.o:
		$(CC) $(CFLAGS) -c $<  -o $@

clean:
	-rm *.o alexico tokens_salida.txt

