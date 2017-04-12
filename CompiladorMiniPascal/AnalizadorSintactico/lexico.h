#ifndef _LEXICO_H
#define _LEXICO_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//**********************************************************************
#define cantkw 25 // cantidad de palabras keyword
#define tamaxid 20 // tamaño maximo de los id
#define tamaxent 9 //cantidad maxima de digitos de un entero, necesario?cual es el limite?

//static TipoToken keywords[cantkw];
//**********************************************************************
typedef struct Token{ //seria conveniente guardar la longitud del token ej ';'=1, 'while'=5, etc. asi luego lo uso para mostrar la columna correcta en el error, retrocediento esta longitud
char *nombre;
char *valor;	
}TipoToken;
//**********************************************************************
void errorLexico(int nroError,int li, int co);
int verificarExtension(char *n, int longi);
void obtenerEntero(FILE *fpp, char *ent, int *linea, int *col, char *c);
void obtenerId(FILE *fpp, char *ids, int *linea, int *col, char *c);
void aMayus(char *str, int size);
int longiptr(char *fname);
void inicializarKeywords();
void imprimeToken(TipoToken tok);
int sonIguales(char *p1, char *p2);
int esOpLog(char *str);
int esKeyword(char *str, TipoToken kw[]);
int avanzarComentario(FILE *fp, int *fila, int *col);
int getToken(FILE *fp, TipoToken *tk,int *lineactual, int *columnactual);// es quien realiza el análisis

//**********************************************************************
#endif //_LEXICO_H
