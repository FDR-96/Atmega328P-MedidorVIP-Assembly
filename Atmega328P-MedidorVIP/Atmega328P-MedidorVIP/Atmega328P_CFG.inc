
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
.equ ASCII_J = 0x50
.equ ASCII_K = 0x51
.equ ASCII_L = 0x52
.equ ASCII_M = 0x53
.equ ASCII_N = 0x54
.equ ASCII_O = 0x55
.equ ASCII_P = 0x56
.equ ASCII_Q = 0x57
.equ ASCII_T = 0x58
.equ ASCII_U = 0x59
.equ ASCII_V = 0x60
.equ ASCII_W = 0x61
.equ ASCII_X = 0x62
.equ ASCII_Y = 0x63
.equ ASCII_Z = 0x64
.equ ASCII_ESPACIO = 0x20
.equ ASCII_IGUAL = 0x3D

;=======================================================================
; DEFINICION DE BYTES EN LA MEMORIA DE DATOS SRAM
;=======================================================================
.equ	VAL_TensionADCH = 0x100		; 0x100
.equ	VAL_TensionADCL = 0x101		; 0x101
.equ	VAL_CorrienteADCH = 0x102		; 0x102
.equ	VAL_CorrienteADCL = 0x103	; 0x103 ..etc
.equ	TensionH = 0x104
.equ	TensionL = 0x105
.equ	PotenciaH = 0x106
.equ	PotenciaL = 0x107
.equ	CorrienteH = 0x108
.equ	CorrienteL = 0x109
.equ	RestodivL = 0x10A
.equ	RestodivH = 0x10B
.equ	VECTOR = 0x120
.equ	DATO_RX = 0x121
.equ	GRANDEH = 0x122
.equ	GRANDEL = 0x123
.equ	Temp1 = 0x124
.equ	Temp2 = 0x125
.equ	Temp3 = 0x126
.equ	CorrienteH_PWM = 0x127
.equ	CorrienteL_PWM = 0x128
.equ	PotenciaH_PWM = 0x129
.equ	PotenciaL_PWM = 0x12A
.def	rmp = r23	
.def	ENTEROL = r12					;Subrutina mostrar
.def	ENTEROH = r13					;Subrutina mostrar
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
.equ INTERRUPCION_EXTERNA_2 = 0x000A			; Solicitud de interrupción de cambio de pin 2
.equ TIMER_COUNTER1_DESBORDAMIENTO = 0x001A	; Timer/Counter1 Overflow
.equ USART_RX  = 0x0024		; USART Rx Completo
