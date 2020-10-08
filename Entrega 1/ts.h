#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


typedef struct
{
  char *lexema;
  char *tipo;
  char *valor;
  int longitud;
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

