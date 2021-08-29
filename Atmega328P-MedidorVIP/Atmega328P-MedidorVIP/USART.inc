/*
 * USART.inc
 *
 *  Created: 10/4/2021 07:26:08
 *   Author: FDPR
 */ 

INIT_USART:
		ldi r16, 103				;Velocidad de transmicion 9600 Bd
		ldi r17, 0
		out UBRR0H, r17
		out UBRR0L, r16

		ldi r16, (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0)	
		out UCSR0B, r16				;Habilita interrupción por recepción, Habilita recepción, Habilita transmición
			
		ldi r16, (0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00)	
		out UCSR0C, r16				;Stop Bit 1, 8 bits	
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
		