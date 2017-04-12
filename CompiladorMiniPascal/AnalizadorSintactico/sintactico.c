#include "sintactico.h"
#include "lexico.h"//lo incluyo tambien el el .h  ...


//deberia guardar token actual y token siguiente?...

int lineaactuall = -1, columnaactuall = -1;// vbles globales, aca o en .h?
//**********************************************************************
void errorSintactico(int nroError){
	switch(nroError){
	case 1:	printf("Error (1) sintáctico en la linea %d columna %d: Se espera el constructor 'PROGRAM'\n",lineaactuall,columnaactuall -1);
			break;
	case 2: printf("Error (2) sintáctico en la linea %d columna %d: Se espera un identificador\n",lineaactuall,columnaactuall - 1);
			break;
	case 3: printf("Error (3) sintáctico en la linea %d columna %d: Declaración de variables incompleta/incorrecta\n",lineaactuall,columnaactuall - 1);
			break;
	case 4:	printf("Error (4) sintáctico en la linea %d columna %d: Tipo de dato no válido, se espera el tipo 'BOOLEAN' o 'INTEGER'\n",lineaactuall,columnaactuall -1);
			break;
	case 5:	printf("Error (5) sintáctico en la linea %d columna %d: Se espera el caracter ';'\n",lineaactuall,columnaactuall -1);
			break;
	case 6:	printf("Error (6) sintáctico en la linea %d columna %d: Se espera el caracter '(' o bien ';'. Definición de procedimiento incorrecta\n",lineaactuall,columnaactuall -1);
			break;
	case 7:	printf("Error (7) sintáctico en la linea %d columna %d: Se espera el caracter '('\n",lineaactuall,columnaactuall - 1);
			break;
	case 8:	printf("Error (8) sintáctico en la linea %d columna %d: Se espera el caracter ')'\n",lineaactuall,columnaactuall - 1);
			break;
	case 9:	printf("Error (9) sintáctico en la linea %d columna %d: Se espera el caracter ':' o bien '('. Definición de función incorrecta.\n",lineaactuall,columnaactuall - 1);
			break;
	case 10: printf("Error (10) sintáctico en la linea %d columna %d: Fin de archivo inesperado. Archivo fuente incompleto\n",lineaactuall,columnaactuall - 1);
			 break;
	case 11: printf("Error (11) sintáctico en la linea %d columna %d: Se espera el constructor de inicio de cuerpo 'BEGIN'\n",lineaactuall,columnaactuall -1);
			 break;
	case 12: printf("Error (12) sintáctico en la linea %d columna %d: Se espera el caracter ':' o bien ','. Declaración de argumentos incorrecta.\n",lineaactuall,columnaactuall -1);
			 break;
	case 13: printf("Error (13) sintáctico en la linea %d columna %d: Se espera el constructor 'OF' correspondiente a la sentencia 'CASE'\n",lineaactuall,columnaactuall - 1);
			 break;
	case 14: printf("Error (14) sintáctico en la linea %d columna %d: Se espera el constructor de fin de cuerpo 'END'. Posible omisión de ';'\n",lineaactuall,columnaactuall - 1);
			 break;
	case 15: printf("Error (15) sintáctico en la linea %d columna %d: Se espera el constructor 'DO' correspondiente a la sentencia 'WHILE'\n",lineaactuall,columnaactuall - 1);
			 break;
	case 16: printf("Error (16) sintáctico en la linea %d columna %d: Se espera el caracter '.' luego del fin de cuerpo del programa principal\n",lineaactuall,columnaactuall -1);
			 break;
	case 17: printf("Error (17) sintáctico en la linea %d columna %d: La instrucción no corresponde a una sentencia válida del lenguaje\n",lineaactuall,columnaactuall -1);//sacar lo de posible omision..
			 break;
	case 18: printf("Error (18) sintáctico en la linea %d columna %d: Sentencia 'CASE' mal formada. Posible omisión de constructor 'END' o posible rótulo inválido (únicamente números enteros)\n",lineaactuall,columnaactuall -1);
			 break;
	case 19: printf("Error (19) sintáctico en la linea %d columna %d: Se espera el caracter ',' o bien ':'.  Rótulo de sentencia 'CASE' mal formado\n",lineaactuall,columnaactuall -1);
			 break;	 		 		 		 		 
	case 20: printf("Error (20) sintáctico en la linea %d columna %d: Se espera el constructor 'THEN' correspondiente a la sentencia 'IF'\n",lineaactuall,columnaactuall -1);
			 break;
	case 21: printf("Error (21) sintáctico en la linea %d columna %d: Expresión no válida\n",lineaactuall,columnaactuall -1);
			 break;
	//case 22: printf("Error (22) sintáctico en la linea %d columna %d: Sentencia alternativa mal formada. El constructor 'ELSE' es válido únicamente cuando la sentencia asociada al 'THEN' no finaliza en ';'\n",lineaactuall,columnaactuall -1);
	//		 break;

	default: ;
	}
exit(1);	
}
//**********************************************************************
void getTk(FILE *fp, TipoToken *tkn){
	if(getToken(fp,tkn,&lineaactuall,&columnaactuall) == -1)
		errorSintactico(10);
}
//**********************************************************************
int analisisSintactico(FILE *fp,TipoToken *tkn){
lineaactuall = 1; columnaactuall = 1;
	
	getTk(fp,tkn);
	reglaProgram(fp,tkn);
return 1;
}
//**********************************************************************	
int reglaProgram(FILE *fp,TipoToken *tkn){ 
int band = 1;

	if(sonIguales((*tkn).nombre,"PROGRAM") == 1){
		getTk(fp,tkn);
		if(sonIguales((*tkn).nombre,"ID") != 1 )
			errorSintactico(2);
		else{	
			getTk(fp,tkn);
			if(sonIguales((*tkn).nombre,"PUNTOYCOMA") != 1)
				errorSintactico(5);
			else{
				getTk(fp,tkn);
				reglaDefVar(fp,tkn);
				
				while (band == 1){		
					band = reglaDefProcFun(fp,tkn);
				}	
				 	
				reglaCuerpo(fp,tkn);				
				getTk(fp,tkn);
				if(sonIguales((*tkn).nombre,"PUNTO") != 1)//verifico que termina con punto. ie, desp del último end
					errorSintactico(16);			
			}		
		}
	}
	else
		errorSintactico(1);		
return 1;		
}
//**********************************************************************
int reglaDefVar(FILE *fp,TipoToken *tkn){
		
	if(sonIguales((*tkn).nombre,"VAR") == 1){//recordar que puerde haber o no definicion de variables
		
eti1:	getTk(fp,tkn);
		if(sonIguales((*tkn).nombre,"ID") != 1)
			errorSintactico(2); 
							 		
eti2:	getTk(fp,tkn);
				
		if(sonIguales((*tkn).nombre,"DOSPUNTOS") == 1){			
			reglaTipoDato(fp,tkn);
			getTk(fp,tkn);									
			if(sonIguales((*tkn).nombre,"PUNTOYCOMA") != 1)
				errorSintactico(5);//seria 3 en vez de 5 ..
						
		getTk(fp,tkn);				
		if(sonIguales((*tkn).nombre,"ID") == 1) //continua declaracion de otra variable de tipo de dato distinto
			goto eti2;
					//si no es ID sigue otra cosa, sale y se retorna a dond se llamo a este proc																
		}
		else{//si no es ':' es ','
			if(sonIguales((*tkn).nombre,"COMA") == 1)
				goto eti1;
			else
				errorSintactico(3);			
		}	
	}//llamo al siguiente método tanto como si hubo definición de variables como si no
return 1;
}
//********************************************************************** 
int reglaDefProcFun(FILE *fp,TipoToken *tkn){ // de que otra forma sino.. (fc y pr deberian verificarse dentro de sus proc respectivamente?), de ultima modificar la gramatica :)
int sale = 1;	
	if(sonIguales((*tkn).nombre,"FUNCTION") == 1)
		reglaFunc(fp,tkn);			
	else{	
		if(sonIguales((*tkn).nombre,"PROCEDURE") == 1)
			reglaProc(fp,tkn);
		else
			sale = -1;			
	}
//si no hay definiciones de procs o funcs sigo llamando
return sale;	
}
//**********************************************************************
int reglaProc(FILE *fp, TipoToken *tkn){
int	band = 1;
			
	getTk(fp,tkn);
	if(sonIguales((*tkn).nombre,"ID") != 1)
		errorSintactico(2);
			
	getTk(fp,tkn);		
		if(sonIguales((*tkn).nombre,"PUNTOYCOMA") == 1) //no hay argumentos, sigue def de var (si la hay)
			getTk(fp,tkn); //vanza aca y en el else, convendria hacerlo una solavez afuera..					
				
		else{//sino sale del if y continua con la cadena de llamados	
			if(sonIguales((*tkn).nombre,"PARENTABRE") == 1){//el proc tiene argumentos
				reglaArg(fp,tkn);
				if(sonIguales((*tkn).nombre,"PARENTCIERRA") == 1){
					getTk(fp,tkn);
					if(sonIguales((*tkn).nombre,"PUNTOYCOMA") != 1)
						errorSintactico(5);// antes era 6
						
				getTk(fp,tkn);				
				}
				else
					errorSintactico(8);	//podria ser 12 (def arg inco)				
			}			
			else//si desp del id del subp no hay ';' ni '('
				errorSintactico(6);					 
		}						
	reglaDefVar(fp,tkn);
		while (band == 1){		
			band = reglaDefProcFun(fp,tkn);
		}
	reglaCuerpo(fp,tkn);//obtener tkns??	
	getTk(fp,tkn);
	if(sonIguales((*tkn).nombre,"PUNTOYCOMA") != 1)
		errorSintactico(5);
		
getTk(fp,tkn);										
return 1;
}
//**********************************************************************
int reglaFunc(FILE *fp,TipoToken *tkn){
int band = 1;
			
	getTk(fp,tkn);
	if(sonIguales((*tkn).nombre,"ID") != 1)
		errorSintactico(2);
				
	getTk(fp,tkn);		
		if(sonIguales((*tkn).nombre,"PARENTABRE") == 1){//si hay '(' entonces hay argumentos
			reglaArg(fp,tkn);
			if(sonIguales((*tkn).nombre,"PARENTCIERRA") != 1)					
				errorSintactico(8);
					
		getTk(fp,tkn);							
		}//no else, no tiene argumentos la func. ej: function f1:boolean;	 
		
		if(sonIguales((*tkn).nombre,"DOSPUNTOS") == 1){	
			reglaTipoDato(fp,tkn);
			getTk(fp,tkn);
			if(sonIguales((*tkn).nombre,"PUNTOYCOMA") != 1)
				errorSintactico(5);
					
		getTk(fp,tkn);			
		}
		else
			errorSintactico(9); //es eñ unico lugar donde tira error 9.. ver. (se espera :)
				
	reglaDefVar(fp,tkn);
	while (band == 1){		
		band = reglaDefProcFun(fp,tkn);
	}
	reglaCuerpo(fp,tkn);
	getTk(fp,tkn);
	
	if(sonIguales((*tkn).nombre,"PUNTOYCOMA") != 1)
		errorSintactico(5);	
				
getTk(fp,tkn);										
return 1;
}
//**********************************************************************
int reglaArg(FILE *fp,TipoToken *tkn){

et1: getTk(fp,tkn);
	 if(sonIguales((*tkn).nombre,"ID") != 1)
		errorSintactico(2);
	
	getTk(fp,tkn);
		
	if(sonIguales((*tkn).nombre,"DOSPUNTOS") == 1){			
		reglaTipoDato(fp,tkn);									
	
	getTk(fp,tkn);
					
		if(sonIguales((*tkn).nombre,"PUNTOYCOMA") == 1)//sigue otro parametros.(q deberia ser de otro tipodedato, checkear en el a.semantico..)
			goto et1;
		//si no es PUNTOYCOMA entoces luego deberia seguir el parentesis que cierra de function, se controla desp de retornar																	
	}
	else{//si no es ':' es ','
		if(sonIguales((*tkn).nombre,"COMA") == 1)
			goto et1;
			
		else
			errorSintactico(12);			
	}	
return 1;
}
//**********************************************************************
int reglaCuerpo(FILE *fp,TipoToken *tkn){
	
	if(sonIguales((*tkn).nombre,"BEGIN") == 1){ 
		getTk(fp,tkn);		
otra:	reglaSentencia(fp,tkn);
		//a la vuelta. preguntar si hay punto y coma, si hay volver a llamar a reglaSentenci		
		 if(sonIguales((*tkn).nombre,"PUNTOYCOMA") == 1){//si hay ';' quiere decir q sigue otra sentencia.
			getTk(fp,tkn);	
			goto otra;		
		}	
		else{//si no hay ';' al final de la sent entonces debe seguir el END
			if(sonIguales((*tkn).nombre,"END") != 1) //ver el tema de en que columna muestra el error.. al final del tkn q encontro.. hacer para q sea al inicio?habria q retroceder
				errorSintactico(14);	
		}
	}
	else
		errorSintactico(11);
		
return 1;
}
//**********************************************************************
int reglaParamAct(FILE *fp, TipoToken *tkn){ //  <expresion> { , <expresion> }
	
getTk(fp,tkn);

	if(sonIguales((*tkn).nombre,"PARENTCIERRA") != 1){//la 1ra vez, por si no tiene args			
act:	reglaExpresion(fp,tkn);
        
		if(sonIguales((*tkn).nombre,"COMA") == 1){
			getTk(fp,tkn);										
			goto act;	
		}//poner algun tipo de error???????		
	}
return 1;	
}

//**********************************************************************
int reglaSentencia(FILE *fp,TipoToken *tkn){
	//<sentencia> → <asignacion>|<llamada-proc>|<repetitiva>|<alternativa>|<alternativa-mult>|<cuerpo>
		
	if(sonIguales((*tkn).nombre,"WHILE") == 1)	
		reglaWhile(fp,tkn);
	else{
		if(sonIguales((*tkn).nombre,"IF") == 1)
			reglaIf(fp,tkn);
		else{
			if(sonIguales((*tkn).nombre,"CASE") == 1)
				reglaCase(fp,tkn);
			else{		
				if(sonIguales((*tkn).nombre,"BEGIN") == 1){
					reglaCuerpo(fp,tkn);
					getTk(fp,tkn);
				}	
				else{			
					if(sonIguales((*tkn).nombre,"ID") == 1){//analizo los toksiguientes
						getTk(fp,tkn);
				
						if(sonIguales((*tkn).nombre,"ASIGNACION") == 1)
							reglaAsignac(fp,tkn);// se ve el lado derecho de la asig
		
						else{// si hay parent que abre deberia retroceder un token y llamar a llamadaSubp?? como se cuanto retroceder con el fseek despues..
							if(sonIguales((*tkn).nombre,"PARENTABRE") == 1){// " id (... " indica q es una llamada a un subpro con parametros
								reglaParamAct(fp,tkn);//mm
							
								if(sonIguales((*tkn).nombre,"PARENTCIERRA") != 1)//a la vuelta
									errorSintactico(8);
								else//avanzo uno mas desp del ')' antes de retornar
									getTk(fp,tkn);																										
							}//ojo cn el else de este(AGREGADO, PROBAR CUAANDO ENTRA ACA, EJEMPLOS)	
							else								
								errorSintactico(17);
							
						}		
		//	printf("desp q leyo el id de regla sentencia, se retorna con el token: ");						
		//	imprimeToken(*tkn);
					}//sino es id puede ser succ, pred, read o write . . NO, ESTO ESTA CONTEMPLADO EN LLAMADASUBPR CAMBIAR!
					else{
						if(sonIguales((*tkn).nombre,"SUCC") == 1)
							reglaSucesor(fp,tkn);
						else{	
							if(sonIguales((*tkn).nombre,"PRED") == 1)
								reglaPredecesor(fp,tkn);
							else{
								if(sonIguales((*tkn).nombre,"READ") == 1)
									reglaLeer(fp,tkn);
								else{
									if(sonIguales((*tkn).nombre,"WRITE") == 1)
										reglaEscribir(fp,tkn);
									else
										errorSintactico(17);//sentencia no válida..ver tipo de error
									
								}
							}
						}
					}
					
				}
			}
		}
	}


//avanzar un token antes de retornar ?
return 1;
}
//**********************************************************************
int reglaAlter(FILE *fp,TipoToken *tkn){//alter> → λ | else <sentencia>
	if(sonIguales((*tkn).nombre,"ELSE") == 1){
		getTk(fp,tkn);			
		reglaSentencia(fp,tkn);//este ya adelanta 1			
	}
	/*else{
		if(sonIguales((*tkn).nombre,"PUNTOYCOMA") != 1)
			errorSintactico(22);
		
		getTk(fp,tkn);
		if(sonIguales((*tkn).nombre,"ELSE") == 1)
			errorSintactico(22);	
	}*/	
return 1;	
}
//**********************************************************************
int reglaIf(FILE *fp,TipoToken *tkn){//<alternativa> → if <expresion> then <sentencia>  <alter>

getTk(fp,tkn);
reglaExpresion(fp,tkn);

	if(sonIguales((*tkn).nombre,"THEN") != 1)
		errorSintactico(20);
	
getTk(fp,tkn);	
reglaSentencia(fp,tkn);
reglaAlter(fp,tkn);
//getTk(fp,tkn);	//ojo con este
return 1;
}
//**********************************************************************
int reglaAsignac(FILE *fp,TipoToken *tkn){//se fija el lado derecho de la asig, lo anterior se comprobo en reglasentencia
 
	getTk(fp,tkn);
	reglaExpresion(fp,tkn);//si se retorna sin error, todo ok
			
return 1;
}
//**********************************************************************
int reglaExpresion(FILE *fp,TipoToken *tkn){//<expresion>	→	<exp> |  <exp> <op1> <exp>
					//factorizar? <expresion> ---> <exp><expii>       <expii> --->  λ | <op1> <exp>
	reglaExp(fp,tkn);
	if(reglaOp1(fp,tkn) == 1){//mmm.. avanzar tk antes?
		getTk(fp,tkn);
		reglaExp(fp,tkn);
	}		
return 1;
}
//**********************************************************************
int reglaExp(FILE *fp,TipoToken *tkn){//<exp> → <termino> <expree>
	
	reglaTermino(fp,tkn);
	reglaExpree(fp,tkn);

return 1;
}
//**********************************************************************
int reglaTermino(FILE *fp,TipoToken *tkn){//<termino> → <factor> <termii>
	
	reglaFactor(fp,tkn);	
	reglaTermii(fp,tkn);

return 1;
}
//**********************************************************************
int reglaExpree(FILE *fp,TipoToken *tkn){//<expree> →	<op2> <termino> <expree> | λ
	//avanzar?..reee
	if(reglaOp2(fp,tkn) == 1){		
		getTk(fp,tkn);		
		reglaTermino(fp,tkn);
		reglaExpree(fp,tkn);
	}
return 1;	
}
//**********************************************************************
int reglaFactor(FILE *fp,TipoToken *tkn){
//<factor>→(<expresion>)|not <factor>|<constante>|<identificador>|<entero>|-<factor>|<llamada-func>		
int sale = -1;
	
	if(sonIguales((*tkn).nombre,"PARENTABRE") == 1){
		getTk(fp,tkn);	
		reglaExpresion(fp,tkn);
		
		if(sonIguales((*tkn).nombre,"PARENTCIERRA") != 1)
			errorSintactico(8);
			
	getTk(fp,tkn);	
	sale = 1;
	}
	else{		
		if((sonIguales((*tkn).nombre,"OPLOGICO") == 1) && (sonIguales((*tkn).valor,"NOT") == 1)){
			getTk(fp,tkn);	
			reglaFactor(fp,tkn); //ver esto
			sale = 1;
		}
		else{
			if((sonIguales((*tkn).nombre,"TRUE") == 1) || (sonIguales((*tkn).nombre,"FALSE") == 1) || (sonIguales((*tkn).nombre,"MAXINT") == 1)){//ver.. hacer metodo esConstante?
				sale = 1;
				getTk(fp,tkn); 
			}	
			else{
				if(sonIguales((*tkn).nombre,"ENTERO") == 1){
					sale = 1;
					getTk(fp,tkn); 
				}
				else{
					if((sonIguales((*tkn).nombre,"OPARITMETICO") == 1) && (sonIguales((*tkn).nombre,"RESTA") == 1)){
						getTk(fp,tkn);				
						reglaFactor(fp,tkn);
						sale = 1;
					}
					else{
						/*if(sonIguales((*tkn).nombre, "ID") == 1){// puede ser una variable o una llamada a func ( Y SUC Y PRED?)
							getTk(fp,tkn);
							
							if(sonIguales((*tkn).nombre, "PARENTABRE") == 1){		
								reglaParamAct(fp,tkn);
							
								if(sonIguales((*tkn).nombre,"PARENTCIERRA") != 1)
									errorSintactico(8);//ver
							
							getTk(fp,tkn);	
							}					
							//else era vble
						}
						else
							errorSintactico(21);*/
						reglallamadaFunc(fp,tkn);
						
					} //hacer que en todos los casos se avance el tkn antes d retornar?.. en llamd func avanza si o si
				}
			}
		}
	}
return sale;	
}
//**********************************************************************
int reglaTermii(FILE *fp,TipoToken *tkn){//<termiii> →	<op3> <factor> <termii> | λ
	
	if(reglaOp3(fp,tkn) == 1){
		getTk(fp,tkn);
		reglaFactor(fp,tkn);
		reglaTermii(fp,tkn);
	}
return 1;
}
//**********************************************************************
int reglaConstante(FILE *fp,TipoToken *tkn){
int sale = -1;	

	if((sonIguales((*tkn).nombre,"TRUE") == 1) || (sonIguales((*tkn).nombre,"FALSE") == 1) || (sonIguales((*tkn).nombre,"MAXINT") == 1))
		sale = 1;

return sale;	
}
//**********************************************************************
int reglaOp1(FILE *fp,TipoToken *tkn){
int sale = -1;
	
	if(sonIguales((*tkn).nombre,"OPRELACIONAL") == 1)
		sale = 1;

return sale;
}
//**********************************************************************
int reglaOp2(FILE *fp,TipoToken *tkn){// +, -, or
int sale = -1;

	if(sonIguales((*tkn).nombre,"OPARITMETICO") == 1){
		if((sonIguales((*tkn).valor,"SUMA") == 1 ) || (sonIguales((*tkn).valor,"RESTA") == 1 ))
			sale = 1;
	}
	else{	
		if((sonIguales((*tkn).nombre,"OPLOGICO") == 1) && (sonIguales((*tkn).valor,"OR") == 1))
			sale = 1;
	}
return sale;
}
//**********************************************************************
int reglaOp3(FILE *fp,TipoToken *tkn){// *, /, and
int sale = -1;

	if(sonIguales((*tkn).nombre,"OPARITMETICO") == 1){
		if((sonIguales((*tkn).valor,"PRODUCTO") == 1) || (sonIguales((*tkn).valor,"DIVISION") == 1))
			sale = 1;
	}
	else{
		if((sonIguales((*tkn).nombre,"OPLOGICO") == 1) && (sonIguales((*tkn).valor,"AND") == 1))
			sale = 1;
	}	
return sale;
}
//**********************************************************************
int reglallamadaFunc(FILE *fp,TipoToken *tkn){
int sale = 1;
	
	if(sonIguales((*tkn).nombre,"SUCC") == 1)
		reglaSucesor(fp,tkn);
	
	else{
		if(sonIguales((*tkn).nombre,"PRED") == 1)
			reglaPredecesor(fp,tkn);
		else{
			if(sonIguales((*tkn).nombre,"ID") == 1){//Deberia buscar en la tabla de simbolos y consultar?
				getTk(fp,tkn);// VER. aca avance un tkn de mas. ver q pasa al retornar en. expr, termii , etc

				if(sonIguales((*tkn).nombre,"PARENTABRE") == 1){//es llamada a func(o proc?, semantic-check). 
					reglaParamAct(fp,tkn);
					
					if(sonIguales((*tkn).nombre,"PARENTCIERRA") != 1)
						errorSintactico(8);//podria ser parm act mal formados, nuevo error
						
				getTk(fp,tkn);//esto lo agregue hace poco. cuidado										
				}		
				//else //desp del id tiene q ir si o si, tenga o no argumentos, '(' (NO!, y si es variable.. recordar q desde factor se llama a esta)
					//errorSintactico(7);				
			}
			else
				errorSintactico(21);//ver..
		}
	}
return sale;
}
//**********************************************************************
int reglallamadaProc(FILE *fp,TipoToken *tkn){//no lo llamo. arreglar
int sale = 1;

	if(sonIguales((*tkn).nombre,"READ") == 1)
		reglaLeer(fp,tkn);
	else{
		if(sonIguales((*tkn).nombre,"WRITE") == 1)
			reglaEscribir(fp,tkn);
		else{
			if(sonIguales((*tkn).nombre,"ID") == 1){
				getTk(fp,tkn);
			
				if(sonIguales((*tkn).nombre,"PARENTABRE") == 1){
					reglaParamAct(fp,tkn);
						
					if(sonIguales((*tkn).nombre,"PARENTCIERRA") != 1)
						errorSintactico(8);//ver
							
				getTk(fp,tkn);						
				}
					else
						errorSintactico(7);	
				}
				else
					sale = -1;		//errorSintactico(23);//ver que poner...	
		}
	}
return sale;
}
//**********************************************************************
int reglaWhile(FILE *fp,TipoToken *tkn){ //while <expresion> do <sentencia>  
	
	getTk(fp,tkn);
	reglaExpresion(fp,tkn);
		
	if(sonIguales((*tkn).nombre,"DO") != 1)//osea que no devuelve -1 WTAF (== -1 retorna false)
		errorSintactico(15);	
		
	getTk(fp,tkn);
	reglaSentencia(fp,tkn);
	
	//if(sonIguales((*tkn).nombre,"PUNTOYCOMA") != 1)
	//	errorSintactico(5); //se espera ';'		

//getTk(fp,tkn);	
return 1;	
}
//**********************************************************************
int reglaRotulo(FILE *fp,TipoToken *tkn){ // <entero> { , <entero> } : <sentencia> ;
	
otroNu:	if(sonIguales((*tkn).nombre,"ENTERO") != 1)
			errorSintactico(18);//se espera nro entero
			
		getTk(fp,tkn);	
	
		if(sonIguales((*tkn).nombre,"COMA") == 1){
			getTk(fp,tkn);		
			goto otroNu;
		}		
		if(sonIguales((*tkn).nombre,"DOSPUNTOS") == 1){
			getTk(fp,tkn);			 
			reglaSentencia(fp,tkn);//a la vuelta pregunto a ver si termina en ';'
			
			if(sonIguales((*tkn).nombre,"PUNTOYCOMA") != 1)
				errorSintactico(5);//se espera ';'
		}
		else
			errorSintactico(19);//desp del entero no habia ni ',' ni ':'
	
getTk(fp,tkn);
return 1;	
}
//**********************************************************************
int reglaCase(FILE *fp,TipoToken *tkn){ //case <id> of <rotulo> { <rotulo> } [else <sentencia>;] end

	getTk(fp,tkn);		
	
	if(sonIguales((*tkn).nombre,"ID") != 1)
		errorSintactico(2);
	
	getTk(fp,tkn);	
	
	if(sonIguales((*tkn).nombre,"OF") != 1)
		errorSintactico(13);	
	
	getTk(fp,tkn);
	
otroRo:	reglaRotulo(fp,tkn);
	
		if(sonIguales((*tkn).nombre,"ENTERO") == 1)
			goto otroRo;
	    
	    if(sonIguales((*tkn).nombre,"ELSE") == 1){ //AGREGADOO
			getTk(fp,tkn);
			reglaSentencia(fp,tkn);
			if(sonIguales((*tkn).nombre,"PUNTOYCOMA") != 1)
				errorSintactico(5);//se espera ';'
		
		getTk(fp,tkn);
		}
	    
		if((sonIguales((*tkn).nombre,"END") != 1))
			errorSintactico(18);//se espera 'END' correspondiente a la sentencia 'CASE'
		
getTk(fp,tkn);			
return 1;
}
//**********************************************************************
int reglaTipoDato(FILE *fp, TipoToken *tkn){
int sale;
	
	getTk(fp,tkn);
		
	if((sonIguales((*tkn).nombre,"BOOLEAN") == 1) || (sonIguales((*tkn).nombre,"INTEGER") == 1))
		sale = 1;
	else
		errorSintactico(4);
		
return sale;		
}
//**********************************************************************
int reglaSucesor(FILE *fp, TipoToken *tkn){

	getTk(fp,tkn);
	if(sonIguales((*tkn).nombre,"PARENTABRE") != 1)
		errorSintactico(7);
	
	getTk(fp,tkn);
	reglaExpresion(fp,tkn);
	
	if(sonIguales((*tkn).nombre,"PARENTCIERRA") != 1)
		errorSintactico(8);
	
getTk(fp,tkn);	
return 1;//hacer que devuelva el valor de la expresión + 1	??
}
//**********************************************************************
int reglaPredecesor(FILE *fp, TipoToken *tkn){
		
	getTk(fp,tkn);
	if(sonIguales((*tkn).nombre,"PARENTABRE") != 1)
		errorSintactico(7);	
	
	getTk(fp,tkn);		
	reglaExpresion(fp,tkn);	
	
	if(sonIguales((*tkn).nombre,"PARENTCIERRA") != 1)
		errorSintactico(8);
	
getTk(fp,tkn);
return 1;//hacer que devuelva el valor de la expresión - 1	??
}
//**********************************************************************
int reglaLeer(FILE *fp, TipoToken *tkn){

	getTk(fp,tkn);
	if(sonIguales((*tkn).nombre,"PARENTABRE") != 1)
		errorSintactico(7);
	
	getTk(fp,tkn);
	if(sonIguales((*tkn).nombre,"ID") != 1)
		errorSintactico(2);//se omite id del arg
	
	getTk(fp,tkn);
	if(sonIguales((*tkn).nombre,"PARENTCIERRA") != 1)
		errorSintactico(8);
	
getTk(fp,tkn);
return 1;
}
//**********************************************************************
int reglaEscribir(FILE *fp, TipoToken *tkn){

	getTk(fp,tkn);
	if(sonIguales((*tkn).nombre,"PARENTABRE") != 1)
		errorSintactico(7);
	
	getTk(fp,tkn);	
	reglaExpresion(fp,tkn);
	
	if(sonIguales((*tkn).nombre,"PARENTCIERRA") != 1)
		errorSintactico(8);

getTk(fp,tkn);
return 1;//...
}
