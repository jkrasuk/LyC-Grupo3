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

	FLD @int5 
	FSTP _nombre
	displayString @str6
	newLine
	displayString @str7
	newLine
	GetFloat _actual
	FLD @int8 
	FSTP _contador
	FLD @flt9 
	FLD _nombre 
	FADD 
	FSTP @aux6
	FLD @aux6 
	FSTP _suma

TAG8:
	FLD _contador 
	FCOMP @int10 
	FSTSW AX 
	SAHF
	JNBE TAG47
	FLD _contador 
	FLD @int11 
	FADD 
	FSTP @aux11
	FLD @aux11 
	FSTP _contador
	FLD _contador 
	FLD @flt12 
	FDIV 
	FSTP @aux13
	FLD @int11 
	FLD @int14 
	FMUL 
	FSTP @aux14
	FLD @aux14 
	FSTP _max
	FLD _suma 
	FSTP _aux
	FLD _aux 
	FCOMP _max 
	FSTSW AX 
	SAHF
	JNA TAG20
	FLD _aux 
	FSTP _max

TAG20:
	FLD @int16 
	FSTP _aux
	FLD _aux 
	FCOMP _max 
	FSTSW AX 
	SAHF
	JNA TAG25
	FLD _aux 
	FSTP _max

TAG25:
	FLD @int16 
	FSTP _max1
	FLD _actual 
	FSTP _aux1
	FLD _aux1 
	FCOMP _max1 
	FSTSW AX 
	SAHF
	JNA TAG31
	FLD _aux1 
	FSTP _max1

TAG31:
	FLD _nombre 
	FSTP _aux1
	FLD _aux1 
	FCOMP _max1 
	FSTSW AX 
	SAHF
	JNA TAG36
	FLD _aux1 
	FSTP _max1

TAG36:
	FLD _max1 
	FSTP _aux
	FLD _aux 
	FCOMP _max 
	FSTSW AX 
	SAHF
	JNA TAG41
	FLD _aux 
	FSTP _max

TAG41:
	FLD @aux13 
	FLD _max 
	FADD 
	FSTP @aux42
	FLD @aux42 
	FSTP _actual
	FLD _suma 
	FLD _actual 
	FADD 
	FSTP @aux44
	FLD @aux44 
	FSTP _suma
	JMP TAG8

TAG47:
	displayString @str19
	newLine
	DisplayFloat _suma, 2
	newLine
	FLD _actual 
	FCOMP _nombre 
	FSTSW AX 
	SAHF
	JNB TAG53
	displayString @str20
	newLine

TAG53:
	FLD _actual 
	FCOMP @int14 
	FSTSW AX 
	SAHF
	JNA TAG60
	FLD _actual 
	FCOMP @int8 
	FSTSW AX 
	SAHF
	JE TAG60
	displayString @str21
	newLine
	JMP TAG64

TAG60:
	FLD _actual 
	FCOMP _nombre 
	FSTSW AX 
	SAHF
	JNB TAG64
	displayString @str20
	newLine

TAG64:


MOV EAX, 4C00h
INT 21h


.DATA

_contador dd ?
_promedio dd ?
_actual dd ?
_suma dd ?
_nombre dd ?
@int5 dd 85.000000
@str6 db "Prueba.txt LyC Tema 3!", "$", 30 dup (?)
@str7 db "Ingrese valor actual: ", "$", 30 dup (?)
@int8 dd 0.000000
@flt9 dd 2.500000
@int10 dd 9.000000
@int11 dd 1.000000
@flt12 dd 0.342000
_max dd ?
@int14 dd 2.000000
_aux dd ?
@int16 dd 4.000000
_max1 dd ?
_aux1 dd ?
@str19 db "La suma es: ", "$", 30 dup (?)
@str20 db "no es mayor que 2", "$", 30 dup (?)
@str21 db "actual  > que 2 y <> de cero", "$", 30 dup (?)
@aux6 dd ?
@aux11 dd ?
@aux13 dd ?
@aux14 dd ?
@aux42 dd ?
@aux44 dd ?

END MAIN
