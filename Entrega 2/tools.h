#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define SIN_RESULTADOS "NO_OK"
extern int yylineno;
/*  Son los nombres de cada tipo */
const char* nombreTiposVal[5] = {"indefinido", "string", "entero", "real", "constante" };

typedef struct
{
  char *lexema;
  char *tipo; 
  char *valor;
  char *longitud;
}tInfo;

typedef tInfo tDato;

typedef struct sNodo
{
  tDato info;
  struct sNodo *sig;
}tNodo;

typedef tNodo *tLista;

/*  Estas estructuras son para optimizar la generación de tercetos.
    Un índice puede apuntar a la lista de tercetos o a la lista
    de símbolos según sea su tipo. */
typedef enum tipoIndice {
    esSimbolo,
    esTerceto
} tipoIndice;


/*  Para que sea mas facil de identificar los tipos de las variables que maneja 
    nuestro compilador. 
    NOTA: El indefinido no es un tipo "válido", nada más es para asignarle a los
    tercetos donde no importa realmente de que tipo son. */
typedef enum tipoValor {
    indefinido,  //0
    string,		 //1
    entero,		 //2	
    real,		 //3
    constante,	
} tipoValor;

typedef struct Datoindice {
  tDato * punteroSimbolo;
  int indiceTerceto;
} Datoindice;

/*Esta estructura se puede obviar pero queda mas legible si manejamos todos los indices de los 
tercetos con una estructura. */

typedef struct indice {
    Datoindice datoind;
     tipoIndice tipo;
} indice;


/* Pila para almacenar indices de los tercetos. */
typedef struct nodoPila {
  indice dato;
  struct nodoPila* sig;
} nodoPila;

typedef nodoPila* pila;

void inicializarPila(pila* p);
void apilar(pila* p, indice val);
indice desapilar(pila* p);

void inicializarPila(pila* p) {
  *p = NULL;
}


void apilar(pila* p, indice val) {
  nodoPila* nodo = (nodoPila*)malloc(sizeof(nodoPila));

  nodo->dato = val;
  nodo->sig = ((*p) == NULL ? NULL : (*p));

  *p = nodo;
}

indice desapilar(pila* p) {
  if(*p == NULL) {
    printf("ERROR: Intento de desapilar una pila que estaba vacia.\n");
    exit(1);
  }

  indice val = (*p)->dato;
  nodoPila* aux = *p;
  *p = (*p)->sig;
  free(aux);

  return val;
}

