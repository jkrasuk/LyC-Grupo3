#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "tercetos.h" //incluye a tools.h
#define LIMITE_STRINGS 30

void generaAssembler(tLista *tablaDeSimbolos);
void generaHeader(FILE *);
void generaCuerpo(FILE *, tLista *tablaDeSimbolos);
void generaTablaDeSimbolos(FILE *, tLista *tablaDeSimbolos);
char *resolverElemento(elemento e);

void generaAssembler(tLista *tablaDeSimbolos)
{
    FILE *f;

    if ((f = fopen("Final.asm", "w")) == NULL)
    {
        printf("No se puede crear el archivo Final.asm");
        exit(1);
    }

    generaHeader(f);
    generaCuerpo(f, tablaDeSimbolos);
    // Pongo la tabla de simbolos despues del cuerpo ya que puedo tener auxiliares que no se tuvieron en cuenta en GCI
    generaTablaDeSimbolos(f, tablaDeSimbolos);

    if (fclose(f) != 0)
    {
        printf("No se puede cerrar el archivo Final.asm");
        exit(1);
    }

    printf("\nGenerado archivo final.asm\n");
}

void generaHeader(FILE *f)
{
    fprintf(f, "include macros.asm\n");
    fprintf(f, "include macros2.asm\n");
    fprintf(f, "include number.asm\n\n");
    fprintf(f, ".MODEL LARGE\n");
    fprintf(f, ".386\n");
    fprintf(f, ".STACK 200h\n");
    fprintf(f, "\n");
}

void generaTablaDeSimbolos(FILE *f, tLista *tablaDeSimbolos)
{
    int i = 0;
    char resultado[20] = "";
    fprintf(f, ".DATA\n\n");

    while (*tablaDeSimbolos)
    {
        float val;
        switch (obtenerTipoSimbolo((*tablaDeSimbolos)->info.tipo))
        {
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
            strcpy(resultado, buscarTipoEnTablaDeSimbolosSinTabla(obtenerValorTerceto((*tablaDeSimbolos)->info.lexema)));

            if (strcmp(resultado, "CTE_FLOAT") == 0)
            {
                val = atof((*tablaDeSimbolos)->info.valor);
                fprintf(f, "dd %f", val);
            }
            else if (strcmp(resultado, "CTE_INTEGER") == 0)
            {
                val = atof((*tablaDeSimbolos)->info.valor);
                fprintf(f, "dd %f", val);
            }
            else if (strcmp(resultado, "CTE_STRING") == 0)
            {
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

void generaCuerpo(FILE *f, tLista *tablaDeSimbolos)
{
    int i, j;

    fprintf(f, "\n.CODE\n\n");
    fprintf(f, "MAIN:\n\n");
    fprintf(f, "MOV EAX, @DATA\n");
    fprintf(f, "MOV DS, EAX\n");
    fprintf(f, "MOV ES, EAX\n\n");

    // Aca van los tercetos
    for (i = 0; i < indTercetos; i++)
    {
        terceto terceto = tercetos[i];
        char *salto, *etiqueta, *str, *strSimbolo, resultado[800] = "";
        int indEtiqueta, indSimbolo;

        switch (terceto.tipoTerc)
        {
        case esAsignacion:
            strcpy(resultado, buscarTipoEnTablaDeSimbolosSinTabla(terceto.elementos[1].valor.cad));

            if (strcmp(resultado, "STRING") == 0)
            {
                strcpy(resultado, buscarTipoEnTablaDeSimbolosSinTabla(terceto.elementos[2].valor.cad));
                fprintf(f, "\tMOV  SI, OFFSET @str%d \n", resultado);
                fprintf(f, "\tMOV  DI, OFFSET %s \n", resolverElemento(terceto.elementos[1]));
                fprintf(f, "\tSTRCPY");
            }
            else
            {
                fprintf(f, "\tFLD %s \n\tFSTP %s",
                        resolverElemento(terceto.elementos[2]), resolverElemento(terceto.elementos[1]));
            }
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
            fprintf(f, "\t%s %s", salto, etiqueta);
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

char *resolverElemento(elemento e)
{
    char buffer[100];
    printf("\n el tipo es %d", e.tipo);

    char tipoSimbolo[30] = "";
    strcpy(tipoSimbolo, buscarTipoEnTablaDeSimbolosSinTabla(e.valor.cad));
    int indiceSimbolo = buscarIndiceSimboloEnTablaDeSimbolosSinTabla(e.valor.cad);

    if (e.tipo == string || e.tipo == entero || e.tipo == real)
    {
        printf("\n\n %s \n\n", e.valor.cad);
        sprintf(buffer, "%s", e.valor.cad);
    }
    else if (e.tipo == cteString)
    {
        sprintf(buffer, "@str%d", indiceSimbolo);
    }
    else if (e.tipo == cteEntero)
    {
        sprintf(buffer, "@int%d", indiceSimbolo);
    }
    else if (e.tipo == cteReal)
    {
        sprintf(buffer, "@flt%d", indiceSimbolo);
    }
    else
    {
        printf("\nError al resolver elemento de tipo string: %s", e.valor.cad);
        sprintf(buffer, "NULL");
    }

    return strdup(buffer);
}