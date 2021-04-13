;
; Atmega328P-MedidorVIP.asm
;
; Created: 10/4/2021 07:22:44
; Author : FDPR
;


.INCLUDE "Atmega328P_CFG.inc"

.MACRO	PUSH_SREG					;Guardar en la pila la posicion de memoria
		push r12
		in r12, SREG			
		push r12					;Guardar registros de trabajo
		push r13
		push r14
		push r15
		push r16
		push r17
		push r18
		push r19
		push r20
		push r21
		push r22
		push r23
		push r24
		push r25
		push r26
		push r27
.ENDMACRO

.MACRO	POP_SREG
		pop r27
		pop r26
		pop r25
		pop r24
		pop r23
		pop r22
		pop r21
		pop r20
		pop r19
		pop r18
		pop r17
		pop r16
		pop r15
		pop r14
		pop r13
		pop r12
		out sreg, r12				;Recuperar de la pila la posicion de memoria
		pop r12
.ENDMACRO

.DSEG

.CSEG


.ORG REINICIO
	jmp INICIO

.ORG INTERRUPCION_EXTERNA_2
	jmp RTI_SELECT
	
.ORG TIMER_COUNTER1_DESBORDAMIENTO
	jmp RTI_TIMER1_OVF

.ORG USART_RX
	jmp USART_RXC

.ORG 0x34
	reti

.INCLUDE "ADC.inc"
;ADC.inc    
;=======INIT_ADC: Configura el ADC, descativa las entradas digitales de los pines ADC0 y ADC1
;=======ADC0: Configuracion ADEMUX, Configuracion del Prescaler en 8, Habilitacion del ADC, Int de conversion completa(ADIE), Activacion auto del ADC(ADATE) autoTrigger. TimerCounter1
;=======LEER_ADC0: Carga la parte baja y alta del ADC y la guarda en la SRAM
.INCLUDE "PWM.inc"
;PWM.inc
;=======INIT_PWM: Inicializa el PWM en fast mode
.INCLUDE "USART.inc"
;USART.inc
;=======INIT_USART: Inicializa el USART con velocidad de trasmision de 9600 baud, habilitamos recepcion y transmicion de datos y la interrepcion por recepcion
;=======USART_ESPERA: Funcion de espera de bandera de transmision
;=======USART_COMPARACION: Lee la recepcion y compara el caracter recibido 
;=======MOSTRAR_POTENCIA: Transmite el valor leido por el ADC y posteriormente convertido a un valor ASCII por el USART, luego limpian el REG
;=======MOSTRAR_CORRIENTE: Transmite el valor leido por el ADC y posteriormente convertido a un valor ASCII por el USART, luego limpian el REG
;=======MOSTRAR_TENSION: Transmite el valor leido por el ADC y posteriormente convertido a un valor ASCII por el USART, lego limpian el REG
;=======MOSTRAR: Muestra
.INCLUDE "SPI.inc"
;SPI.inc
;=======INIT_SPI: Configuramos el SPI en modo Maestro, con un preescaler de 16 (1Mhz) y lo activamos
;=======SPI_ESPERA: Esperar que se complete la transmisión
;=======SPI_MOSTRAR_TENSION: Empieza la transmicion por el SPI  
;=======SPI_MOSTRAR_CORRIENTE: Empieza la transmicion por el SPI 
;=======SPI_MOSTRAR_POTENCIA: Empieza la transmicion por el SPI 
;=======SPI_TRANSMITIR: Funcion de espera de bandera de transmision
.INCLUDE "INT.inc"
;INT.inc
;=======INIT_INT: Configuramos las interrupciones PCINT 23 - 22 - 21 
.INCLUDE "Operaciones.inc"
;Operaciones.inc
;=======DESCOMPOSICION: Descompone las unidades
;=======CALCULO_TENSION: 
;=======CALCULO_CORRIENTE: Configuramos las interrupciones PCINT 23 - 22 - 21 
;=======CALCULO_POTENCIA: Configuramos las interrupciones PCINT 23 - 22 - 21 
;=======CALCULO_CORRIENTE_PWM:
;=======CALCULO_POTENCIA_PWM:
;=======MULTIPLICACION_16:
;=======DIVISION_16:

INICIO:

			ldi r16, high(ramend)		;Configuracion de pila
			out sph, r16
			ldi r16, low(ramend)
			out spl, r16
			cli
			call INIT_ADC
			call INIT_INT
			call INIT_PWM
			call INIT_USART
			call INIT_SPI
			sei


BUCLE:
		call ADC0
		call LEER_ADC0
		call ADC1
		call LEER_ADC1
		call CALCULO_TENSION
		call CALCULO_CORRIENTE
		call CALCULO_POTENCIA
		call CALCULO_CORRIENTE_PWM
		call CALCULO_POTENCIA_PWM
		call USART_COMPARACION
		jmp BUCLE
		
RTI_SELECT:
		PUSH_SREG

		in r16, PIND
		sbrs r16, 7					;Pregunta si PD7 esta en 0
		call SPI_MOSTRAR_POTENCIA	;Llama funcion para mostrar potencia
		sbrs r16, 6					;Pregunta si PD6 esta en 0
		call SPI_MOSTRAR_CORRIENTE	;Llama funcion para mostrar corriente 
		sbrs r16, 5					;Pregunta si PD5 esta en 0
		call SPI_MOSTRAR_TENSION	;Llama funcion para mostrar tension
			
		POP_SREG
		reti

RTI_TIMER1_OVF:			
		PUSH_SREG					;Guardo en la pila la posicion de memoria
								
		lds r21, PotenciaH_PWM
		sts OCR1AH, r21				;Salida PWMA timer OC1A
		lds r21, PotenciaL_PWM	
		sts OCR1AL, r21
			
		lds r20, CorrienteH_PWM
		sts OCR1BH, r20				;Salida PWMB timer OC1B
		lds r20, CorrienteL_PWM	
		sts OCR1BL, r20
			
		POP_SREG					;Recupero el valor de la pila
		reti

USART_RXC:

		PUSH_SREG
		lds r16, UDR0
		sts DATO_RX, r16
		POP_SREG
		reti

