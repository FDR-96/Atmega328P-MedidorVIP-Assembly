/*
 * USART.inc
 *
 *   Author: FDPR
 */ 


INIT_USART:
		ldi r16, 103				;Velocidad de transmicion 9600 Bd
		ldi r17, 0
		sts UBRR0H, r17
		sts UBRR0L, r16

		ldi r16, (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0)	
		sts UCSR0B, r16				;Habilita interrupci�n por recepci�n, Habilita recepci�n, Habilita transmici�n
			
		ldi r16, (0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00)	
		sts UCSR0C, r16				;Stop Bit 1, 8 bits				

	
		ret

USART_ESPERA:

		lds r26, UCSR0A				;Espera que se limpie la bandera de transmision
		sbrs r26, UDRE0
		rjmp USART_ESPERA
		ret

USART_COMPARACION:
		
		lds r16, DATO_RX			;Cargar dato recibido
		ldi r17, ASCII_V			;Comparar con V
		cpse r16, r17
		rjmp I						;Si es falso, compara con I
		call MOSTRAR_TENSION		
	I:
		ldi r17, ASCII_I			;Comparar con I
		cpse r16, r17
		rjmp P						;Si es falso, compara con P
		call MOSTRAR_CORRIENTE
	P:
		ldi r17, ASCII_P				;Comparar con P
		cpse r16, r17
		ret
		call MOSTRAR_POTENCIA
		ret
MOSTRAR_POTENCIA:
		
		lds ValorH, PotenciaH		;Cargar valor de potencia alta
		lds ValorL, PotenciaL		;Cargar valor de potencia baja
		
		call CONVERSION
				
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
		
		lds ValorH, CorrienteH		;Cargar valor de corriente alta
		lds ValorL, CorrienteL		;Cargar valor de corriente baja
		
		call CONVERSION
				
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
		ldi r20, ASCII_M			; m
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

		lds ValorH, TensionH		;Cargar valor de tension alta
		lds ValorL, TensionL		;Cargar valor de tension baja
		
		call CONVERSION
				
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
