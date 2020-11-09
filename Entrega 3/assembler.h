#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void generaAssembler();
void generaHeader(FILE*);
void generaCuerpo(FILE*);
void generaTablaDeSimbolos(FILE*);

void generaAssembler() {
    FILE *f;

    if ((f = fopen("Final.asm", "w")) == NULL) {
        printf("No se puede crear el archivo Final.asm");
        exit(1);
    }

    generaHeader(f);
    generaTablaDeSimbolos(f);
    generaCuerpo(f);
    
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

void generaTablaDeSimbolos(FILE* f) {
    fprintf(f, ".DATA\n\n");

    // Recorrer la tabla de simbolos
}

void generaCuerpo(FILE* f) {
    fprintf(f, ".CODE\n\n");
    fprintf(f, "MAIN:\n\n");
    fprintf(f, "MOV EAX, @DATA\n");
    fprintf(f, "MOV DS, EAX\n");
    fprintf(f, "MOV ES, EAX\n\n");

    // Aca van los tercetos

    fprintf(f, "\n");
    fprintf(f, "MOV EAX, 4C00h\n");
    fprintf(f, "INT 21h\n\n");
    fprintf(f, "\n");
}