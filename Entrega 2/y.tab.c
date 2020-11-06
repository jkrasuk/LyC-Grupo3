
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "Sintactico.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "pila_int.h"
#include "tercetos.h"//incluye a tools.h
#define YYDEBUG 1

/*NOTA: No se crean tercetos por cada vez que identifica un ID o CTE. ej: (_1,_,_) ó (b,_,_). Directamente se crean los tercetos con 
los operadores, sean aritmeticos o de asiganión.*/


/* Punteros y pilas para expresiones*/
/* En las expresiones con paréntesis se complico en poder anidar los tercetos, es por eso que se usaron pilas para los indices.*/
pila pilaExpr, pilaTerm, pilaFact, pilaBusquedaMaximo, pilaCond, pilaWhile, pilaMaximo; 
pilaInt pilaTipoComp;



indice indExpr,indTerm, indFact, indComp, indMaximo, indTipoComp; //Punteros a la tabla de simbolos o al array globar de tercetos.

indice aux_maximo,max, indExprAux; //variables para la semantica del maximo.



/* Este array sirve para guardar los simbolos de la ts para que cuando llegue al bloque de declaracion de tipos le asigne el tipo a cada uno.*/
indice tiposVariablesDeclaracion[700];
indice auxindice;
int comparar(char *yytext , tDato *dato );
void inicializarCompilador();
void crearTablaDeSimbolos(tLista *pl);
indice buscarEnTablaDeSimbolos(char *yytext , tLista *tablaDeSimbolos);
indice buscarOInsertarSinTablaDeSimbolos(char *yytext);
indice insertarEnTablaDeSimbolos (char *yytext , tLista *tablaDeSimbolos);
indice crearIndice(int tipoIndice, void * dato_indice);
void cargartipoVariable(int tipo,indice ind);
void cargarConstanteReal  (indice ind,int tipo_real);
void cargarConstanteEntera(indice ind,int tipo_entero);
void cargarConstanteString(indice ind,int tipo_string);
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


/* Line 189 of yacc.c  */
#line 132 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 214 of yacc.c  */
#line 92 "Sintactico.y"

    int intVal;
    float floatVal;
    char strVal[30];
    char* auxLogicOperator;



/* Line 214 of yacc.c  */
#line 263 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 275 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   159

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNRULES -- Number of states.  */
#define YYNSTATES  143

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     8,    11,    13,    22,    26,    28,
      32,    34,    36,    38,    40,    42,    45,    49,    52,    54,
      56,    58,    60,    62,    64,    66,    67,    80,    88,    92,
      93,    99,   103,   105,   106,   112,   113,   122,   125,   128,
     131,   134,   137,   139,   141,   143,   148,   152,   160,   164,
     172,   173,   178,   179,   184,   185,   190,   191,   196,   197,
     202,   203,   208,   209,   214,   215,   220,   222,   223,   228,
     229,   234,   236,   238,   240,   242,   244,   248
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      45,     0,    -1,    -1,    46,    47,    52,    -1,    47,    48,
      -1,    48,    -1,    31,    12,    49,    13,    32,    12,    50,
      13,    -1,    49,    25,     3,    -1,     3,    -1,    50,    25,
      51,    -1,    51,    -1,    21,    -1,    22,    -1,    23,    -1,
      53,    -1,    54,    26,    -1,    53,    54,    26,    -1,    53,
      54,    -1,    54,    -1,    55,    -1,    57,    -1,    65,    -1,
      66,    -1,    63,    -1,    58,    -1,    -1,    28,    34,    67,
      35,    38,    53,    39,    56,    29,    38,    53,    39,    -1,
      28,    34,    67,    35,    38,    53,    39,    -1,     3,     7,
      77,    -1,    -1,    33,     3,    59,     7,    77,    -1,    60,
      25,    77,    -1,    77,    -1,    -1,    43,    62,    34,    60,
      35,    -1,    -1,    42,    64,    34,    67,    35,    38,    53,
      39,    -1,    40,     3,    -1,    40,     4,    -1,    40,     6,
      -1,    40,     5,    -1,    41,     3,    -1,    70,    -1,    69,
      -1,    68,    -1,    20,    34,    70,    35,    -1,    70,    18,
      70,    -1,    34,    70,    35,    18,    34,    70,    35,    -1,
      70,    19,    70,    -1,    34,    70,    35,    19,    34,    70,
      35,    -1,    -1,    77,    71,    14,    77,    -1,    -1,    77,
      72,    15,    77,    -1,    -1,    77,    73,    13,    77,    -1,
      -1,    77,    74,    12,    77,    -1,    -1,    77,    75,    17,
      77,    -1,    -1,    77,    76,    16,    77,    -1,    -1,    77,
      78,     8,    80,    -1,    -1,    77,    79,     9,    80,    -1,
      80,    -1,    -1,    80,    81,    10,    83,    -1,    -1,    80,
      82,    11,    83,    -1,    83,    -1,     3,    -1,     4,    -1,
       6,    -1,     5,    -1,    34,    77,    35,    -1,    61,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   101,   101,   101,   113,   114,   117,   120,   129,   140,
     141,   145,   150,   155,   162,   165,   166,   167,   168,   171,
     172,   173,   174,   175,   176,   180,   179,   188,   194,   201,
     201,   211,   251,   261,   261,   279,   279,   287,   288,   289,
     290,   293,   296,   297,   298,   302,   306,   307,   308,   309,
     312,   312,   320,   320,   328,   328,   336,   336,   344,   344,
     352,   352,   361,   361,   362,   362,   363,   367,   367,   368,
     368,   369,   372,   381,   382,   383,   384,   385
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "CTE_INT", "CTE_STRING",
  "CTE_REAL", "ASIG", "OP_SUMA", "OP_RESTA", "OP_MULT", "OP_DIV", "MENOR",
  "MAYOR", "IGUAL", "DISTINTO", "MENOR_IGUAL", "MAYOR_IGUAL", "AND", "OR",
  "NOT", "INTEGER", "FLOAT", "STRING", "GUION_BAJO", "COMA", "PUNTO_COMA",
  "DOS_PUNTOS", "IF", "ELSE", "ENDIF", "DIM", "AS", "CONST", "P_A", "P_C",
  "C_A", "C_C", "L_A", "L_C", "PUT", "GET", "WHILE", "MAXIMO", "$accept",
  "programa", "$@1", "sentencia_declaracion",
  "bloque_declaracion_variables", "lista_variables", "tipos_variables",
  "tipo_variable", "algoritmo", "bloque", "sentencia", "decision", "$@2",
  "asignacion", "asignacion_constante", "$@3", "lista_expresiones",
  "maximo", "$@4", "iteracion", "$@5", "put", "get", "condicion",
  "comparacion_negada", "comparacion_doble", "comparacion", "$@6", "$@7",
  "$@8", "$@9", "$@10", "$@11", "expresion", "$@12", "$@13", "termino",
  "$@14", "$@15", "factor", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    46,    45,    47,    47,    48,    49,    49,    50,
      50,    51,    51,    51,    52,    53,    53,    53,    53,    54,
      54,    54,    54,    54,    54,    56,    55,    55,    57,    59,
      58,    60,    60,    62,    61,    64,    63,    65,    65,    65,
      65,    66,    67,    67,    67,    68,    69,    69,    69,    69,
      71,    70,    72,    70,    73,    70,    74,    70,    75,    70,
      76,    70,    78,    77,    79,    77,    77,    81,    80,    82,
      80,    80,    83,    83,    83,    83,    83,    83
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     2,     1,     8,     3,     1,     3,
       1,     1,     1,     1,     1,     2,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     0,    12,     7,     3,     0,
       5,     3,     1,     0,     5,     0,     8,     2,     2,     2,
       2,     2,     1,     1,     1,     4,     3,     7,     3,     7,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     1,     0,     4,     0,
       4,     1,     1,     1,     1,     1,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     5,     0,     0,     0,
       0,     0,     0,    35,     4,     3,    14,    18,    19,    20,
      24,    23,    21,    22,     8,     0,     0,     0,    29,    37,
      38,    40,    39,    41,     0,    17,    15,     0,     0,    72,
      73,    75,    74,     0,    33,    77,    28,    66,    71,     0,
       0,     0,    44,    43,    42,    50,     0,     0,    16,     0,
       7,    62,     0,     0,     0,     0,     0,     0,     0,    50,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    76,     0,     0,     0,     0,     0,     0,     0,
       0,    46,    48,     0,     0,     0,     0,     0,     0,    30,
       0,    11,    12,    13,     0,    10,     0,    32,    63,    65,
      68,    70,    45,     0,     0,     0,    51,    53,    55,    57,
      59,    61,     0,     6,     0,     0,    34,     0,     0,    27,
       0,     9,    31,     0,     0,     0,    36,    47,    49,     0,
       0,     0,    26
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     5,     6,    25,   104,   105,    15,    16,
      17,    18,   135,    19,    20,    56,   106,    45,    62,    21,
      34,    22,    23,    51,    52,    53,    54,    73,    74,    75,
      76,    77,    78,    55,    63,    64,    47,    65,    66,    48
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -88
static const yytype_int8 yypact[] =
{
     -88,    20,    13,   -88,    38,     1,   -88,    52,    50,    32,
      58,    81,    73,   -88,   -88,   -88,    80,    55,   -88,   -88,
     -88,   -88,   -88,   -88,   -88,     3,     6,     2,   -88,   -88,
     -88,   -88,   -88,   -88,    44,    69,   -88,    66,    93,   -88,
     -88,   -88,   -88,     6,   -88,   -88,    22,    27,   -88,    67,
       6,    72,   -88,   -88,    -4,   125,    95,     2,   -88,    97,
     -88,     4,    76,   103,   106,   102,   105,     6,    82,   115,
      88,     6,     6,   104,   114,   122,   107,   119,   123,     6,
     108,    25,   -88,     6,     6,     6,     6,     6,   109,    41,
      80,   -88,   -88,     6,     6,     6,     6,     6,     6,    22,
     110,   -88,   -88,   -88,     8,   -88,    -8,    22,    27,    27,
     -88,   -88,   -88,   111,   112,    23,    22,    22,    22,    22,
      22,    22,    80,   -88,    25,     6,   -88,     6,     6,   118,
      49,   -88,    22,   116,   117,   120,   -88,   -88,   -88,   121,
      80,    64,   -88
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -88,   -88,   -88,   -88,   148,   -88,   -88,    30,   -88,   -87,
     -16,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,
     -88,   -88,   -88,    98,   -88,   -88,   -48,   -88,   -88,   -88,
     -88,   -88,   -88,   -25,   -88,   -88,   -10,   -88,   -88,     7
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -70
static const yytype_int16 yytable[] =
{
      35,    46,    68,   115,     8,    39,    40,    41,    42,    39,
      40,    41,    42,   -64,    71,    72,    37,   125,    61,    88,
       3,   123,    49,    91,    92,    69,     8,   126,    38,     9,
     -62,   -64,     4,   124,    10,   130,    50,   -67,   -69,    82,
      43,    11,    12,    13,     4,    44,   101,   102,   103,    44,
       7,     9,     8,   141,    99,    24,    10,    26,   107,   113,
     114,    28,   129,    11,    12,    13,    27,     8,   116,   117,
     118,   119,   120,   121,   108,   109,    33,     9,    57,   133,
     134,    36,    10,     8,    29,    30,    31,    32,   136,    11,
      12,    13,     9,   110,   111,    58,    60,    10,    59,    35,
     132,    67,    79,   142,    11,    12,    13,    70,     9,    81,
      83,    84,    86,    10,    35,    85,    87,    89,    93,    96,
      11,    12,    13,   -62,   -64,    35,    90,   -56,   -54,    94,
     -52,   -60,   -58,   -62,   -64,    95,    97,   -56,   -54,    98,
     -52,   -60,   -58,   100,   112,   127,   128,   -25,   122,   139,
      82,   137,   138,    14,   131,    80,     0,     0,     0,   140
};

static const yytype_int16 yycheck[] =
{
      16,    26,    50,    90,     3,     3,     4,     5,     6,     3,
       4,     5,     6,     9,    18,    19,    13,    25,    43,    67,
       0,    13,    20,    71,    72,    50,     3,    35,    25,    28,
       8,     9,    31,    25,    33,   122,    34,    10,    11,    35,
      34,    40,    41,    42,    31,    43,    21,    22,    23,    43,
      12,    28,     3,   140,    79,     3,    33,     7,    83,    18,
      19,     3,    39,    40,    41,    42,    34,     3,    93,    94,
      95,    96,    97,    98,    84,    85,     3,    28,    34,   127,
     128,    26,    33,     3,     3,     4,     5,     6,    39,    40,
      41,    42,    28,    86,    87,    26,     3,    33,    32,   115,
     125,    34,     7,    39,    40,    41,    42,    35,    28,    12,
      34,     8,    10,    33,   130,     9,    11,    35,    14,    12,
      40,    41,    42,     8,     9,   141,    38,    12,    13,    15,
      15,    16,    17,     8,     9,    13,    17,    12,    13,    16,
      15,    16,    17,    35,    35,    34,    34,    29,    38,    29,
      35,    35,    35,     5,   124,    57,    -1,    -1,    -1,    38
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    45,    46,     0,    31,    47,    48,    12,     3,    28,
      33,    40,    41,    42,    48,    52,    53,    54,    55,    57,
      58,    63,    65,    66,     3,    49,     7,    34,     3,     3,
       4,     5,     6,     3,    64,    54,    26,    13,    25,     3,
       4,     5,     6,    34,    43,    61,    77,    80,    83,    20,
      34,    67,    68,    69,    70,    77,    59,    34,    26,    32,
       3,    77,    62,    78,    79,    81,    82,    34,    70,    77,
      35,    18,    19,    71,    72,    73,    74,    75,    76,     7,
      67,    12,    35,    34,     8,     9,    10,    11,    70,    35,
      38,    70,    70,    14,    15,    13,    12,    17,    16,    77,
      35,    21,    22,    23,    50,    51,    60,    77,    80,    80,
      83,    83,    35,    18,    19,    53,    77,    77,    77,    77,
      77,    77,    38,    13,    25,    25,    35,    34,    34,    39,
      53,    51,    77,    70,    70,    56,    39,    35,    35,    29,
      38,    53,    39
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 101 "Sintactico.y"
    {
              printf("Inicia COMPILADOR\n"); inicializarCompilador();
          }
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 104 "Sintactico.y"
    {
                                            printf("\n Regla - programa: sentencia_declaracion algoritmo \n");
                                            printf("\n COMPILACION EXITOSA \n");
                                            imprimirTablaDeSimbolos();
                                            printf("\n");
                                            imprimirTercetos();
                                          }
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 113 "Sintactico.y"
    {printf("\n Regla - sentencia_declaracion: sentencia_declaracion bloque_declaracion_variables \n");}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 114 "Sintactico.y"
    {printf("\n Regla - sentencia: bloque_declaracion_variables \n");}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 117 "Sintactico.y"
    {printf("\n Regla - bloque_declaracion_variables: DIM MENOR declaracion_variables MAYOR AS MENOR tipos_variables MAYOR \n"); validarVariables();}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 121 "Sintactico.y"
    {
    printf("\n Regla - lista_variables: lista_variables COMA ID \n"); 
    
    auxindice = buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos);
    /*Guardamos el indice del simbolo para despues asignarle el tipo a cada uno.*/
    tiposVariablesDeclaracion[cantVariables] = auxindice;
    cantVariables++; 
  }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 130 "Sintactico.y"
    {
    printf("\n Regla - lista_variables: ID \n");
    
    auxindice = buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos);
    /*Guardamos el indice del simbolo para despues asignarle el tipo a cada uno.*/
    tiposVariablesDeclaracion[cantVariables] = auxindice;
    cantVariables++; 
  }
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 140 "Sintactico.y"
    {printf("\n Regla - lista_variables: lista_variables COMA tipo_variable \n"); }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 141 "Sintactico.y"
    {printf("\n Regla - lista_variables: tipo_variable \n"); }
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 145 "Sintactico.y"
    {
              printf("\n Regla - tipo_variable: INTEGER \n");   
              cargartipoVariable(entero,tiposVariablesDeclaracion[cantTipoVariables]);
              cantTipoVariables++;
            }
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 150 "Sintactico.y"
    {
             printf("\n Regla - tipo_variable: FLOAT \n");    
             cargartipoVariable(real,tiposVariablesDeclaracion[cantTipoVariables]);
             cantTipoVariables++; 
            }
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 155 "Sintactico.y"
    {
              printf("\n Regla - tipo_variable: STRING \n");   
              cargartipoVariable(string,tiposVariablesDeclaracion[cantTipoVariables]);
              cantTipoVariables++;
            }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 162 "Sintactico.y"
    {printf("\n Regla - algoritmo: bloque \n");}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 165 "Sintactico.y"
    {printf("\n Regla - bloque: sentencia PUNTO_COMA \n");}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 166 "Sintactico.y"
    {printf("\n Regla - bloque: bloque sentencia PUNTO_COMA \n");}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 167 "Sintactico.y"
    {printf("\n Regla - bloque: bloque sentencia \n");}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 168 "Sintactico.y"
    {printf("\n Regla - bloque: sentencia \n");}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 171 "Sintactico.y"
    {printf("\n Regla - sentencia: decision \n");}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 172 "Sintactico.y"
    {printf("\n Regla - sentencia: asignacion \n");}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 173 "Sintactico.y"
    {printf("\n Regla - sentencia: put \n");}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 174 "Sintactico.y"
    {printf("\n Regla - sentencia: get \n");}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 175 "Sintactico.y"
    {printf("\n Regla - sentencia: iteracion \n");}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 176 "Sintactico.y"
    {printf("\n Regla - asignacion_constante \n");}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 180 "Sintactico.y"
    {	indice indJmpAux = crearTercetoDesplazamiento("JMP", 0);
								generarCodigoIf();
								apilar(&pilaCond, indJmpAux);
							}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 184 "Sintactico.y"
    {
                printf("\n Regla - decision: IF P_A condicion P_C L_A bloque L_C ELSE L_A bloque L_C \n");
                modificarDesplazamientoTerceto(desapilar(&pilaCond), crearTercetoTag().datoind.indiceTerceto);
              }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 188 "Sintactico.y"
    {
      printf("\n Regla - decision: IF P_A condicion P_C L_A bloque L_C \n");
      generarCodigoIf();
    }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 194 "Sintactico.y"
    {
                                printf("\n Regla - asignacion: ID ASIG expresion \n"); 
                                printf("\n lexema en la asignacion %s \n",(yyvsp[(1) - (3)].strVal));
                                crearTercetoAsignacion(buscarEnTablaDeSimbolos((yyvsp[(1) - (3)].strVal),&tablaDeSimbolos),indExpr);
                              }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 201 "Sintactico.y"
    {
                                auxindice = buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos);
                                cargarConstante(auxindice,constante);
                               }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 205 "Sintactico.y"
    {
                                printf("\n Regla - asignacion_constante: CONST ID ASIG expresion \n");
                                crearTercetoAsignacion(auxindice,indExpr);
                               }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 212 "Sintactico.y"
    {
                max = desapilar(&pilaMaximo);
                printf("\n aca1");
                                  printf("\n\n tengo la dire %p", max);

printf("\n\n %s", max.datoind.punteroSimbolo->lexema);
                printf("\n aca2");

                char *position_ptr = strchr(max.datoind.punteroSimbolo->lexema, 'x');
                                printf("\n aca!!!");

                char* numeroObtenido = ++position_ptr;
                char bufferNombre[20] = "aux";
                strcat(bufferNombre, numeroObtenido);
                printf("\n\n el indice es %s", bufferNombre);

                /*Insertamos el resultado que trae expresion en aux_maximo*/
                printf("\n\n %s \n\n", bufferNombre);
                aux_maximo = buscarEnTablaDeSimbolos(bufferNombre,&tablaDeSimbolos);
                cargartipoVariable(real,aux_maximo);
                crearTercetoAsignacion(aux_maximo,indExpr);
                crearTercetoComparacion(aux_maximo,max);
                /*Insertamos el resultado que trae expresion en aux_maximo*/

                /*Apilar*/
                apilar(&pilaBusquedaMaximo,crearTercetoDesplazamiento("BLE",0));
                /*Apilar*/ 

                /*Avanzar*/ 
                crearTercetoAsignacion(max,aux_maximo);
                /*Avanzar*/

                
                modificarDesplazamientoTerceto(desapilar(&pilaBusquedaMaximo),obtenerIndiceTercetoSiguente());

                apilar(&pilaMaximo, max);

                printf("\n Regla - lista_expresiones:  lista_expresiones COMA termino \n");
              }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 252 "Sintactico.y"
    {
                max = desapilar(&pilaMaximo);

                crearTercetoAsignacion(max,indExpr);
                printf("\n Regla - lista_expresiones: termino \n");
                apilar(&pilaMaximo, max);
              }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 261 "Sintactico.y"
    { 

                  max = crearTercetoMaximo();
                  printf("\n\n tengo la dire %p", max);
                  apilar(&pilaMaximo, max);
imprimirTercetos();
                }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 271 "Sintactico.y"
    {
                  max = desapilar(&pilaMaximo);

                  indMaximo = crearTercetoMaximoEncontrado(max);
                  printf("\n Regla - maximo: MAXIMO P_A lista_expresiones P_C \n");
               }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 279 "Sintactico.y"
    { apilar(&pilaWhile, crearTercetoTag()); }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 280 "Sintactico.y"
    {printf("\n Regla - iteracion: WHILE P_A condicion P_C L_A bloque L_C \n");
																				      crearTercetoDesplazamiento("JMP", desapilar(&pilaWhile).datoind.indiceTerceto); // agrego un terceto con un salto al comienzo del while
                                              indice indTag = crearTercetoTag();
                                              modificarDesplazamientoTerceto(desapilar(&pilaCond), crearTercetoTag().datoind.indiceTerceto);
																			      }
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 287 "Sintactico.y"
    {buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos); crearTercetoPut((yyvsp[(2) - (2)].strVal)); printf("\n Regla - put: PUT ID \n");}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 288 "Sintactico.y"
    {buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos); crearTercetoPutInt((yyvsp[(2) - (2)].intVal)); printf("\n Regla - put: PUT CTE_INT \n");}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 289 "Sintactico.y"
    {buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos); crearTercetoPutReal((yyvsp[(2) - (2)].floatVal)); printf("\n Regla - put: PUT CTE_REAL \n");}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 290 "Sintactico.y"
    {buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos); crearTercetoPutString((yyvsp[(2) - (2)].strVal)); printf("\n Regla - put: PUT CTE_STRING \n");}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 293 "Sintactico.y"
    { crearTercetoGetID((yyvsp[(2) - (2)].strVal)); printf("\n Regla - get: GET ID \n"); }
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 296 "Sintactico.y"
    {printf("\n Regla - condicion: comparacion \n"); apilarInt(&pilaTipoComp, comparacionSimple); }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 297 "Sintactico.y"
    {printf("\n Regla - condicion: comparacion_doble \n");}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 298 "Sintactico.y"
    {printf("\n Regla - condicion: comparacion_negada \n");}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 302 "Sintactico.y"
    {	printf("  Regla - comparacion_negada: NOT P_A comparacion P_C "); negarTerceto(indTercetos-1); apilarInt(&pilaTipoComp, comparacionSimple); }
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 306 "Sintactico.y"
    { printf("\n Regla - comparacion_doble: comparacion AND comparacion \n"); apilarInt(&pilaTipoComp, comparacionDobleAND); }
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 307 "Sintactico.y"
    { printf("\n Regla - comparacion_doble: P_A comparacion P_C AND P_A comparacion P_C \n");  apilarInt(&pilaTipoComp, comparacionDobleAND); }
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 308 "Sintactico.y"
    { printf("\n Regla - comparacion_doble: comparacion OR comparacion \n");  apilarInt(&pilaTipoComp, comparacionDobleOR); crearTercetoTag(); }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 309 "Sintactico.y"
    { printf("\n Regla - comparacion_doble: P_A comparacion P_C OR P_A comparacion P_C \n");  apilarInt(&pilaTipoComp, comparacionDobleOR); crearTercetoTag();}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 312 "Sintactico.y"
    { indExprAux = indExpr; }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 312 "Sintactico.y"
    {
    printf("\n Regla - comparacion: expresion IGUAL expresion \n");
  indComp = crearTercetoComparacion(indExprAux, indExpr); 

  /*Apilar*/
  apilar(&pilaCond, crearTercetoDesplazamiento("BNE",0));
  /*Apilar*/ 
}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 320 "Sintactico.y"
    { indExprAux = indExpr; }
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 320 "Sintactico.y"
    {
    printf("\n Regla - comparacion: expresion DISTINTO expresion \n");
  indComp = crearTercetoComparacion(indExprAux, indExpr); 

  /*Apilar*/
  apilar(&pilaCond, crearTercetoDesplazamiento("BEQ",0));
  /*Apilar*/ 
}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 328 "Sintactico.y"
    { indExprAux = indExpr; }
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 328 "Sintactico.y"
    {
    printf("\n Regla - comparacion: expresion MAYOR expresion \n");
  indComp = crearTercetoComparacion(indExprAux, indExpr); 

  /*Apilar*/
  apilar(&pilaCond, crearTercetoDesplazamiento("BLE",0));
  /*Apilar*/ 
}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 336 "Sintactico.y"
    { indExprAux = indExpr; }
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 336 "Sintactico.y"
    {
    printf("\n Regla - comparacion: expresion MENOR expresion \n");
  indComp = crearTercetoComparacion(indExprAux, indExpr); 

  /*Apilar*/
  apilar(&pilaCond, crearTercetoDesplazamiento("BGE",0));
  /*Apilar*/ 
}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 344 "Sintactico.y"
    { indExprAux = indExpr; }
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 344 "Sintactico.y"
    {
    printf("\n Regla - comparacion: expresion MAYOR_IGUAL expresion \n");
  indComp = crearTercetoComparacion(indExprAux, indExpr); 

  /*Apilar*/
  apilar(&pilaCond, crearTercetoDesplazamiento("BLT",0));
  /*Apilar*/ 
}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 352 "Sintactico.y"
    { indExprAux = indExpr; }
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 352 "Sintactico.y"
    {
    printf("\n Regla - comparacion: expresion MENORR_IGUAL expresion \n");
  indComp = crearTercetoComparacion(indExprAux, indExpr); 

  /*Apilar*/
  apilar(&pilaCond, crearTercetoDesplazamiento("BGT",0));
  /*Apilar*/ 
}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 361 "Sintactico.y"
    {apilar(&pilaExpr, indExpr);}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 361 "Sintactico.y"
    { printf("\n Regla - expresion: expresion OP_SUMA termino\n");  indExpr = crearTercetoOperacion("+", desapilar(&pilaExpr), indTerm);}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 362 "Sintactico.y"
    {apilar(&pilaExpr, indExpr);}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 362 "Sintactico.y"
    { printf("\n Regla - expresion: expresion OP_RESTA termino\n"); indExpr = crearTercetoOperacion("-", desapilar(&pilaExpr), indTerm);}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 363 "Sintactico.y"
    {printf("\n Regla - expresion: termino\n"); indExpr = indTerm;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 367 "Sintactico.y"
    {apilar(&pilaTerm, indTerm);}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 367 "Sintactico.y"
    {printf("\n Regla - termino: termino OP_MULT factor\n"); indTerm = crearTercetoOperacion("*", desapilar(&pilaTerm), indFact);  }
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 368 "Sintactico.y"
    {apilar(&pilaTerm, indTerm);}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 368 "Sintactico.y"
    {printf("\n Regla - termino: termino OP_DIV factor\n");  indTerm = crearTercetoOperacion("/", desapilar(&pilaTerm), indFact);  }
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 369 "Sintactico.y"
    {printf("\n Regla - termino: factor\n"); indTerm = indFact; }
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 373 "Sintactico.y"
    {
              printf("\n Regla - factor: ID \n"); 
              /* en este caso ya debería estar el ID en la ts no haría falta volver a insertarlo (podriamos sacarlo).*/
              indFact =  buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos);  
          }
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 381 "Sintactico.y"
    { printf("\n Regla - factor: CTE_INT \n");      indFact = buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos); cargarConstanteEntera(indFact,entero);}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 382 "Sintactico.y"
    { printf("\n Regla - factor: CTE_REAL \n");    indFact = buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos); cargarConstanteReal(indFact,real);}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 383 "Sintactico.y"
    {printf("\n Regla - factor: CTE_STRING \n"); indFact = buscarEnTablaDeSimbolos(yytext , &tablaDeSimbolos); cargarConstanteString(indFact,string);}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 384 "Sintactico.y"
    {printf("\n Regla - factor: P_A expresion P_C \n"); indFact = indExpr;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 385 "Sintactico.y"
    {printf("\n Regla - factor: maximo \n");         indFact = indMaximo;}
    break;



/* Line 1455 of yacc.c  */
#line 2292 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 388 "Sintactico.y"


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
        printf(" %-40s\t%-10s\t%-40s\t%-5d\n", (*tablaDeSimbolos).info.lexema, (*tablaDeSimbolos).info.tipo, (*tablaDeSimbolos).info.valor, (*tablaDeSimbolos).info.longitud);
        fprintf(archivoTablaDeSimbolos, "%-40s\t%-10s\t%-40s\t%-5d\n", (tablaDeSimbolos)->info.lexema, (tablaDeSimbolos)->info.tipo, (tablaDeSimbolos)->info.valor, (*tablaDeSimbolos).info.longitud);

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
printf("\naca %s\n",(*tablaDeSimbolosCopiaLocal)->info.lexema);
        if(strncmp((*tablaDeSimbolosCopiaLocal)->info.lexema, "_max", strlen("_max")) == 0)
        {
          printf("\n dentro del if");
            dato = (*tablaDeSimbolosCopiaLocal)->info;
                      printf("\n dato asignado del if");
      encontreValor = 1;
        }
            
        tablaDeSimbolosCopiaLocal = &(*tablaDeSimbolosCopiaLocal)->sig;
      }

      if(encontreValor == 0){
        dato.lexema = (char *) malloc(sizeof(""));
        strcpy(dato.lexema, "_");
      }
printf("\n salgo");
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
printf("\n\n ACA!");

    tDato resultado = buscarAuxEnTablaDeSimbolosSinTabla();
    printf("\nHE VUELTO");

    printf("\nHE VUELTO 2");

    printf("\n TENGO EL %s", resultado.lexema);
    // Si encontre algun aux, entonces tengo que agarrar el ultimo y sumarle un numero
    if(strncmp(resultado.lexema, "_max", strlen("_max")) == 0){
        printf("\n nop existe");
        char *position_ptr = strchr(resultado.lexema, 'x');
        char* numeroObtenido = ++position_ptr;
        int auxNumber = atoi(numeroObtenido);
        auxNumber++;
        char numero[10] = "";
        itoa(auxNumber, numero, 10);

        printf("\n --  %s -- \n", numero);
        printf("\n --  %s -- \n", nombre);
        strcat(nombre, numero);
                printf("\n --  %s -- \n", nombre);

    }
printf("\n ARMO CON EL NOMBRE %s", nombre);


    aux_maximo = buscarEnTablaDeSimbolos(nombre,&tablaDeSimbolos);

    cargartipoVariable(real,aux_maximo);
    printf("\n acaaa %s", aux_maximo.datoind.punteroSimbolo->lexema);
crearTerceto(crearElemStr(nombre), crearElemNull(), crearElemNull(), real, esMaximo);
    return aux_maximo;
}
