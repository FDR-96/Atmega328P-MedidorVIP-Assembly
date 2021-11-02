/*
 * USART.inc
 *
 *  Created: 10/4/2021 07:26:08
 *   Author: FDPR
 */ 

INIT_USART:
		ldi r16, 103				;Velocidad de transmicion 9600 Bd
		ldi r17, 0
		sts UBRR0H, r17
		sts UBRR0L, r16

		ldi r16, (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0)	
		sts UCSR0B, r16				;Habilita interrupción por recepción, Habilita recepción, Habilita transmición
			
		ldi r16, (0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00)	
		sts UCSR0C, r16				;Stop Bit 1, 8 bits				

		
		call CONFIG_MAX				;Inicializar MAX
			

CONFIG_MAX:

		ldi r17,(1<<SPE)|(1<<MSTR)|(1<<SPR0)	
		out SPCR,r17				;Habilitar SPI como Master, Velocidad de reloj f/16 (1Mhz)
			
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; SETEAR BRILLO ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
					
		ldi r17, (0<<PC5)			;Mando 0 a PC5 para indicarle a MAX que inicia transferencia de datos
		out PORTC, r17
		nop							;Cumplir tcss de hoja de datos MAX
		ldi r17, 0x0A
		out SPDR, r17				;Entrar Set Brillo MAX
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, 0x00
		out SPDR,r17				;Setear el brillo MAX al Minimo
		call SPI_ESPERA				;Empezar la TX de información
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
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, 0x0F
		out SPDR,r17				;Setear Code B decode for digits 3–0 No decode for digits 7–4
		call SPI_ESPERA				;Empezar la TX de información
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
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, 0x05
		out SPDR,r17				;Display digits 0 1 2 3 4 5
		call SPI_ESPERA				;Empezar la TX de información
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
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, 1
		out SPDR,r17				;Normal Operation
		call SPI_ESPERA				;Empezar la TX de información
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
		call SPI_ESPERA				;Empezar la TX de información
		nop
		ldi r17, 0
		out SPDR,r17				;Normal Operation
		call SPI_ESPERA				;Empezar la TX de información
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
		

USART_ESPERA:

		lds r26, UCSR0A				;Espera que se limpie la bandera de transmision
		sbrs r26, UDRE0
		rjmp USART_ESPERA
		ret

USART_COMPARACION:
		
		lds r16, DATO_RX			;Cargar dato recibido
		ldi r17, 0x56				;Comparar con V
		cpse r16, r17
		rjmp I						;Si es falso, compara con I
		call MOSTRAR_TENSION		
		I:
		ldi r17, 0x49				;Comparar con I
		cpse r16, r17
		rjmp P						;Si es falso, compara con P
		call MOSTRAR_CORRIENTE
		P:
		ldi r17, 0x50				;Comparar con P
		cpse r16, r17
		ret
		call MOSTRAR_POTENCIA
		ret
MOSTRAR_POTENCIA:
		
		lds ENTEROH, PotenciaH		;Cargar valor de potencia alta
		lds ENTEROL, PotenciaL		;Cargar valor de potencia baja
		
		call DESCOMPOSICION
				
		call USART_ESPERA			
		ldi r20, ASCII_P				; P
		sts UDR0, r20

		call USART_ESPERA
		ldi r20, ASCII_ESPACIO				; (espacio)
		sts UDR0, r20

		call USART_ESPERA			
		ldi r20, ASCII_IGUAL				; =
		sts UDR0, r20

		call USART_ESPERA
		ldi r20, ASCII_ESPACIO		; (espacio)
		sts UDR0, r20

		call MOSTRAR

		call USART_ESPERA
		ldi r20, ASCII_ESPACIO				; (espacio)
		sts UDR0, r20

		call USART_ESPERA			
		ldi r20, ASCII_W				; W
		sts UDR0, r20

		call USART_ESPERA			
		ldi r20, ASCII_A				; a
		sts UDR0, r20

		call USART_ESPERA			
		ldi r20, ASCII_T				; t
		sts UDR0, r20

		call USART_ESPERA			
		ldi r20, ASCII_T				; t
		sts UDR0, r20

		call USART_ESPERA			
		ldi r20, 0x0A				; (salto de linea)
		sts UDR0, r20

		call USART_ESPERA			
		ldi r20, 0x0D				; (retorno de carro)
		sts UDR0, r20

		clr r17						;Limpiar registro de dato recibido
		sts DATO_RX, r17
	
		ret


MOSTRAR_CORRIENTE:
		
		lds ENTEROH, CorrienteH		;Cargar valor de corriente alta
		lds ENTEROL, CorrienteL		;Cargar valor de corriente baja
		
		call DESCOMPOSICION
				
		call USART_ESPERA			
		ldi r20, ASCII_I			; I
		sts UDR0, r20

		call USART_ESPERA
		ldi r20, ASCII_ESPACIO				; (espacio)
		sts UDR0, r20

		call USART_ESPERA			
		ldi r20, ASCII_IGUAL		; =
		sts UDR0, r20

		call USART_ESPERA
		ldi r20, ASCII_ESPACIO				; (espacio)
		sts UDR0, r20

		call MOSTRAR

		call USART_ESPERA
		ldi r20, ASCII_ESPACIO				; (espacio)
		sts UDR0, r20

		call USART_ESPERA			
		ldi r20, ASCII_A	; A
		sts UDR0, r20

		call USART_ESPERA			
		ldi r20, ASCII_N			; m
		sts UDR0, r20

		call USART_ESPERA			
		ldi r20, ASCII_P				; p
		sts UDR0, r20

		call USART_ESPERA			
		ldi r20, ASCII_E		; e
		sts UDR0, r20
		
		call USART_ESPERA			
		ldi r20, ASCII_R			; r
		sts UDR0, r20

		call USART_ESPERA			
		ldi r20, 0x0A				; (salto de linea)
		sts UDR0, r20

		call USART_ESPERA			
		ldi r20, 0x0D				; (retorno de carro)
		sts UDR0, r20

		clr r17						;Limpiar registro de dato recibido
		sts DATO_RX, r17
	
		ret


MOSTRAR_TENSION:

		lds ENTEROH, TensionH		;Cargar valor de tension alta
		lds ENTEROL, TensionL		;Cargar valor de tension baja
		
		call DESCOMPOSICION
				
		call USART_ESPERA			
		ldi r20, ASCII_V			; V
		sts UDR0, r20

		call USART_ESPERA
		ldi r20, ASCII_ESPACIO				; (espacio)
		sts UDR0, r20

		call USART_ESPERA			
		ldi r20, ASCII_IGUAL			; =
		sts UDR0, r20

		call USART_ESPERA
		ldi r20, ASCII_ESPACIO				; (espacio)
		sts UDR0, r20

		call MOSTRAR

		call USART_ESPERA
		ldi r20, ASCII_ESPACIO				; (espacio)
		sts UDR0, r20

		call USART_ESPERA			
		ldi r20, ASCII_V				; V
		sts UDR0, r20

		call USART_ESPERA			
		ldi r20, ASCII_O				; o
		sts UDR0, r20

		call USART_ESPERA			
		ldi r20, ASCII_L			; l
		sts UDR0, r20

		call USART_ESPERA			
		ldi r20, ASCII_T		; t
		sts UDR0, r20
		
		call USART_ESPERA			
		ldi r20, 0x0A				; (salto de linea)
		sts UDR0, r20

		call USART_ESPERA			
		ldi r20, 0x0D				; (retorno de carro)
		sts UDR0, r20

		clr r17						;Limpiar registro de dato recibido
		sts DATO_RX, r17
		ret


MOSTRAR:	
		call USART_ESPERA
		ld	r27, Z+					;Cargamos decena
		ldi r29, 48
		add r27, r29				;Sumamos 48 para convertirlo en ASCII
		sts UDR0,r27				;Enviamos por puerto serie
		call USART_ESPERA
	
		call USART_ESPERA
		ld	r27, Z+					;Cargamos unidad
		ldi r29, 48
		add r27, r29				;Sumamos 48 para convertirlo en ASCII
		sts UDR0,r27				;Enviamos por puerto serie
		call USART_ESPERA

		call USART_ESPERA			
		ldi r20, 0x2C				; ,
		sts UDR0, r20				;Enviamos por puerto serie

		call USART_ESPERA
		ld	r27, Z+					;Cargamos primer decimal
		ldi r29, 48
		add r27, r29				;Sumamos 48 para convertirlo en ASCII
		sts UDR0,r27				;Enviamos por puerto serie
		call USART_ESPERA

		call USART_ESPERA
		ld	r27, Z+					;Cargamos segundo decimal
		ldi r29, 48
		add r27, r29				;Sumamos 48 para convertirlo en ASCII
		sts UDR0,r27				;Enviamos por puerto serie
		call USART_ESPERA
	
		call USART_ESPERA
		ld	r27, Z					;Cargamos tercer decimal
		ldi r29, 48
		add r27, r29				;Sumamos 48 para convertirlo en ASCII
		sts UDR0,r27				;Enviamos por puerto serie
		call USART_ESPERA

		SBIW ZL, 4					;Poner el puntero en el primer BCD
		ret
		