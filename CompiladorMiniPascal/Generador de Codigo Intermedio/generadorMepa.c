#include "generadorMepa.h"


void setearFPM(FILE *fp){
	fpm = fp;
}

char *crearEtiq(int n){
int c1, c2;
char *eti;

eti = malloc(4*sizeof(char));
eti[0] = 'l';

 if(n>9){ 
  c1 = n / 10;
  c2 = n % 10;
  eti[1] = c1 + '0';
  eti[2] = c2 + '0';
  eti[3] = '\0';
 }
 else{
  eti[1] = n + '0'; 
  eti[2] = '\0';
 }
//printf("etiq: %s\n", eti); 
return eti; 
}


//*********************PROGRAMAS Y PROCEDIMIENTOS***********************
void inpp(){
  fprintf(fpm,"\t  INPP \n");
}

void enpr(int k, char *etiq){
  fprintf(fpm,"%s \t  ENPR  %d \n", etiq, k);
}

void llpr(char *etiq){
  fprintf(fpm,"\t  LLPR  %s \n", etiq);
}

void rmem(int m){
  fprintf(fpm,"\t  RMEM  %d \n", m);
}

void lmem(int m){
  fprintf(fpm,"\t  LMEM  %d \n", m);	 
}

void rtpr(int k, int n){
  fprintf(fpm,"\t  RTPR  %d,%d \n", k, n);	
}
//**********************************************************************
//********************COMANDOS DE ENTRADA Y SALIDA**********************
void leer(){
  fprintf(fpm,"\t  LEER \n");
}

void impr(){
  fprintf(fpm,"\t  IMPR \n");
}

//**********************************************************************
//******************COMANDOS CONDICIONALES E ITERATIVOS*****************
void dsvs(char *etiq){
  fprintf(fpm,"\t  DSVS  %s \n", etiq);
}

void dsvf(char *etiq){
  fprintf(fpm,"\t  DSVF  %s \n", etiq);
}
//**********************************************************************
//***********COMANDOS DE ASIGNACION Y RECUPERACION DE VALORES***********
void apvl(int m, int n){
  fprintf(fpm,"\t  APVL  %d,%d \n", m, n);
}

void alvl(int m, int n){
  fprintf(fpm,"\t  ALVL  %d,%d \n", m, n);
}
//**********************************************************************
//**********************EVALUACION DE EXPRESIONES***********************

void apct(char *k){
  fprintf(fpm,"\t  APCT  %s \n", k);
}
void suma(){
  fprintf(fpm,"\t  SUMA \n");
}

void sust(){
  fprintf(fpm,"\t  SUST \n");
}

void mult(){
  fprintf(fpm,"\t  MULT \n");
}

void divi(){
  fprintf(fpm,"\t  DIVI \n");
}

void umen(){
  fprintf(fpm,"\t  UMEN \n");
}

void conjun(){
  fprintf(fpm,"\t  CONJ \n");
}

void disjun(){
  fprintf(fpm,"\t  DISJ \n");
}

void nega(){
  fprintf(fpm,"\t  NEGA \n");
}

void cmme(){
fprintf(fpm,"\t  CMME \n");
}

void cmma(){
  fprintf(fpm,"\t  CMMA \n");
}

void cmig(){
  fprintf(fpm,"\t  CMIG \n");
}

void cmdg(){
  fprintf(fpm,"\t  CMDG \n");
}

void cmni(){
  fprintf(fpm,"\t  CMNI \n");
}

void cmyi(){
  fprintf(fpm,"\t  CMYI \n");
}

void divc(){
  fprintf(fpm,"\t  DIVC \n");	
}
//**********************************************************************
void nada(char *etiq){
  fprintf(fpm,"%s \t  NADA \n",etiq);
}

void para(){
  fprintf(fpm,"\t  PARA \n");
}
