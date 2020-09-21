flex lexico.l
pause
bison -dyv sintactico.y
pause
gcc.exe lex.yy.c -o Entrega1.exe
pause
pause
Entrega1.exe prueba.txt
del lex.yy.c
del y.tab.c
del y.output
del y.tab.h
del Entrega1.exe
pause