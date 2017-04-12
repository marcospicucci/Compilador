#ifndef _TABLADESIMBOLOS_H
#define _TABLADESIMBOLOS_H

#include <stdio.h>
#include <stdlib.h>

#define maxParam 6 //uso esto?
#define cantEntradas 137
#define maxArgs 10
#define palres 0
#define var 1
#define proc 2
#define func 3
#define varArg 4
#define maxVars 10

//*****DEFINICION DEL ELTO CORRESPONDIENTE A LAS ENTRADAS DE LA TS******
typedef struct ElementoTS{
  char *nombre;	//el lexema
  int categoria;//si es palabra reservada, variable, proc o func ( vble - parametro tmb?)
  char *tipoDato; //caso de variables o lo que retorna una fc
  int nivel;
  int desplz;
  char *etiq;
  char asignado;
  int nroArg;	//para los proc o func  
  char **listaParam;//tipos de param en orden
   //agregar valor? para ver q tenga asiganado algo la vble..
}ItemTs;


typedef struct Nodo{//eltos con mismo hash
  ItemTs *item;	
  struct Nodo *sig;	
	
}NodoTS;

typedef NodoTS * Lista;// una lista es un puntero a un nodo							

typedef struct Env{ //definicion de ambiente. nombre de quien lo definio, nro de nivel y su TS propia
  char *name;//nombre del pp, proc o func creador del ambiente.
  int lvl;	//nivel del ambiente
  Lista TablaSimbolos[cantEntradas];
  struct Env *padre;//referencia al ambiente padre 
}Ambiente;


//CREAR UNA ESTRUCTURA PARA MANTENER A LOS AMBIENTES DEL MISMO NIVEL? asi no piso las referencias??



//**********************************************************************

Ambiente *crearAmbiente(char *n, int lv, Ambiente *p);
ItemTs *crearItem(char *n, int cat,char *td, int nv, int dpz, char *eti, char asig, int nA, char **lp);
void eliminarAmbiente(Ambiente *p);
void eliminarItem(ItemTs *it);	
unsigned int hash(char *s);
void insertar(ItemTs *elem, Ambiente *ambi);
void eliminar(ItemTs *elem, Ambiente *ambi);
int existe(char *s, Ambiente *ambi);//si existe
int existeLocal(char *s, Ambiente *ambi); // no se fija en los padres
ItemTs *getItem(char *s, Ambiente *ambi);
void tablaToFile(FILE *fp, Ambiente *ambi);

//existeFun();
//existeProc();

Lista initList();
int esVacia(Lista lis);
Lista agregar(Lista lis, ItemTs *itm);
Lista quitar(Lista lis, ItemTs *itm);
int pertenece(Lista lis, char *s);
ItemTs *obtenerElto(Lista lis, char *s);
void imprimirLista(Lista lis,FILE *fp);

#endif // _TABLADESIMBOLOS_H
