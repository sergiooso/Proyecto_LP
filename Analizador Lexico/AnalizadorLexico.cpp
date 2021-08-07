#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <iostream>
#define MAX 650
#define MAX_RES 23

using namespace std;

char *PalabrasReservadas[MAX_RES] = {"si","entonces","sino","entero","decimal","logico","texto","char","mientras","haga","repita",
"hasta","var","como","verdadero","falso","declare","inicie","termine","lea","imprima","rompa","nop"};
char tokenSimbolos[MAX];
char auxWord[MAX];
string tokenNumeros[MAX];
string tokenIdentificadores[MAX];
string tokenReservadas[MAX];
string tokensNoValidos[MAX];
bool esNumero=true;
bool esIdentificador = true;

int auxTR=0;
int auxTI=0;
int auxTN=0;
int auxTNV=0;

bool verificarNumero(char palabra[]);
bool verificarIdentificador(char palabra[]);
bool verificarReservada(char palabra[]);
void imprimirTokenNumeros();
void imprimirTokenSimbolos();
void imprimirTokenReservadas();
void imprimirTokenIdentificadores();
void imprimirIdentificadoresNoValidos();

main()
{
   system("COLOR 0A");
   unsigned char entrada[MAX];
   char *p = entrada;
   printf("Ingrese la primera linea del lenguaje: ");
   fflush(stdin);
   gets(entrada);
   fflush(stdin);
   clrscr();
   system("COLOR 0B");

   char palabra[MAX]; 
   int indexPalabra=0;
   int indexSimbolos = 0;


   for(int i=0;i<MAX;i++){tokenReservadas[i] = "";}

   for(int i=0;i<MAX;i++){tokensNoValidos[i] = "";}

   for(int i=0;i<MAX;i++){
		palabra[i] = '\0';
   }

   while(*p!='\0')
   {
		if((*p != ' ') && (*p !=','))
      {
      	if((*p== ';') || (*p=='"') || (*p=='(') || (*p==')') || (*p=='+') || (*p=='-') || (*p=='*') || (*p=='/') || (*p=='#') || (*p=='<') || (*p=='>') || (*p=='='))
	      {
      	   tokenSimbolos[indexSimbolos] = *p;
         	indexSimbolos++;
	      }
         else
         {
				palabra[indexPalabra] = *p;
            auxWord[indexPalabra] = *p;	
            indexPalabra++;
         }
      }
      else if((*p ==' ') || (*p ==','))
      {
         if(verificarReservada(palabra) == true){
				tokenReservadas[auxTR] = palabra;
          	auxTR++;
         }else if(verificarIdentificador(palabra) == true){
         	tokenIdentificadores[auxTI] = palabra;
		      auxTI++;
         }else if(verificarNumero(auxWord)==true){
         	tokenNumeros[auxTN] = auxWord;
		      auxTN++;
         }
         for(int i=0;i<MAX;i++){palabra[i]='\0';}	
         for(int i=0;i<MAX;i++){auxWord[i]='\0';}	
         indexPalabra=0;
      }
      p++;
   }

   if(verificarReservada(palabra) == true){
   	tokenReservadas[auxTR] = palabra;
    	auxTR++;
   }else if(verificarIdentificador(palabra) == true){
		tokenIdentificadores[auxTI] = palabra;
		auxTI++;
   }else if(verificarNumero(auxWord)==true){
    	tokenNumeros[auxTN] = auxWord;
      auxTN++;
   }
	
   printf("\t\tEXPRESION: %s\n",entrada);
   imprimirTokenReservadas();
   imprimirTokenSimbolos();
   imprimirTokenIdentificadores();
   imprimirTokenNumeros();
   imprimirIdentificadoresNoValidos();
   getch();
}

void imprimirTokenSimbolos(){
	puts("\n\n----------------\n|TOKENS SIMBOLOS|\n----------------");
	for(int i=0;i<strlen(tokenSimbolos);i++){printf("%c\n",tokenSimbolos[i]);}
}

void imprimirTokenReservadas(){
	puts("\n-----------------------\n|TOKENS Reservadas|\n-----------------------");
	for(int i=0;i<auxTR;i++){printf("%d %s\n",i+1,tokenReservadas[i]);}
}

void imprimirTokenIdentificadores(){
	puts("\n-----------------------\n|TOKENS IDENTIFICADORES|\n-----------------------");
	for(int i=0;i<auxTI;i++){printf("%d %s\n",i+1,tokenIdentificadores[i]);}
}

void imprimirTokenNumeros(){
	puts("\n-----------------------\n|TOKENS NUMEROS|\n-----------------------");
	for(int i=0;i<auxTN;i++){printf("%d %s\n",i+1,tokenNumeros[i]);}
}

void imprimirIdentificadoresNoValidos(){
	puts(" ");
	printf("********************************* MENSAJES *********************************\n");
   if(auxTNV == 0){
   	printf("\t\t 0 Errores, programa fuente exitoso...");
   }else{
   	for(int i=0;i<auxTNV;i++)
	   {
   		printf("\t\tERROR: No es Valido el Token: %s \n",tokensNoValidos[i]);
   	}
   }
}


bool verificarReservada(char palabra[]){
   int comp;
   bool esReservada=false;
   string str(palabra);
	for(int i=0; i<MAX_RES; i++)
   {
   	comp = strcmp(PalabrasReservadas[i],palabra);
      if(comp == 0)
      {
         esReservada = true;
         break;
      }
   }
   return esReservada;
}

bool verificarIdentificador(char palabra[]){
	string auxPalabra = palabra;
   esIdentificador = false;
   short estado = 0;
   char *p = palabra;
   while(*p != '\0')
   {
   	switch(estado)
      {
      	case 0:
         	if((isalpha(*p)) || (*p=='_')){
            	estado = 1;
               esIdentificador = true;
            }
            else{
            	estado = 2;
               esIdentificador = false;
            }
            p++;
         break;
         case 1:
         	if((isalpha(*p)) || (isdigit(*p)) || (*p=='_')){
            	estado = 1;
               esIdentificador = true;
            }
            else{
            	estado = 2;
               esIdentificador = false;
            }
            p++;
         break;
         case 2:

            esIdentificador = false;
            *p = '\0';
         break;
      }
   }
   return esIdentificador;
}

bool verificarNumero(char palabra[]){
	string auxPalabra = palabra;
   esNumero = false;
	short estado = 0,cont=0;
   char *p = palabra;
	while(*p!='\0')
   {
   	switch(estado)
      {
      	case 0:
            if(isdigit(*p)){
					estado = 0;
               esNumero = true;
               cont++;
            }
            else if( ((*p == '.') && (cont==0)) || (isalpha(*p))){
					estado = 2;
               esNumero=false;
            }else if(*p=='.'){
					estado = 1;
            	esNumero = false;
            }
         	p++;
         break;
         case 1:
            if(isdigit(*p)){
            	estado = 1;
               esNumero = true;
            }else
            {
            	estado = 2;
               esNumero = false;
            }
         	p++;
         break;
         case 2:
				esNumero = false;
         	*p = '\0';
         break;
      }
   }
   if(esNumero == false){
      if(auxPalabra != ""){
   	   tokensNoValidos[auxTNV] = auxPalabra;
	      auxTNV++;
      }
   }
 	return esNumero;
}
