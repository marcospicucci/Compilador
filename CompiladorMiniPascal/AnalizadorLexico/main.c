#include <stdio.h>
#include <stdlib.h>
#include "lexico.h"
//#include "time.h"

int main(int argc, char *argv[]){

char *fname;
FILE *fp, *fps; 
TipoToken tok = {"0","0"};
int cont = 1, state, linea = 1, col = 1;


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
			
			if((fps = fopen("tokens_salida.txt","w")) == NULL){
				printf("Ha ocurrido un error al crear el archivo de salida tokens_salida.txt");
				exit(1);
			}
				
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
	
	while (1){
		state = getToken(fp,&tok,&linea,&col); 
		
		if(state == -1)
			break;
			
		else{
		fprintf(fps,"token %d: <%s, %s>\n", cont, tok.nombre, tok.valor);
		(tok).nombre = " ";
		(tok).valor = " ";		
		cont++;
		}
	}
	printf("¡El análisis léxico finalizó con éxito!\n");

	return 1;
}
