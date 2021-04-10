/*
 * SPI.inc
 *
 *  Created: 10/4/2021 07:26:35
 *   Author: FDPR
 */ 
 INIT_SPI:

		ldi r17,(1<<SPE)|(1<<MSTR)|(1<<SPR0)	;SPR0 determina el preescaler 
							;SPI2X   SPR1   SPR0   PreEscaler
							;  0	   0	  0 	  4
							;  0	   0	  1 	  16
							;  0	   1	  0 	  64
							;etc
							;MSTR establece el modo de funcionamiento, en 0 el spi es esclavo en 1 es maestro
							;Con SPE en 1 activamos el SPI
		out SPCR,r17				;Habilitar SPI como Master, Velocidad de reloj f/16 (1Mhz)
			
				
		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x0A
		out SPDR, r17				;Entrar Set Brillo MAX
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, 0x00
		out SPDR,r17				;Setear el brillo MAX al Minimo
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; SETEAR MODOS ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x09
		out SPDR, r17				;Entrar en modo de codificacion
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, 0x0F
		out SPDR,r17				;Setear Code B decode for digits 3�0 No decode for digits 7�4
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; SCAN LIMIT ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x0B
		out SPDR, r17				;Entrar Scan Limit
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, 0x05
		out SPDR,r17				;Display digits 0 1 2 3 4 5
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Setear Modo ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x0C
		out SPDR, r17				;Entrar MODO
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, 1
		out SPDR,r17				;Normal Operation
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Setear TEST ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x0F
		out SPDR, r17				;Entrar TEST
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, 0
		out SPDR,r17				;Normal Operation
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Iniciar digitos en "HELLO" ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

		ldi r17, (0<<PC5)			;Mando 0 a PB4 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x01
		out SPDR, r17				;Digito 0
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, 0x00
		out SPDR,r17				;O
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x02
		out SPDR, r17				;Digito 1
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, 0x0D
		out SPDR,r17				;L
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x03
		out SPDR, r17				;Digito 2
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, 0x0D
		out SPDR,r17				;L
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x04
		out SPDR, r17				;Digito 3
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, 0x0B
		out SPDR,r17				;E
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x05
		out SPDR, r17				;Digito 4
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, 0x37
		out SPDR,r17				;H
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x06
		out SPDR, r17				;Digito 5
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, 0x00
		out SPDR,r17				;0
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop
		ret

SPI_ESPERA:	
		in r26, SPSR		
		sbrs r26, SPIF				; Esperar que se complete la transmisi�n
		rjmp SPI_ESPERA
		ret
SPI_TRANSMITIR:
			
	;ENTERO PARTE ALTA
		ldi r17, (0<<PC5)			;Mando 0 a PB0 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop
		ldi r17, 0x04
		out SPDR, r17				;Digito entero alto
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop

		ld	r17, Z+						
		out SPDR, r17				;Envio digito entero alto
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PB0 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

	;ENTERO PARTE BAJA
		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop
		ldi r17, 0x03
		out SPDR, r17				;Digito entero bajo
		call SPI_ESPERA 			;Empezar la TX de informaci�n
		nop
	
		ld	r17, Z+						
		ldi r16, 0xF0
		add r17, r16				;Suma para mostrar puntto decimal
		out SPDR, r17				;Envio digito entero bajo
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

	;PRIMER DECIMAL
		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop
		ldi r17, 0x02
		out SPDR, r17				;Digito primer decimal
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop

		ld	r17, Z+					;Primer decimal
		out SPDR, r17				;Envio primer decimal
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

	;SEGUNDO DECIMAL
		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop
		ldi r17, 0x1
		out SPDR, r17				;Digito segundo decimal
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop

		ld	r17, Z+					;Segundo decimal
		out SPDR, r17				;Envio segundo decimal
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop
		
		ld	r17, Z
		SBIW ZL, 4
		clr r17

		ret