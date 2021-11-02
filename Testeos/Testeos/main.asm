;
; Testeos.asm
;
; Created: 13/4/2021 07:54:57
; Author : FDPR
;


; Replace with your application code

.MACRO	PUSH_SREG					;Guardar en la pila la posicion de memoria
		push r12
		in r12, SREG			
		push r12					;Guardar registros de trabajo
		push r13
		push r14
		push r15
		push r16
		push r17
		push r18
		push r19
		push r20
		push r21
		push r22
		push r23
		push r24
		push r25
		push r26
		push r27
.ENDMACRO

.MACRO	POP_SREG
		pop r27
		pop r26
		pop r25
		pop r24
		pop r23
		pop r22
		pop r21
		pop r20
		pop r19
		pop r18
		pop r17
		pop r16
		pop r15
		pop r14
		pop r13
		pop r12
		out sreg, r12				;Recuperar de la pila la posicion de memoria
		pop r12
.ENDMACRO

.DSEG
;########################################################## VECTORES DE INTERRUPCION #########################################################

.CSEG
.ORG  0x0000
	jmp INICIO

.ORG 0x34
	reti
.include "Atmega328P_CFG.inc"
.include "USART.inc"
INICIO:

			ldi r16, high(ramend)		;Configuracion de pila
			out sph, r16
			ldi r16, low(ramend)
			out spl, r16
			cli
			call  INIT_USART
			sei


