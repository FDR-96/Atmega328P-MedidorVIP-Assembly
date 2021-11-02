/*
 * PWM.inc
 *
 *  Created: 10/4/2021 07:25:46
 *   Author: FDPR
 */ 

 INIT_PWM:
		ldi r16, (1<<COM1A1)|(0<<COM1A0)|(1<<COM1B1)|(0<<COM1B0)|(1<<WGM11)|(1<<WGM10) 
		sts TCCR1A, r16				;Modo fase correcta PWM, comparacion igual no invertido, resolucion 10-bit
		ldi r16, (1<<WGM12)|(0<<WGM13)|(0<<CS12)|(1<<CS11)|(0<<CS10)  
		sts TCCR1B, r16				;Selector de reloj de timer/counter: Clock_I-O/8(from prescaler)

		ldi r16, (1<<TOIE1)			;Interrupcion de salida del temporizador/contador  
		sts TIMSK1, r16
		
		ldi r16, 0x00
		sts OCR1AH, r16
		sts OCR1AL, r16
		sts OCR1BH, r16
		sts OCR1BL, r16
		ret