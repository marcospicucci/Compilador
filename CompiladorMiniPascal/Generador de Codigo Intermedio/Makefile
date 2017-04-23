CC = gcc
CFLAGS = -Wall -g

INCLUDES = -I. -I../AnalizadorLexico -I../AnalizadorSemantico

SOURCES = \
../AnalizadorLexico/lexico.c \
../AnalizadorSemantico/semantico.c \
../AnalizadorSemantico/TablaDeSimbolos.c \
sintactico.c \
generadorMepa.c \
main.c \

MAIN = gencodint
OBJS = $(SOURCES:.c=.o)

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) 

.c.o:
		$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	-rm *.o gencodint traduccionMEPA.txt \
		../AnalizadorLexico/lexico.o \
		../AnalizadorSemantico/semantico.o \
		../AnalizadorSemantico/TablaDeSimbolos.o

