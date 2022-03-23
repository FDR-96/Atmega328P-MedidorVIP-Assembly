.def	cont = r23	
.def	ValorL = r12					;Subrutina mostrar
.def	ValorH = r13					;Subrutina mostrar
.def	RestoL = r14					;Subrutina division
.def	RestoH = r15					;Subrutina division
.def	DividendoL = r16				;Subrutina division
.def	DividendoH = r17				;Subrutina division
.def	DivisorL = r18				;Subrutina division
.def	DivisorH = r19				;Subrutina division
.def	Contador = r20				;Subrutina division2
.def	rBin2L = r21					;Subrutina descomposicion
.def	rBin2H = r22					;Subrutina descomposicion


;=======================================================================
; VECTOR DE INTERRUPCION
;=======================================================================
.equ REINICIO =  0x0000			; Pin externo, reinicio de encendido, reinicio de bajada y reinicio del sistema de vigilancia.
.equ INTERRUPCION_EXTERNA_2 = 0x000A			; Solicitud de interrupci�n de cambio de pin 2
.equ TIMER_COUNTER1_DESBORDAMIENTO = 0x001A	; Timer/Counter1 Overflow
.equ USART_RX  = 0x0024		; USART Rx Completo



;=======================================================================
; ASCII ETIQUETAS
;=======================================================================
.equ ASCII_A = 0x41
.equ ASCII_B = 0x42
.equ ASCII_C = 0x43
.equ ASCII_D = 0x44
.equ ASCII_E = 0x45
.equ ASCII_F = 0x46
.equ ASCII_G = 0x47
.equ ASCII_H = 0x48
.equ ASCII_I = 0x49
.equ ASCII_J = 0x4A
.equ ASCII_K = 0x4B
.equ ASCII_L = 0x4C
.equ ASCII_M = 0x4D
.equ ASCII_N = 0x4E
.equ ASCII_O = 0x4F
.equ ASCII_P = 0x50
.equ ASCII_Q = 0x51
.equ ASCII_R = 0x52
.equ ASCII_S = 0x53
.equ ASCII_T = 0x54
.equ ASCII_U = 0x55
.equ ASCII_V = 0x56
.equ ASCII_W = 0x57
.equ ASCII_X = 0x58
.equ ASCII_Y = 0x59
.equ ASCII_Z = 0x5A
.equ ASCII_ESPACIO = 0x20
.equ ASCII_IGUAL = 0x3D

;=======================================================================
; DEFINICION DE BYTES EN LA MEMORIA DE DATOS SRAM
;=======================================================================

.DSEG

.ORG 0x100
	TensionADCH: .Byte 1
	TensionADCL: .Byte 1
	CorrienteADCH: .Byte 1
	CorrienteADCL: .Byte 1
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
	ResultadoH: .Byte 1
	ResultadoL: .Byte 1
	ValA: .Byte 1
	ValB: .Byte 1
	ValC: .Byte 1
	CorrienteH_PWM: .Byte 1
	CorrienteL_PWM: .Byte 1
	PotenciaH_PWM: .Byte 1
	PotenciaL_PWM: .Byte 1
.CSEG