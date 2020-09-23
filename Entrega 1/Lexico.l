%{
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <float.h>
#include <string.h>
#include "y.tab.h"

void validarLimitesConstanteString();
void validarLimitesConstanteReal();
void validarLimitesConstanteInt();
void validarID();
%}
%option noyywrap
%option yylineno

DIGITO									[0-9]
LETRA									[a-zA-Z]
DELIM									[ \t\n\r]
CARACTER								[a-z|A-Z|0-9|=|>|<|!|:|+|-|*|/|?|¿|!|¡|@|%|#|&|°|´|^|`|~|/|\\|-|_|.|,|;|¬||]
VALID_STRING							({CARACTER}+|{DELIM})*
COMENTARIO								\*-.({CARACTER}|{DELIM})*.-\*

CTE_STRING								\"{VALID_STRING}\"
CTE_REAL								-?{DIGITO}+"."{DIGITO}*
CTE_INT									-?{DIGITO}+
ID										{LETRA}({LETRA}|{DIGITO}|_)*

DIM										[Dd][Ii][Mm]
AS										[Aa][Ss]
INTEGER									[Ii][Nn][Tt][Ee][Gg][Ee][Rr]
FLOAT									[Ff][Ll][Oo][Aa][Tt]
STRING									[Ss][Tt][Rr][Ii][Nn][Gg]
CONST									[Cc][Oo][Nn][Ss][Tt]
PUT										[Pp][Uu][Tt]
GET										[Gg][Ee][Tt]
WHILE									[Ww][Hh][Ii][Ll][Ee]
IF										[Ii][Ff]
ENDIF									[Ee][Nn][Dd][Ii][Ff]
ELSE									[Ee][Ll][Ss][Ee]
AND										[Aa][Nn][Dd]
OR										[Oo][Rr]
NOT										[Nn][Oo][Tt]
MAXIMO									[Mm][Aa][Xx][Ii][Mm][Oo]


%%

"+"										{ return OP_SUMA; }
"-"										{ return OP_RESTA; }
"*"										{ return OP_MULT; }
"/"										{ return OP_DIV; }
"="										{ return ASIG; }
"("										{ return P_A; }
")"										{ return P_C; }
"{"										{ return L_A; }
"}"										{ return L_C; }
"["										{ return C_A; }
"]"										{ return C_C; }
";"										{ return PUNTO_COMA; }
","										{ return COMA; }
":"										{ return DOS_PUNTOS; }
"_"										{ return GUION_BAJO; }
{DIM}									{ return DIM; }
{AS}									{ return AS; }
{CONST}									{ return CONST; }
{PUT}									{ return PUT; }
{GET}									{ return GET; }
{WHILE}									{ return WHILE; }
{IF}									{ return IF; }
{ENDIF}									{ return ENDIF; }
{ELSE}									{ return ELSE; }
{AND}									{ return AND; }
{OR}									{ return OR; }
{NOT}									{ return NOT; }
{MAXIMO}								{ return MAXIMO; }
">"										{ return MAYOR; }
">="									{ return MAYOR_IGUAL; }
"<"										{ return MENOR; }
"<="									{ return MENOR_IGUAL; }
"=="									{ return IGUAL; }
"<>"									{ return DISTINTO; }
{FLOAT}									{ strcpy(yylval.strVal, yytext); return FLOAT;}
{INTEGER}								{ strcpy(yylval.strVal, yytext); return INTEGER; }
{STRING}								{ strcpy(yylval.strVal, yytext); return STRING; }
{CTE_INT}							{ validarLimitesConstanteInt(); yylval.intVal = atoi(yytext);  return CTE_INT; }
{CTE_STRING}							{ validarLimitesConstanteString(); strcpy(yylval.strVal, yytext);  return CTE_STRING; }
{CTE_REAL}								{ validarLimitesConstanteReal(); yylval.floatVal = atof(yytext);  return CTE_REAL; }
{ID}									{ strcpy(yylval.strVal, yytext); validarID();  return ID; }
" "
"\t"
"\n"
{COMENTARIO}
<<EOF>>									{ yyterminate(); }
%%

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

void validarID()
{
	if (yyleng > 10) 
	{
		printf("Longitud maxima excedida en linea %d\n", yylineno);
		fprintf(stderr, "Fin de ejecucion.\n");
		system ("Pause");
		exit (1);
	}
}

int yyerror(void)
{
	printf("Syntax Error\n");
	system ("Pause");
	exit (1);
}