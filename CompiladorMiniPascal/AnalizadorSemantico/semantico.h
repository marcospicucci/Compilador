#ifndef _SEMANTICO_H
#define _SEMANTICO_H

#include "TablaDeSimbolos.h"
//CONTIENE LOS METODOS Q VAN A SER LLAMADOS POR EL A.SINTACTICO, IE EL A.SEMANTICO SE IMPLEMENTA DENTRO/JUNTO CON EL SINTACTICO

void chequearTiposDatos(char *tli,int linea ,char *tld); //se fija q los tipos de datos del ladoizq y lado derecho sean iguales (ver si se puede reusar para otra, cambiar nombre)
void esEntera(char *td, int co, int li);
void esBooleana(char *td, int co, int li,char *constructor);
void chequearTipoOprd(char *dor, char *ando);
void setearStr(char *str, char *cad);
char **crearArrayTD();

void tieneValor(ItemTs *itm, int linea, int col, Ambiente *ambi);  //se fija q tenga valor asignado
int esProcedimiento(ItemTs *itm); //por medio del lexema
int esFuncion(ItemTs *itm); //por medio del lexema
int esVariable(ItemTs *itm);
int verificarAsigFunc(ItemTs *itm, Ambiente *env);

void esVbleEnteraCase(ItemTs *itm, int linea, int col, Ambiente *env);

void errorSemantico(int nroError, int li, int co, char *op, char *te);
void estaEnTS(char *s, int linea, int col, Ambiente *ambi);//se fija si un lexema esta en la TS
void checkArgsRepetidos(char **lisPar, char *subpr, int linea, Ambiente *ambi);//se fija q no haya args repetidos
void checkTipoyCantArgs(char **lisPar, int canti, char *subpr, int linea, int col, Ambiente *ambi);//se fija q sea la misma cantidad en la llamada q en la definicion
void checkRetornoFunc(char *lex, int linea, int col, Ambiente *ambi);//se fija si la vble de retorno(mismo nombre q el proc) tiene asignado un valor()
int verificarVarNombFun(char *lex, char *s);
int getNroArg(char *lex, Ambiente *ambi);
char *crearStr(char *str);
void setearTD(char *lex, char *td, Ambiente *amb);
void setCantyTiposArgs(Ambiente *env, char *str,char **tdArgs,int cantii);
char *getTipoDato(char *lex, Ambiente *amb);
void existeElem(char *lex,int linea, int col, Ambiente *ambi);

void vaciarTDarg(char **tdar);
void vaciarParamForm(char **parfor);
void vaciarVariables(char **vbles);


//hacer metodo q chekee q una vble no tenga el nombre de un subp. Deberia guardar el "padre" de cada subp





#endif // _SEMANTICO_H
