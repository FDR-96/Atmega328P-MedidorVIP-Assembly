/*
 * ADC.inc
 *
 *  Created: 10/4/2021 07:25:13
 *   Author: FDPR
 */ 
 INIT_ADC:
		ldi r16, (1<<ADC1D)|(1<<ADC0D)	
		sts DIDR0, r16				;Descativo entrada digital de los pines ADC0 y ADC1
