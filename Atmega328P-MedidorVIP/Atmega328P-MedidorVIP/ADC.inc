/*
 * ADC.inc
 *
 *  Created: 10/4/2021 07:25:13
 *   Author: FDPR
 */ 
INIT_ADC:
		ldi r16, (1<<ADC1D)|(1<<ADC0D)	
		sts DIDR0, r16				;Descativo entrada digital de los pines ADC0 y ADC1
		ret
ADC0:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Configuracion ADEMUX ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

		ldi r16, (0<<REFS1)|(1<<REFS0)|(0<<ADLAR)|(0<<MUX3)|(0<<MUX2)|(0<<MUX0)|(0<<MUX0) 
		sts ADMUX, r16				;Referencia de Voltaje Con AVCC y Capacitor, Activar ADC, Canal ADC0  
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Iniciar conversion ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

		ldi r16, (1<<ADEN)|(1<<ADSC)|(1<<ADIE)|(1<<ADATE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0) 
		sts ADCSRA, r16				;Prescaler en 8, Habilito ADC, Int de conversion completa(ADIE), Activacion auto del ADC(ADATE)
		ldi r16, (1<<ADTS2)|(1<<ADTS1)|(0<<ADTS0)	
		sts ADCSRB, r16				;Timer/Counter1 Overflow

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Leer ADC0 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LEER_ADC0:

		lds r16, ADCSRA				;Cargar el control ADCSRA
		SBRC r16, 6					;Saltar si se completo la conversion ADCS = 0
		rjmp LEER_ADC0 
			
		lds r17, ADCL				;Cargar parte baja del ADC
		lds r16, ADCH				;Cargar parte alta del ADC
		sts VAL_CorrienteADCL, r17	;Guardar el valor de ADC en VAL_CorrienteADC
		sts VAL_CorrienteADCH, r16
	
		ret

			

	ADC1:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Configuracion ADEMUX ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

		ldi r18, (0<<REFS1)|(1<<REFS0)|(0<<ADLAR)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(1<<MUX0) 
		sts ADMUX, r18				;Referencia de Voltaje Con AVCC y Capacitor, Activar ADC, Canal ADC1    

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Iniciar conversion ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

		ldi r18, (1<<ADEN)|(1<<ADSC)|(1<<ADIE)|(1<<ADATE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0) 
		sts ADCSRA, r18				;Prescaler en 8, Habilito ADC, Int de conversion completa(ADIE), Activacion auto del ADC(ADATE)  
		ldi r18, (1<<ADTS2)|(1<<ADTS1)|(0<<ADTS0)	
		sts ADCSRB, r18				;Timer/Counter1 Overflow

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Leer ADC1 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LEER_ADC1:

		lds r18, ADCSRA				;Cargar el control ADCSRA
		sbrc r18, 6					;Saltar si se completo la conversion ADCS = 0
		rjmp LEER_ADC1 
			
		lds r18, ADCL				;Cargar parte baja del ADC
		lds r19, ADCH				;Cargar parte alta del ADC
		sts VAL_TensionADCL, r18	;Guardar el valor de ADC en VAL_TensionADC
		sts VAL_TensionADCH, r19
	
		ret	