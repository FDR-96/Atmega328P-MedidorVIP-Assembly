/*
 * INT.inc
 *
 *   Author: FDPR
 */ 

INIT_INT:
		ldi r16, (0<<DDD7)|(0<<DDD6)|(0<<DDD5)			
		out DDRD,r16				;Pines como entrada interrupcion de PCIE2
		ldi r16, (1<<PD7)|(1<<PD6)|(1<<PD5)				
		out PORTD, r16				;Resistencias Pull Up
		ldi r16, (1<<PCIE2)			;Habilito int por cambio de pines[7:0] (PCIE2)
		sts PCICR, r16
		ldi r16, 0b1110_0000		;Habilito los pines 7-6-5 de interrupcion (PCINT 23 - 22 - 21)
		sts PCMSK2, r16
		ret

