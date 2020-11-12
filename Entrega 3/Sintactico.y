%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "pila_int.h"
#include "assembler.h"
#define YYDEBUG 1

/*NOTA: No se crean tercetos por cada vez que identifica un ID o CTE. ej: (_1,_,_) ó (b,_,_). Directamente se crean los tercetos con 
los operadores, sean aritmeticos o de asiganión.*/


/* Punteros y pilas para expresiones*/
/* En las expresiones con paréntesis se complico en poder anidar los tercetos, es por eso que se usaron pilas para los indices.*/
pila pilaExpr, pilaTerm, pilaFact, pilaBusquedaMaximo, pilaCond, pilaWhile, pilaMaximo; 
pilaInt pilaTipoComp;



indice indExpr,indTerm, indFact, indComp, indMaximo, indTipoComp, indPut; //Punteros a la tabla de simbolos o al array globar de tercetos.

indice aux_maximo,max, indExprAux; //variables para la semantica del maximo.



/* Este array sirve para guardar los simbolos de la ts para que cuando llegue al bloque de declaracion de tipos le asigne el tipo a cada uno.*/
indice tiposVariablesDeclaracion[700];
indice auxindice;
int comparar(char *yytext , tDato *dato );
void inicializarCompilador();
void crearTablaDeSimbolos(tLista *pl);
indice buscarEnTablaDeSimbolos(char *yytext , tLista *tablaDeSimbolos);
void validarExistenciaId(char *yytext, tLista * tablaDeSimbolos);
void validarDuplicacionId(char *yytext, tLista * tablaDeSimbolos);
indice insertarEnTablaDeSimbolos (char *yytext , tLista *tablaDeSimbolos);
indice crearIndice(int tipoIndice, void * dato_indice);
void cargartipoVariable(int tipo,indice ind);
void cargarConstanteReal  (indice ind,int tipo_real);
void cargarConstanteEntera(indice ind,int tipo_entero);
void cargarConstanteString(indice ind,int tipo_string);
void cargarConstanteCteReal  (indice ind,int tipo_real);
void cargarConstanteCteEntera(indice ind,int tipo_entero);
void cargarConstanteCteString(indice ind,int tipo_string);
void cargarConstante(indice ind, int tipo_constante);
void generarCodigoIf();
void imprimirTablaDeSimbolos();
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
                                            printf("\n COMPILACION EXITOSA \n");
                                            generaAssembler(&tablaDeSimbolos);
                                           imprimirTablaDeSimbolos();
                                            printf("\n");
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
    validarDuplicacionId(yytext , &tablaDeSimbolos);
    printf("\n Regla - lista_variables: lista_variables COMA ID \n"); 
    
    auxindice = buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos);
    /*Guardamos el indice del simbolo para despues asignarle el tipo a cada uno.*/
    tiposVariablesDeclaracion[cantVariables] = auxindice;
    cantVariables++; 
  }
|ID 
  {
    validarDuplicacionId(yytext , &tablaDeSimbolos);

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

decision: IF P_A condicion P_C L_A bloque L_C 
              {	indice indJmpAux = crearTercetoDesplazamiento("JMP", 0);
								generarCodigoIf();
								apilar(&pilaCond, indJmpAux);
							}
          ELSE L_A bloque L_C {
                printf("\n Regla - decision: IF P_A condicion P_C L_A bloque L_C ELSE L_A bloque L_C \n");
                modificarDesplazamientoTerceto(desapilar(&pilaCond), crearTercetoTag().datoind.indiceTerceto);
              }
  | IF P_A condicion P_C L_A bloque L_C {
      printf("\n Regla - decision: IF P_A condicion P_C L_A bloque L_C \n");
      generarCodigoIf();
    }
  ;

asignacion: ID {validarExistenciaId(yytext , &tablaDeSimbolos);} ASIG expresion {
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

lista_expresiones: lista_expresiones COMA expresion 
              {
                max = desapilar(&pilaMaximo);

                char *position_ptr = strchr(max.datoind.punteroSimbolo->lexema, 'x');
                char* numeroObtenido = ++position_ptr;
                char bufferNombre[20] = "aux";
                strcat(bufferNombre, numeroObtenido);

                /*Insertamos el resultado que trae expresion en aux_maximo*/
                aux_maximo = buscarEnTablaDeSimbolos(bufferNombre,&tablaDeSimbolos);
                cargartipoVariable(real,aux_maximo);
                crearTercetoAsignacion(aux_maximo,indExpr);
                crearTercetoComparacion(aux_maximo,max);
                /*Insertamos el resultado que trae expresion en aux_maximo*/

                /*Apilar*/
                apilar(&pilaBusquedaMaximo,crearTercetoDesplazamiento("JNA",0));
                /*Apilar*/ 

                /*Avanzar*/ 
                crearTercetoAsignacion(max,aux_maximo);
                /*Avanzar*/

                
                modificarDesplazamientoTerceto(desapilar(&pilaBusquedaMaximo),obtenerIndiceTercetoSiguente());

                apilar(&pilaMaximo, max);

                printf("\n Regla - lista_expresiones:  lista_expresiones COMA termino \n");
              }
 | expresion 
              {
                max = desapilar(&pilaMaximo);

                crearTercetoAsignacion(max,indExpr);
                printf("\n Regla - lista_expresiones: termino \n");
                apilar(&pilaMaximo, max);
              }
 ;

maximo: MAXIMO  { 

                  max = crearTercetoMaximo();
                  apilar(&pilaMaximo, max);
                } 

                P_A lista_expresiones P_C  

               {
                  max = desapilar(&pilaMaximo);

                  indMaximo = crearTercetoMaximoEncontrado(max);
                  printf("\n Regla - maximo: MAXIMO P_A lista_expresiones P_C \n");
               }
  ;

iteracion: WHILE { apilar(&pilaWhile, crearTercetoTag()); } 
            P_A condicion P_C L_A bloque L_C {printf("\n Regla - iteracion: WHILE P_A condicion P_C L_A bloque L_C \n");
																				      crearTercetoDesplazamiento("JMP", desapilar(&pilaWhile).datoind.indiceTerceto); // agrego un terceto con un salto al comienzo del while
                                              indice indTag = crearTercetoTag();
                                              modificarDesplazamientoTerceto(desapilar(&pilaCond), crearTercetoTag().datoind.indiceTerceto);
																			      }
  ;

put: PUT ID {validarExistenciaId(yytext , &tablaDeSimbolos); buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos); crearTercetoPut($2); printf("\n Regla - put: PUT ID \n");}
  | PUT CTE_INT {indPut = buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos);  cargarConstanteCteEntera(indPut,cteEntero); crearTercetoPutInt($2); printf("\n Regla - put: PUT CTE_INT \n");}
  | PUT CTE_REAL {indPut = buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos);  cargarConstanteCteReal(indPut,cteReal); crearTercetoPutReal($2); printf("\n Regla - put: PUT CTE_REAL \n");}
  | PUT CTE_STRING {indPut = buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos);  cargarConstanteCteString(indPut,cteString); crearTercetoPutString($2); printf("\n Regla - put: PUT CTE_STRING \n");}
  ;
   
get: GET ID { crearTercetoGetID($2); printf("\n Regla - get: GET ID \n"); }
  ;

condicion: comparacion {printf("\n Regla - condicion: comparacion \n"); apilarInt(&pilaTipoComp, comparacionSimple); }
  | comparacion_doble {printf("\n Regla - condicion: comparacion_doble \n");}
  | comparacion_negada {printf("\n Regla - condicion: comparacion_negada \n");}
  ;

comparacion_negada:
	NOT P_A comparacion P_C {	printf("  Regla - comparacion_negada: NOT P_A comparacion P_C "); negarTerceto(indTercetos-1); apilarInt(&pilaTipoComp, comparacionSimple); }
    ;

comparacion_doble:
	comparacion AND comparacion	{ printf("\n Regla - comparacion_doble: comparacion AND comparacion \n"); apilarInt(&pilaTipoComp, comparacionDobleAND); }
	| P_A comparacion P_C AND P_A comparacion P_C 	{ printf("\n Regla - comparacion_doble: P_A comparacion P_C AND P_A comparacion P_C \n");  apilarInt(&pilaTipoComp, comparacionDobleAND); }
  | comparacion OR comparacion 	{ printf("\n Regla - comparacion_doble: comparacion OR comparacion \n");  apilarInt(&pilaTipoComp, comparacionDobleOR); crearTercetoTag(); }
  | P_A comparacion P_C OR P_A comparacion P_C 	{ printf("\n Regla - comparacion_doble: P_A comparacion P_C OR P_A comparacion P_C \n");  apilarInt(&pilaTipoComp, comparacionDobleOR); crearTercetoTag();}
	;

comparacion: expresion { indExprAux = indExpr; } IGUAL expresion {
    printf("\n Regla - comparacion: expresion IGUAL expresion \n");
  indComp = crearTercetoComparacion(indExprAux, indExpr); 

  /*Apilar*/
  apilar(&pilaCond, crearTercetoDesplazamiento("JNE",0));
  /*Apilar*/ 
} 
| expresion { indExprAux = indExpr; } DISTINTO expresion {
    printf("\n Regla - comparacion: expresion DISTINTO expresion \n");
  indComp = crearTercetoComparacion(indExprAux, indExpr); 

  /*Apilar*/
  apilar(&pilaCond, crearTercetoDesplazamiento("JE",0));
  /*Apilar*/ 
}
| expresion { indExprAux = indExpr; } MAYOR expresion {
    printf("\n Regla - comparacion: expresion MAYOR expresion \n");
  indComp = crearTercetoComparacion(indExprAux, indExpr); 

  /*Apilar*/
  apilar(&pilaCond, crearTercetoDesplazamiento("JNA",0));
  /*Apilar*/ 
} 
| expresion { indExprAux = indExpr; } MENOR expresion {
    printf("\n Regla - comparacion: expresion MENOR expresion \n");
  indComp = crearTercetoComparacion(indExprAux, indExpr); 

  /*Apilar*/
  apilar(&pilaCond, crearTercetoDesplazamiento("JNB",0));
  /*Apilar*/ 
}
| expresion { indExprAux = indExpr; } MAYOR_IGUAL expresion {
    printf("\n Regla - comparacion: expresion MAYOR_IGUAL expresion \n");
  indComp = crearTercetoComparacion(indExprAux, indExpr); 

  /*Apilar*/
  apilar(&pilaCond, crearTercetoDesplazamiento("JNAE",0));
  /*Apilar*/ 
} 
| expresion { indExprAux = indExpr; } MENOR_IGUAL expresion {
    printf("\n Regla - comparacion: expresion MENORR_IGUAL expresion \n");
  indComp = crearTercetoComparacion(indExprAux, indExpr); 

  /*Apilar*/
  apilar(&pilaCond, crearTercetoDesplazamiento("JNBE",0));
  /*Apilar*/ 
};

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
              validarExistenciaId(yytext , &tablaDeSimbolos);
              printf("\n Regla - factor: ID \n"); 
              /* en este caso ya debería estar el ID en la ts no haría falta volver a insertarlo (podriamos sacarlo).*/
              indFact =  buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos);  
          }



  | CTE_INT { printf("\n Regla - factor: CTE_INT \n");      indFact = buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos); cargarConstanteCteEntera(indFact,cteEntero);} 
  | CTE_REAL { printf("\n Regla - factor: CTE_REAL \n");    indFact = buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos); cargarConstanteCteReal(indFact,cteReal);}
  | CTE_STRING {printf("\n Regla - factor: CTE_STRING \n"); indFact = buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos); cargarConstanteCteString(indFact,cteString);}
  | P_A expresion P_C {printf("\n Regla - factor: P_A expresion P_C \n"); indFact = indExpr;}
  | maximo {printf("\n Regla - factor: maximo \n");         indFact = indMaximo;}
  ;

%%

int main(int argc, char *argv[]) {

    crearTablaDeSimbolos(&tablaDeSimbolos);
    yydebug = 0;
    if ((yyin = fopen(argv[1], "rt")) == NULL) {
        printf("\nNo se puede abrir el archivo: %s\n", argv[1]);
    } else {
        yyparse();
    }

    fclose(yyin);

    return 0;
}
void imprimirTablaDeSimbolos(){
    FILE *archivoTablaDeSimbolos;

    archivoTablaDeSimbolos = fopen("ts.txt", "wt");

    printf("\n TABLA DE SIMBOLOS\n");
    printf("\n %-40s\t%-10s\t%-40s\t%-5s", "NOMBRE", "TIPO DATO", "VALOR", "LONGITUD");

    if (!archivoTablaDeSimbolos) {
        printf("no se pudo abrir el archivo");
    } else {
        fprintf(archivoTablaDeSimbolos, "%-40s\t%-10s\t%-40s\t%-5s\n", "NOMBRE", "TIPO DATO", "VALOR", "LONGITUD");
    }

    while (tablaDeSimbolos) {


    if(strcmp((*tablaDeSimbolos).info.tipo, "CTE_INTEGER") == 0 ||
          strcmp((*tablaDeSimbolos).info.tipo, "CTE_STRING") == 0 ||
          strcmp((*tablaDeSimbolos).info.tipo, "CTE_FLOAT") == 0){
        printf(" %-40s\t%-10s\t%-40s\t%-5d\n", (*tablaDeSimbolos).info.lexema, (*tablaDeSimbolos).info.tipo, (*tablaDeSimbolos).info.valor, (*tablaDeSimbolos).info.longitud);
        fprintf(archivoTablaDeSimbolos, "%-40s\t%-10s\t%-40s\t%-5d\n", (tablaDeSimbolos)->info.lexema, (tablaDeSimbolos)->info.tipo, (tablaDeSimbolos)->info.valor, (*tablaDeSimbolos).info.longitud);
    } else {
    printf(" %-40s\t%-10s\t%-40s\t%-5s\n", (*tablaDeSimbolos).info.lexema, (*tablaDeSimbolos).info.tipo, (*tablaDeSimbolos).info.valor, "-");
        fprintf(archivoTablaDeSimbolos, "%-40s\t%-10s\t%-40s\t%-5s\n", (tablaDeSimbolos)->info.lexema, (tablaDeSimbolos)->info.tipo, (tablaDeSimbolos)->info.valor, "-");
    }
        

        tablaDeSimbolos = (*tablaDeSimbolos).sig;
    }
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
    while(*tablaDeSimbolosCopiaLocal )
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

tDato buscarAuxEnTablaDeSimbolosSinTabla()
{
    int encontreValor = 0;
    tDato dato;
    tLista * tablaDeSimbolosCopiaLocal = &tablaDeSimbolos;
    while(*tablaDeSimbolosCopiaLocal )
    {
        if(strncmp((*tablaDeSimbolosCopiaLocal)->info.lexema, "_max", strlen("_max")) == 0)
        {
            dato = (*tablaDeSimbolosCopiaLocal)->info;
            encontreValor = 1;
        }
            
        tablaDeSimbolosCopiaLocal = &(*tablaDeSimbolosCopiaLocal)->sig;
      }

      if(encontreValor == 0){
        dato.lexema = (char *) malloc(sizeof(""));
        strcpy(dato.lexema, "_");
      }

    return dato;
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

    if(!nuevo){
        indice ind;
        ind.tipo=noEsNuevo;
        return ind;
    }

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
        case cteEntero:
            tipoT = "CTE_INTEGER";
            break;
        case cteReal:
            tipoT = "CTE_FLOAT";
            break;
        case cteString:
            tipoT = "CTE_STRING";
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
void cargarConstanteCteReal(indice ind, int tipo_real){
  ind.datoind.punteroSimbolo->tipo="CTE_FLOAT";
}
void cargarConstanteCteString(indice ind, int tipo_string){
  ind.datoind.punteroSimbolo->tipo="CTE_STRING";
}
void cargarConstanteCteEntera(indice ind, int tipo_entero){
  ind.datoind.punteroSimbolo->tipo="CTE_INTEGER";
}
void cargarConstante(indice ind, int tipo_constante){
  ind.datoind.punteroSimbolo->tipo="CONST";
}

void validarExistenciaId(char *yytext, tLista * tablaDeSimbolos)
{
    while( *tablaDeSimbolos )
    {
        if( (comparar(yytext, &(*tablaDeSimbolos)->info) == 0))
        {
            return;
        }
        else
        {
            tablaDeSimbolos = &(*tablaDeSimbolos)->sig;
        }
    }

    printf("\nLa variable %s no fue declarada.\n", yytext);
    exit(1);
}

void validarDuplicacionId(char *yytext, tLista * tablaDeSimbolos)
{
    while( *tablaDeSimbolos )
    {
        if( (comparar(yytext, &(*tablaDeSimbolos)->info) == 0))
        {
          printf("\nLa variable %s ya fue declarada.\n", yytext);
          exit(1);
        }
        else
        {
            tablaDeSimbolos = &(*tablaDeSimbolos)->sig;
        }
    }
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
    inicializarPila(&pilaMaximo);
    inicializarPilaInt(&pilaTipoComp);
}

void generarCodigoIf() {
    tipoComparacion tipoComp = desapilarInt(&pilaTipoComp);
    
    if (tipoComp == comparacionSimple) {
        indice indTag = crearTercetoTag();
        modificarDesplazamientoTerceto(desapilar(&pilaCond), indTag.datoind.indiceTerceto);
    } else if (tipoComp == comparacionDobleOR) {
        indice indJump2 = desapilar(&pilaCond);
        indice indJump1 = desapilar(&pilaCond);
        negarTerceto(indJump1.datoind.indiceTerceto);
        indice indTag = crearTercetoTag();

        modificarDesplazamientoTerceto(indJump1, indJump1.datoind.indiceTerceto + 3);
        modificarDesplazamientoTerceto(indJump2, indTag.datoind.indiceTerceto);
    } else { /* Es una comparación doble con AND */
        indice indJump2 = desapilar(&pilaCond);
        indice indJump1 = desapilar(&pilaCond);
        indice indTag = crearTercetoTag();
        modificarDesplazamientoTerceto(indJump1, indTag.datoind.indiceTerceto);
        modificarDesplazamientoTerceto(indJump2, indTag.datoind.indiceTerceto);
    }
}

indice crearTercetoMaximo(){
    char nombre[20] = "max";

    tDato resultado = buscarAuxEnTablaDeSimbolosSinTabla();

    // Si encontre algun aux, entonces tengo que agarrar el ultimo y sumarle un numero
    if(strncmp(resultado.lexema, "_max", strlen("_max")) == 0){
        char *position_ptr = strchr(resultado.lexema, 'x');
        char* numeroObtenido = ++position_ptr;
        int auxNumber = atoi(numeroObtenido);
        auxNumber++;
        char numero[10] = "";
        itoa(auxNumber, numero, 10);
        strcat(nombre, numero);
    }

    aux_maximo = buscarEnTablaDeSimbolos(nombre,&tablaDeSimbolos);

    cargartipoVariable(real,aux_maximo);

    return aux_maximo;
}