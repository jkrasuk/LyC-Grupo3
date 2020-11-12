#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "tercetos.h"//incluye a tools.h
#define LIMITE_STRINGS 30

void generaAssembler(tLista * tablaDeSimbolos);
void generaHeader(FILE*);
void generaCuerpo(FILE*);
void generaTablaDeSimbolos(FILE*, tLista * tablaDeSimbolos);

void generaAssembler(tLista * tablaDeSimbolos) {
    FILE *f;

    if ((f = fopen("Final.asm", "w")) == NULL) {
        printf("No se puede crear el archivo Final.asm");
        exit(1);
    }

    generaHeader(f);
    generaCuerpo(f);
    // Pongo la tabla de simbolos despues del cuerpo ya que puedo tener auxiliares que no se tuvieron en cuenta en GCI
    generaTablaDeSimbolos(f, tablaDeSimbolos);

    if (fclose(f) != 0) {
        printf("No se puede cerrar el archivo Final.asm");
        exit(1);
    }

    printf("\nGenerado archivo final.asm\n");
}

void generaHeader(FILE* f) {
    fprintf(f, "include macros.asm\n");
    fprintf(f, "include macros2.asm\n");
    fprintf(f, "include number.asm\n\n");
    fprintf(f, ".MODEL LARGE\n");
    fprintf(f, ".386\n");
    fprintf(f, ".STACK 200h\n");
    fprintf(f, "\n");
}

void generaTablaDeSimbolos(FILE* f, tLista * tablaDeSimbolos) {
	int i = 0;
    char resultado[20] = "";
    fprintf(f, ".DATA\n\n");

    while(*tablaDeSimbolos )
    {
        float val;
        switch(obtenerTipoSimbolo((*tablaDeSimbolos)->info.tipo)) {
            case string:
                fprintf(f, "%s ", (*tablaDeSimbolos)->info.valor);
                fprintf(f, "db %d dup (?), \"$\"", LIMITE_STRINGS);
                fprintf(f, "\n");
                break;
            case entero:
                fprintf(f, "%s ", (*tablaDeSimbolos)->info.valor);
                fprintf(f, "dd ?");
                fprintf(f, "\n");
                break;
            case real:
                fprintf(f, "%s ", (*tablaDeSimbolos)->info.valor);
                fprintf(f, "dd ?");
                fprintf(f, "\n");
                break;
            /*case constante:
                fprintf(f, "%s ", (*tablaDeSimbolos)->info.valor);

                // Recupero el tipo de la constante
				strcpy(resultado, buscarEnTablaDeSimbolosSinTabla(obtenerValorTerceto((*tablaDeSimbolos)->info.lexema)));
			
				if(strcmp(resultado, "CTE_FLOAT") == 0){
		            val = atof((*tablaDeSimbolos)->info.valor);
            		fprintf(f, "dd %f", val);
		        } else if(strcmp(resultado, "CTE_INTEGER") == 0){
		            val = atof((*tablaDeSimbolos)->info.valor);
                	fprintf(f, "dd %f", val);
		        } else if(strcmp(resultado, "CTE_STRING") == 0){
			         fprintf(f, "db \"%s\", \"$\", %d dup (?)", (*tablaDeSimbolos)->info.valor, LIMITE_STRINGS);
		        }

                break;*/
            case cteEntero:
                fprintf(f, "@int%d ", i);
                val = atof((*tablaDeSimbolos)->info.valor);
                fprintf(f, "dd %f", val);
                fprintf(f, "\n");
                break;
            case cteReal:
                fprintf(f, "@flt%d ", i);
                val = atof((*tablaDeSimbolos)->info.valor);
                fprintf(f, "dd %f", val);
                fprintf(f, "\n");
                break;
            case cteString:
                fprintf(f, "@str%d ", i);
                fprintf(f, "db %s, \"$\", %d dup (?)", (*tablaDeSimbolos)->info.valor, LIMITE_STRINGS);
                fprintf(f, "\n");
                break;
            default:
            	break;
        }
        tablaDeSimbolos = &(*tablaDeSimbolos)->sig;
        i++;
    }

    fprintf(f, "\nEND MAIN\n");
}

void generaCuerpo(FILE* f) {
	int i,j;

    fprintf(f, "\n.CODE\n\n");
    fprintf(f, "MAIN:\n\n");
    fprintf(f, "MOV EAX, @DATA\n");
    fprintf(f, "MOV DS, EAX\n");
    fprintf(f, "MOV ES, EAX\n\n");

    // Aca van los tercetos
    for (i = 0; i < indTercetos; i++) {
        terceto terceto = tercetos[i];
        char* salto, *etiqueta, *str, *strSimbolo;
        int indEtiqueta, indSimbolo;

        switch(terceto.tipoTerc){
        	case esAsignacion:
        		break;
		    case esSuma:
		    	break;
		    case esResta:
		    	break;
		    case esMultiplicacion:
		    	break;
		    case esDivision:
		    	break;
		    case esComparacion:
		    	break;
		    case esUnDesplazamiento:
                salto = terceto.elementos[0].valor.cad;
                indEtiqueta = terceto.elementos[1].valor.ind;
                etiqueta = tercetos[indEtiqueta].elementos[0].valor.cad;
                fprintf(f, "\tTERCETO %d %s %s", i+1, salto, etiqueta);
		    	break;
		    case esMaximoEncontrado:
		    	break;
		    case esMaximo:
		    	break;
		    case esGet:
		    	break;
		    case esPut:
		    	break;
		    case esDesconocido:
		    	break;
		    case esEtiqueta:
                fprintf(f, "\n%s:", terceto.elementos[0].valor.cad);
		    	break;
		    default:
		    	break;
        }
        fprintf(f, "\n");
        // PRINTFs para debug
        /*
        fprintf(stdout, "%d: (", i + 1);

        for (j = 0; j < 3; j++) {
            elemento e = t.elementos[j];

            switch (e.tipo) {
                case string:
                    fprintf(stdout, "%s", e.valor.cad);
                    break;
                case entero:
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
        */
    }
    fprintf(f, "\n\n");
    fprintf(f, "MOV EAX, 4C00h\n");
    fprintf(f, "INT 21h\n\n");
    fprintf(f, "\n");
}