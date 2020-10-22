#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "tools.h"

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
    esDesconocido
} tipoTerceto;

/*  Esta estructura es para identificar el tipo de elemento en el terceto:
	char *: El elemento del terceto es un identificador/cte.
	ind: El elemento del terceto es un indice a otro terceto.	
*/
typedef struct  unionTerceto {
    char* cad; //puntero al lexema en la ts.
    int ind;   //indice a un terceto en el array global de tercetos.
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
    /*Este tipo va a servir para validar compatibilidad de los datos en las operaciones. Vendria a hacer el "Tipo de valor del resultado".*/
    tipoValor tipoVal;
} terceto;

char* buscarEnTablaDeSimbolosSinTabla(char *yytext);
char* obtenerValorTerceto(char * nombre);
tipoValor obtenerTipoTerceto(char * nombre);
elemento crearElemStr(const char*);
elemento crearElemInt(int);
indice crearTerceto(elemento, elemento, elemento, tipoValor, tipoTerceto);
indice crearTercetoOperacion(const char* op, indice ind1, indice ind2);
indice crearTercetoAsignacion(indice ind1, indice ind2);
tipoValor obtenerTipoSimbolo(char * tipo);
void imprimirTercetos();

/* Índice global para tercetos */
int indTercetos = 0;
/* Array de Tercetos */
terceto tercetos[900];


elemento crearElemStr(const char* str) {
    elemento e;
    e.valor.cad = strdup(str);
    e.tipo = string;
    return e;
}

elemento crearElemInt(int ind) {
    elemento e;
    e.valor.ind = ind;
    e.tipo = entero;
    return e;
}
/*  Crear un terceto con los elementos pasados por parámetro y se Agregamos
    al array global de tercetos. Esta es una función genérica para insertar
    un terceto. */
indice crearTerceto(elemento e1, elemento e2, elemento e3, tipoValor tipoV, tipoTerceto tipoT) {
    terceto t;
    indice ind;

    t.elementos[0] = e1;
    t.elementos[1] = e2;
    t.elementos[2] = e3;
    t.tipoVal = tipoV;
    t.tipoTerc = tipoT;
    /* Agregamos el terceto al array global de tercetos */
    tercetos[indTercetos] = t;
    ind.tipo = esTerceto;
    ind.datoind.indiceTerceto = indTercetos;
    indTercetos++;

imprimirTercetosPantalla();
    /* Devolvemos el índice que apunta al terceto creado */
    return ind;
}
/*  Crear un terceto, donde el primer elemento es una string con el valor
    de alguna operación (ejemplo, "+") y los otros 2 son valores int que
    corresponden a los índices de los tercetos sobre los que se realiza
    la operación. */

indice crearTercetoOperacion(const char* op, indice ind1, indice ind2) {
    elemento elem1, elem2;
    tipoValor tipo1, tipo2, tipoConstante, tipoResultado;
    tipoTerceto tipoT;

    if (ind1.tipo == esTerceto) {
        printf("\n 1 es terceto");
        elem1 = crearElemInt(ind1.datoind.indiceTerceto);
        tipo1 = tercetos[ind1.datoind.indiceTerceto].tipoVal;
    } else { /* El índice es de un símbolo */
                printf("\n 1 no es terceto");
        elem1 = crearElemStr(ind1.datoind.punteroSimbolo->lexema);
        tipo1 = obtenerTipoSimbolo(ind1.datoind.punteroSimbolo->tipo);
    }
            printf("%d\n", ind1.tipo);

        printf("%d\n", ind2.tipo);
    if (ind2.tipo == esTerceto) {
                printf("\n 2 es terceto");
        elem2 = crearElemInt(ind2.datoind.indiceTerceto);
        tipo2 = tercetos[ind2.datoind.indiceTerceto].tipoVal;

    } else {
                printf("\n 2 no es terceto");

        elem2 = crearElemStr(ind2.datoind.punteroSimbolo->lexema);
        tipo2 = obtenerTipoSimbolo(ind2.datoind.punteroSimbolo->tipo);
    }
        printf("\n %d \n", tipo2);

    if(tipo2 == constante){
        printf("TENGO UNA CONSTANTE\n" );
        printf("\n\n %d \n\n", obtenerTipoTerceto(ind2.datoind.punteroSimbolo->lexema));
        tipo2 = obtenerTipoTerceto(ind2.datoind.punteroSimbolo->lexema);
//         char valor[20] = "";

//         strcpy(valor, buscarEnTablaDeSimbolosSinTabla(obtenerValorTerceto(ind2.datoind.punteroSimbolo->lexema)));
// printf("% s - num %s\n",   resultado,   ind2.datoind.punteroSimbolo->lexema);


    }
        printf("\n\n %s %s \n\n", nombreTiposVal[tipo1], nombreTiposVal[tipo2]);

    /* Validamos que los tipos de la expresión sean compatibles (esto hay que definirlo entre todos por ahora yo tome este criterio de validación)*/
    if (tipo1 == tipo2) {
        tipoResultado = tipo1;
    } else if ((tipo1 == real && tipo2 == entero) || (tipo1 == entero && tipo2 == real)) { //lo pensé como los lenguajes de alto nivel que si sumas real a entero suma a la parte entera del real como corresponde.
        tipoResultado = real;
    } else {
        printf("\nError Error en la linea %d: La operacion %s con esos tipos de datos no es compatible.", 
                yylineno, op, nombreTiposVal[tipo1], nombreTiposVal[tipo2]);
        exit(1);
    }
     /* Seteamos el tipo de operación */
    switch (op[0]) {
        case '+':
            tipoT = esSuma;
            break;
        case '-':
            tipoT = esResta;
            break;
        case '*':
            tipoT = esMultiplicacion;
            break;
        case '/':
            tipoT = esDivision;
            break;
        default:
            tipoT = esDesconocido;
            break;
    }

    return crearTerceto(crearElemStr(op), elem1, elem2, tipoResultado, tipoT);
}
/*  Crear un terceto, donde el primer y segundo elementos son indices de 
    tercetos. Crea una operación de asignación ("=", ind1, ind2) pero antes
    valida que la asignación pueda realizarse */
indice crearTercetoAsignacion(indice ind1, indice ind2) {
    elemento elem1, elem2;
    tipoValor tipo1, tipo2;

    if (ind1.tipo == esTerceto) {
        elem1 = crearElemInt(ind1.datoind.indiceTerceto);
        tipo1 = tercetos[ind1.datoind.indiceTerceto].tipoVal;
    } else { /* El índice es de un símbolo */
        elem1 = crearElemStr(ind1.datoind.punteroSimbolo->lexema);
        tipo1 = obtenerTipoSimbolo(ind1.datoind.punteroSimbolo->tipo);
    }

    if (ind2.tipo == esTerceto) {
        elem2 = crearElemInt(ind2.datoind.indiceTerceto);
        tipo2 = tercetos[ind2.datoind.indiceTerceto].tipoVal;
    } else {
        // ACA CREA EL STR //
        elem2 = crearElemStr(ind2.datoind.punteroSimbolo->lexema);
        tipo2 = obtenerTipoSimbolo(ind2.datoind.punteroSimbolo->tipo);
    }
        printf("\nasignar un %s a una variable de tipo %s.", nombreTiposVal[tipo2], nombreTiposVal[tipo1]);


    /*  La razón por la cuál se necesitó hacer una función aparte solo para las
        asignaciones es porque la validación de tipo es diferente a la que se hace 
        en crearTercetoOperación. */
    if (tipo1 == tipo2 || (tipo1 == real && tipo2 == entero) || (tipo1 == constante && (tipo2 == real || tipo2 == entero))) { 
        return crearTerceto(crearElemStr("="), elem1, elem2, tipo1, esAsignacion);
    } else {
        printf("\nError en la linea %d: Se intento asignar un %s a una variable de tipo %s.", 
                yylineno, nombreTiposVal[tipo2], nombreTiposVal[tipo1]);
        exit(1);
    }
}
void imprimirTercetosPantalla() {
    int i, j;

    fprintf(stdout, "\n--- TERCETOS ---\n\n");
    for (i = 0; i < indTercetos; i++) {
        terceto t = tercetos[i];
        fprintf(stdout, "%d: (", i + 1);

        for (j = 0; j < 3; j++) {
            elemento e = t.elementos[j];

            switch (e.tipo) {
                case string:
                    fprintf(stdout, "%s", e.valor.cad);
                    break;
                case entero: /* Si es entero, es un índice y le sumamos 1 al mostrarlo */
                    fprintf(stdout, "[%d]", e.valor.ind + 1);
                    break;
                default:
                    fprintf(stdout, "_");
            }

            if (j < 2) {
                fprintf(stdout, ", ");
            } 
        }
        fprintf(stdout, ")");
        fprintf(stdout, "\n");
    }
    fprintf(stdout,"\n--- TERCETOS ---\n");
        system("Pause");

}

char* obtenerValorTerceto(char * nombre) {
    int i, j;

    for (i = 0; i < indTercetos; i++) {
        terceto t = tercetos[i];
        elemento e = t.elementos[1];
        elemento e1 = t.elementos[2];
        if(strcmp(nombre, e.valor.cad) == 0){
            //fprintf(stdout, "%s - %s - %s", nombre, e.valor.cad, e1.valor.cad);
            return e1.valor.cad;
        }
    }

    return "";
}

tipoValor obtenerTipoTerceto(char * nombre) {
    int i, j;

    for (i = 0; i < indTercetos; i++) {
        terceto t = tercetos[i];
        elemento e = t.elementos[1];
        elemento e1 = t.elementos[2];
                fprintf(stdout, "%s\n", nombre);
        fprintf(stdout, "%d - %s\n", e1.valor.ind, nombreTiposVal[e1.tipo]);
        // if(strcmp(nombre, e.valor.cad) == 0){
        //     return e1.tipo;
        // }
    }

    return indefinido;
}

void imprimirTercetos() {
   printf("Generando archivo intermedia.txt...\n");
    FILE *gci;
    int i, j;

    if ((gci = fopen("intermedia.txt", "w")) == NULL) {
        printf("No se puede crear el archivo de la lista de tercetos.");
        exit(1);
    }

    fprintf(gci, "\n--- TERCETOS ---\n\n");
    for (i = 0; i < indTercetos; i++) {
        terceto t = tercetos[i];
        fprintf(gci, "%d: (", i + 1);

        for (j = 0; j < 3; j++) {
            elemento e = t.elementos[j];

            switch (e.tipo) {
                case string:
                    fprintf(gci, "%s", e.valor.cad);
                    break;
                case entero: /* Si es entero, es un índice y le sumamos 1 al mostrarlo */
                    fprintf(gci, "[%d]", e.valor.ind + 1);
                    break;
                default:
                    fprintf(gci, "_");
            }

            if (j < 2) {
                fprintf(gci, ", ");
            } 
        }
        fprintf(gci, ")");
        fprintf(gci, "\n");
    }
    fprintf(gci,"\n--- TERCETOS ---\n");
    
    if (fclose(gci) != 0) {
        printf("No se puede CERRAR el archivo de la lista de tercetos.");
        exit(1);
    }
}
tipoValor obtenerTipoSimbolo(char * tipo){

        if(strcmp(tipo, "STRING")==0){
           return string; 
        }
        if(strcmp(tipo, "INTEGER")==0){
           return entero; 
        }
        if(strcmp(tipo, "FLOAT")==0){
           return real; 
        }
        if(strcmp(tipo, "CONST")==0){
           return constante; 
        }
}
