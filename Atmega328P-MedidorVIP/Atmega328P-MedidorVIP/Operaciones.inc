/*
 * IncFile1.inc
 *
 *  Created: 10/4/2021 07:45:29
 *   Author: FDPR
 */ 

.def	ENTEROL=r12					;Subrutina mostrar
.def	ENTEROH=r13					;Subrutina mostrar
.def	RestoL=r14					;Subrutina division
.def	RestoH=r15					;Subrutina division
.def	DividendoL=r16				;Subrutina division
.def	DividendoH=r17				;Subrutina division
.def	DivisorL=r18				;Subrutina division
.def	DivisorH=r19				;Subrutina division
.def	Contador=r20				;Subrutina division
.def	rBin2L=r21					;Subrutina descomposicion
.def	rBin2H=r22					;Subrutina descomposicion
.def	rmp=r23						;Subrutina descomposicion



DESCOMPOSICION:

		ldi	ZL, LOW(VECTOR)
		ldi	ZH, HIGH(VECTOR)			
		ldi rmp, 0x27				;Cargamos 10000
		mov rBin2H,rmp
		ldi rmp, 0x10
		mov rBin2L,rmp
		rcall Bin2ToDigit			;Funcion para calcular digito
		ldi rmp, 0x03				;Cargamos 1000
		mov rBin2H,rmp
		ldi rmp, 0xE8
		mov rBin2L,rmp
		rcall Bin2ToDigit			;Funcion para calcular digito
		ldi rmp, 0x00				;Cargamos 100
		mov rBin2H,rmp
		ldi rmp, 0x64
		mov rBin2L,rmp
		rcall Bin2ToDigit			;Funcion para calcular digito
		ldi rmp, 0x00				;Cargamos 10
		mov rBin2H,rmp
		ldi rmp, 0x0A
		mov rBin2L,rmp
		rcall Bin2ToDigit			;Funcion para calcular digito
		st z,ENTEROL
		sbiw ZL,4					;Poner el puntero en el primer BCD
		ret
	Bin2ToDigit:
		clr rmp						;Conteo en cero

	Bin2ToDigita:
		cp ENTEROH,rBin2H			;Comparo nro con comparacion parte alta
		brcs Bin2ToDigitc			;Si Carry=1 el nro es menor a comparacion, vuelve a rutina para comparar con un valor menor
		brne Bin2ToDigitb	 
		cp ENTEROL,rBin2L			;Si es igual, Comparo nro con comparacion parte baja
		brcs Bin2ToDigitc			;Si Carry=1 nro menor a comparacion

	Bin2ToDigitb:			
		sub ENTEROL,rBin2L			;Resto partes bajas
		sbc ENTEROH,rBin2H			;Resto partes altas con carry
		inc rmp						;Incremento cuenta para digito BCD
		rjmp Bin2ToDigita			;Repito el proceso hasta que sea menor a comparacion

	Bin2ToDigitc:
		st z+,rmp					;Salva el digito 
		ret


;################################################################### CALCULO DE TENSION ###################################################################
	
	CALCULO_TENSION:
		
		lds R23, VAL_TensionADCH
		lds R22, VAL_TensionADCL	;Carga el numero VAL_Tension en r23:r22
		ldi R21,0x00
		ldi R20,0x13				;Carga el numero 19 r21:r20
		call mul16x16_16			;Llamado a rutina de multiplicacion de 16 bits x 16 bits
		sts GRANDEH, r17			;Guardamos resultado de la primer multiplicacion
		sts GRANDEL, r16

		lds R23, VAL_TensionADCH
		lds R22, VAL_TensionADCL	;Carga el numero VAL_Tension en r23:r22
		ldi R21,0x00
		ldi R20,0x05				;Carga el numero 5 r21:r20
		call mul16x16_16			;Llamado a rutina de multiplicacion de 16 bits x 16 bits
		
		ldi	DivisorL,0x0A			;El dividendo ya esta en r16 y r17
		ldi	DivisorH,0x00			;Dividimos por 10
		call Division16_16

		lds r19, GRANDEH
		lds r18, GRANDEL
		add r18, r16				;Sumamos primer calculo con segundo calculo
		adc r19, r17
		sts	TensionH, r19			;Valor de la tension
		sts	TensionL, r18

		lds R23, VAL_TensionADCH
		lds R22, VAL_TensionADCL	;Carga el numero VAL_Tension en r23:r22
		ldi R21,0x00
		ldi R20,0x03				;Carga el numero 3 r21:r20
		call mul16x16_16			;Llamado a rutina de multiplicacion de 16 bits x 16 bits
	
		ldi	DivisorL,0x64			;El dividendo ya esta en r16 y r17
		ldi	DivisorH,0x00			;Dividimos por 100
		call Division16_16

		lds r19, TensionH
		lds r18, TensionL

		add r18, DividendoL			;Sumamos primer calculo con segundo calculo
		adc r19, DividendoH
		sts	TensionH, r19			;Valor de la tension real
		sts	TensionL, r18
		ret

;################################################################### CALCULO DE CORRIENTE ###################################################################
 
	CALCULO_CORRIENTE:

		lds r23, VAL_CorrienteADCH	;Carga valores del ADC
		lds r22, VAL_CorrienteADCL
		ldi R21,0x00
		ldi R20,0x1D				;Carga el numero 29 r21:r20
		call mul16x16_16			;Llamado a rutina de multiplicacion de 16 bits x 16 bits
		ldi DivisorH, 0x00			;Carga 10 en el divisor (para obtener nuestro factor >> 2.929)
		ldi DivisorL, 0x0A
		call Division16_16			;Llama funcion division
		sts GRANDEH, r17			;Guardamos resultado de la primer multiplicacion
		sts GRANDEL, r16

		lds r23, VAL_CorrienteADCH	;Carga valores del ADC
		lds r22, VAL_CorrienteADCL
		ldi R21,0x00
		ldi R20,0x1D				;Carga el numero 29 r21:r20
		call mul16x16_16			;Llamado a rutina de multiplicacion de 16 bits x 16 bits
		ldi DivisorH, 0x03			;Carga 10 en el divisor (para obtener nuestro factor >> 2.929)
		ldi DivisorL, 0xE8
		call Division16_16			;Llama funcion division

		lds r19, GRANDEH
		lds r18, GRANDEL

		add r18, DividendoL			;Sumamos primer calculo con segundo calculo
		adc r19, DividendoH
		sts CorrienteH, r19			;Resultado corriente
		sts CorrienteL, r18
		 				
		ret

;################################################################### CALCULO DE POTENCIA ###################################################################
 
	CALCULO_POTENCIA:

		lds DividendoH, TensionH	;Cargar valor de tension
		lds DividendoL, TensionL
		ldi DivisorH, 0x03			;Cargar 1000 en divisor
		ldi DivisorL, 0xE8
		call Division16_16			;Llamar funcion division
		sts GRANDEH, r17			;Guardar resultado
		sts GRANDEL, r16

		mov DividendoH, RestoH		;Cargar resto para dividir
		mov DividendoL, RestoL
		ldi DivisorH, 0x00			;Cargar 100 en divisor
		ldi DivisorL, 0x64
		call Division16_16			;Llamar funcion division		
		sts Temp1, r16				;Guardar resultado (primer decimal)

		mov DividendoH, RestoH		;Cargar resto para dividir
		mov DividendoL, RestoL
		ldi DivisorH, 0x00			;Cargar 10 en divisor
		ldi DivisorL, 0x0A
		call Division16_16			;Llamar funcion division
		sts Temp2, r16				;Guardar resultado (segundo decimal)
		sts Temp3, RestoL			;Guardar resto (tercer decimal)

		lds r23, CorrienteH			;Cargar valor de corriente
		lds r22, CorrienteL
		lds r21, GRANDEH			;Cargar valor entero de tension
		lds r20, GRANDEL
		call mul16x16_16			;Llamar funcion multiplicacion
		sts PotenciaH, r17			;Guardar resultado temporal de la potencia
		sts PotenciaL, r16

		lds r23, CorrienteH			;Cargar valor de corriente
		lds r22, CorrienteL
		ldi r21, 0x00				;Cargar valor del primer decimal
		lds r20, Temp1
		call mul16x16_16			;Llamar funcion multiplicacion
		ldi DivisorH, 0x00			;Cargar 10 en divisor para acomodar numero
		ldi DivisorL, 0x0A
		call Division16_16			;Llamar funcion division		
		lds r19, PotenciaH			;Cargar valor temporal de potencia
		lds r18, PotenciaL
		add r16, r18				;Sumar potencia con resultado de corriente por primer decimal
		adc r17, r19
		sts PotenciaH, r17			;Guardar resultado temporal de la potencia
		sts PotenciaL, r16

		lds r23, CorrienteH			;Cargar valor de corriente
		lds r22, CorrienteL
		ldi r21, 0x00				;Cargar valor del segundo decimal
		lds r20, Temp2
		call mul16x16_16			;Llamar funcion multiplicacion
		ldi DivisorH, 0x00			;Cargar 100 en divisor para acomodar numero
		ldi DivisorL, 0x64
		call Division16_16			;Llamar funcion division		
		lds r19, PotenciaH			;Cargar valor temporal de potencia
		lds r18, PotenciaL
		add r16, r18				;Sumar potencia con resultado de corriente por primer decimal
		adc r17, r19
		sts PotenciaH, r17			;Guardar resultado temporal de la potencia
		sts PotenciaL, r16

		lds r23, CorrienteH			;Cargar valor de corriente
		lds r22, CorrienteL
		ldi r21, 0x00				;Cargar valor del segundo decimal
		lds r20, Temp3
		call mul16x16_16			;Llamar funcion multiplicacion
		ldi DivisorH, 0x03			;Cargar 1000 en divisor para acomodar numero
		ldi DivisorL, 0xE8
		call Division16_16			;Llamar funcion division		
		lds r19, PotenciaH			;Cargar valor temporal de potencia
		lds r18, PotenciaL
		add r16, r18				;Sumar potencia con resultado de corriente por primer decimal
		adc r17, r19
		sts PotenciaH, r17			;Guardar resultado de la potencia
		sts PotenciaL, r16

		ret

;################################################################### CALCULO DE CORRIENTE PWM ###################################################################
 
	CALCULO_CORRIENTE_PWM:
		
		lds r23, CorrienteH			;Valor corriente
		lds r22, CorrienteL	
		ldi r21, 0x00				;Multiplicar por 2
		ldi r20, 0x02
		call mul16x16_16
		ldi r19, 0x00				;dividir por 10
		ldi r18, 0x0A
		call Division16_16
		sts CorrienteH_PWM, r17
		sts CorrienteL_PWM, r16

		lds r23, CorrienteH			;Valor corriente
		lds r22, CorrienteL	
		ldi r21, 0x00				;Multiplicar por 7
		ldi r20, 0x07
		call mul16x16_16
		ldi r19, 0x00				;dividir por 100
		ldi r18, 0x64
		call Division16_16
		lds r20, CorrienteH_PWM
		lds r19, CorrienteL_PWM
		add r16, r19
		adc r17, r20
		sts CorrienteH_PWM, r17
		sts CorrienteL_PWM, r16

		lds r23, CorrienteH			;Valor corriente
		lds r22, CorrienteL	
		ldi r21, 0x00				;Multiplicar por 3
		ldi r20, 0x03
		call mul16x16_16
		ldi r19, 0x03				;dividir por 1000
		ldi r18, 0xE8
		call Division16_16
		lds r20, CorrienteH_PWM
		lds r19, CorrienteL_PWM
		add r16, r19
		adc r17, r20
		ldi r20, 0x00
		ldi r19, 0xCC				; SUMA 204 para llegar a 5V
		add r16, r19
		adc r17, r20
		sts CorrienteH_PWM, r17
		sts CorrienteL_PWM, r16
		
		ret

;################################################################### CALCULO DE POTENCIA PWM ###################################################################
 
	CALCULO_POTENCIA_PWM:
		
		lds DividendoH, PotenciaH	;Cargar valor de potencia
		lds DividendoL, PotenciaL
		ldi DivisorH, 0x00			;Cargar 10 en divisor
		ldi DivisorL, 0x0A
		call Division16_16			;Llamar funcion division
		sts GRANDEH, r17			;Guardar resultado
		sts GRANDEL, r16

		lds r17, GRANDEH			;Valor de potencia hasta 6000
		lds r16, GRANDEL	
		ldi r19, 0x00				;dividir por 10
		ldi r18, 0x0A
		call Division16_16
		sts PotenciaH_PWM, r17
		sts PotenciaL_PWM, r16

		lds r23, GRANDEH			;Valor corriente
		lds r22, GRANDEL	
		ldi r21, 0x00				;Multiplicar por 3
		ldi r20, 0x03
		call mul16x16_16
		ldi r19, 0x00				;dividir por 100
		ldi r18, 0x64
		call Division16_16
		lds r20, PotenciaH_PWM
		lds r19, PotenciaL_PWM
		add r16, r19
		adc r17, r20
		sts PotenciaH_PWM, r17
		sts PotenciaL_PWM, r16

		lds r23, GRANDEH			;Valor corriente
		lds r22, GRANDEL	
		ldi r21, 0x00				;Multiplicar por 6
		ldi r20, 0x06
		call mul16x16_16
		ldi r19, 0x03				;dividir por 1000
		ldi r18, 0xE8
		call Division16_16
		lds r20, PotenciaH_PWM
		lds r19, PotenciaL_PWM
		add r16, r19
		adc r17, r20
		ldi r20, 0x00
		ldi r19, 0xCF				;Sumar 1 volt
		add r16, r19
		adc r17, r20
		sts PotenciaH_PWM, r17
		sts PotenciaL_PWM, r16
		
		ret
		
;################################################################### FUNCION DE MULTIPLICACION ###################################################################

	mul16x16_16:

		mul	r22, r20				;Multiplica parte baja de A con parte baja de B
		movw	r17:r16, r1:r0
		mul	r23, r20				;Multiplica parte alta de A con parte baja de B
		add	r17, r0
		mul	r21, r22				;Multiplica parte baja de A con parte alta de B
		add	r17, r0
									;Resultado r17, r16
		ret

;############################################################ FUNCION DE MULTIPLICACION DEL RESTO ###################################################################

	mul16x16_24:
		mul		r23, r21			;Multiplica parte alta de A con parte alta de B
		mov		r18, r0
		mul		r22, r20			;Multiplica parte baja de A con parte baja de B
		movw	r17:r16, r1:r0
		mul		r23, r20			;Multiplica parte alta de A con parte baja de Bah * bl
		add		r17, r0
		adc		r18, r1
		mul		r21, r22			;Multiplica parte baja de A con parte alta de B
		add		r17, r0
		adc		r18, r1
									;Resultado r18, r17, r16
		ret


;################################################################### FUNCION DE DIVISION ###################################################################

	Division16_16:	
		clr	RestoL					;Borra byte low de Resto
		sub	RestoH,RestoH			;Borra el byte alto y acarreo
		ldi	Contador,17				;Contador de bucle infinito
		div_1:	
		rol	DividendoL				;Desplazo a la izquierda el dividendo
		rol	DividendoH
		dec	Contador				;Decremento contador
		brne	div_2				;if done
		sts RestodivL, RestoL
		sts RestodivH, RestoH
		ret							;Salida
		div_2:	
		rol	RestoL					;Resplazo a la izquerda el resto
		rol	RestoH
		sub	RestoL,DivisorL			;Resto = resto - divisor
		sbc	RestoH,DivisorH	
		brcc	div_3				;Si el resultado es negativo
		add	RestoL,DivisorL			;Restaurar el resto
		adc	RestoH,DivisorH
		clc							;Limpia el acarreo para ser deplazado al resultado
		rjmp	div_1				;Else
		div_3:	
		sec							;Pone a 1 la bandera de acarreo para ser trasladado al resultado
		rjmp	div_1
									;Resultado de la division r17, r16
									;Resto de la division r15, r14

;########################################################## MOSTRAR POTENCIA #########################################################

