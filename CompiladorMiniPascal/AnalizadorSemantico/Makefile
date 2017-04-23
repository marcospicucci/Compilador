CC = gcc
CFLAGS = -Wall -g

INCLUDES = -I. -I../AnalizadorLexico

SOURCES = \
../AnalizadorLexico/lexico.c \
TablaDeSimbolos.c \
semantico.c \
sintactico.c \
main.c

MAIN = asemantico
OBJS = $(SOURCES:.c=.o)

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) 

.c.o:
		$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	-rm *.o asemantico \
		../AnalizadorLexico/lexico.o

