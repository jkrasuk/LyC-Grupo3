#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


typedef struct
{
  char *lexema;
  char *tipo;
  char *valor;

}tInfo;

typedef tInfo tDato;

typedef struct sNodo
{
  tDato info;
  struct sNodo *sig;

}tNodo;

typedef tNodo *tLista; 

int comparar(char *yytext , tDato *dato );
void crearTablaDeSimbolos(tLista * pl);
int buscarEnTablaDeSimbolos(char *yytext , tLista * tablaDeSimbolos);
int insertarEnTablaDeSimbolos (char *yytext , tLista * tablaDeSimbolos);

tLista tablaDeSimbolos;

void crearTablaDeSimbolos(tLista * pl)
{
    printf("cree la lista\n");
    *pl=NULL;
}

int comparar(char *yytext , tDato * dato )
{
	
	return strcmp(yytext , dato->valor); 
	
	
}

int buscarEnTablaDeSimbolos(char *yytext , tLista * tablaDeSimbolos)
{
	int contador=0;
	
	while( *tablaDeSimbolos )
	{	
		contador++;
		if( (comparar(yytext , &(*tablaDeSimbolos)->info) == 0))
			{
				printf("\nEl identificador: %s  esta duplicado\n",yytext);
				return 0;
			}
		else
			{
				
				
				tablaDeSimbolos = &(*tablaDeSimbolos)->sig; 
			}
	}	


	insertarEnTablaDeSimbolos(yytext,tablaDeSimbolos);
	
	return 1;
}

int insertarEnTablaDeSimbolos (char *yytext , tLista * tablaDeSimbolos)
{
	
	tDato dato;
	
	dato.valor = (char*) malloc(sizeof(char[yyleng + 1]));
	dato.tipo = (char*)	malloc(sizeof(char));
	dato.lexema = (char*) malloc(sizeof(char[yyleng+2]));


	
	strcpy(dato.valor,yytext);
	strcpy(dato.tipo,"");
	strcpy(dato.lexema,"_");
	strcat(dato.lexema,yytext);
	
	tNodo * nuevo = (tNodo*) malloc (sizeof(tNodo));

	if(!nuevo)
	return 0;

	nuevo->info = dato;
	nuevo->sig  = *tablaDeSimbolos;
	*tablaDeSimbolos = nuevo;
	return 1;	
}
