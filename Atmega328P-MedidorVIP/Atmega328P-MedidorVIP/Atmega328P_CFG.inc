

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
.def	Contador = r20				;Subrutina division
.def	rBin2L = r21					;Subrutina descomposicion
.def	rBin2H = r22					;Subrutina descomposicion


;=======================================================================
; VECTOR DE INTERRUPCION
;=======================================================================
.equ REINICIO =  0x0000			; Pin externo, reinicio de encendido, reinicio de bajada y reinicio del sistema de vigilancia.
.equ INTERRUPCION_EXTERNA_2 = 0x000A			; Solicitud de interrupción de cambio de pin 2
.equ TIMER_COUNTER1_DESBORDAMIENTO = 0x001A	; Timer/Counter1 Overflow
.equ USART_RX  = 0x0024		; USART Rx Completo


