#include "TablaDeSimbolos.h"
#include "lexico.h"

ItemTs *crearItem(char *n, int cat,char *td, int nv, int dpz, char *eti, char asig, int nA, char **lp){ //completar esto
  ItemTs *item;
  
  item = malloc(sizeof(ItemTs));//cast?
  (*item).nombre = n;
  (*item).categoria = cat;
  (*item).tipoDato = td;
  (*item).nivel = nv;
  (*item).desplz = dpz;
  (*item).etiq = eti;
  (*item).asignado = asig;
  (*item).nroArg = nA; 
  (*item).listaParam = lp; //error aca e?

return item;	
}
//**********************************************************************
void eliminarAmbiente(Ambiente *p){
free(p);
}
void eliminarItem(ItemTs *it){
free(it);
}





Ambiente *crearAmbiente(char *n, int nivel, Ambiente *p){
  ItemTs *item;
  Ambiente *ambi;   
  int i;
  
  ambi = malloc(sizeof(Ambiente));  
  (*ambi).name = n;
  (*ambi).lvl = nivel;
  (*ambi).padre = p;
 
 
  for(i=0; i<cantEntradas;i++)
	(*ambi).TablaSimbolos[i] = NULL;
  
 item = crearItem("PROGRAM", palres,NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("IF", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("THEN", palres,NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("ELSE", palres,NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("CASE", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("WHILE", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("DO", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("PROCEDURE", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("FUNCTION", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("VAR", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("TRUE", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("FALSE", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("MAXINT", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("INTEGER", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("BOOLEAN", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("AND", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("OR", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("NOT", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("READ", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("WRITE", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("SUCC", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("PRED", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("BEGIN", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("END", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);
  item = crearItem("OF", palres, NULL, 0, 0, NULL, ' ', 0, NULL);
  insertar(item, ambi);

return ambi;
}




unsigned int hash(char *s){
  int i;
  unsigned int valor = 5381;
   
  for(i=0; s[i]!='\0'; i++)
	valor = 33 * valor + s[i];

return valor;
}


void insertar(ItemTs *elem, Ambiente *ambi){//pasar el puntero a TS como arg
  unsigned int i;
  Lista l;

  i =  hash((*elem).nombre) % cantEntradas; //obtengo la clave del lexema 
  l = (*ambi).TablaSimbolos[i];
  (*ambi).TablaSimbolos[i] = (Lista)agregar(l, elem);//es necesaria la asign?pareciera q si   
 
  //printf("valor de hash al insertar: %d\n",i);
  //printf("nombre del item antes de insertar: %s\n", (*elem).nombre);	
}

void eliminar(ItemTs *elem, Ambiente *ambi){//recibe el lexema o el item
  unsigned int i; 			
  Lista l;
  
  i =  hash((*elem).nombre) % cantEntradas;
  l = (*ambi).TablaSimbolos[i];
  
  (*ambi).TablaSimbolos[i] = (Lista)quitar(l, elem);
  //printf("valor hash: %d\n",i);	
}

int existe(char *s, Ambiente *ambi){ //MODIFICAR PARA Q BUSQUE POR LOS AMBIENTES PADRE
  unsigned int i;
  int sale=0, band=1;;
  Lista lis;
  Ambiente *dad;
  i =  hash(s) % cantEntradas;
  
  dad = ambi;
  while(band == 1){
	lis = (*dad).TablaSimbolos[i];  
	sale = pertenece(lis, s);
	 if(sale == 0){
	   dad = (*dad).padre;	  
	    if(dad == NULL)	 
	     band = 0;		 
	 }
	 else
		band = 0;	  
  }  
return sale;
}

int existeLocal(char *s, Ambiente *ambi){
int sale = 0;
unsigned int i;
Lista lis;

i =  hash(s) % cantEntradas;
lis = (*ambi).TablaSimbolos[i];  
sale = pertenece(lis, s);

return sale;
}



ItemTs *getItem(char *s, Ambiente *ambi){//MODIFICAR PARA Q BUSQUE POR LOS AMBIENTES PADRE
  unsigned int i;
  int  band=1;
  Lista lis;
  Ambiente *dad;
  ItemTs *itm;	
  i =  hash(s) % cantEntradas;
  
  dad = ambi;
  while(band == 1){
  lis = (*dad).TablaSimbolos[i];
  itm = obtenerElto(lis, s);
   if(itm == NULL){
    dad = (*dad).padre;	  
	if(dad == NULL)	 
	  band = 0;
	  
   }
   else
    band = 0;
  } 
return itm;
}

void tablaToFile(FILE *fp, Ambiente *ambi){
  int i;
  Lista l;	
	
  for(i=0; i<cantEntradas;i++){
    l = (*ambi).TablaSimbolos[i];   
    imprimirLista(l, fp);
  }
}

//***************************LOS DE LISTA*******************************
Lista initList(){
return NULL;	
}

int esVacia(Lista lis){
  int sale = 0;
  
  if(lis == NULL)
    sale = 1;
      
return sale; 
}

Lista agregar(Lista lis, ItemTs *itm){
  NodoTS *nuevo = malloc(sizeof(NodoTS)); 
  
  (*nuevo).item = itm;
  (*nuevo).sig = lis;
  lis = nuevo;
   
return lis;
}

Lista quitar(Lista lis, ItemTs *itm){	
	NodoTS *aux, *ant;
	int sale = 0;
	
	for(ant=NULL, aux=lis; (aux!=NULL && sale==0); ant=aux, aux=(*aux).sig){
	  if( sonIguales( (*((*aux).item)).nombre , (*itm).nombre) == 1 ){
	    if(ant == NULL) //ie, primer elto de la lista
		  lis = (*aux).sig;
		else
		  (*ant).sig = (*aux).sig;    
	 
	  free(aux);
	  sale = 1;
	  } 			
	}
		
return lis;	
}

int pertenece(Lista lis, char *s){
  NodoTS *aux;
  int sale = 0;
  
  for(aux=lis; aux!=NULL && sale==0; aux=(*aux).sig){
    if( sonIguales( (*((*aux).item)).nombre , s) == 1 )
      sale = 1;
  }
return sale;   
}

ItemTs *obtenerElto(Lista lis, char *s){
  NodoTS *aux;
  int band = 0;
  ItemTs *elto = NULL;  
   
  for(aux=lis; (aux!=NULL && band==0); aux=(*aux).sig){	 	
	  
    if( sonIguales( (*((*aux).item)).nombre , s) == 1 ){
      elto = (*aux).item;
      band = 1;
    }    
  }     
return elto;
}

void imprimirLista(Lista lis, FILE *fp){
  NodoTS *aux;
  ItemTs *itm;
  int i, numargs;
  char **listPar;
  
  for(aux=lis; aux!=NULL; aux=(*aux).sig){
    itm = (*aux).item;
    numargs = (*itm).nroArg;
    listPar = (*itm).listaParam;
    
    fprintf(fp, "lexema: %s, categoria: %d, tipo de dato: %s, asignado: %c, nro de args: %d, tipo de los args: ",(*itm).nombre, (*itm).categoria, (*itm).tipoDato, (*itm).asignado, (*itm).nroArg);		 
    if(numargs > 0){
	  for(i= 0; i<numargs;i++)
        fprintf(fp, "%s ",listPar[i]);	  
 	}
  fprintf(fp,"\n"); 
  }
}


//**********************************************************************


//int modificar(){}
