%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YYDEBUG 1
extern int yylex();
extern int yyparse();
extern yylineno;
extern FILE* yyin;

%}

%token ID CTE_INT CTE_STRING CTE_REAL
%token ASIG OP_SUMA OP_RESTA OP_MULT OP_DIV
%token MENOR MAYOR IGUAL DISTINTO MENOR_IGUAL MAYOR_IGUAL
%token AND OR NOT
%token INTEGER FLOAT STRING 
%token GUION_BAJO COMA PUNTO_COMA DOS_PUNTOS
%token IF ELSE ENDIF
%token DIM AS
%token P_A P_C C_A C_C
%token PUT GET
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
%start programa
%type <intVal> CTE_INT
%type <floatVal> CTE_REAL
%type <strVal> CTE_STRING
%type <strVal> ID

%type <auxLogicOperator> logic_operator
%type <auxLogicOperator> logic_concatenator

%union 
{
  int intVal;
  float floatVal;
  char strVal[30];
  char* auxLogicOperator;
}

%%
programa: sentencia_declaracion {printf("\n Regla - COMPILACION EXITOSA\n");}
  ;

sentencia_declaracion: bloque_declaracion_variables {printf("\n Regla: sentencia: bloque_declaracion_variables \n");}
  ;

bloque_declaracion_variables: DIM MENOR declaracion_variables MAYOR AS MENOR tipos_variables MAYOR {printf("\n Regla: bloque_declaracion_variables: DIM MENOR declaracion_variables MAYOR AS MENOR tipos_variables MAYOR \n");}
  ;

put: PUT ID {printf("\n Regla: print: PRINT ID \n");}
  | put CTE_INT {printf("\n Regla: print: PRINT CTE_INT \n");}
  | put CTE_REAL {printf("\n Regla: print: PRINT CTE_REAL \n");}
  | put CTE_STRING {printf("\n Regla: print: PRINT CTE_STRING \n");}
  ;
   
get: GET ID {printf("\n Regla: read: GET ID \n");};

condicion: comparacion {printf("\n Regla: condicion: comparacion \n");}
  | comparacion logic_concatenator comparacion {printf("\n Regla: condicion: comparacion logic_concatenator comparacion \n");}
  | NOT P_A comparacion P_C {printf("\n Regla: condicion: NOT comparacion \n");}
  ;

comparacion: expresion  logic_operator  expresion {printf("\n Regla: comparacion: expresion  logic_operator  expresion \n");}
  ;

logic_operator: IGUAL {printf("\n Regla: logic_operator: IGUAL \n");}
  | DISTINTO {printf("\n Regla: logic_operator: DISTINTO \n");}
  | MAYOR {printf("\n Regla: logic_operator: MAYOR \n");}
  | MAYOR_IGUAL {printf("\n Regla: logic_operator: MAYOR_IGUAL \n");}
  | MENOR {printf("\n Regla: logic_operator: MENOR \n");}
  | MENOR_IGUAL {printf("\n Regla: logic_operator: MENOR_IGUAL \n");}
  ;

logic_concatenator: OR {printf("\n Regla: logic_concatenator: OR \n");}
  | AND {printf("\n Regla: logic_concatenator: AND \n");}
  ;

expresion: expresion OP_SUMA termino {printf("\n Regla - expresion: expresion OP_SUMA termino\n");}
  | expresion OP_RESTA termino { printf("\n Regla - expresion: expresion OP_RESTA termino\n");}
  | termino {printf("\n Regla - expresion: termino\n");}
  ;

termino: termino OP_MULT factor {printf("\n Regla - termino: termino OP_MULT factor\n");}
  | termino OP_DIV factor {printf("\n Regla - termino: termino OP_DIV factor\n");}
  | factor {printf("\n Regla - termino: factor\n");}
  ;

factor: ID {printf("\n Regla - factor: ID \n");}
  | CTE_INT {printf("\n Regla - factor: CTE_INT \n");}
  | CTE_REAL { printf("\n Regla - factor: CTE_REAL \n");}
  | CTE_STRING {printf("\n Regla - factor: CTE_STRING \n");}
  | P_A expresion P_C {printf("\n Regla - factor: P_A expresion P_C \n");}
  ;

%%

int main(int argc, char *argv[]) 
{
    yyin = fopen(argv[1], "r");
      yydebug = 0;
  printf("COMENZANDO COMPILACION\n");
    do 
  {
        yyparse();
    } 
  while(!feof(yyin));

    return 0;
}

