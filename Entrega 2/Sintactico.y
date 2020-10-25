%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "tercetos.h"//incluye a tools.h
#define YYDEBUG 1

/*NOTA: No se crean tercetos por cada vez que identifica un ID o CTE. ej: (_1,_,_) ó (b,_,_). Directamente se crean los tercetos con 
los operadores, sean aritmeticos o de asiganión.*/


/* Punteros y pilas para expresiones*/
/* En las expresiones con paréntesis se complico en poder anidar los tercetos, es por eso que se usaron pilas para los indices.*/
pila pilaExpr, pilaTerm, pilaFact; 


indice indExpr,indTerm, indFact, indComp; //Punteros a la tabla de simbolos o al array globar de tercetos.


/* Este array sirve para guardar los simbolos de la ts para que cuando llegue al bloque de declaracion de tipos le asigne el tipo a cada uno.*/
indice tiposVariablesDeclaracion[700];
indice auxindice;
int comparar(char *yytext , tDato *dato );
void inicializarCompilador();
void crearTablaDeSimbolos(tLista *pl);
indice buscarEnTablaDeSimbolos(char *yytext , tLista *tablaDeSimbolos);
indice insertarEnTablaDeSimbolos (char *yytext , tLista *tablaDeSimbolos);
indice crearIndice(int tipoIndice, void * dato_indice);
void cargartipoVariable(int tipo,indice ind);
void cargarConstanteReal  (indice ind,int tipo_real);
void cargarConstanteEntera(indice ind,int tipo_entero);
void cargarConstanteString(indice ind,int tipo_string);
void cargarConstante(indice ind, int tipo_constante);
tLista tablaDeSimbolos;

extern int yylex();
extern int yyparse();
void yyerror(const char *s);
extern FILE* yyin;
extern int yylineno;
extern int yyleng;
extern char *yytext;
int cantVariables=0;
int cantTipoVariables=0;

void validarVariables();

%}
%token ID CTE_INT CTE_STRING CTE_REAL
%token ASIG OP_SUMA OP_RESTA OP_MULT OP_DIV
%token MENOR MAYOR IGUAL DISTINTO MENOR_IGUAL MAYOR_IGUAL
%token AND OR NOT
%token INTEGER FLOAT STRING
%token GUION_BAJO COMA PUNTO_COMA DOS_PUNTOS
%token IF ELSE ENDIF
%token DIM AS
%token CONST
%token P_A P_C C_A C_C L_A L_C
%token PUT GET
%token WHILE
%token MAXIMO
%left OP_SUMA
%left OP_RESTA
%left OP_DIV
%left OP_MULT
%left IGUAL
%left DISTINTO
%left MAYOR
%left MAYOR_IGUAL
%left MENOR
%left MENOR_IGUAL
%left OR
%left AND

%type <intVal> CTE_INT
%type <floatVal> CTE_REAL
%type <strVal> CTE_STRING
%type <strVal> ID

%type <auxLogicOperator> logic_operator
%type <auxLogicOperator> logic_concatenator
%start programa

%union
{
    int intVal;
    float floatVal;
    char strVal[30];
    char* auxLogicOperator;
}
%%

programa: 
          {
              printf("Inicia COMPILADOR\n"); inicializarCompilador();
          }
          sentencia_declaracion algoritmo {
                                            printf("\n Regla - programa: sentencia_declaracion algoritmo \n");
                                            imprimirTercetos();
                                          }
  ;

sentencia_declaracion: sentencia_declaracion bloque_declaracion_variables {printf("\n Regla - sentencia_declaracion: sentencia_declaracion bloque_declaracion_variables \n");}
| bloque_declaracion_variables {printf("\n Regla - sentencia: bloque_declaracion_variables \n");}
  ;

bloque_declaracion_variables: DIM MENOR lista_variables MAYOR AS MENOR tipos_variables MAYOR {printf("\n Regla - bloque_declaracion_variables: DIM MENOR declaracion_variables MAYOR AS MENOR tipos_variables MAYOR \n"); validarVariables();}
  ;

lista_variables: lista_variables COMA ID  
  {
    printf("\n Regla - lista_variables: lista_variables COMA ID \n"); 
    
    auxindice = buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos);
    /*Guardamos el indice del simbolo para despues asignarle el tipo a cada uno.*/
    tiposVariablesDeclaracion[cantVariables] = auxindice;
    cantVariables++; 
  }
|ID 
  {
    printf("\n Regla - lista_variables: ID \n");
    
    auxindice = buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos);
    /*Guardamos el indice del simbolo para despues asignarle el tipo a cada uno.*/
    tiposVariablesDeclaracion[cantVariables] = auxindice;
    cantVariables++; 
  }
  ;

tipos_variables: tipos_variables COMA tipo_variable {printf("\n Regla - lista_variables: lista_variables COMA tipo_variable \n"); }
|tipo_variable {printf("\n Regla - lista_variables: tipo_variable \n"); } 
;

tipo_variable:   /*Aca ya se puede dar valor al tipo de lexema en la tabla de simbolo usando el array de indice de simbolos. */                                       
    INTEGER {
              printf("\n Regla - tipo_variable: INTEGER \n");   
              cargartipoVariable(entero,tiposVariablesDeclaracion[cantTipoVariables]);
              cantTipoVariables++;
            }
  | FLOAT   {
             printf("\n Regla - tipo_variable: FLOAT \n");    
             cargartipoVariable(real,tiposVariablesDeclaracion[cantTipoVariables]);
             cantTipoVariables++; 
            }
  | STRING  {
              printf("\n Regla - tipo_variable: STRING \n");   
              cargartipoVariable(string,tiposVariablesDeclaracion[cantTipoVariables]);
              cantTipoVariables++;
            }
  ;

algoritmo: bloque {printf("\n Regla - algoritmo: bloque \n");}
 ;

bloque: sentencia PUNTO_COMA {printf("\n Regla - bloque: sentencia PUNTO_COMA \n");}
  | bloque sentencia PUNTO_COMA {printf("\n Regla - bloque: bloque sentencia PUNTO_COMA \n");}
  | bloque sentencia {printf("\n Regla - bloque: bloque sentencia \n");}
  | sentencia {printf("\n Regla - bloque: sentencia \n");}
  ;

sentencia: decision {printf("\n Regla - sentencia: decision \n");}
  | asignacion {printf("\n Regla - sentencia: asignacion \n");}
  | put {printf("\n Regla - sentencia: put \n");}
  | get {printf("\n Regla - sentencia: get \n");}
  | iteracion {printf("\n Regla - sentencia: iteracion \n");}
  | asignacion_constante  {printf("\n Regla - asignacion_constante \n");}
  ;

decision: IF P_A condicion P_C L_A bloque L_C ELSE L_A bloque L_C {printf("\n Regla - decision: IF P_A condicion P_C L_A bloque L_C ELSE L_A bloque L_C \n");}
  | IF P_A condicion P_C L_A bloque L_C {printf("\n Regla - decision: IF P_A condicion P_C L_A bloque L_C \n");}
  ;

asignacion: ID ASIG expresion {
                                printf("\n Regla - asignacion: ID ASIG expresion \n"); 
                                printf("\n lexema en la asignacion %s \n",$1);
                                crearTercetoAsignacion(buscarEnTablaDeSimbolos($1,&tablaDeSimbolos),indExpr);
                              }
  ;

asignacion_constante: CONST ID {
                                auxindice = buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos);
                                cargarConstante(auxindice,constante);
                               }
                ASIG expresion {
                                printf("\n Regla - asignacion_constante: CONST ID ASIG expresion \n");
                                crearTercetoAsignacion(auxindice,indExpr);
                               }
    ;

lista_expresiones: lista_expresiones COMA termino {printf("\n Regla - lista_expresiones:  lista_expresiones COMA termino \n");}
 | termino {printf("\n Regla - lista_expresiones: termino \n");}
 ;

maximo: MAXIMO P_A lista_expresiones P_C {printf("\n Regla - maximo: MAXIMO P_A lista_expresiones P_C \n");}
  ;

iteracion: WHILE P_A condicion P_C L_A bloque L_C {printf("\n Regla - iteracion: WHILE P_A condicion P_C L_A bloque L_C \n");}
  ;

put: PUT ID {buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos); printf("\n Regla - put: PUT ID \n");}
  | PUT CTE_INT {buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos); printf("\n Regla - put: PUT CTE_INT \n");}
  | PUT CTE_REAL {buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos); printf("\n Regla - put: PUT CTE_REAL \n");}
  | PUT CTE_STRING {buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos); printf("\n Regla - put: PUT CTE_STRING \n");}
  ;
   
get: GET ID {printf("\n Regla - get: GET ID \n");}
  ;

condicion: comparacion {printf("\n Regla - condicion: comparacion \n");}
  | comparacion logic_concatenator comparacion {printf("\n Regla - condicion: comparacion logic_concatenator comparacion \n");}
  | NOT comparacion  {printf("\n Regla - condicion: NOT comparacion \n");}
  | NOT factor {printf("\n Regla - condicion: NOT factor \n");}
  | factor {printf("\n Regla - condicion: factor \n");}
  ;

comparacion: expresion  logic_operator  expresion {printf("\n Regla - comparacion: expresion  logic_operator  expresion \n");}
| P_A expresion logic_operator expresion P_C {printf("\n Regla - comparacion: P_A expresion logic_operator expresion P_C \n");}
  ;

logic_operator: IGUAL {printf("\n Regla - logic_operator: IGUAL \n");}
  | DISTINTO {printf("\n Regla - logic_operator: DISTINTO \n");}
  | MAYOR {printf("\n Regla - logic_operator: MAYOR \n");}
  | MAYOR_IGUAL {printf("\n Regla - logic_operator: MAYOR_IGUAL \n");}
  | MENOR {printf("\n Regla - logic_operator: MENOR \n");}
  | MENOR_IGUAL {printf("\n Regla - logic_operator: MENOR_IGUAL \n");}
  ;

logic_concatenator: OR {printf("\n Regla - logic_concatenator: OR \n");}
  | AND {printf("\n Regla - logic_concatenator: AND \n");}
  ;

expresion: expresion {apilar(&pilaExpr, indExpr);} OP_SUMA termino  { printf("\n Regla - expresion: expresion OP_SUMA termino\n");  indExpr = crearTercetoOperacion("+", desapilar(&pilaExpr), indTerm);}
  |        expresion {apilar(&pilaExpr, indExpr);} OP_RESTA termino { printf("\n Regla - expresion: expresion OP_RESTA termino\n"); indExpr = crearTercetoOperacion("-", desapilar(&pilaExpr), indTerm);}
  |        termino   {printf("\n Regla - expresion: termino\n"); indExpr = indTerm;}
  ;

termino: 
        termino {apilar(&pilaTerm, indTerm);}   OP_MULT factor {printf("\n Regla - termino: termino OP_MULT factor\n"); indTerm = crearTercetoOperacion("*", desapilar(&pilaTerm), indFact);  }
  |     termino {apilar(&pilaTerm, indTerm);}   OP_DIV factor  {printf("\n Regla - termino: termino OP_DIV factor\n");  indTerm = crearTercetoOperacion("/", desapilar(&pilaTerm), indFact);  }
  |     factor {printf("\n Regla - termino: factor\n"); indTerm = indFact; }
  ;

factor: ID 
          {
              printf("\n Regla - factor: ID \n"); 
              /* en este caso ya debería estar el ID en la ts no haría falta volver a insertarlo (podriamos sacarlo).*/
              indFact =  buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos);  
          }



  | CTE_INT { printf("\n Regla - factor: CTE_INT \n");      indFact = buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos); cargarConstanteEntera(indFact,entero);} 
  | CTE_REAL { printf("\n Regla - factor: CTE_REAL \n");    indFact = buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos); cargarConstanteReal(indFact,real);}
  | CTE_STRING {printf("\n Regla - factor: CTE_STRING \n"); indFact = buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos); cargarConstanteString(indFact,string);}
  | P_A expresion P_C {printf("\n Regla - factor: P_A expresion P_C \n"); indFact = indExpr;}
  | maximo { printf("\n Regla - factor: maximo \n");}
  ;

%%

int main(int argc, char *argv[]) {
    FILE *archivoTablaDeSimbolos;

    crearTablaDeSimbolos(&tablaDeSimbolos);
    yydebug = 0;
    if ((yyin = fopen(argv[1], "rt")) == NULL) {
        printf("\nNo se puede abrir el archivo: %s\n", argv[1]);
    } else {
        yyparse();
    }

    fclose(yyin);
    printf("\n COMPILACION EXITOSA \n");

    printf("\n TABLA DE SIMBOLOS\n");
    printf("\n %-40s\t%-10s\t%-40s\t%-5s", "NOMBRE", "TIPO DATO", "VALOR", "LONGITUD");

    archivoTablaDeSimbolos = fopen("ts.txt", "wt");

    if (!archivoTablaDeSimbolos) {
        printf("no se pudo abrir el archivo");
    } else {
        fprintf(archivoTablaDeSimbolos, "%-40s\t%-10s\t%-40s\t%-5s\n", "NOMBRE", "TIPO DATO", "VALOR", "LONGITUD");
    }

    while (tablaDeSimbolos) {
        printf(" %-40s\t%-10s\t%-40s\t%-5d\n", (*tablaDeSimbolos).info.lexema, (*tablaDeSimbolos).info.tipo, (*tablaDeSimbolos).info.valor, (*tablaDeSimbolos).info.longitud);
        fprintf(archivoTablaDeSimbolos, "%-40s\t%-10s\t%-40s\t%-5d\n", (tablaDeSimbolos)->info.lexema, (tablaDeSimbolos)->info.tipo, (tablaDeSimbolos)->info.valor, (*tablaDeSimbolos).info.longitud);

        tablaDeSimbolos = (*tablaDeSimbolos).sig;
    }

    return 0;
}

void yyerror(const char *str) {
    fprintf(stderr, "Error: %s en la linea %d\n", str, yylineno);
    system("Pause");
    exit(1);
}

void crearTablaDeSimbolos(tLista * pl)
{
    *pl=NULL;
}

int comparar(char *yytext, tDato * dato )
{

    return strcmp(yytext, dato->valor);


}
/*Devuelve un indice del simbolo, con este puede acceder al info del simbolo de la ts. (ver struct indice en tools.h)*/
indice buscarEnTablaDeSimbolos(char *yytext, tLista * tablaDeSimbolos)
{
    indice ind;
    while( *tablaDeSimbolos )
    {
        if( (comparar(yytext, &(*tablaDeSimbolos)->info) == 0))
        {
            ind.datoind.punteroSimbolo=&(*tablaDeSimbolos)->info;
            ind.tipo=esSimbolo;
            return ind;
        }
        else
        {


            tablaDeSimbolos = &(*tablaDeSimbolos)->sig;
        }
    }

  return insertarEnTablaDeSimbolos(yytext, tablaDeSimbolos);
}

char* buscarEnTablaDeSimbolosSinTabla(char *yytext)
{
    indice ind;
    tLista * tablaDeSimbolosCopiaLocal = &tablaDeSimbolos;
    while(tablaDeSimbolosCopiaLocal )
    {
        if((strcmp(yytext, (*tablaDeSimbolosCopiaLocal)->info.lexema) == 0))
        {
            return (*tablaDeSimbolosCopiaLocal)->info.tipo;
        }
        else
        {
            tablaDeSimbolosCopiaLocal = &(*tablaDeSimbolosCopiaLocal)->sig;
        }
    }

    return SIN_RESULTADOS;
}
indice insertarEnTablaDeSimbolos (char *yytext, tLista * tablaDeSimbolos)
{
    int len = strlen(yytext);
    tDato dato;

    dato.valor = (char *) malloc(sizeof(char[yyleng + 1]));
    dato.tipo = (char *) malloc(sizeof(char));
    dato.lexema = (char *) malloc(sizeof(char[yyleng + 2]));
    dato.longitud = yyleng;

    strcpy(dato.valor, yytext);
    strcpy(dato.tipo, "-");
    strcpy(dato.lexema, "_");
    strcat(dato.lexema, yytext);

    tNodo * nuevo = (tNodo*) malloc (sizeof(tNodo));

    if(!nuevo)
        return;

    nuevo->info = dato;
    nuevo->sig  = *tablaDeSimbolos;
    *tablaDeSimbolos = nuevo;

    return crearIndice(esSimbolo,&nuevo->info); //devolvemos el indice del simbolo.
}

indice crearIndice(int tipoIndice, void * dato_indice){

      indice ind;

      if(tipoIndice == esSimbolo){    
        ind.datoind.punteroSimbolo=(tDato *)dato_indice; //dato del simbolo (es el mismo dato que tiene en la ts.).
        ind.tipo=esSimbolo;
        return ind;
      }
      if(tipoIndice == esTerceto){    
        ind.datoind.indiceTerceto = (int) dato_indice; //indice al array global de tercetos.
        ind.tipo=esTerceto;
        return ind;
      }

}
void cargartipoVariable(int tipo,indice ind){
  char * tipoT;
  switch (tipo) {
        case entero:
            tipoT = "INTEGER";
            break;
        case string:
            tipoT = "STRING";
            break;
        case real:
            tipoT = "FLOAT";
            break;
        case constante:
            tipoT = "CONST";
            break;
        default:
            tipoT = "indefinido";
            break;
    }
    ind.datoind.punteroSimbolo->tipo=tipoT;
}
void cargarConstanteReal(indice ind, int tipo_real){
  ind.datoind.punteroSimbolo->tipo="FLOAT";
}
void cargarConstanteString(indice ind, int tipo_string){
  ind.datoind.punteroSimbolo->tipo="STRING";
}
void cargarConstanteEntera(indice ind, int tipo_entero){
  ind.datoind.punteroSimbolo->tipo="INTEGER";
}
void cargarConstante(indice ind, int tipo_constante){
  ind.datoind.punteroSimbolo->tipo="CONST";
}

void validarVariables() {

    if(cantVariables == cantTipoVariables) {
      printf("\nCantidad correcta de variables y tipos\n");
    } else {
      printf("\nCantidad incorrecta de variables y tipos\n");
      exit(1);
    }

}
/*  Esta función es para cualquier cosa que se necesite hacer antes de iniciar con el parsing.*/
void inicializarCompilador() {
    inicializarPila(&pilaExpr);
    inicializarPila(&pilaTerm);
    inicializarPila(&pilaFact);
}

