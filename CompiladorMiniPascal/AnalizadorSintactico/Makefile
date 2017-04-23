CC = gcc
CFLAGS = -Wall -g

INCLUDES = -I. -I../AnalizadorLexico

SOURCES	= \
../AnalizadorLexico/lexico.c \
sintactico.c \
main.c


MAIN = asintactico
OBJS = $(SOURCES:.c=.o)

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) 

.c.o:
		$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	-rm *.o asintactico \
		../AnalizadorLexico/lexico.o

