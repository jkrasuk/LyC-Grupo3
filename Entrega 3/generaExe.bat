flex Lexico.l
pause
bison -dyv Sintactico.y
pause
gcc.exe lex.yy.c y.tab.c -o Grupo03.exe
pause
pause
Grupo03.exe prueba.txt
del lex.yy.c
del y.tab.c
del y.output
del y.tab.h
pause