;
; Atmega328P-MedidorVIP.asm
;
; Created: 10/4/2021 07:22:44
; Author : FDPR
;


; Replace with your application code
.include "ADC.inc"
.include "PWM.inc"
.include "USART.inc"
.include "SPI.inc"
.include "INT.inc"
.include "Declaraciones.inc"
.include "Operaciones.inc"
.include "MostrarValor.inc"
;ADC.ini    
;=======INIT_ADC: Configura el ADC
;
;




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
.ORG 0x100   ;Definen las variables de un byte y cinco bytes en la memoria de datos SRAM
	VAL_TensionADCH: .Byte 1		; 0x100
	VAL_TensionADCL: .Byte 1		; 0x101
	VAL_CorrienteADCH: .Byte 1		; 0x102
	VAL_CorrienteADCL: .Byte 1		; 0x103 ..etc
	TensionH: .Byte 1
	TensionL: .Byte 1
	PotenciaH: .Byte 1
	PotenciaL: .Byte 1
	CorrienteH: .Byte 1
	CorrienteL: .Byte 1
	RestodivL: .Byte 1
	RestodivH: .Byte 1
	VECTOR: .Byte 5
	DATO_RX: .Byte 1
	GRANDEH: .Byte 1
	GRANDEL: .Byte 1
	Temp1: .Byte 1
	Temp2: .Byte 1
	Temp3: .Byte 1
	CorrienteH_PWM: .Byte 1
	CorrienteL_PWM: .Byte 1
	PotenciaH_PWM: .Byte 1
	PotenciaL_PWM: .Byte 1
	
;########################################################## VECTORES DE INTERRUPCION #########################################################

.CSEG
.ORG 0x00
	jmp INICIO

.ORG 0x000A
	jmp RTI_SELECT
	
.ORG 0x001A
	jmp RTI_TIMER1_OVF

.ORG 0x0024
	jmp USART_RXC

.ORG 0x34
	reti

		INICIO:

			ldi r16, high(ramend)		;Configuracion de pila
			out sph, r16
			ldi r16, low(ramend)
			out spl, r16
			cli
			call INIT_ADC
			call INIT_INT
			call INIT_PWM
			call INIT_USART
			call INIT_SPI
			sei
