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









max dd ?

aux dd ?

max1 dd ?
aux1 dd ?



.CODE

MAIN:

MOV EAX, @DATA
MOV DS, EAX
MOV ES, EAX


MOV EAX, 4C00h
INT 21h


