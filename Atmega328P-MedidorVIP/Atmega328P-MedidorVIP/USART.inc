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

		
USART_RXC:

		PUSH_SREG
		lds r16, UDR0
		sts DATO_RX, r16
		POP_SREG
		reti

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
