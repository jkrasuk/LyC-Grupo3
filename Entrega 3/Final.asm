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

	FLD _85 
	FSTP _nombre



	FLD _0 
	FSTP _contador

	FLD  
	FSTP _suma

TAG8:

	JNBE TAG49

	FLD  
	FSTP _contador


	FLD _^‹å]Â 
	FSTP _max
	FLD _suma 
	FSTP _aux

	JNA TAG20
	FLD _aux 
	FSTP _max

TAG20:
	FLD _4 
	FSTP _aux

	JNA TAG25
	FLD _aux 
	FSTP _max

TAG25:
	FLD _4 
	FSTP _max1
	FLD _actual 
	FSTP _aux1

	JNA TAG31
	FLD _aux1 
	FSTP _max1

TAG31:
	FLD _nombre 
	FSTP _aux1

	JNA TAG36
	FLD _aux1 
	FSTP _max1

TAG36:

	FLD _^‹å]Â 
	FSTP _aux

	JNA TAG42
	FLD _aux 
	FSTP _max

TAG42:


	FLD  
	FSTP _actual

	FLD  
	FSTP _suma
	JMP TAG8

TAG49:



	JNB TAG55


TAG55:

	JNA TAG62

	JE TAG62

	JMP TAG66

TAG62:

	JNB TAG66


TAG66:


MOV EAX, 4C00h
INT 21h


.DATA

contador dd ?
promedio dd ?
actual dd ?
suma dd ?
@int5 dd 85.000000
@str6 db "Prueba.txt LyC Tema 3!", "$", 30 dup (?)
@str7 db "Ingrese valor actual: ", "$", 30 dup (?)
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
@str19 db "La suma es: ", "$", 30 dup (?)
@str20 db "no es mayor que 2", "$", 30 dup (?)
@str21 db "actual  > que 2 y <> de cero", "$", 30 dup (?)

END MAIN
