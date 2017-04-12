#include <stdio.h>
#include <stdlib.h>
#include "semantico.h"
#include "TablaDeSimbolos.h"
#include "lexico.h"
#include "sintactico.h"

int main(int argc, char *argv[]){
char *fname;
FILE *fp;	 
TipoToken tok = {"0","0"};	
	
	if(argc == 1){
		printf("Error, omisión de parámetro. ¡Debe ingresar el nombre del archivo fuente!\n");
		exit(1);
	}
	else{
		
		if(argc > 2){
			printf("Error, ¡ha excedido el número de parámetros validos!\n");
			exit(1);
		}
		else{
				
			fname = argv[1];
			if((fp = fopen(fname,"r")) == NULL){
				printf("Se produjo un error al intentar abrir el archivo. Archivo inexistente.\n");
				exit(1);
			}	
			else{				
				if(verificarExtension(fname,longiptr(fname)) == -1){
					printf("Extensión del archivo no valida, se espera .pas\n");
					exit(1);
				}
			}
		}
	}
	
inicializarKeywords();	
analisisSintactico(fp, &tok);
//tablaToFile(fp,amb);

printf("¡El análisis semántico finalizó con éxito!\n");
	
return 1;	
}
