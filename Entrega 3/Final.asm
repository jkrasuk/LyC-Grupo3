include macros.asm
include macros2.asm
include number.asm

.MODEL LARGE
.386
.STACK 200h

.DATA

contador dd ?
promedio dd ?
actual dd ?
suma dd ?
@int5 dd 85.000000
@str6 db ""Prueba.txt LyC Tema 3!"", "$", 30 dup (?)
@str7 db ""Ingrese valor actual: "", "$", 30 dup (?)
@int8 dd 0.000000
@flt9 dd 2.500000
@int10 dd 9.000000
@int11 dd 1.000000
@flt12 dd 0.342000
max dd ?
@int14 dd 2.000000
aux dd ?
@int16 dd 4.000000
max1 dd ?
aux1 dd ?
@str19 db ""La suma es: "", "$", 30 dup (?)
@str20 db ""no es mayor que 2"", "$", 30 dup (?)
@str21 db ""actual  > que 2 y <> de cero"", "$", 30 dup (?)

.CODE

MAIN:

MOV EAX, @DATA
MOV DS, EAX
MOV ES, EAX


MOV EAX, 4C00h
INT 21h


