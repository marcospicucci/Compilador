#include "lexico.h"
#include <stdio.h> //agregado

//**** variables globales ****
char actual, i_d[tamaxid], entero[tamaxent];;   
//int lineactual = 1, columnactual = 1;//idem
TipoToken keywords[cantkw]; //ponerlo en .h?
//TipoToken tkAnt, tkAct;
//guardar la distancia, en espacios, entre token y token? que pasa si hay salto de linea etc

void errorLexico(int nroError,int li, int co){
  switch(nroError){
	case 1: printf("Error (1) léxico en la linea %d columna %d: Se inicia sección de comentario y no se finaliza. Se omite el caracter '}'\n",li,co);	
	        break;
	case 2: printf("Error (2) léxico en la linea %d columna %d: El número entero excede el tamaño máximo permitido de 9 dígitos\n",li,co);	
	        break;
	case 3: printf("Error (3) léxico en la linea %d columna %d: El identificador excede el tamaño máximo permitido de 20 caracteres\n",li,co);	
	        break;
	case 4: printf("Error (4) léxico en la linea %d columna %d: El caracter no forma parte del alfabeto del lenguaje\n",li,co);	
	        break;
	case 5: printf("Error (5) léxico en la linea %d columna %d: Identificador/número mal formado\n",li,co);	
	        break;
	case 6: printf("Error (6) léxico en la linea %d columna %d: Caracter '}' inesperado.\n",li,co);	
	        break;        
	default: ;                                               	
  }
exit(1);  
}
//**********************************************************************
int verificarExtension(char *n, int longi){ //verifica que la extension del archivo fuente sea la correcta (.pas)
	int i = 0;
	int corta = 1;
	int sale = -1;
	
	while((i<longi) && (corta == 1)){
		if(n[i] == '.' && (longi == i+4)){
			if((n[i+1] == 'p') && (n[i+2] == 'a') && (n[i+3] == 's'))
				sale = 1;		
			
		corta = 0;
		}	
		else
			i++;	
	}
	return sale;
}
//**********************************************************************
void aMayus(char *str, int size){ //pasa el contenido de un puntero a char a mayusculas
	 int i;
	 for(i=0;i<size;i++){
		*(str+i) = toupper((*(str+i)));
		}
}
//**********************************************************************
int longiptr(char *fname){//devuelve la longitud de un puntero a char
	int i=0;
	while(fname[i] != '\0'){
		i++;
	}	
	return i;		
}

//**********************************************************************
void inicializarKeywords(){ // guardo los tokens correspondientes a las palabras claves
	TipoToken t;				//si keywords es global, no hace falta q tenga parametros este metodo
	t.nombre = "PROGRAM";t.valor = "0";
	keywords[0] = t;
	t.nombre = "IF";t.valor = "0";
	keywords[1] = t;
	t.nombre = "THEN";t.valor = "0";
	keywords[2] = t;
	t.nombre = "ELSE";t.valor = "0";
	keywords[3] = t;
	t.nombre = "CASE";t.valor = "0";
	keywords[4] = t;
	t.nombre = "WHILE";t.valor = "0";
	keywords[5] = t;
	t.nombre = "DO";t.valor = "0";
	keywords[6] = t;
	t.nombre = "PROCEDURE";t.valor = "0";
	keywords[7] = t;
	t.nombre = "FUNCTION";t.valor = "0";
	keywords[8] = t;
	t.nombre = "VAR";t.valor = "0";
	keywords[9] = t;
	t.nombre = "TRUE";t.valor = "0";
	keywords[10] = t;
	t.nombre = "FALSE";t.valor = "0";
	keywords[11] = t;
	t.nombre = "MAXINT";t.valor = "0";
	keywords[12] = t;
	t.nombre = "INTEGER";t.valor = "0";
	keywords[13] = t;
	t.nombre = "BOOLEAN";t.valor = "0";
	keywords[14] = t;
	t.nombre = "OPLOGICO";t.valor = "AND";
	keywords[15] = t;
	t.nombre = "OPLOGICO";t.valor = "OR";
	keywords[16] = t;
	t.nombre = "OPLOGICO";t.valor = "NOT";
	keywords[17] = t;
	t.nombre = "READ";t.valor = "0";
	keywords[18] = t;
	t.nombre = "WRITE";t.valor = "0";
	keywords[19] = t;
	t.nombre = "SUCC";t.valor = "0";
	keywords[20] = t;
	t.nombre = "PRED";t.valor = "0";
	keywords[21] = t;
	t.nombre = "BEGIN";t.valor = "0";
	keywords[22] = t;
	t.nombre = "END";t.valor = "0";
	keywords[23] = t;
	t.nombre = "OF";t.valor = "0";
	keywords[24] = t;	
	
}
//**********************************************************************
void imprimeToken(TipoToken tok){ // imprime por pantalla un token de la forma <nombretoken, valor>
	printf("<%s, %s>\n",tok.nombre,tok.valor);//o preguntar aca si es == " " luego no imprimir
}
//**********************************************************************
int sonIguales(char *p1, char *p2){
	int i;
	int band = 1, sale = 1;
	char c1,c2;
	
	if(longiptr(p1) == longiptr(p2)){

		for(i=0; (i<(longiptr(p1)) && (band==1)); i++){
			c1 = *(p1 + i);
			c2 = *(p2 + i);
							
			if(c1 != c2){
				band = 0;
				sale = 0;
			}			
		}
	}
	else
		sale = 0;	
	
	return sale;
} 
//**********************************************************************
int esOpLog(char *str){//mala practica, ver de como cambiar (debido a la forma de los token de or, and y not, que son kw)
	int sale = 0;
	
	if(sonIguales(i_d, "AND") == 1)
		sale = 15;
	if(sonIguales(i_d, "OR") == 1)
		sale = 16;
	if(sonIguales(i_d, "NOT") == 1)
		sale = 17;
	
	return sale;
}
//**********************************************************************
int esKeyword(char *str, TipoToken kw[]){ //se fija si str corresponde a algun keyword y devuelve la pos asociada o -1 en caso contrario
	int band = 1, i = 0, sale = -1, aux;
	
	aMayus(str, longiptr(str));		
	
	while((i < cantkw) && (band == 1)){		
		if((sonIguales(str,(kw[i].nombre)) == 1)){
					band = 0;
					sale = i;				
		}
		else{
			if((aux = esOpLog(str)) != 0){
				band = 0;
				sale = aux;
			}
		}		
		i++;							
	}	
	return sale;
}
//**********************************************************************
int avanzarComentario(FILE *fp, int *fila, int *col){// avanza hasta finalizar el comentario, devuelve 0 si no encuentra el fin }
int sale = 0;
char c;
c = fgetc(fp);
	while(1){
		if((c == EOF) || (sale == 1))
			break;
		else{
			switch(c){
				case '}':  sale = 1; //falta aumentar col??
						   *col = *col + 1;
						   break;	
				case '\t': *col = *col + 4;//ver de cambiar esto(la longitud de la tabulacion varia, ¿poner para que avance un solo lugar?)
						   c = fgetc(fp);
						   break;
				    		   
				case '\r': *fila = *fila + 2;// seguro 2?
						   c = fgetc(fp);
						   *col = 1;
						   break;
						   
				case '\n': *fila = *fila + 1;
						   c = fgetc(fp);
						   *col = 1;
						   break;
				
				default:   *col = *col + 1;
						   c = fgetc(fp);
						   break;
			}
		}
	}
return sale;
}	
//**********************************************************************
void obtenerId(FILE *fpp, char *ids, int *linea, int *col, char *c){
	int i=1, sale = 0;
	
	*c = fgetc(fpp);
	*col = *col + 1;
	
	while(1){	
		if(((*c >= 'a') && (*c <= 'z')) || ((*c >= 'A') && (*c <= 'Z')) || (*c == '_') || ((*c >= '0') && (*c <= '9')) ){
			*(ids + i) = *c;
			i++;
			*c = fgetc(fpp);
			*col = *col +1;
			if(i > tamaxid)
				errorLexico(3,*linea, (*col) -1);						
		}
		else{
			switch(*c){//cualquiera de estos caracteres indica el fin del identificador
				case ' ': 					  
				case ';': 						  
				case ',': 
				case '<':			
				case '>':
				case '=':
				case '+':
				case '-':
				case '*':
				case '/':
				case '(':
				case ')':
				case '.': 		  
				case ':': 									  					  
				case '\n': 						  
				case '\t':				  
				case '\r': 
						 sale = 1;
						 *(ids + i) = '\0';
						 break;					   
						  
				default: errorLexico(4,*linea,*col);// no -1
						 break;
				}						
		}		
	if(sale == 1)
		break;
	}//while
	
	//OJO CON ESTO
	fseek(fpp, -1, SEEK_CUR);
}
//**********************************************************************
void obtenerEntero(FILE *fpp, char *ent, int *linea, int *col, char *c){
int i = 1, sale = 0;

*c = fgetc(fpp);
*col = *col + 1;

while(1){
		if((*c >= '0') && (*c <= '9')){
			*(ent + i) = *c;
			i++;
			*c = fgetc(fpp);
			*col = *col +1;
				if(i > tamaxent)
					errorLexico(2, *linea,(*col) - 1);
					
		}
		else{
			switch(*c){
				case ' ': 					  
				case ';': 						  
				case ',': 
				case '<':			
				case '>':
				case '=':
				case '+':
				case '-':
				case '*':
				case '/':
				case '(':
				case ')':
				case '.': 		  
				case ':': 									  					  
				case '\n': 						  
				case '\t':				  
				case '\r': 
							sale = 1;
						    *(ent + i) = '\0';
						    break;					   
						  
				default: 
						if(((*c >= 'a') && (*c <= 'z')) || ((*c >= 'A') && (*c <= 'Z')) || (*c == '_'))	
							errorLexico(5,*linea,(*col));
						else 
							errorLexico(4,*linea,(*col));//no -1
						break;		
				}						
		}						   						  										
	if(sale == 1)
		break;
	}
fseek(fpp, -1, SEEK_CUR);
}
//**********************************************************************

int getToken(FILE *fp,TipoToken *tk, int *lineactual, int *columnactual){
						

(*tk).nombre = " ";
(*tk).valor = " ";	
int estadoComent, viejalinea, viejacol, posikw, sale = 1;
	
	actual = fgetc(fp);	
							
			if(actual == EOF){
				sale = -1;
			}			
			else{
							
			  while(1){
					  				  
				(*tk).nombre = " ";
				(*tk).valor = " ";    //agregado
				
				switch(actual){
					
					case '.': 
							  (*tk).nombre = "PUNTO";
							  (*tk).valor = "0";							  							  
							  (*columnactual)++;						
							  break;
							  
					case ';': 
							  (*tk).nombre = "PUNTOYCOMA";
							  (*tk).valor = "0";							
							  (*columnactual)++;							  
							  break;								  							
					case ':':	
								if((actual = fgetc(fp)) == '='){//obtengo el siguiente
									(*tk).nombre = "ASIGNACION";
									(*tk).valor = "0";												
									*columnactual = *columnactual + 2;
									break;
								}							
								else{
									(*tk).nombre = "DOSPUNTOS";
									(*tk).valor = "0";
									fseek(fp, -1, SEEK_CUR);
									(*columnactual)++;
									break;
								}					
					case ',': 
							  (*tk).nombre = "COMA";
							  (*tk).valor = "0";						  
							  (*columnactual)++;
							  break;						  
					case '(': 
							  (*tk).nombre = "PARENTABRE";
							  (*tk).valor = "0";							  
							  (*columnactual)++;
							  break;							  
					case ')': 
							  (*tk).nombre = "PARENTCIERRA";
							  (*tk).valor = "0";						  
							  (*columnactual)++;
							  break;							  
					case '+': 
							  (*tk).nombre = "OPARITMETICO";
							  (*tk).valor = "SUMA";							  					 
							  (*columnactual)++;
							  break;							  
					case '-': 
							  (*tk).nombre = "OPARITMETICO";
							  (*tk).valor = "RESTA";							  
							  (*columnactual)++;
							  break;							  
					case '*': 
							  (*tk).nombre = "OPARITMETICO";
							  (*tk).valor = "PRODUCTO";							  
							  (*columnactual)++;
							  break;							  
					case '/': 
							  (*tk).nombre = "OPARITMETICO";
							  (*tk).valor = "DIVISION";							  
							  (*columnactual)++;
							  break;							  
					case '=': 
							  (*tk).nombre = "OPRELACIONAL";
							  (*tk).valor = "EQ";							  
							  (*columnactual)++;
							  break;							  
					case '<':	
							  if((actual = fgetc(fp)) == '='){//obtengo el siguiente
									(*tk).nombre = "OPRELACIONAL";
									(*tk).valor = "LE";												
									*columnactual = *columnactual + 2;
									break;
								}	
								else{
									if(actual == '>'){
										(*tk).nombre = "OPRELACIONAL";
										(*tk).valor = "NE";												
										*columnactual = *columnactual + 2;
										break;											
									}
									else{
										(*tk).nombre = "OPRELACIONAL";
										(*tk).valor = "LT";
										fseek(fp, -1, SEEK_CUR);												
										(*columnactual)++;
										break;
									}
								}
					case '>':	
							  if((actual = fgetc(fp)) == '='){//obtengo el siguiente
									(*tk).nombre = "OPRELACIONAL";
									(*tk).valor = "GE";									
									*columnactual = *columnactual + 2;
									break;							
								}							
								else{//deberia ver q lo q sigue sea num??
									(*tk).nombre = "OPRELACIONAL";
									(*tk).valor = "GT";									
									fseek(fp, -1, SEEK_CUR);			
									(*columnactual)++;
									break;
								}								
					case '{':
							  viejalinea = *lineactual;
							  viejacol = *columnactual;							  
							  if((estadoComent = avanzarComentario(fp,lineactual,columnactual)) == 0){//debo enviar la direccion de fila y columna para ir modificandolos
								  errorLexico(1,viejalinea,viejacol);
							  }	
							  else{
								  actual = fgetc(fp);//consumio comentario, obtengo siguiente caracter
								  (*columnactual)++;//cuia				  
								  break;
							  }  				
					case '}':
							  //(*columnactual)--;//??
							  errorLexico(6,*lineactual,*columnactual);		 	
							  break;
					case ' ': 
							  actual = fgetc(fp);
							  (*columnactual)++;
							  break;				
					case '\t':
							  *columnactual = *columnactual + 4;//en mi maquina se mueve 4 blancos, depende de la implementación??
							  actual = fgetc(fp);
							  break;									
					case '\n': 
							  *lineactual = *lineactual + 1;
							  actual = fgetc(fp);
							  *columnactual = 1;
							  break;					
					case '\r': 
							  *lineactual = *lineactual + 2;//seguro 2?????????????????
							  actual = fgetc(fp);
							  *columnactual = 1;
							  break;					
					default:				
							  if(((actual >= 'a') && (actual <= 'z')) || ((actual >= 'A') && (actual <= 'Z')) ){
								  i_d[0] = actual;
								  obtenerId(fp,i_d,lineactual,columnactual,&actual);							 
								
									if((posikw = (esKeyword(i_d,keywords))) == -1){//es id, no es pal reservada
										(*tk).nombre = "ID";
										(*tk).valor = i_d;																 								 																	 
									}
									else{//es palabra reservada
										(*tk).nombre = keywords[posikw].nombre;									 
										(*tk).valor = keywords[posikw].valor;	 
									}
							     							  			 
							  }
							  else{ //encontre un entero o no
									if((actual >= '0') && (actual <= '9')){
										entero[0] = actual;
										obtenerEntero(fp,entero,lineactual,columnactual,&actual);
										(*tk).nombre = "ENTERO";
										(*tk).valor = entero;											
									}
									else
									  errorLexico(4,*lineactual,(*columnactual)); //no -1								
							  }
							  break;			
					}//switch
					
					if((sonIguales((*tk).nombre, " ") == 0) && (sonIguales((*tk).valor, " ") == 0) ){					
					sale = 1;												
					return sale;		
					}
					else
						sale = 0;
					
					
					if(actual == EOF){//como actual cambio vuelvo a preguntar
						sale = -1;//taba comentado
						break; //sale del while 1
					}		  
				
				  }//while
				}		
			return sale;									
}//analizar
	
