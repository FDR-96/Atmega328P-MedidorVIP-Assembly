/*
 * SPI.inc
 *

 *   Author: FDPR
 */ 

 INIT_SPI:
 			
		ldi r16, (1<<DDB1)|(1<<DDB2)|(1<<DDB3)|(1<<DDB5)	
		out DDRB, r16				;Como salida PB1-9(OC1A), PB2-10(OC1B)|| PB5-13(CSK), PB3-11(MOSI)
		ldi r16, (1<<DDC5)			;Pin PC5-A5 (Load) como salida
		out DDRC, r16
		ldi r17,(1<<SPE)|(1<<MSTR)|(1<<SPR0)	;SPR0 determina el preescaler 
							;SPI2X   SPR1   SPR0   PreEscaler
							;  0	   0	  0 	  4
							;  0	   0	  1 	  16
							;  0	   1	  0 	  64
							;etc
							;MSTR establece el modo de funcionamiento, en 0 el spi es esclavo en 1 es maestro
							;Con SPE en 1 activamos el SPI
		out SPCR,r17		;Habilitar SPI como Master, Velocidad de reloj f/16 (1Mhz)
			
;=======================================================================
; Formato de Registro de Intensidad (Dirección (Hex) = 0xXA)
;=======================================================================
	
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
;=======================================================================
; Registros en modo decodificación (Dirección (Hex) = 0xX9)
;=======================================================================

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

;=======================================================================
; Formato de registro de límite de escaneo (Dirección (Hex) = 0xXB)
;=======================================================================
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

;=======================================================================
; Formato de registro de apagado (Dirección (Hex) = 0xXC)
;=======================================================================
	

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
;=======================================================================
; Formato de registro de prueba de pantalla (Dirección (Hex) = 0xXF)
;=======================================================================
	
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

;=======================================================================
; Saludar
;=======================================================================
	    ldi r17, (0<<PC5)			;Mando 0 a PB4 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x01
		out SPDR, r17				;Digito 0
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, 0x00
		out SPDR,r17				;O
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x02
		out SPDR, r17				;Digito 1
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, 0x0D
		out SPDR,r17				;L
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x03
		out SPDR, r17				;Digito 2
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, 0x0D
		out SPDR,r17				;L
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x04
		out SPDR, r17				;Digito 3
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, 0x0B
		out SPDR,r17				;E
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x05
		out SPDR, r17				;Digito 4
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, 0x37
		out SPDR,r17				;H
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x06
		out SPDR, r17				;Digito 5
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, 0x00
		out SPDR,r17				;0
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop
		ret

;=======================================================================
; SPI ESPERA
; Se establece el indicador SPIF en SPSR, y si la interrupción SPI está habilitada y se establece el bit I en SREG, la rutina de interrupción
; será ejecutado.
;=======================================================================

SPI_ESPERA:	
		in r26, SPSR		
		sbrs r26, SPIF				; Esperar que se complete la transmisi�n
		rjmp SPI_ESPERA
		ret

;=======================================================================
; SPI MOSTRAR TENSION
;=======================================================================

SPI_MOSTRAR_TENSION:
				
		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x06
		out SPDR, r17				;Digito 5
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, 0b0011_1110
		out SPDR,r17				; U
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x05
		out SPDR, r17				;Digito 5
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, 0b0000_1001
		out SPDR,r17				; =
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

		lds ValorH, TensionH		;Cargar valor de tension alta
		lds ValorL, TensionL		;Cargar valor de tension baja
		call CONVERSION
		call SPI_TRANSMITIR
		ret

;=======================================================================
; SPI MOSTRAR CORRIENTE
;=======================================================================
SPI_MOSTRAR_CORRIENTE:
		
		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x06
		out SPDR, r17				;Digito 5
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, 0b0011_0000
		out SPDR,r17				; I
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x05
		out SPDR, r17				;Digito 5
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, 0b0000_1001
		out SPDR,r17				; =
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

		lds ValorH, CorrienteH		;Cargar valor de corriente alta
		lds ValorL, CorrienteL		;Cargar valor de corriente baja
		call CONVERSION
		call SPI_TRANSMITIR
		ret
		
;=======================================================================
; SPI MOSTRAR POTENCIA
;=======================================================================
	
SPI_MOSTRAR_POTENCIA:

		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x06
		out SPDR, r17				;Digito 5
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, 0b0110_0111
		out SPDR,r17				; P
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x05
		out SPDR, r17				;Digito 5
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, 0b0000_1001
		out SPDR,r17				; =
		call SPI_ESPERA				;Empezar la TX de informaci�n
		nop
		ldi r17, (1<<PC5)			;Mando 1 a PC5 para indicarle a MAX que finalizo transferencia
		out PORTC, r17
		nop

		lds ValorH, PotenciaH		;Cargar valor de potencia alta
		lds ValorL, PotenciaL		;Cargar valor de potencia baja
		call CONVERSION
		call SPI_TRANSMITIR
		ret
		
;=======================================================================
; SPI TRASMITIR VALORES
;=======================================================================
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
	