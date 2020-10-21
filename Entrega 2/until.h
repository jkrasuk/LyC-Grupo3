#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

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


/*  Para que sea mas facil de identificar los tipos de las variables que maneja 
    nuestro compilador. 
    NOTA: El indefinido no es un tipo "válido", nada más es para asignarle a los
    tercetos donde no importa realmente de que tipo son. */
typedef enum tipoValor {
    indefinido,  //0
    string,		 //1
    entero,		 //2	
    real,		 //3	
} tipoValor;



/* Pila para almacenar punteros a los datos en la ts. */
typedef struct nodoPila {
  tDato dato;
  struct nodoPila* sig;
} nodoPila;

typedef nodoPila* pila;

void inicializarPila(pila* p);
void apilar(pila* p, indice val);
indice mirarTope(pila* p);
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

