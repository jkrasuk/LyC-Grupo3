
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     CTE_INT = 259,
     CTE_STRING = 260,
     CTE_REAL = 261,
     ASIG = 262,
     OP_SUMA = 263,
     OP_RESTA = 264,
     OP_MULT = 265,
     OP_DIV = 266,
     MENOR = 267,
     MAYOR = 268,
     IGUAL = 269,
     DISTINTO = 270,
     MENOR_IGUAL = 271,
     MAYOR_IGUAL = 272,
     AND = 273,
     OR = 274,
     NOT = 275,
     INTEGER = 276,
     FLOAT = 277,
     STRING = 278,
     GUION_BAJO = 279,
     COMA = 280,
     PUNTO_COMA = 281,
     DOS_PUNTOS = 282,
     IF = 283,
     ELSE = 284,
     ENDIF = 285,
     DIM = 286,
     AS = 287,
     CONST = 288,
     P_A = 289,
     P_C = 290,
     C_A = 291,
     C_C = 292,
     L_A = 293,
     L_C = 294,
     PUT = 295,
     GET = 296,
     WHILE = 297,
     MAXIMO = 298
   };
#endif
/* Tokens.  */
#define ID 258
#define CTE_INT 259
#define CTE_STRING 260
#define CTE_REAL 261
#define ASIG 262
#define OP_SUMA 263
#define OP_RESTA 264
#define OP_MULT 265
#define OP_DIV 266
#define MENOR 267
#define MAYOR 268
#define IGUAL 269
#define DISTINTO 270
#define MENOR_IGUAL 271
#define MAYOR_IGUAL 272
#define AND 273
#define OR 274
#define NOT 275
#define INTEGER 276
#define FLOAT 277
#define STRING 278
#define GUION_BAJO 279
#define COMA 280
#define PUNTO_COMA 281
#define DOS_PUNTOS 282
#define IF 283
#define ELSE 284
#define ENDIF 285
#define DIM 286
#define AS 287
#define CONST 288
#define P_A 289
#define P_C 290
#define C_A 291
#define C_C 292
#define L_A 293
#define L_C 294
#define PUT 295
#define GET 296
#define WHILE 297
#define MAXIMO 298




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 92 "Sintactico.y"

    int intVal;
    float floatVal;
    char strVal[30];
    char* auxLogicOperator;



/* Line 1676 of yacc.c  */
#line 147 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


