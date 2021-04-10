/*
 * IncFile1.inc
 *
 *  Created: 10/4/2021 07:45:29
 *   Author: FDPR
 */ 
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

