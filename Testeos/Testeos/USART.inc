/*
 * USART.inc
 *
 *  Created: 13/4/2021 08:52:24
 *   Author: FDPR
 */ 
#ifndef _USART_INC_
#define _USART_INC_

 INIT_USART:
		ldi r16, 103				;Velocidad de transmicion 9600 Bd
		ldi r17, 0
		out UBRR0H, r17
		out UBRR0L, r16

		ldi r16, (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0)	
		out UCSR0B, r16				;Habilita interrupción por recepción, Habilita recepción, Habilita transmición
			
		ldi r16, (0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00)	
		out UCSR0C, r16				;Stop Bit 1, 8 bits	

#endif
; ***** END OF FILE ******************************************************
 