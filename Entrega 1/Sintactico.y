%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#define YYDEBUG 1

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

int comparar(char *yytext , tDato *dato );
void crearTablaDeSimbolos(tLista *pl);
int buscarEnTablaDeSimbolos(char *yytext , tLista *tablaDeSimbolos);
int insertarEnTablaDeSimbolos (char *yytext , tLista *tablaDeSimbolos);

tLista tablaDeSimbolos;

extern int yylex();
extern int yyparse();
void yyerror(const char *s);
extern FILE* yyin;
extern int yylineno;
extern int yyleng;
extern char *yytext;
int cantVariables;
int cantTipoVariables;

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

programa: sentencia_declaracion algoritmo {printf("\n Regla - programa: sentencia_declaracion algoritmo \n");}
  ;

sentencia_declaracion: sentencia_declaracion bloque_declaracion_variables {printf("\n Regla - sentencia_declaracion: sentencia_declaracion bloque_declaracion_variables \n");}
| bloque_declaracion_variables {printf("\n Regla - sentencia: bloque_declaracion_variables \n");}
  ;

bloque_declaracion_variables: DIM MENOR lista_variables MAYOR AS MENOR tipos_variables MAYOR {printf("\n Regla - bloque_declaracion_variables: DIM MENOR declaracion_variables MAYOR AS MENOR tipos_variables MAYOR \n"); validarVariables();}
  ;

lista_variables: lista_variables COMA ID   {printf("\n Regla - lista_variables: lista_variables COMA ID \n"); cantVariables++; buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos);}
|ID {printf("\n Regla - lista_variables: ID \n");cantVariables++; buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos);}
  ;

tipos_variables: tipos_variables COMA tipo_variable {printf("\n Regla - lista_variables: lista_variables COMA tipo_variable \n"); cantTipoVariables++;}
|tipo_variable {printf("\n Regla - lista_variables: tipo_variable \n"); cantTipoVariables++;} 
;

tipo_variable: INTEGER {printf("\n Regla - tipo_variable: INTEGER \n");}
  | FLOAT {printf("\n Regla - tipo_variable: FLOAT \n");}
  | STRING {printf("\n Regla - tipo_variable: STRING \n");}
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

asignacion: ID ASIG expresion {printf("\n Regla - asignacion: ID ASIG expresion \n");}
  ;

asignacion_constante: CONST ID {buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos);} ASIG expresion {printf("\n Regla - asignacion_constante: CONST ID ASIG expresion \n");}
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
  | NOT P_A comparacion P_C {printf("\n Regla - condicion: NOT comparacion \n");}
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

expresion: expresion OP_SUMA termino {printf("\n Regla - expresion: expresion OP_SUMA termino\n");}
  | expresion OP_RESTA termino { printf("\n Regla - expresion: expresion OP_RESTA termino\n");}
  | termino {printf("\n Regla - expresion: termino\n");}
  ;

termino: termino OP_MULT factor {printf("\n Regla - termino: termino OP_MULT factor\n");}
  | termino OP_DIV factor {printf("\n Regla - termino: termino OP_DIV factor\n");}
  | factor {printf("\n Regla - termino: factor\n");}
  ;

factor: ID {printf("\n Regla - factor: ID \n"); buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos);}
  | CTE_INT { printf("\n Regla - factor: CTE_INT \n"); buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos);}
  | CTE_REAL { printf("\n Regla - factor: CTE_REAL \n"); buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos);}
  | CTE_STRING {printf("\n Regla - factor: CTE_STRING \n"); buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos);}
  | P_A expresion P_C {printf("\n Regla - factor: P_A expresion P_C \n");}
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
        printf(" %-40s\t%-10s\t%-40s\t%-5s\n", (*tablaDeSimbolos).info.lexema, (*tablaDeSimbolos).info.tipo, (*tablaDeSimbolos).info.valor, (*tablaDeSimbolos).info.longitud);
        fprintf(archivoTablaDeSimbolos, "%-40s\t%-10s\t%-40s\t%-5s\n", (tablaDeSimbolos)->info.lexema, (tablaDeSimbolos)->info.tipo, (tablaDeSimbolos)->info.valor, (*tablaDeSimbolos).info.longitud);

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

int buscarEnTablaDeSimbolos(char *yytext, tLista * tablaDeSimbolos)
{
    while( *tablaDeSimbolos )
    {
        if( (comparar(yytext, &(*tablaDeSimbolos)->info) == 0))
        {
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

int insertarEnTablaDeSimbolos (char *yytext, tLista * tablaDeSimbolos)
{
    int len = strlen(yytext);
    tDato dato;

    dato.valor = (char *) malloc(sizeof(char[yyleng + 1]));
    dato.tipo = (char *) malloc(sizeof(char));
    dato.lexema = (char *) malloc(sizeof(char[yyleng + 2]));
    dato.longitud = (char *) malloc(sizeof(yyleng));

    strcpy(dato.valor, yytext);
    strcpy(dato.tipo, "-");
    strcpy(dato.longitud, "-");
    strcpy(dato.lexema, "_");
    strcat(dato.lexema, yytext);

    tNodo * nuevo = (tNodo*) malloc (sizeof(tNodo));

    if(!nuevo)
        return 0;

    nuevo->info = dato;
    nuevo->sig  = *tablaDeSimbolos;
    *tablaDeSimbolos = nuevo;
    return 1;
}

void validarVariables() {

    if(cantVariables == cantTipoVariables) {
      printf("\nCantidad correcta de variables y tipos\n");
    } else {
      printf("\nCantidad incorrecta de variables y tipos\n");
      exit(1);
    }

}
