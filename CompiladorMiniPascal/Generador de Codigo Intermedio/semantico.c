#include "semantico.h"
#include "lexico.h"
#include <stdlib.h>


void errorSemantico(int nroError, int li, int co, char *operador, char *tipoesp){
  switch(nroError){
	case 1: printf("Error (1) semántico en la linea %d columna %d: El número de parámetros actuales en el llamado a '%s' no coincide con el número indicado en la definición del subprograma\n",li,co -1,tipoesp);	
	        break;
	case 2: printf("Error (2) semántico en la linea %d columna %d: El tipo de los parámetros actuales no coincide con el tipo indicado en la definición del subprograma\n",li,co -1);	
	        break;
	case 3: printf("Error (3) semántico en la linea %d columna %d: El identificador '%s' ya se encuentra en uso y no puede re-definirse\n",li,co -1,tipoesp);	
	        break;
	case 4: printf("Error (4) semántico en la linea %d columna %d: El elemento '%s' es una variable, no es un identificador que se corresponda con el llamado de un subprograma\n",li,co -1,tipoesp);	
	         break; 
	case 5: printf("Error (5) semántico en la linea %d: Se espera que la expresión asociada a la condición del constructor '%s' sea del tipo BOOLEAN'\n",li,tipoesp);	
	        break;
	case 6: printf("Error (6) semántico en la linea %d columna %d: Se espera que la expresión asociada al parámetro de la función 'SUCC' o 'PRED' sea del tipo INTEGER'\n",li,co -1);	
	        break;
	case 7: printf("Error (7) semántico en la linea %d: Los tipos de datos de los lados izquierdo y derecho de la asignación no coinciden\n", li);
	        break;        
	case 8: printf("Error (8) semántico en la linea %d columna %d: El elemento '%s' no se encuentra definido o bien no puede ser accedido desde el alcance actual\n",li,co -1,tipoesp);	
	         break;       	        
	case 9: printf("Error (9) semántico en la linea %d columna %d: Se espera que el identificador '%s' sea un identificador asociado a una variable\n",li,co -1,tipoesp);	
	        break;        
	case 10: printf("Error (10) semántico en la linea %d columna %d: El llamado a la función '%s' debe ser utilizado como factor en una expresión, se le debe dar un uso al valor retornado\n",li,co -1,tipoesp);	
	         break;        
	case 11: printf("Error (11) semántico en la linea %d columna %d: El llamado a un procedimiento no retorna ningún valor, no puede ser utilizado como parte de una expresión\n",li,co -1);	
	         break;        
	case 12: printf("Error (12) semántico en la linea %d columna %d: La variable %s no tiene asignado ningún valor\n",li,co -1,tipoesp);	
	         break;                
	case 13: printf("Error (13) semántico en la linea %d columna %d: Se finaliza la función '%s' sin haber realizado la asignación de un valor de retorno\n",li,co -1,tipoesp);
			 break;
	case 14: printf("Error (14) semántico en la linea %d columna %d: Se espera que el operando del operador '%s' sea del tipo '%s'\n",li,co -1, operador, tipoesp);	
	         break;
	case 15: printf("Error (15) semántico en la linea %d columna %d: Se espera que la variable '%s' asociada al discriminador de la sentencia 'CASE' sea del tipo 'INTEGER'\n",li,co -1, tipoesp);	
	         break;     
	        
	default: ;
  }
exit(1);

}

void esVbleEnteraCase(ItemTs *itm, int linea, int col, Ambiente *env){
  
  if(esVariable(itm) == 1){
	if(existeLocal((*itm).nombre,env) == 1)//si es vble local chequeo que tenga un valor asignado
		tieneValor(itm,linea,col,env);			 
	
	 if(sonIguales((*itm).tipoDato, "INTEGER") != 1)
		errorSemantico(15, linea , col, NULL, (*itm).nombre);
  }
  else
	errorSemantico(9,linea,col,NULL,(*itm).nombre);
  
}

void estaEnTS(char *lex, int linea, int col, Ambiente *ambi){	//se fija si ya esta ver cuando usarlo
  if(existe(lex, ambi) == 1){
    printf("Error semántico en la linea %d columna %d: el lexema '%s' ya se encuentra definido\n",linea, col, lex);
    exit(1);	  
  } 	
}

void existeElem(char *lex, int linea, int col, Ambiente *ambi){
 //printf("elemento haber si existe: %s\n",lex);
 
  if(getItem(lex, ambi) == NULL)
	errorSemantico(8,linea,col,NULL,lex);
}

void checkArgsRepetidos(char **lisPar, char *subp, int linea, Ambiente *ambi){//lispar son los nombres(lexemas) de los param (act?, form?)
  int i, j, cantArgs;	//obtner lisPar a partir del lexema?
  char *a;				//ya se comprobo la cantidad de param previamente antes d llamar a este metodo
  ItemTs  *elem;
  
  elem = getItem(subp, ambi);
  cantArgs = (*elem).nroArg;
  
  if(cantArgs > 1){
    for(i=0;i<cantArgs;i++){//obtengo y comparo con los otros
      a = lisPar[i];   
      for(j=i+1;j<cantArgs;j++){
	    if(sonIguales(a, lisPar[j]) == 1){
		  printf("Error semántico en la linea %d: el parámetro '%s' se encuentra repetido\n",linea, a);
	      exit(1);
	    }
	  }	 
    }
  }
}

void checkTipoyCantArgs(char **lisPar, int canti, char *subpr, int linea, int col, Ambiente *ambi){//listPar serian los par act. con *subpr obtengo los formales
  ItemTs *elem;		
  char **parForm;
  int i;
  
  elem = getItem(subpr, ambi);
  parForm = (*elem).listaParam; 
  
  if(canti != (*elem).nroArg){
	printf("Error (1) semántico en la linea %d columna %d: El número de parámetros actuales (%d) en el llamado a '%s' no coincide con el número de parámetros formales (%d) indicado en su definición \n",linea,col -1,canti,subpr,(*elem).nroArg);  
	exit(1);	
  }
  for(i=0;i<canti;i++){
	  
    if(sonIguales(parForm[i],lisPar[i]) == 0){ 
	  printf("Error (2) semántico en la linea %d columna %d: Se espera que el parámetro actual #%d en el llamado a '%s' sea del tipo '%s'\n",linea, col-1, i+1, subpr, parForm[i]);
	  exit(1);
	} 
  }	
}

void checkRetornoFunc(char *lex, int linea, int col, Ambiente *ambi){
ItemTs *itm;
itm = getItem(lex,ambi);
	
 if((*itm).asignado != 'Y')
	errorSemantico(13,linea,col,NULL,lex);
		
}

//**********************************************************************
int verificarVarNombFun(char *lex, char *s){ //???
 return (sonIguales(lex,s));	
}
//**********************************************************************
int getNroArg(char *lex, Ambiente *ambi){
 ItemTs *itm;	
 itm = getItem(lex, ambi);
 	
return ((*itm).nroArg);
}
//**********************************************************************
void vaciarTDarg(char **tdar){
int i;
	for(i=0;i<maxArgs;i++)
		tdar[i] = NULL;   // asi o  *tdar[i]
}

void vaciarParamForm(char **parfor){
int i;
	for(i=0;i<maxArgs;i++)
		parfor[i] = NULL;
}

void vaciarVariables(char **vbles){
int i;
	for(i=0;i<maxVars;i++)
		vbles[i] = NULL;	
}

//**********************************************************************


void setearTD(char *lex, char *td, Ambiente *amb){
ItemTs *itm;
			
itm = getItem(lex,amb); 
(*itm).tipoDato = td; //no deberia usar setStr???

}

char *getTipoDato(char *lex, Ambiente *amb){//antes se verifico q exista
ItemTs	*itm;

itm = getItem(lex, amb);
return ((*itm).tipoDato);
}


void setCantyTiposArgs(Ambiente *amb,char *str,char **tdArgg, int cantii){
ItemTs *itm;
			
itm = getItem(str,amb);
(*itm).nroArg = cantii;
(*itm).listaParam = tdArgg;	
}

//**********************************************************************
void chequearTiposDatos(char *tli, int linea, char *tld){
	
	if(sonIguales(tli, tld) != 1){
		printf("Error semántico (7) en la linea %d: Los tipos de datos de los lados izquierdo y derecho de la asginación no coinciden\n",linea);
		exit(1);
	}	
}

//**********************************************************************

void tieneValor(ItemTs *itm, int linea, int col, Ambiente *ambi){ //chequea q la variable (id) tenga valor
  if((*itm).asignado != 'Y') //CAMBIAR
	errorSemantico(12, linea, col, NULL, (*itm).nombre);
}

int esProcedimiento(ItemTs *itm){
int sale = 0;

  if((*itm).categoria == proc)
	sale = 1;
	
return	sale;
}

int esFuncion(ItemTs *itm){
int sale = 0;

  if((*itm).categoria == func)
	sale = 1;
	
return	sale;
}

int esVariable(ItemTs *itm){
int sale = 0;

  if(((*itm).categoria == var) || ((*itm).categoria == varArg) )
	sale = 1;
	
return sale;	
}

void esEntera(char *td, int co, int li){
  if(sonIguales(td, "INTEGER") != 1)
	errorSemantico(6, li , co, NULL, NULL);
}

void esBooleana(char *td, int co, int li , char *constructor){ //CHAR O EX
	if(sonIguales(td, "BOOLEAN") != 1)
	  errorSemantico(5, li , co, NULL, constructor);
}
//**********************************************************************
void setearStr(char *str, char *cad){
int i=0;
	for(i=0; cad[i] != '\0';i++)
		*(str +i) = *(cad +i);

*(str +i) = '\0';	
}

char *crearStr(char *s){
int i;
char *str;

str = malloc(20*sizeof(char)); //ver si 20 0 21 para '\0'
  for(i=0;s[i] != '\0';i++)
	str[i] = s[i];
	
str[i] = '\0';	
return str;
}
//**********************************************************************
int verificarAsigFunc(ItemTs *itm, Ambiente *env){
int sale = -1;

  if((esFuncion(itm) == 1) && (sonIguales((*itm).nombre, (*env).name) == 1))
    sale = 1;
  
return sale;	
}

char **crearArrayTD(){
int i;
char **arrayTD;
arrayTD = malloc(maxArgs*sizeof(char*));
  for(i=0;i<maxArgs;i++)
	  arrayTD[i] = malloc(20*sizeof(char));
	  
return arrayTD;
}

	




