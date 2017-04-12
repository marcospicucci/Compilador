#ifndef _SINTACTICO_H
#define _SINTACTICO_H

#include <stdio.h>
#include <stdlib.h>
#include "lexico.h"//ver
#include "semantico.h"

//**********************************************************************
void errorSintactico(int nroError);

int analisisSintactico(FILE *fp,TipoToken *tkn);
void getTk(FILE *fp, TipoToken *tkn);

int hayDef(TipoToken *tkn);
int reglaParamAct(FILE *fp, TipoToken *tkn,Ambiente *env, int *cantiParAct;);

int reglaProgram(FILE *fp,TipoToken *tkn);
int reglaDefVar(FILE *fp,TipoToken *tkn,Ambiente *env);
int reglaDefProcFun(FILE *fp,TipoToken *tkn,Ambiente *env);
int reglaProc(FILE *fp, TipoToken *tkn,Ambiente *env);
int reglaFunc(FILE *fp,TipoToken *tkn,Ambiente *env);
int reglaArg(FILE *fp,TipoToken *tkn,Ambiente *env,char **tda);
int reglaCuerpo(FILE *fp,TipoToken *tkn,Ambiente *env);
int reglaSentencia(FILE *fp,TipoToken *tkn,Ambiente *env);
int reglaIf(FILE *fp,TipoToken *tkn,Ambiente *env);
int reglaAlter(FILE *fp,TipoToken *tkn,Ambiente *env);
int reglaAsignac(FILE *fp,TipoToken *tkn, char *td,Ambiente *env);
int reglaExpresion(FILE *fp,TipoToken *tkn, char *tipodevuelto, Ambiente *env);

int esRWoSP(FILE *fp, TipoToken *tkn); // VER SI ACA O EN LEXICO..

int reglaExp(FILE *fp,TipoToken *tkn, char *td,Ambiente *env);
int reglaTermino(FILE *fp,TipoToken *tkn, char *td,Ambiente *env);
int reglaExpree(FILE *fp,TipoToken *tkn, char *td,Ambiente *env);
int reglaFactor(FILE *fp,TipoToken *tkn, char *tipodevuelto, Ambiente *env);
int reglaTermii(FILE *fp,TipoToken *tkn, char *td,Ambiente *env);
int reglaConstante(FILE *fp,TipoToken *tkn,char *td);
int reglaRotulo(FILE *fp,TipoToken *tkn,Ambiente *env);

int reglaOp1(FILE *fp,TipoToken *tkn);
int reglaOp2(FILE *fp,TipoToken *tkn);
int reglaOp3(FILE *fp,TipoToken *tkn);
int reglallamadaFunc(FILE *fp,TipoToken *tkn, char *tipodevuelto, Ambiente *env);
int reglaWhile(FILE *fp,TipoToken *tkn,Ambiente *env);
int reglaCase(FILE *fp,TipoToken *tkn,Ambiente *env);
int reglaTipoDato(FILE *fp, TipoToken *tkn);
int reglaSucesor(FILE *fp, TipoToken *tkn, char *tipodevuelto, Ambiente *env);
int reglaPredecesor(FILE *fp, TipoToken *tkn, char *tipodevuelto, Ambiente *env);
int reglaLeer(FILE *fp, TipoToken *tkn,Ambiente *env);
int reglaEscribir(FILE *fp, TipoToken *tkn, Ambiente *env);
//**********************************************************************
#endif //_SINTACTICO_H
