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
    esUnDesplazamiento, //salto
    esMaximoEncontrado,
    esDesconocido,
    esEtiqueta
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
elemento crearElemStr(const char*);
elemento crearElemInt(int);
elemento crearElemReal(const char*);
elemento crearElemNull();
indice crearTerceto(elemento, elemento, elemento, tipoValor, tipoTerceto);
indice crearTercetoOperacion(const char* op, indice ind1, indice ind2);
indice crearTercetoAsignacion(indice ind1, indice ind2);
tipoValor obtenerTipoSimbolo(char * tipo);
indice crearTercetoDesplazamiento(const char* op, int salto);
void modificarDesplazamientoTerceto(indice ind, int salto);
indice crearTercetoMaximoEncontrado(indice max);
int obtenerIndiceTercetoSiguente();
void imprimirTercetos();
void negarTerceto(int);

/* Índice global para tercetos */
int indTercetos = 0;
/* Array de Tercetos */
terceto tercetos[900];

elemento crearElemReal(const char* str_float){
    elemento e;
    e.valor.cad = strdup(str_float);
    e.tipo = real;
    return e;
}
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
elemento crearElemNull() {
    elemento e;
    e.tipo = indefinido;
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

    /* Devolvemos el índice que apunta al terceto creado */
    return ind;
}
/*  Crear un terceto, donde el primer elemento es una string con el valor
    de alguna operación (ejemplo, "+") y los otros 2 son valores int que
    corresponden a los índices de los tercetos sobre los que se realiza
    la operación. */

indice crearTercetoOperacion(const char* op, indice ind1, indice ind2) {
    elemento elem1, elem2;
    tipoValor tipo1, tipo2, tipoResultado;
    tipoTerceto tipoT;

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
        elem2 = crearElemStr(ind2.datoind.punteroSimbolo->lexema);
        tipo2 = obtenerTipoSimbolo(ind2.datoind.punteroSimbolo->tipo);
    }

    if(tipo2 == constante){
        char resultado[20] = "";

        strcpy(resultado, buscarEnTablaDeSimbolosSinTabla(obtenerValorTerceto(ind2.datoind.punteroSimbolo->lexema)));

        if(strcmp(resultado, "INTEGER") == 0){
            tipo2 = entero;
        } else if(strcmp(resultado, "STRING") == 0){
            tipo2 = string;
        } else if(strcmp(resultado, "FLOAT") == 0){
            tipo2 = real;
        } else{
            tipo2 = indefinido;
        }   
    }

    /* Validamos que los tipos de la expresión sean compatibles (esto hay que definirlo entre todos por ahora yo tome este criterio de validación)*/
    if (tipo1 == tipo2) {
        tipoResultado = tipo1;
    } else if ((tipo1 == real && tipo2 == entero) || (tipo1 == entero && tipo2 == real)) { 
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
        elem2 = crearElemStr(ind2.datoind.punteroSimbolo->lexema);
        tipo2 = obtenerTipoSimbolo(ind2.datoind.punteroSimbolo->tipo);
    }

     if(tipo2 == constante){
        char resultado[20] = "";

        strcpy(resultado, buscarEnTablaDeSimbolosSinTabla(obtenerValorTerceto(ind2.datoind.punteroSimbolo->lexema)));

        if(strcmp(resultado, "INTEGER") == 0){
            tipo2 = entero;
        } else if(strcmp(resultado, "STRING") == 0){
            tipo2 = string;
        } else if(strcmp(resultado, "FLOAT") == 0){
            tipo2 = real;
        } else{
            tipo2 = indefinido;
        }   
    }

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
/*  Similar a crearTercetoOperacion pero con CMP */
indice crearTercetoComparacion(indice ind1, indice ind2) {
    elemento elem1, elem2;
    tipoValor tipo1, tipo2, tipoResultado;
    tipoTerceto tipoT;

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
        elem2 = crearElemStr(ind2.datoind.punteroSimbolo->lexema);
        tipo2 = obtenerTipoSimbolo(ind2.datoind.punteroSimbolo->tipo);
    }

    if(tipo2 == constante){
        char resultado[20] = "";

        strcpy(resultado, buscarEnTablaDeSimbolosSinTabla(obtenerValorTerceto(ind2.datoind.punteroSimbolo->lexema)));

        if(strcmp(resultado, "INTEGER") == 0){
            tipo2 = entero;
        } else if(strcmp(resultado, "STRING") == 0){
            tipo2 = string;
        } else if(strcmp(resultado, "FLOAT") == 0){
            tipo2 = real;
        } else{
            tipo2 = indefinido;
        }   
    }

    /* Validamos que los tipos de la comparación sean compatibles */
    if (tipo1 == tipo2) {
        tipoResultado = tipo1;
    } else if ((tipo1 == real && tipo2 == entero) || (tipo1 == entero && tipo2 == real)) {
        tipoResultado = real;
    } else {
        printf("\nError Error en la linea %d: La comparacion entre %s y %s no es compatible.", 
                yylineno, nombreTiposVal[tipo1], nombreTiposVal[tipo2]);
        exit(1);
    }

    return crearTerceto(crearElemStr("CMP"), elem1, elem2, tipoResultado, esComparacion);
}
/*Al pasarle el valor 0 quiere decir que todavia no se conoce el valor de desplazamiento y luego se usara modificarDesplazamientoTerceto()*/
indice crearTercetoDesplazamiento(const char* op, int salto) {
    return crearTerceto(crearElemStr(op), crearElemInt(salto), crearElemNull(), indefinido, esUnDesplazamiento);
}
void modificarDesplazamientoTerceto(indice ind, int salto) {
    tercetos[ind.datoind.indiceTerceto].elementos[1].valor.ind = salto;
}
int obtenerIndiceTercetoSiguente(){
    return indTercetos;
}
indice crearTercetoMaximoEncontrado(indice max){
return crearTerceto(crearElemStr(max.datoind.punteroSimbolo->lexema), crearElemNull(), crearElemNull(), real, esMaximoEncontrado);
}
char* obtenerValorTerceto(char * nombre) {
    int i, j;

    for (i = 0; i < indTercetos; i++) {
        terceto t = tercetos[i];
        elemento e = t.elementos[1];
        elemento e1 = t.elementos[2];
        if(strcmp(nombre, e.valor.cad) == 0){
            return e1.valor.cad;
        }
    }

    return "";
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
    fprintf(stdout, "\n--- TERCETOS ---\n\n");
    for (i = 0; i < indTercetos; i++) {
        terceto t = tercetos[i];
        fprintf(gci, "%d: (", i + 1);
        fprintf(stdout, "%d: (", i + 1);

        for (j = 0; j < 3; j++) {
            elemento e = t.elementos[j];

            switch (e.tipo) {
                case string:
                    fprintf(gci, "%s", e.valor.cad);
                    fprintf(stdout, "%s", e.valor.cad);
                    break;
                case entero: /* Si es entero, es un índice y le sumamos 1 al mostrarlo */
                    fprintf(gci, "[%d]", e.valor.ind + 1);
                    fprintf(stdout, "[%d]", e.valor.ind + 1);
                    break;
                default:
                    fprintf(gci, "_");
                    fprintf(stdout, "_");
            }

            if (j < 2) {
                fprintf(gci, ", ");
                fprintf(stdout, ", ");
            } 
        }
        fprintf(gci, ")");
        fprintf(stdout, ")");
        fprintf(gci, "\n");
        fprintf(stdout, "\n");
    }
    fprintf(gci,"\n--- TERCETOS ---\n");
    fprintf(stdout,"\n--- TERCETOS ---\n");

    if (fclose(gci) != 0) {
        printf("No se puede CERRAR el archivo de la lista de tercetos.");
        exit(1);
    }
}

/*  Crea un terceto de etiqueta. La etiqueta va a tener pegada el número de
    terceto asociado. No sé si esto realmente es necesario hacerlo acá ya que
    se podría diferenciar en la generación de assembler por más que diga solo
    TAG, pero en la clase de Mara mostraba que en CGI tenían los números de 
    terceto pegados así que para que quede igual lo modifiqué.
*/
indice crearTercetoTag() {
    char tag[10];

    /*  Nos fijamos si el último terceto creado también es un tag, de ser así
        directamente devolvemos un indice que apunte a tal tag. Esto puede
        pasar cuando hay ifs anidados por ejemplo*/
    if(tercetos[indTercetos - 1].tipoTerc == esEtiqueta) {
        indice ind;
        ind.datoind.indiceTerceto = indTercetos - 1;
        ind.tipo = esTerceto;
        return ind;
    }

    sprintf(tag, "TAG%d", indTercetos + 1);
    return crearTerceto(crearElemStr(tag), crearElemNull(), crearElemNull(), indefinido, esEtiqueta);
}
/* Niega la la condicion de un terceto */
void negarTerceto(int numeroTerceto) {
	if(strcmp(tercetos[numeroTerceto].elementos[0].valor.cad, ">=") == 0)
		 tercetos[numeroTerceto].elementos[0].valor.cad = "<";
	 
	 else if(strcmp(tercetos[numeroTerceto].elementos[0].valor.cad, ">") == 0)
		 tercetos[numeroTerceto].elementos[0].valor.cad = "<=";
	 
	 else if(strcmp(tercetos[numeroTerceto].elementos[0].valor.cad, "<=") == 0)
		 tercetos[numeroTerceto].elementos[0].valor.cad = ">";
	 
	 else if(strcmp(tercetos[numeroTerceto].elementos[0].valor.cad, "<") == 0)
		 tercetos[numeroTerceto].elementos[0].valor.cad = ">=";
	 
	 else if(strcmp(tercetos[numeroTerceto].elementos[0].valor.cad, "!=") == 0)
		 tercetos[numeroTerceto].elementos[0].valor.cad = "==";
	 
	 else if(strcmp(tercetos[numeroTerceto].elementos[0].valor.cad, "==") == 0)
		 tercetos[numeroTerceto].elementos[0].valor.cad = "!=";
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
