#include "sintactico.h"
#include "lexico.h"//lo incluyo tambien el el .h  ...
#include "semantico.h"
#include "TablaDeSimbolos.h"

//deberia guardar token actual y token siguiente?...

int lineaactuall = -1, columnaactuall = -1, nivel = 0, tot = 0, tat = 0;// vbles globales, aca o en .h?
char *variables[maxVars], *paramFor[maxArgs],*tdArgs[maxArgs], *parAct[maxArgs], *tdAct[maxArgs]; //antes tenia el 10 como tamaño dirctamente
FILE *fpss;
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

//fpss = fopen("t_s.txt","w");
	
	getTk(fp,tkn);
	reglaProgram(fp,tkn);
return 1;
}
//**********************************************************************	
int reglaProgram(FILE *fp,TipoToken *tkn){ 
char *str;
int band =1;
Ambiente *env;

	if(sonIguales((*tkn).nombre,"PROGRAM") == 1){
		getTk(fp,tkn);
		if(sonIguales((*tkn).nombre,"ID") != 1 )
			errorSintactico(2);
		else{
			str = crearStr((*tkn).valor);
			env = crearAmbiente(str, 0, NULL);
				
			getTk(fp,tkn);
			if(sonIguales((*tkn).nombre,"PUNTOYCOMA") != 1)
				errorSintactico(5);
			else{
				getTk(fp,tkn);
				
				reglaDefVar(fp,tkn,env); 			//le paso el ambiente como parametro?		
				
				while (band == 1){		
					band = reglaDefProcFun(fp,tkn,env);//ta bien le paso el mismo ambiente a los subpr de igual nivel
				}		
				reglaCuerpo(fp,tkn,env);				
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
int reglaDefVar(FILE *fp,TipoToken *tkn, Ambiente *env){ //HACER PARA Q NO HAYA IDS REPETIDOS EN UNA DEFINICION LOCAL
ItemTs *itm;
int j;
char *td;
int cantiVar = 0;
//FILE *fps;	
//fps = fopen("t_s.txt","w");

vaciarVariables(variables);//cuando puedas, sacar esto y crear un array de nombres. sacar la vble global
	
	if(sonIguales((*tkn).nombre,"VAR") == 1){//recordar que puerde haber o no definicion de variables
		
eti1:	getTk(fp,tkn);
		if(sonIguales((*tkn).nombre,"ID") != 1)
			errorSintactico(2); 
		
		variables[tot] = crearStr((*tkn).valor);
			if(existeLocal(variables[tot], env) == 1)//ya existe una variable en la definicion local con ese nombre			
				errorSemantico(3,lineaactuall,columnaactuall,NULL,variables[tot]);
				
		itm = crearItem(variables[tot], 1, NULL, (*env).lvl, cantiVar, NULL, '-', 0, NULL);
		tot++;		    
		insertar(itm, env);
		cantiVar++; // --
							 		
eti2:	getTk(fp,tkn);
				
		if(sonIguales((*tkn).nombre,"DOSPUNTOS") == 1){
			
			reglaTipoDato(fp,tkn);		
			td = crearStr((*tkn).nombre);		
											
			getTk(fp,tkn);									
			if(sonIguales((*tkn).nombre,"PUNTOYCOMA") != 1)
				errorSintactico(5);//seria 3 en vez de 5 ..
				
			for(j=0;j<tot;j++){ 
				setearTD(variables[j], td, env); //ojo con este metodo
			}
			tot = 0;									
						
		getTk(fp,tkn);				
			if(sonIguales((*tkn).nombre,"ID") == 1){ //continua declaracion de otra variable de tipo de dato distinto
				
				variables[tot] = crearStr((*tkn).valor);
				  if(existeLocal(variables[tot], env) == 1)//ya existe una variable en la definicion local con ese nombre			
				    errorSemantico(3,lineaactuall,columnaactuall,NULL,variables[tot]);
				
				itm = crearItem(variables[tot], 1, NULL, (*env).lvl, cantiVar, NULL, '-', 0, NULL);
				tot++;
				insertar(itm, env);	
				cantiVar++;
				
				goto eti2;
						//si no es ID sigue otra cosa, sale y se retorna a dond se llamo a este proc																
			}
		}
		else{//si no es ':' es ','
			if(sonIguales((*tkn).nombre,"COMA") == 1)
				goto eti1;
			else
				errorSintactico(3);			
		}	
	}//llamo al siguiente método tanto como si hubo definición de variables como si no
	
//tablaToFile(fps,env);//pls god	
return 1;
}
//********************************************************************** 
int reglaDefProcFun(FILE *fp,TipoToken *tkn, Ambiente *env){ // de que otra forma sino.. (fc y pr deberian verificarse dentro de sus proc respectivamente?), de ultima modificar la gramatica :)
int sale = 1;	
	if(sonIguales((*tkn).nombre,"FUNCTION") == 1)
		reglaFunc(fp,tkn, env);			
	else{	
		if(sonIguales((*tkn).nombre,"PROCEDURE") == 1)
			reglaProc(fp,tkn,env);
		else
			sale = -1;			
	}
//si no hay definiciones de procs o funcs sigo llamando
return sale;	
}
//**********************************************************************
int reglaProc(FILE *fp, TipoToken *tkn,Ambiente *envPadre){//env seria el padre
int	band = 1, cantii;
ItemTs *itm;	
char *str, **tdaa; //en tda se van a poner los td de los parfor
Ambiente *env;

//FILE *fps;	 //desp sacar esto
//fps = fopen("t_s.txt","w");
		
	getTk(fp,tkn);
	if(sonIguales((*tkn).nombre,"ID") != 1)
		errorSintactico(2);
													//chequear que no este en uso el id???
		str = crearStr((*tkn).valor);
		if(existeLocal(str,envPadre) == 1) // el pdre tiene definido un elto con el mismo id, otro proc o fun..
		  errorSemantico(3,lineaactuall,columnaactuall,NULL,str);
		
		env = crearAmbiente(str, ((*envPadre).lvl) + 1, envPadre);	
		itm = crearItem(str, proc, NULL, (*env).lvl, 0, NULL, '-', 0, NULL);//creo el ambiente e inserto el nombre del proc en su ts (o en la del padre? o en ambas?)..
		insertar(itm, env);//en si mismo? par q no utilize el nombre dentro como var.. en func para asignar el retorno :)
		insertar(itm, envPadre);//para q pueda ser invocado desde el padre
			
	getTk(fp,tkn);		
		if(sonIguales((*tkn).nombre,"PUNTOYCOMA") == 1) //no hay argumentos, sigue def de var (si la hay)
			getTk(fp,tkn); //vanza aca y en el else, convendria hacerlo una solavez afuera..					
				
		else{//sino sale del if y continua con la cadena de llamados	
			if(sonIguales((*tkn).nombre,"PARENTABRE") == 1){//el proc tiene argumentos
				
				tdaa = crearArrayTD();		
							
				cantii = reglaArg(fp,tkn,env,tdaa);//bingo err16, p2 aca violacion d segmento		
																		
				setCantyTiposArgs(env,str,tdaa,cantii);//	SETEAR ACA LOS TDARGS Y LA CANTI				
				
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
	reglaDefVar(fp,tkn,env);
		while (band == 1){		
			band = reglaDefProcFun(fp,tkn,env);
		}	
	
	reglaCuerpo(fp,tkn,env);//obtener tkns??		
	
	getTk(fp,tkn);
	if(sonIguales((*tkn).nombre,"PUNTOYCOMA") != 1)
		errorSintactico(5);
		
getTk(fp,tkn);

//PROBAR ESTO, HACER UN TOFILE seria solamente del ambiente este
//tablaToFile(fps,env);									
return 1;
}
//**********************************************************************
int reglaFunc(FILE *fp,TipoToken *tkn,Ambiente *envPadre){
int band = 1, cantii = 0;
ItemTs *itm;	
char *str, *tdretorno, **tdaa;
Ambiente *env;

//FILE *fps;	//desp sacar esto
//fps = fopen("t_s.txt","w");	
			
	getTk(fp,tkn);
	if(sonIguales((*tkn).nombre,"ID") != 1)
		errorSintactico(2);
		
		str = crearStr((*tkn).valor);
										// CON PADRE O ACTUAL?????????????????
		if(existeLocal(str,envPadre) == 1) // el pdre tiene definido un elto con el mismo id, otro proc o fun..
		  errorSemantico(3,lineaactuall,columnaactuall,NULL,str);
		
		env = crearAmbiente(str, ((*envPadre).lvl) + 1, envPadre);	
		itm = crearItem(str, func, NULL, (*env).lvl, 0, NULL, 'N', 0, NULL);//todavia nose su tipo ni sus args. N q no esta asignado
		insertar(itm, env);//en si mismo para asignar el retorno :)
		insertar(itm, envPadre);//para q pueda ser invocado desde el padre	
		
		
				
	getTk(fp,tkn);		
		if(sonIguales((*tkn).nombre,"PARENTABRE") == 1){//si hay '(' entonces hay argumentos
			
			tdaa = crearArrayTD();
			cantii = reglaArg(fp,tkn,env,tdaa);
			setCantyTiposArgs(env,str,tdaa,cantii); //DEBERIA SETEAR ESTO AFUERA, Q PASA SI NO HAY ARG, NO HAY '('
			
			if(sonIguales((*tkn).nombre,"PARENTCIERRA") != 1)					
				errorSintactico(8);
					
		getTk(fp,tkn);							
		}//no else, no tiene argumentos la func. ej: function f1:boolean;	 
		
		if(sonIguales((*tkn).nombre,"DOSPUNTOS") == 1){	
			reglaTipoDato(fp,tkn);
			tdretorno = crearStr((*tkn).nombre);
			setearTD((*env).name, tdretorno, env);
			
			getTk(fp,tkn);
			if(sonIguales((*tkn).nombre,"PUNTOYCOMA") != 1)
				errorSintactico(5);
					
		getTk(fp,tkn);			
		}
		else
			errorSintactico(9); //es eñ unico lugar donde tira error 9.. ver. (se espera :)
				
	reglaDefVar(fp,tkn,env);
	while (band == 1){		
		band = reglaDefProcFun(fp,tkn,env);
	}
	reglaCuerpo(fp,tkn,env);
	getTk(fp,tkn);
	
	if(sonIguales((*tkn).nombre,"PUNTOYCOMA") != 1)
		errorSintactico(5);	
	
	checkRetornoFunc((*env).name, lineaactuall, columnaactuall, env);
	
//tablaToFile(fps,env); //desp sacar
getTk(fp,tkn);	
									
return 1;
}
//**********************************************************************
int reglaArg(FILE *fp,TipoToken *tkn,Ambiente *env, char **tda){
char *tdarg, *str;
ItemTs *itm, *arrItm[maxArgs];
int i,m,j,k = 0, totala = 0;

tat = 0;


vaciarTDarg(tdArgs);
vaciarParamForm(paramFor); //cuando puedas, sacar esto y crear un array de nombres. sacar la vble global

et1: getTk(fp,tkn);
	 if(sonIguales((*tkn).nombre,"ID") != 1)
		errorSintactico(2);
	
	 str = crearStr((*tkn).valor);//nombre del arg	
	 paramFor[tat] = str;
	 
		if(existeLocal(str, env) == 1)//ya existe una argumento en la definicion local con ese nombre			
				errorSemantico(3,lineaactuall,columnaactuall,NULL,str);
	
	
		
	 itm = crearItem(str, varArg, NULL, (*env).lvl, 0, NULL, 'Y', 0, NULL);//todavia nose su nro de args ni la lis de parm en orden
	 arrItm[totala] = itm; // --
	 tat++;											
	 totala++;
	 insertar(itm, env); 	
	 	 		 	
	getTk(fp,tkn);
		
	if(sonIguales((*tkn).nombre,"DOSPUNTOS") == 1){			
		reglaTipoDato(fp,tkn);
		tdarg = crearStr((*tkn).nombre);		
	//printf("valor de tat:%d\n",tat);
	
		for(m=0,j=k;m<tat;j++,m++){ 
			setearTD(paramFor[m], tdarg, env); //seteo el td de los param form q encontre hasta aca
			tda[j] = tdarg; //ojo 
		}
													
	getTk(fp,tkn);
					
		if(sonIguales((*tkn).nombre,"PUNTOYCOMA") == 1){//sigue otro parametros.(q deberia ser de otro tipodedato, checkear en el a.semantico..)
			
			tat = 0; //evidentemente no qda en 0 para el proximo llamado.. se agrego esto al principio del metodo
			k = j;
			goto et1;
		
		}
		//si no es PUNTOYCOMA entoces luego deberia seguir el parentesis que cierra de function, se controla desp de retornar																	
	}
	else{//si no es ':' es ','
		if(sonIguales((*tkn).nombre,"COMA") == 1)
			goto et1;
			
		else
			errorSintactico(12);			
	}
	
for(i=0; i<totala; i++){ // -- seteo el desplz de cada arg
	(*(arrItm[i])).desplz = -(totala + 3 - (i+1));
}
		
return totala;
}
//**********************************************************************
int reglaCuerpo(FILE *fp,TipoToken *tkn,Ambiente *env){
	
	if(sonIguales((*tkn).nombre,"BEGIN") == 1){ 
		getTk(fp,tkn);		
otra:	reglaSentencia(fp,tkn,env);		
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
int reglaParamAct(FILE *fp, TipoToken *tkn,Ambiente *env, int *cantP){ //  <expresion> { , <expresion> }    //COMPLETAAAAAAAAAAAAR
char *td;

vaciarTDarg(tdArgs);
				//guardar los tipos de los actuales(exrpresiones..) para comprobar desp se llama a checkTipoyCantArgs
getTk(fp,tkn);

	if(sonIguales((*tkn).nombre,"PARENTCIERRA") != 1){//la 1ra vez, por si no tiene args
act:	td = crearStr("x");//aca o ni bien empieza			
		reglaExpresion(fp,tkn,td,env); //obtener el tipo de la expresion; aca mismo se fija si el parametros es una vble, si esta inicializada
     		
        tdArgs[*cantP] = td;       
        *cantP = *cantP + 1;
        
		if(sonIguales((*tkn).nombre,"COMA") == 1){
			getTk(fp,tkn);										
			goto act;	
		}//poner algun tipo de error???????		
	
	//free(td);
	}		
return 1;	
}

//**********************************************************************
int reglaSentencia(FILE *fp,TipoToken *tkn,Ambiente *env){ //<sentencia> → <asignacion>|<llamada-proc>|<repetitiva>|<alternativa>|<alternativa-mult>|<cuerpo>
char *ide, *td;
ItemTs *itm;
int *cantiPa, li, co;
 
 //CREAR TIPODATO dentro de cada opcion

		
	if(sonIguales((*tkn).nombre,"WHILE") == 1)	
		reglaWhile(fp,tkn,env);
	else{
		if(sonIguales((*tkn).nombre,"IF") == 1)
			reglaIf(fp,tkn,env);
		else{
			if(sonIguales((*tkn).nombre,"CASE") == 1)
				reglaCase(fp,tkn,env);
			else{		
				if(sonIguales((*tkn).nombre,"BEGIN") == 1){
					reglaCuerpo(fp,tkn,env);
					getTk(fp,tkn);
				}	
				else{			
					if(sonIguales((*tkn).nombre,"ID") == 1){//analizo los toksiguientes puede ser id de asig o de proced
						ide = crearStr((*tkn).valor);
						existeElem(ide,lineaactuall,columnaactuall,env);
						itm = getItem(ide,env);
						td = crearStr("x");
						li = lineaactuall;
						co = columnaactuall;
																				
						getTk(fp,tkn);					
				
						if(sonIguales((*tkn).nombre,"ASIGNACION") == 1){
							if((esVariable(itm) == 1) || verificarAsigFunc(itm,env) == 1)
								setearStr(td, (*itm).tipoDato);
							else
								errorSemantico(9,li,co,NULL,ide);// el id del lado izq de la asig tiene q ser un id de variable							
																																																		
						reglaAsignac(fp,tkn,td,env);// se ve el lado derecho de la asig	
						(*itm).asignado = 'Y';
						//setear q se fue asignado el li. 'Y'					
						}	
						else{
							if(sonIguales((*tkn).nombre,"PARENTABRE") == 1){						
								
								cantiPa = malloc(sizeof(int));
								*cantiPa = 0;					
																								
								reglaParamAct(fp,tkn,env,cantiPa);//mm		
																										
								if(sonIguales((*tkn).nombre,"PARENTCIERRA") != 1)//a la vuelta
									errorSintactico(8);
								else{//avanzo uno mas desp del ')' antes de retornar
									
										if(esVariable(itm) == 1)
											errorSemantico(4,lineaactuall,columnaactuall,NULL,ide);
											
										checkTipoyCantArgs(tdArgs,*cantiPa,ide,lineaactuall, columnaactuall, env);	
										
										if(esFuncion(itm) == 1)
											errorSemantico(10,lineaactuall,columnaactuall,NULL,ide);			
																																
								getTk(fp,tkn);	//si llega hasta aca es porq era procedimiento																	
								}
																																	
							}//ojo cn el else de este(AGREGADO, PROBAR CUAANDO ENTRA ACA, EJEMPLOS)	
							else								
								errorSintactico(17); //cuando lo q sigue desp de id no es ni := ni (					
						}		

					}//sino es id puede ser un procedimiento read o write, o los tkn de funcion succ pred
					else{
						if((sonIguales((*tkn).nombre,"SUCC") == 1) || (sonIguales((*tkn).nombre,"PRED") == 1) )// error 10, una sentencia no puede empezar con el llamado a una fc
							errorSemantico(10,lineaactuall,columnaactuall,NULL,(*tkn).nombre);
						else{	
							if(sonIguales((*tkn).nombre,"READ") == 1)
								reglaLeer(fp,tkn,env);
							else{
								if(sonIguales((*tkn).nombre,"WRITE") == 1)
									reglaEscribir(fp,tkn,env);
								else
									errorSintactico(17);//sentencia no válida..ver tipo de error							
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
int reglaAlter(FILE *fp,TipoToken *tkn,Ambiente *env){//alter> → λ | else <sentencia> 
	if(sonIguales((*tkn).nombre,"ELSE") == 1){
		getTk(fp,tkn);			
		reglaSentencia(fp,tkn,env);//este ya adelanta 1			
	}
	/*else{	//si no es else tiene q ser ';'		
		if(sonIguales((*tkn).nombre,"PUNTOYCOMA") != 1)
			errorSintactico(22);
		
		getTk(fp,tkn);
		if(sonIguales((*tkn).nombre,"ELSE") == 1)
			errorSintactico(22);	
	}*/									
return 1;	
}
//**********************************************************************
int reglaIf(FILE *fp,TipoToken *tkn,Ambiente *env){//<alternativa> → if <expresion> then <sentencia>  <alter>
char *td;

getTk(fp,tkn);
td = crearStr("x");

reglaExpresion(fp,tkn,td,env); //ver los parametros
esBooleana(td, columnaactuall, lineaactuall, "IF");
free(td);

	if(sonIguales((*tkn).nombre,"THEN") != 1)
		errorSintactico(20);
	
getTk(fp,tkn);	
reglaSentencia(fp,tkn,env);
reglaAlter(fp,tkn,env);
//getTk(fp,tkn);	//ojo con este
return 1;
}
//**********************************************************************
int reglaAsignac(FILE *fp,TipoToken *tkn,char *tdLI,Ambiente *env){//se fija el lado derecho de la asig, lo anterior se comprobo en reglasentencia
char *tdLD;

tdLD = crearStr("x");

	getTk(fp,tkn);
		
	reglaExpresion(fp,tkn,tdLD,env);//si se retorna sin error, todo ok	
	chequearTiposDatos(tdLI, lineaactuall, tdLD);
	
free(tdLD);			
return 1;
}
//**********************************************************************
int reglaExpresion(FILE *fp,TipoToken *tkn, char *tipodevuelto, Ambiente *env){//<expresion>	→	<exp> |  <exp> <op1> <exp>					//factorizar? <expresion> ---> <exp><expii>       <expii> --->  λ | <op1> <exp>
int co, li;
char *nombreOp;		
		
//tipodevuelto = crearStr("x");	
		
	reglaExp(fp,tkn,tipodevuelto,env); //pasar por parametro ex1 y que setee lo q tenga q setear
		
	if(reglaOp1(fp,tkn) == 1){ //operador relacional
		nombreOp = crearStr((*tkn).valor);
		
		if(sonIguales(tipodevuelto,"INTEGER") != 1)
			errorSemantico(14,lineaactuall,columnaactuall,nombreOp,"INTEGER"); //va a escribir el nombre del valor del token GT, LT etc
						
		co = columnaactuall;
		li = lineaactuall;
		
		getTk(fp,tkn);	
		
		reglaExp(fp,tkn,tipodevuelto,env);
		
		if(sonIguales(tipodevuelto,"INTEGER") != 1)
			errorSemantico(14,li,co,nombreOp,"INTEGER");
			
		setearStr(tipodevuelto,"BOOLEAN");	//el resultado de una op relacional con dos integers es un boolean		
	
	free(nombreOp);
	}	
	
return 1;
}
//**********************************************************************
int reglaExp(FILE *fp,TipoToken *tkn, char *td,Ambiente *env){//<exp> → <termino> <expree>
	
	reglaTermino(fp,tkn,td,env);	
	reglaExpree(fp,tkn,td,env);

return 1;
}
//**********************************************************************
int reglaTermino(FILE *fp,TipoToken *tkn, char *td,Ambiente *env){//<termino> → <factor> <termii>
	
	reglaFactor(fp,tkn,td,env);			
	reglaTermii(fp,tkn,td,env); 

return 1;
}
//**********************************************************************
int reglaExpree(FILE *fp,TipoToken *tkn, char *tipodevuelto, Ambiente *env){//<expree> →	<op2> <termino> <expree> | λ
char *ope;
int quees, band = 0, li , co;//ver si es necesario avisar q no se encontro op2(ni op3). si hay q retornar algun valor especifico o solo lo tipodevuelto asi como lo recibi
//char *td;	
	
	if((quees = reglaOp2(fp,tkn)) != -1){
	 band = 1;
	 
	  if(quees == 1 || quees ==2){ //+,-	
		if(quees == 1)
			ope = crearStr("+");
		else
			ope = crearStr("-");
		
		  
		if(sonIguales(tipodevuelto,"INTEGER") != 1)
			errorSemantico(14,lineaactuall,columnaactuall,ope,"INTEGER");
	    
	  }   
	  else{ //or
		ope = crearStr("OR"); 
		if(sonIguales(tipodevuelto,"BOOLEAN") != 1)	   			
			errorSemantico(14,lineaactuall,columnaactuall,"OR","BOOLEAN");
	  }	
	li = lineaactuall;
	co = columnaactuall;	  
	getTk(fp,tkn);			
			
	reglaTermino(fp,tkn,tipodevuelto,env);
		if((sonIguales(tipodevuelto,"BOOLEAN") == 1) && (quees == 1 || quees ==2)) //tipodevuelto compatible con +, - 
			errorSemantico(14,li,co,ope, "INTEGER"); 
			
		if((sonIguales(tipodevuelto,"INTEGER") == 1) && (quees == 3))	 //tipodevuelto compatible con OR
			errorSemantico(14,li,co,ope, "BOOLEAN");   
			
											
	reglaExpree(fp,tkn,tipodevuelto,env);
	free(ope);
	}

	
return band;
}
//**********************************************************************
int reglaFactor(FILE *fp,TipoToken *tkn, char *tipodevuelto, Ambiente *env){
//<factor>→(<expresion>)|not <factor>|<constante>|<identificador>|<entero>|-<factor>|<llamada-func>		
int li, co;
char *str;	
									
	
	if(sonIguales((*tkn).nombre,"PARENTABRE") == 1){
			
		getTk(fp,tkn);	
	     reglaExpresion(fp,tkn,tipodevuelto,env);
	    		
		if(sonIguales((*tkn).nombre,"PARENTCIERRA") != 1)
			errorSintactico(8);
				
	getTk(fp,tkn);	
	
	}
	else{		
		if((sonIguales((*tkn).nombre,"OPLOGICO") == 1) && (sonIguales((*tkn).valor,"NOT") == 1)){
			str = crearStr("NOT");						
			li = lineaactuall;
			co = columnaactuall;
			getTk(fp,tkn);
			
			reglaFactor(fp,tkn,tipodevuelto,env);
			
			if(sonIguales(tipodevuelto,"BOOLEAN") != 1) 
				errorSemantico(14,li,co,str,"BOOLEAN");	
						
		free(str);		
		}
		else{
			
			if(reglaConstante(fp,tkn,tipodevuelto) == 1){												
				getTk(fp,tkn); 
			}	
			else{
				if(sonIguales((*tkn).nombre,"ENTERO") == 1){	
					setearStr(tipodevuelto,"INTEGER");													
					getTk(fp,tkn); 
				}
				else{
					if((sonIguales((*tkn).nombre,"OPARITMETICO") == 1) && (sonIguales((*tkn).valor,"RESTA") == 1)){			
						str = crearStr("MENOS UNARIO");
						
						li = lineaactuall;
						co = columnaactuall;
						getTk(fp,tkn);		
						//guardad fila y columna??? deberia hacerlo en todos lados para este tipo de error
						
																
						reglaFactor(fp,tkn,tipodevuelto,env);//  a la vuelta me fijo q sea entera la expresion
						
						if(sonIguales(tipodevuelto,"INTEGER") != 1) 
							errorSemantico(14,li,co,str,"INTEGER");
						
						
					free(str);		
					}
					else{
						reglallamadaFunc(fp,tkn,tipodevuelto,env);
						
					} //hacer que en todos los casos se avance el tkn antes d retornar?.. en llamd func avanza si o si
				}
			}
		}
	}
//printf("tipo dato expre antes de retornar d factor : %s\n", (*exx).tipo); //null	
return 1;	
}
//**********************************************************************
int reglaTermii(FILE *fp,TipoToken *tkn, char *tipodevuelto,Ambiente *env){//<termiii> →	<op3> <factor> <termii> | λ
int band = 0, quees, li, co;			
char *ope;

	if((quees = reglaOp3(fp,tkn)) != -1){
		band = 1;
		if(quees == 1 || quees ==2){ 	
			if(quees == 1)
				ope = crearStr("*");
			else
				ope = crearStr("/");
	 
		if(sonIguales(tipodevuelto,"INTEGER") != 1)
			errorSemantico(14,lineaactuall,columnaactuall,ope,"INTEGER");	  
		
		}
	    else{ //and
		  ope = crearStr("AND");
		  if(sonIguales(tipodevuelto, "BOOLEAN") != 1)
			errorSemantico(14,lineaactuall,columnaactuall,ope,"BOOLEAN");	  	  
	    }
	li = lineaactuall;
	co = columnaactuall;
	getTk(fp,tkn);		
	
		
	reglaFactor(fp,tkn,tipodevuelto,env); 
							//comprobar a la vuelta los tipos
		if((sonIguales(tipodevuelto,"BOOLEAN") == 1) && (quees == 1 || quees ==2)) //tipodevuelto compatible con *, / 
			errorSemantico(14,li,co,ope, "INTEGER"); 
			
		if((sonIguales(tipodevuelto,"INTEGER") == 1) && (quees == 3))	 //tipodevuelto compatible con AND
			errorSemantico(14,li,co,ope, "BOOLEAN");					
														
	reglaTermii(fp,tkn,tipodevuelto,env);
	free(ope);
	}
	
return band; //ver q pasa en termino si devuelve 0 aca
}
//**********************************************************************
int reglaConstante(FILE *fp,TipoToken *tkn, char *td){
int sale = -1;	

	if((sonIguales((*tkn).nombre,"TRUE") == 1) || (sonIguales((*tkn).nombre,"FALSE") == 1)){	
		setearStr(td,"BOOLEAN");
		sale = 1;
	}	
	if((sonIguales((*tkn).nombre,"MAXINT") == 1)){	
		setearStr(td,"INTEGER");
		sale = 1;
	}
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
		if(sonIguales((*tkn).valor,"SUMA") == 1)
			sale = 1;
		if(sonIguales((*tkn).valor,"RESTA") == 1)
			sale = 2;
	}
	else{	
		if((sonIguales((*tkn).nombre,"OPLOGICO") == 1) && (sonIguales((*tkn).valor,"OR") == 1))
			sale = 3;
	}
return sale;
}
//**********************************************************************
int reglaOp3(FILE *fp,TipoToken *tkn){// *, /, and
int sale = -1;

	if(sonIguales((*tkn).nombre,"OPARITMETICO") == 1){
		if(sonIguales((*tkn).valor,"PRODUCTO") == 1) 
			sale = 1;
		if(sonIguales((*tkn).valor,"DIVISION") == 1)
			sale = 2;		
	}
	else{
		if((sonIguales((*tkn).nombre,"OPLOGICO") == 1) && (sonIguales((*tkn).valor,"AND") == 1))
			sale = 3;
	}	
return sale;
}
//**********************************************************************
int reglallamadaFunc(FILE *fp,TipoToken *tkn, char *tipodevuelto, Ambiente *env){ //llamada desde factor
ItemTs *itm;
char *str;	
int *cantiParAct, li ,co;
	
	if(sonIguales((*tkn).nombre,"SUCC") == 1){
		reglaSucesor(fp,tkn,tipodevuelto,env);
	}
	else{
		if(sonIguales((*tkn).nombre,"PRED") == 1){	
			reglaPredecesor(fp,tkn,tipodevuelto,env);			
		}	
		else{
			if(sonIguales((*tkn).nombre,"ID") == 1){
				str = crearStr((*tkn).valor);
				existeElem(str, lineaactuall, columnaactuall, env);				
				itm = getItem(str, env); //ver el tema de los ambientes	
				li = lineaactuall;
				co = columnaactuall;				
											
				getTk(fp,tkn);//habia advertencia con expr, termii , etc
			
				if(sonIguales((*tkn).nombre,"PARENTABRE") == 1){									
					
					cantiParAct = malloc(sizeof(int));	
					*cantiParAct = 0;						   						
									 
					reglaParamAct(fp,tkn,env,cantiParAct);
					
					if(sonIguales((*tkn).nombre,"PARENTCIERRA") != 1) 
						errorSintactico(8);//podria ser parm act mal formados, nuevo error			
					
					if(esVariable(itm) == 1)
						errorSemantico(4,lineaactuall,columnaactuall,NULL, str);
						
					checkTipoyCantArgs(tdArgs,*cantiParAct,str,lineaactuall, columnaactuall, env);
																
					if(esProcedimiento(itm) == 1)
						errorSemantico(11,lineaactuall,columnaactuall,NULL, NULL);
																	
				setearStr(tipodevuelto, (*itm).tipoDato);//es fc
											
				free(cantiParAct);						
				getTk(fp,tkn);//esto lo agregue hace poco. cuidado										
				}		
				else{			
					if(esVariable(itm) == 1){
						if(existeLocal(str,env) == 1)//si es vble local chequeo que tenga un valor asignado
						  tieneValor(itm,li,co,env);
						
						setearStr(tipodevuelto, (*itm).tipoDato); //seteo el tipo de la variable a tipodevuelto		
					}
					else
						errorSemantico(9,li,co,NULL,str); //un id q no es variable..
				}	
			free(str);				
			}
			else
				errorSintactico(21);//ver..
		}
	}		
return 1;
}
//**********************************************************************
/*int reglallamadaProc(FILE *fp,TipoToken *tkn){//no lo llamo. arreglar VER ESTO
int sale = 1;
char *str;
ItemTs itm;

	if(sonIguales((*tkn).nombre,"READ") == 1)
		reglaLeer(fp,tkn);
	else{
		if(sonIguales((*tkn).nombre,"WRITE") == 1)
			reglaEscribir(fp,tkn);
		else{
			if(sonIguales((*tkn).nombre,"ID") == 1){
				//chequear q sea proc
				str = crearStr((*tkn).valor);
				existeElem(str, lineaactuall, columnaactuall, env); //ver el tema del env. capaz q recibirlo como param
				itm = getItem(str, env);
				
				if(esProcedimiento(itm) != 1){
				//	errorSemantico()
				}
				
				getTk(fp,tkn);
			
				if(sonIguales((*tkn).nombre,"PARENTABRE") == 1){
					reglaParamAct(fp,tkn); //dnd chequeo esto
						
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
free(str);	
return sale;
}*/
//**********************************************************************
int reglaWhile(FILE *fp,TipoToken *tkn,Ambiente *env){ //while <expresion> do <sentencia>
char *td;
	
	getTk(fp,tkn);
	td = crearStr("x");
		
	reglaExpresion(fp,tkn,td,env); //chequear q sea booleana
	esBooleana(td, columnaactuall, lineaactuall, "WHILE");
	free(td);	
		
	if(sonIguales((*tkn).nombre,"DO") != 1)//osea que no devuelve -1 WTAF (== -1 retorna false)
		errorSintactico(15);	
		
	getTk(fp,tkn);
	reglaSentencia(fp,tkn,env);
	
	//if(sonIguales((*tkn).nombre,"PUNTOYCOMA") != 1)
	//	errorSintactico(5); //se espera ';'		        //si? same white else..

//getTk(fp,tkn);
return 1;	
}
//**********************************************************************
int reglaRotulo(FILE *fp,TipoToken *tkn,Ambiente *env){ // <entero> { , <entero> } : <sentencia> ;
	
otroNu:	if(sonIguales((*tkn).nombre,"ENTERO") != 1)
			errorSintactico(18);//se espera nro entero
			
		getTk(fp,tkn);	
	
		if(sonIguales((*tkn).nombre,"COMA") == 1){
			getTk(fp,tkn);		
			goto otroNu;
		}		
		if(sonIguales((*tkn).nombre,"DOSPUNTOS") == 1){
			getTk(fp,tkn);			 
			reglaSentencia(fp,tkn,env);//a la vuelta pregunto a ver si termina en ';'
			
			if(sonIguales((*tkn).nombre,"PUNTOYCOMA") != 1)
				errorSintactico(5);//se espera ';'
		}
		else
			errorSintactico(19);//desp del entero no habia ni ',' ni ':'
	
getTk(fp,tkn);
return 1;	
}
//**********************************************************************
int reglaCase(FILE *fp,TipoToken *tkn,Ambiente *env){ //case <id> of <rotulo> { <rotulo> } [else <sentencia>;] end
char *str;
ItemTs *itm;

	getTk(fp,tkn);
	
	if(sonIguales((*tkn).nombre,"ID") != 1)
		errorSintactico(2);
			
	str = crearStr((*tkn).valor);
	existeElem(str, lineaactuall, columnaactuall, env);				
	itm = getItem(str, env); //ver el tema de los ambientes							
	esVbleEnteraCase(itm, lineaactuall, columnaactuall, env);
		
	getTk(fp,tkn);
	if(sonIguales((*tkn).nombre,"OF") != 1)
		errorSintactico(13);	
	
	getTk(fp,tkn);
	
otroRo:	reglaRotulo(fp,tkn,env);
	
		if(sonIguales((*tkn).nombre,"ENTERO") == 1)
			goto otroRo;
			
		if(sonIguales((*tkn).nombre,"ELSE") == 1){ //AGREGADOO
			getTk(fp,tkn);
			reglaSentencia(fp,tkn,env);
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
int reglaSucesor(FILE *fp, TipoToken *tkn, char *td, Ambiente *env){
//char *td;//creo uno local aca, no hace falta recibirlo por parametro

 
	getTk(fp,tkn);
	if(sonIguales((*tkn).nombre,"PARENTABRE") != 1)
		errorSintactico(7);
	
	getTk(fp,tkn);
	 	
	reglaExpresion(fp,tkn,td,env);		
	esEntera(td, columnaactuall, lineaactuall);		//O USAR ERROR 2
		
	if(sonIguales((*tkn).nombre,"PARENTCIERRA") != 1)
		errorSintactico(8);
	
getTk(fp,tkn);
return 1;
}
//**********************************************************************
int reglaPredecesor(FILE *fp, TipoToken *tkn,char *td, Ambiente *env){
	
	getTk(fp,tkn);
	if(sonIguales((*tkn).nombre,"PARENTABRE") != 1)
		errorSintactico(7);	
	
	getTk(fp,tkn);	
		
	reglaExpresion(fp,tkn,td,env);	//chequear que sea entera
	esEntera(td, columnaactuall, lineaactuall);					//O USAR ERROR 2
	
	if(sonIguales((*tkn).nombre,"PARENTCIERRA") != 1)
		errorSintactico(8);
	
getTk(fp,tkn);
return 1;
}
//**********************************************************************
int reglaLeer(FILE *fp, TipoToken *tkn,Ambiente *env){
ItemTs *itm; 
char *lex;

	getTk(fp,tkn);
	if(sonIguales((*tkn).nombre,"PARENTABRE") != 1)
		errorSintactico(7);
	
	getTk(fp,tkn);
	if(sonIguales((*tkn).nombre,"ID") != 1)
		errorSintactico(2);//se omite id del arg
		
	lex = crearStr((*tkn).valor);	
	existeElem(lex, lineaactuall, columnaactuall, env); //ver el tema del env. capaz q recibirlo como param
	itm = getItem(lex, env);
	
	if(esVariable(itm) != 1)								//preguntar aca o desp del parentesis...
	 errorSemantico(9, lineaactuall, columnaactuall, NULL, lex);
	 
	(*itm).asignado = 'Y'; // ahora tiene un valor asignado
	
	getTk(fp,tkn);
	if(sonIguales((*tkn).nombre,"PARENTCIERRA") != 1)
		errorSintactico(8);
	
getTk(fp,tkn);
free(lex);
//eliminarItem(itm);
return 1;
}
//**********************************************************************
int reglaEscribir(FILE *fp, TipoToken *tkn,Ambiente *env){
char *td;

	getTk(fp,tkn);
	if(sonIguales((*tkn).nombre,"PARENTABRE") != 1)
		errorSintactico(7);
	
	getTk(fp,tkn);
	
	td = crearStr("x");	
	reglaExpresion(fp,tkn,td,env); // expr evuel
	free(td); //mientras no tire error la exp, todo bien
	
	if(sonIguales((*tkn).nombre,"PARENTCIERRA") != 1)
		errorSintactico(8);

getTk(fp,tkn);
return 1;
}
