/*
 * MostrarValor.inc
 *
 *  Created: 10/4/2021 07:41:31
 *   Author: FDPR
 */ 
 .include "SPI.inc"
 .include "Operaciones.inc"

 MOSTRAR_CORRIENTE_MAX:
		
		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x06
		out SPDR, r17				;Digito 5
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, 0b0011_0000
		out SPDR,r17				; I
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x05
		out SPDR, r17				;Digito 5
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, 0b0000_1001
		out SPDR,r17				; =
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

		lds ENTEROH, CorrienteH		;Cargar valor de corriente alta
		lds ENTEROL, CorrienteL		;Cargar valor de corriente baja
		call DESCOMPOSICION
		call SPI_TRANSMITIR
		ret
		