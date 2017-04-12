#ifndef _GENERADORMEPA_H
#define _GENERADORMEPA_H

#include <stdio.h>
#include <stdlib.h>

FILE *fpm; //archivo de salida. aca?

void setearFPM(FILE *fp);
char *crearEtiq(int n);
//**********************EVALUACION DE EXPRESIONES***********************
void apct(char *k);//apila constante k
void suma();//sumar
void sust();//sustraccion
void mult();//multiplicación
void divi();//division
void umen();//menos unario
void conjun();//conjunción
void disjun();//disyuncion
void nega();//negacion
void cmme();//comparar por menor
void cmma();//comparar por mayor
void cmig();//comparar por igual
void cmdg();//comparar por desigual
void cmni();//comparar por menor o igual
void cmyi();//comparar por mayor o igual

void divc();//control de division por cero

//**********************************************************************
//******************COMANDOS CONDICIONALES E ITERATIVOS*****************
void dsvs(char *etiq);//desviar siempre
void dsvf(char *etiq);//desviar si el tope es falso

//**********************************************************************
//********************COMANDOS DE ENTRADA Y SALIDA**********************
void leer();//lectura de un valor entero (usado en cjto con el cmd d asignacion d vbles)
void impr();//impresion de un valor entero

//**********************************************************************
//***********COMANDOS DE ASIGNACION Y RECUPERACION DE VALORES***********
void apvl(int m, int n);//apila el valor de una variable (nivel, despl)
void alvl(int m, int n);//almacena el tope de la pila en una variable

//**********************************************************************
//*********************PROGRAMAS Y PROCEDIMIENTOS***********************
void inpp();//iniciar programa principal
void enpr(int k, char *etiq);//entrar al procedimiento de nivel k
void llpr(char *etiq);//llamar a un procedimiento p
void rmem(int m);//reservar memoria para variables
void lmem(int m);//libera memoria de variables locales
void rtpr(int k, int n);//retornar de un procedimiento de nivel k, n tamaño

void para();//parada de la maquina MEPA
void nada(char *etiq);// nada..

#endif //_GENERADORMEPA_H
