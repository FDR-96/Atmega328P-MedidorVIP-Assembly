/*DIVISION_16
 * IncFile1.inc
 *
 *   Author: FDPR
 */ 


;=======================================================================
; Conversión de Binario a BCD-16 BITS - https://www.youtube.com/watch?v=saId4lt7r48
;=======================================================================
CONVERSION:

		ldi	ZL, LOW(VECTOR)
		ldi	ZH, HIGH(VECTOR)			
		ldi cont, 0x27				;Cargamos 10000
		mov rBin2H,cont
		ldi cont, 0x10
		mov rBin2L,cont
		rcall Bin2ToDigit			;Funcion para calcular digito
		ldi cont, 0x03				;Cargamos 1000
		mov rBin2H,cont
		ldi cont, 0xE8
		mov rBin2L,cont
		rcall Bin2ToDigit			;Funcion para calcular digito
		ldi cont, 0x00				;Cargamos 100
		mov rBin2H,cont
		ldi cont, 0x64
		mov rBin2L,cont
		rcall Bin2ToDigit			;Funcion para calcular digito
		ldi cont, 0x00				;Cargamos 10
		mov rBin2H,cont
		ldi cont, 0x0A
		mov rBin2L,cont
		rcall Bin2ToDigit			;Funcion para calcular digito
		st z,ValorL
		sbiw z,4					;Poner el puntero en el primer BCD
		ret
	Bin2ToDigit:
		clr cont						;Conteo en cero

	Bin2ToDigita:
		cp ValorH,rBin2H			;Comparo nro con comparacion parte alta
		brcs Bin2ToDigitc			;Si Carry=1 el nro es menor a comparacion, vuelve a rutina para comparar con un valor menor
		brne Bin2ToDigitb	 
		cp ValorL,rBin2L			;Si es igual, Comparo nro con comparacion parte baja
		brcs Bin2ToDigitc			;Si Carry=1 nro menor a comparacion

	Bin2ToDigitb:			
		sub ValorL,rBin2L			;Resto partes bajas
		sbc ValorH,rBin2H			;Resto partes altas con carry
		inc cont						;Incremento cuenta para digito BCD
		rjmp Bin2ToDigita			;Repito el proceso hasta que sea menor a comparacion

	Bin2ToDigitc:
		st z+,cont					;Salva el digito 
		ret

;=======================================================================
; Calculo de Tension
;=======================================================================
	
	CALCULO_TENSION:

		lds R23, TensionADCH
		lds R22, TensionADCL	;Carga el numero VAL_Tension en r23:r22
		ldi R21,0x00
		ldi R20,0x1D				;Carga el numero 28 r21:r20
		call MULTIPLICACION_16			;Llamado a rutina de multiplicacion de 16 bits x 16 bits
		sts TensionH, r17			;Guardamos resultado de la primer multiplicacion
		sts TensionL, r16
		ret
	
;=======================================================================
; Calculo de Corriente
;=======================================================================
 
	CALCULO_CORRIENTE:

		lds r23, CorrienteADCH	;Carga valores del ADC
		lds r22, CorrienteADCL
		ldi R21,0x00
		ldi R20,0x14				;Carga el numero 20 r21:r20
		call MULTIPLICACION_16			;Llamado a rutina de multiplicacion de 16 bits x 16 bits
		ldi DivisorH, 0x00			;Carga 10 en el divisor (para obtener nuestro factor >> 1.929) notacion =  da 20480
		ldi DivisorL, 0x0A
		call DIVISION_16			;Llama funcion division = 2048 el valor maximo de corriente
		sts CorrienteH, r17			;Guardamos resultado de la primer multiplicacion
		sts CorrienteL, r16
		ret

;=======================================================================
; Calculo de Potencia
;=======================================================================
 
	CALCULO_POTENCIA:

		lds DividendoH, TensionH	;Cargar valor de tension
		lds DividendoL, TensionL
		ldi DivisorH, 0x03			;Cargar 1000 en divisor
		ldi DivisorL, 0xE8
		call DIVISION_16			;Llamar funcion division
		sts ResultadoH, r17			;Guardar resultado
		sts ResultadoL, r16

		mov DividendoH, RestoH		;Cargar resto para dividir
		mov DividendoL, RestoL
		ldi DivisorH, 0x00			;Cargar 100 en divisor
		ldi DivisorL, 0x64
		call DIVISION_16			;Llamar funcion division		
		sts ValA, r16				;Guardar resultado (primer decimal)

		mov DividendoH, RestoH		;Cargar resto para dividir
		mov DividendoL, RestoL
		ldi DivisorH, 0x00			;Cargar 10 en divisor
		ldi DivisorL, 0x0A
		call DIVISION_16			;Llamar funcion division
		sts ValB, r16				;Guardar resultado (segundo decimal)
		sts ValC, RestoL			;Guardar resto (tercer decimal)

		lds r23, CorrienteH			;Cargar valor de corriente
		lds r22, CorrienteL
		lds r21, ResultadoH			;Cargar valor entero de tension
		lds r20, ResultadoL
		call MULTIPLICACION_16			;Llamar funcion multiplicacion
		sts PotenciaH, r17			;Guardar resultado temporal de la potencia
		sts PotenciaL, r16

		lds r23, CorrienteH			;Cargar valor de corriente
		lds r22, CorrienteL
		ldi r21, 0x00				;Cargar valor del primer decimal
		lds r20, ValA
		call MULTIPLICACION_16			;Llamar funcion multiplicacion
		ldi DivisorH, 0x00			;Cargar 10 en divisor para acomodar numero
		ldi DivisorL, 0x0A
		call DIVISION_16			;Llamar funcion division		
		lds r19, PotenciaH			;Cargar valor temporal de potencia
		lds r18, PotenciaL
		add r16, r18				;Sumar potencia con resultado de corriente por primer decimal
		adc r17, r19
		sts PotenciaH, r17			;Guardar resultado temporal de la potencia
		sts PotenciaL, r16

		lds r23, CorrienteH			;Cargar valor de corriente
		lds r22, CorrienteL
		ldi r21, 0x00				;Cargar valor del segundo decimal
		lds r20, ValB
		call MULTIPLICACION_16			;Llamar funcion multiplicacion
		ldi DivisorH, 0x00			;Cargar 100 en divisor para acomodar numero
		ldi DivisorL, 0x64
		call DIVISION_16			;Llamar funcion division		
		lds r19, PotenciaH			;Cargar valor temporal de potencia
		lds r18, PotenciaL
		add r16, r18				;Sumar potencia con resultado de corriente por primer decimal
		adc r17, r19
		sts PotenciaH, r17			;Guardar resultado temporal de la potencia
		sts PotenciaL, r16

		lds r23, CorrienteH			;Cargar valor de corriente
		lds r22, CorrienteL
		ldi r21, 0x00				;Cargar valor del segundo decimal
		lds r20, ValC
		call MULTIPLICACION_16			;Llamar funcion multiplicacion
		ldi DivisorH, 0x03			;Cargar 1000 en divisor para acomodar numero
		ldi DivisorL, 0xE8
		call DIVISION_16			;Llamar funcion division		
		lds r19, PotenciaH			;Cargar valor temporal de potencia
		lds r18, PotenciaL
		add r16, r18				;Sumar potencia con resultado de corriente por primer decimal
		adc r17, r19
		sts PotenciaH, r17			;Guardar resultado de la potencia
		sts PotenciaL, r16

		ret
;=======================================================================
; Calculo de Corriente PWM
;=======================================================================
 
	CALCULO_CORRIENTE_PWM:	
		
		lds r23, CorrienteH			;Valor corriente 2048 
		lds r22, CorrienteL	
		ldi r21, 0x00				;Multiplicar por 4 = 8192
		ldi r20, 0x04
		call MULTIPLICACION_16
		ldi r19, 0x00				;dividir por 10 = 819
		ldi r18, 0x0A
		call DIVISION_16
		sts CorrienteH_PWM, r17
		sts CorrienteL_PWM, r16
		ldi r20, 0x00
		ldi r19, 0xCC				; sumamos 204 para tener 1V a 5V
		add r16, r19
		adc r17, r20
		sts CorrienteH_PWM, r17
		sts CorrienteL_PWM, r16
		
		ret
;=======================================================================
; Calculo de Potencia PWM 
;=======================================================================
	CALCULO_POTENCIA_PWM:

	    lds DividendoH, PotenciaH	;Cargar valor de potencia
		lds DividendoL, PotenciaL		
		ldi DivisorH, 0x00			;Cargar 100 en divisor
		ldi DivisorL, 0x64
		call DIVISION_16
		sts ResultadoH, r17			;Guardar resultado
		sts ResultadoL, r16
		
		lds r23, ResultadoH			;Valor Potencia 600
		lds r22, ResultadoL	
		ldi r21, 0x00				;multiplico x14
		ldi r20, 0x0E
		call MULTIPLICACION_16
	
		ldi DivisorH, 0x00			;Cargar 10 en divisor, ya se cargo el resultado de la multiplicacion en R16 y R17
		ldi DivisorL, 0x0A
		call DIVISION_16

		ldi r20, 0x00
	    ldi r19, 0xCC				; sumamos 204 para tener 1V a 5V
		add r16, r19
		adc r17, r20
		sts PotenciaH_PWM, r17
		sts PotenciaL_PWM, r16
		
		ret
;=======================================================================
; Subrutina Multiplicación 16x16 
;=======================================================================
	MULTIPLICACION_16:

		mul	r22, r20				;Multiplica parte baja de A con parte baja de B
		movw	r17:r16, r1:r0
		mul	r23, r20				;Multiplica parte alta de A con parte baja de B
		add	r17, r0
		mul	r21, r22				;Multiplica parte baja de A con parte alta de B
		add	r17, r0
									;Resultado r17, r16
		ret
;=======================================================================
; Subrutina División - https://www.youtube.com/watch?v=3jjfxRP_8ZM
;=======================================================================
DIVISION_16:

		SUB		RestoL,RestoL		
		SUB		RestoH,RestoH	
		LDI		Contador,0x11		 
		RJMP	SEGUIR16		 
VOLVER16:
		
		ROL		RestoL		
		ROL		RestoH	
		CP		RestoL,DivisorL		 
		CPC		RestoH,DivisorH		 
		BRCS	SEGUIR16		
		SUB		RestoL,DivisorL		 
		SBC		RestoH,DivisorH		 
SEGUIR16:

		ROL		DividendoL		 
		ROL		DividendoH		 
		DEC		Contador		 
		BRNE	VOLVER16		 
		COM		DividendoL		 
		COM		DividendoH	 
		RET 	