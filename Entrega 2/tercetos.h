#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "tabla_simbolos.h"

/*
Esto permite manejarnos mejor con los tipos de los tercetos antes que tener un define para cada uno.
*/

typedef enum tipoTerceto {
    esAsignacion,
    esSuma,
    esResta,
    esMultiplicacion,
    esDivision,
    esComparacion,
} tipoTerceto;

/*  Esta estructura es para identificar el tipo de elemento en el terceto:
	char *: El elemento del terceto es un identificador/cte.
	ind: El elemento del terceto es un indice a otro terceto.	
*/
typedef struct  unionTerceto {
    char* cad;
    int ind;
} unionTerceto;

/*  Esta struct es necesaria para poder determinar que tipo de 
    valor está siendo almacenado en la union */
typedef struct elemento {
    /* Los tercetos solo deberían poder tener elementos que sean de tipo
    string, entero (para índices) o nada (indefinido). Ver estructura de tipoValor  */
    tipoValor tipo;
    unionTerceto valor;
} elemento;

typedef struct terceto {
    elemento elementos[3];
    tipoTerceto tipoTerc;
} terceto;
