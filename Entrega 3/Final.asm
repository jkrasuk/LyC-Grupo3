include macros.asm
include macros2.asm
include number.asm

.MODEL LARGE
.386
.STACK 200h

.CODE

MAIN:

MOV EAX, @DATA
MOV DS, EAX
MOV ES, EAX


MOV EAX, 4C00h
INT 21h


