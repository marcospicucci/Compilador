#ifndef _SINTACTICO_H
#define _SINTACTICO_H

#include <stdio.h>
#include <stdlib.h>
#include "lexico.h"//ver


//**********************************************************************
void errorSintactico(int nroError);

int analisisSintactico(FILE *fp,TipoToken *tkn);
void getTk(FILE *fp, TipoToken *tkn);

int reglaProgram(FILE *fp,TipoToken *tkn);
int reglaDefVar(FILE *fp,TipoToken *tkn);
int reglaDefProcFun(FILE *fp,TipoToken *tkn);
int reglaProc(FILE *fp, TipoToken *tkn);
int reglaFunc(FILE *fp,TipoToken *tkn);
int reglaArg(FILE *fp,TipoToken *tkn);
int reglaCuerpo(FILE *fp,TipoToken *tkn);
int reglaSentencia(FILE *fp,TipoToken *tkn);
int reglaIf(FILE *fp,TipoToken *tkn);
int reglaAsignac(FILE *fp,TipoToken *tkn);
int reglaExpresion(FILE *fp,TipoToken *tkn);

int esRWoSP(FILE *fp, TipoToken *tkn); // VER SI ACA O EN LEXICO..

int reglaExp(FILE *fp,TipoToken *tkn);
int reglaTermino(FILE *fp,TipoToken *tkn);
int reglaExpree(FILE *fp,TipoToken *tkn);
int reglaFactor(FILE *fp,TipoToken *tkn);
int reglaTermii(FILE *fp,TipoToken *tkn);
int reglaConstante(FILE *fp,TipoToken *tkn);
int reglaRotulo(FILE *fp,TipoToken *tkn);

int reglaOp1(FILE *fp,TipoToken *tkn);
int reglaOp2(FILE *fp,TipoToken *tkn);
int reglaOp3(FILE *fp,TipoToken *tkn);
int reglallamadaFunc(FILE *fp,TipoToken *tkn);
int reglallamadaProc(FILE *fp,TipoToken *tkn);
int reglaWhile(FILE *fp,TipoToken *tkn);
int reglaCase(FILE *fp,TipoToken *tkn);
int reglaTipoDato(FILE *fp, TipoToken *tkn);
int reglaSucesor(FILE *fp, TipoToken *tkn);
int reglaPredecesor(FILE *fp, TipoToken *tkn);
int reglaLeer(FILE *fp, TipoToken *tkn);
int reglaEscribir(FILE *fp, TipoToken *tkn);
//**********************************************************************
#endif //_SINTACTICO_H
