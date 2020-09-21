%{
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "y.tab.h"
FILE *  yyin;
int     yylval;
char *  yyltext;

  void validarLimitesConstanteString();
  void validarLimitesConstanteReal();
  void validarLimitesConstanteInt();
  
%}
%option noyywrap
%option yylineno

DIGITO                   [0-9]
LETRA                    [a-zA-Z]
DELIM                    [ \t\n\r]
CARACTER                 [a-z|A-Z|0-9|=|>|<|!|:|+|-|*|/|?|¿|!|¡|@|%|#|&|°|´|^|`|~|/|\\|-|_|.|,|;|¬||]
VALID_STRING             ({CARACTER}+|{DELIM})*
COMENTARIO               --\/.({CARACTER}|{DELIM})*.\/--

CTE_STRING               \"{VALID_STRING}\"
CTE_REAL                 -?{DIGITO}+"."{DIGITO}*
CTE_INT                  -?{DIGITO}+
ID                       {LETRA}({LETRA}|{DIGITO}|_)*

DIM                      [Dd][Ii][Mm]
AS                       [Aa][Ss]
INTEGER                  [Ii][Nn][Tt][Ee][Gg][Ee][Rr]
FLOAT                    [Ff][Ll][Oo][Aa][Tt]
STRING                   [Ss][Tt][Rr][Ii][Nn][Gg]
CONST                    [Cc][Oo][Nn][Ss][Tt]
PUT                      [Pp][Uu][Tt]
GET                      [Gg][Ee][Tt]
WHILE                    [Ww][Hh][Ii][Ll][Ee]
IF                       [Ii][Ff]
ENDIF                    [Ee][Nn][Dd][Ii][Ff]
ELSE                     [Ee][Ll][Ss][Ee]
AND                      [Aa][Nn][Dd]
OR                       [Oo][Rr]
NOT                      [Nn][Oo][Tt]
MAXIMO                   [Mm][Aa][Xx][Ii][Mm][Oo]


%%
.                        yyerror();
%%

int yyerror(void)
{
    printf("Error léxico: linea %d  %s\n", yylineno, yytext);
    system ("Pause");
    exit (1);
}

void validarLimitesConstanteString() 
{
  if (yyleng > 30) 
  {
    printf("Longitud maxima excedida en linea %d\n", yylineno);
    exit(1);
  }
}

void validarLimitesConstanteReal() 
{
  if (atof(yytext) > FLT_MAX || yyleng > 39) 
  {
    printf("Valor maximo excedido en linea %d\n", yylineno);
    exit(1);
  }
}


void validarLimitesConstanteInt() 
{
  if (atoi(yytext) > 32767) 
  {
    printf("Valor maximo excedido en linea %d\n", yylineno);
    exit(1);
  }
}