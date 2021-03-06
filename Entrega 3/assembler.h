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
    char *token;
    const char s[2] = "@";

    fprintf(f, ".DATA\n\n");

    while (*tablaDeSimbolos)
    {
        float val;
        token = strstr((*tablaDeSimbolos)->info.valor, s);
        switch (obtenerTipoSimbolo((*tablaDeSimbolos)->info.tipo))
        {
        case string:
            if (token != NULL)
            {
                fprintf(f, "%s ", (*tablaDeSimbolos)->info.valor);
            }
            else
            {
                fprintf(f, "_%s ", (*tablaDeSimbolos)->info.valor);
            }

            fprintf(f, "db %d dup (?), \"$\"", LIMITE_STRINGS);
            fprintf(f, "\n");
            break;
        case entero:
            if (token != NULL)
            {
                fprintf(f, "%s ", (*tablaDeSimbolos)->info.valor);
            }
            else
            {
                fprintf(f, "_%s ", (*tablaDeSimbolos)->info.valor);
            }
            fprintf(f, "dd ?");
            fprintf(f, "\n");
            break;
        case real:
            if (token != NULL)
            {
                fprintf(f, "%s ", (*tablaDeSimbolos)->info.valor);
            }
            else
            {
                fprintf(f, "_%s ", (*tablaDeSimbolos)->info.valor);
            }
            fprintf(f, "dd ?");
            fprintf(f, "\n");
            break;
        case constante:
            fprintf(f, "_%s ", (*tablaDeSimbolos)->info.valor);

            // Recupero el tipo de la constante
            strcpy(resultado, buscarTipoEnTablaDeSimbolosSinTabla(obtenerValorTerceto((*tablaDeSimbolos)->info.lexema)));

            if (strcmp(resultado, "CTE_FLOAT") == 0)
            {
                fprintf(f, "dd ?");
            }
            else if (strcmp(resultado, "CTE_INTEGER") == 0)
            {
                fprintf(f, "dd ?");
            }
            else if (strcmp(resultado, "CTE_STRING") == 0)
            {
                fprintf(f, "db %d dup (?), \"$\"", LIMITE_STRINGS);
            }
            fprintf(f, "\n");
            break;
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
    char buffer[100];
    indice indBuffer;

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
                int num = buscarIndiceSimboloEnTablaDeSimbolosSinTabla(terceto.elementos[2].valor.cad);

                fprintf(f, "\tMOV  SI, OFFSET @str%d \n", num);
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
            sprintf(buffer, "@aux%d", i + 1);
            fprintf(f, "\tFLD %s \n\tFLD %s \n\tFADD \n\tFSTP %s",
                    resolverElemento(terceto.elementos[1]), resolverElemento(terceto.elementos[2]), buffer);

            indBuffer = buscarEnTablaDeSimbolos(buffer, tablaDeSimbolos);
            cargartipoVariable(real, indBuffer);
            break;
        case esResta:
            sprintf(buffer, "@aux%d", i + 1);
            fprintf(f, "\tFLD %s \n\tFLD %s \n\tFSUB \n\tFSTP %s",
                    resolverElemento(terceto.elementos[1]), resolverElemento(terceto.elementos[2]), buffer);

            indBuffer = buscarEnTablaDeSimbolos(buffer, tablaDeSimbolos);
            cargartipoVariable(real, indBuffer);
            break;
        case esMultiplicacion:
            sprintf(buffer, "@aux%d", i + 1);
            fprintf(f, "\tFLD %s \n\tFLD %s \n\tFMUL \n\tFSTP %s",
                    resolverElemento(terceto.elementos[1]), resolverElemento(terceto.elementos[2]), buffer);

            indBuffer = buscarEnTablaDeSimbolos(buffer, tablaDeSimbolos);
            cargartipoVariable(real, indBuffer);
            break;
        case esDivision:
            sprintf(buffer, "@aux%d", i + 1);
            fprintf(f, "\tFLD %s \n\tFLD %s \n\tFDIV \n\tFSTP %s",
                    resolverElemento(terceto.elementos[1]), resolverElemento(terceto.elementos[2]), buffer);

            indBuffer = buscarEnTablaDeSimbolos(buffer, tablaDeSimbolos);
            cargartipoVariable(real, indBuffer);
            break;
        case esComparacion:
            fprintf(f, "\tFLD %s \n\tFCOMP %s \n\tFSTSW AX \n\tSAHF",
                    resolverElemento(terceto.elementos[1]), resolverElemento(terceto.elementos[2]));
            break;
        case esUnDesplazamiento:
            salto = terceto.elementos[0].valor.cad;
            indEtiqueta = terceto.elementos[1].valor.ind;
            etiqueta = tercetos[indEtiqueta].elementos[0].valor.cad;
            fprintf(f, "\t%s %s", salto, etiqueta);
            break;

        case esGet:
            strcpy(resultado, buscarTipoEnTablaDeSimbolosSinTabla(terceto.elementos[1].valor.cad));

            if (strcmp(resultado, "STRING") == 0)
            {
                fprintf(f, "\tgetString %s", resolverElemento(terceto.elementos[1]));
            }
            else if (strcmp(resultado, "FLOAT") == 0 || strcmp(resultado, "INTEGER") == 0)
            {
                fprintf(f, "\tGetFloat %s", resolverElemento(terceto.elementos[1]));
            }
            else
            {
                printf("\nError al generar Get de: %s", resolverElemento(terceto.elementos[1]));
            }
            break;
        case esPut:
            strcpy(resultado, buscarTipoEnTablaDeSimbolosSinTabla(terceto.elementos[1].valor.cad));

            if (strcmp(resultado, "STRING") == 0 || strcmp(resultado, "CTE_STRING") == 0)
            {
                fprintf(f, "\tdisplayString %s\n", resolverElemento(terceto.elementos[1]));
                fprintf(f, "\tnewLine");
            }
            else if (strcmp(resultado, "FLOAT") == 0 || strcmp(resultado, "CTE_FLOAT") == 0 || strcmp(resultado, "INTEGER") == 0 || strcmp(resultado, "CTE_INTEGER") == 0)
            {
                fprintf(f, "\tDisplayFloat %s, 2\n", resolverElemento(terceto.elementos[1]));
                fprintf(f, "\tnewLine");
            }
            else if (strcmp(resultado, "CONST") == 0)
            {
                // Recupero el tipo de la constante
                strcpy(resultado, buscarTipoEnTablaDeSimbolosSinTabla(obtenerValorTerceto(terceto.elementos[1].valor.cad)));

                if (strcmp(resultado, "STRING") == 0 || strcmp(resultado, "CTE_STRING") == 0)
                {
                    fprintf(f, "\tdisplayString %s\n", resolverElemento(terceto.elementos[1]));
                    fprintf(f, "\tnewLine");
                }
                else if (strcmp(resultado, "FLOAT") == 0 || strcmp(resultado, "CTE_FLOAT") == 0 || strcmp(resultado, "INTEGER") == 0 || strcmp(resultado, "CTE_INTEGER") == 0)
                {
                    fprintf(f, "\tDisplayFloat %s, 2\n", resolverElemento(terceto.elementos[1]));
                    fprintf(f, "\tnewLine");
                }
                else
                {
                    printf("\nError al generar Put de: %s", resolverElemento(terceto.elementos[1]));
                }
            }
            else
            {
                printf("\nError al generar Put de: %s", resolverElemento(terceto.elementos[1]));
            }
            break;
        case esEtiqueta:
            fprintf(f, "\n%s:", terceto.elementos[0].valor.cad);
            break;
        case esMaximoEncontrado:
            break;
        case esMaximo:
            break;
        case esDesconocido:
            break;
        default:
            break;
        }
        fprintf(f, "\n");
        // PRINTFs para debug
        /*
        fprintf(stdout, "%d: (", i + 1);

        for (j = 0; j < 3; j++) {
            elemento e = terceto.elementos[j];

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

    char tipoSimbolo[30] = "";
    strcpy(tipoSimbolo, buscarTipoEnTablaDeSimbolosSinTabla(e.valor.cad));
    int indiceSimbolo = buscarIndiceSimboloEnTablaDeSimbolosSinTabla(e.valor.cad);

    if (e.tipo == entero)
    {
        sprintf(buffer, "@aux%d", e.valor.ind + 1);
    }
    else if (e.tipo == string)
    {
        if (strcmp(tipoSimbolo, "STRING") == 0 || strcmp(tipoSimbolo, "INTEGER") == 0 || strcmp(tipoSimbolo, "FLOAT") == 0 || strcmp(tipoSimbolo, "CONST") == 0)
        {
            sprintf(buffer, "%s", e.valor.cad);
        }
        else if (strcmp(tipoSimbolo, "CTE_STRING") == 0)
        {
            sprintf(buffer, "@str%d", indiceSimbolo);
        }
        else if (strcmp(tipoSimbolo, "CTE_INTEGER") == 0)
        {
            sprintf(buffer, "@int%d", indiceSimbolo);
        }
        else if (strcmp(tipoSimbolo, "CTE_FLOAT") == 0)
        {
            sprintf(buffer, "@flt%d", indiceSimbolo);
        }
        else
        {
            printf("\nError al resolver elemento de tipo string: %s", e.valor.cad);
            sprintf(buffer, "NULL");
        }
    }
    return strdup(buffer);
}