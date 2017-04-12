#include <stdio.h>
#include <stdlib.h>
#include "lexico.h"
#include "sintactico.h"
#include "semantico.h"
#include "TablaDeSimbolos.h"
#include "generadorMepa.h"
#include <string.h>

int main(int argc, char *argv[]){
	
char *fname;
FILE *fp, *fps;	 
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
			
			if((fps = fopen("traduccionMEPA.txt","w")) == NULL){
				printf("Ha ocurrido un error al crear el archivo de salida traduccionMEPA.txt");
				exit(1);
			}
			
		}
	}
	
inicializarKeywords();
setearFPM(fps);	
analisisSintactico(fp, &tok);

printf("¡La generación de código intermedio finalizó con éxito!\n");
	
return 1;	
}
