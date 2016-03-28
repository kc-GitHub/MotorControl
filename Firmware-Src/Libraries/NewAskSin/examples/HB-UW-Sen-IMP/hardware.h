//- -----------------------------------------------------------------------------------------------------------------------
// AskSin driver implementation
// 2013-08-03 <trilu@gmx.de> Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
//- -----------------------------------------------------------------------------------------------------------------------
//- AskSin hardware definition ----------------------------------------------------------------------------------------
//- with a lot of support from martin876 at FHEM forum
//- -------------------------------------------------------------------------------------------------------------------

#include <HAL.h>

#ifndef _HARDWARE_h
	#define _HARDWARE_h

	#define DEBOUNCE                   5										// input debounce time in ms - 5 seems to be a good value

	#if defined(__AVR_ATmega328P__)
		//- cc1100 hardware CS and GDO0 definitions
		#define CC_CS_DDR              DDRB										// SPI chip select definition
		#define CC_CS_PORT             PORTB
		#define CC_CS_PIN              PORTB2

		#define CC_GDO0_DDR            DDRD										// GDO0 pin, signals received data
		#define CC_GDO0_PIN            PORTB2

		#define CC_GDO0_PCICR          PCICR									// GDO0 interrupt register
		#define CC_GDO0_PCIE           PCIE2
		#define CC_GDO0_PCMSK          PCMSK2									// GDO0 interrupt mask
		#define CC_GDO0_INT            PCINT18									// pin interrupt

		//- LED's definition
		#define LED_RED_DDR            DDRD										// define led port and remaining pin
		#define LED_RED_PORT           PORTD
		#define LED_RED_PIN            PORTD4

		#define LED_GRN_DDR            DDRD
		#define LED_GRN_PORT           PORTD
		#define LED_GRN_PIN            PORTD4

		#define LED_ACTIVE_LOW         0										// leds connected to GND = 0, VCC = 1

		//- configuration key
		#define CONFIG_KEY_DDR         DDRB										// define config key port and remaining pin
		#define CONFIG_KEY_PORT	       PORTB
		#define CONFIG_KEY_PIN         PORTB0

		#define CONFIG_KEY_PCICR       PCICR									// interrupt register
		#define CONFIG_KEY_PCIE        PCIE0									// pin change interrupt port bit
		#define CONFIG_KEY_PCMSK       PCMSK0									// interrupt mask
		#define CONFIG_KEY_INT         PCINT0									// pin interrupt

		//- battery external measurement functions
		#define BATT_ENABLE_DDR        DDRD										// define battery measurement enable pin, has to be low to start measuring
		#define BATT_ENABLE_PORT       PORTD
		#define BATT_ENABLE_PIN        PORTD7

		#define BATT_MEASURE_DDR       DDRC										// define battery measure pin, where ADC gets the measurement
		#define BATT_MEASURE_PORT      PORTC
		#define BATT_MEASURE_PIN       PORTC1

		//- configuration for sensor related pins / ports
		#define SENSOR_LED_TIGGER_DDR  DDRC										// Data direction register for triggering sensor LED
		#define SENSOR_LED_TIGGER_PORT PORTC									// Port for triggering sensor LED
		#define SENSOR_LED_TIGGER_PIN  PINC3									// Pin for triggering sensor LED

		#define SENSOR_PCICR	       PCICR									// The Pin Change Interrupt Control Register

		#define SENSOR_CH1_DDR         DDRC										// Data direction register for sensor channel 1
		#define SENSOR_CH1_PORT	       PORTC									// Port for for sensor channel 1
		#define SENSOR_CH1_PIN         PINC2									// (PCINT10) Pin for for sensor channel 1
		#define SENSOR_CH1_PCICR       PCICR									// Pin change interrupt control register for sensor channel 1
		#define SENSOR_CH1_PCIE        PCIE1									// Pin change interrupt enable register for sensor channel 1
		#define SENSOR_CH1_PCMSK       PCMSK1									// Pin change mask register for sensor channel 1
		#define SENSOR_CH1_INT         PCINT10									// Pin change interrupt

		#define SENSOR_CH2_DDR         DDRC										// Data direction register for sensor channel 2
		#define SENSOR_CH2_PORT	       PORTC									// Port for for sensor channel 2
		#define SENSOR_CH2_PIN         PINC1									// (PCINT9) Pin for for sensor channel 2
		#define SENSOR_CH2_PCIE        PCIE1									// pin change interrupt enable register for sensor channel 2
		#define SENSOR_CH2_PCMSK       PCMSK1									// Pin change mask register for sensor channel 2
		#define SENSOR_CH2_INT         PCINT9									// Pin change interrupt

//		#define SENSOR_CH3_DDR         DDRC										// Data direction register for sensor channel 2
//		#define SENSOR_CH3_PORT	       PORTC									// Port for for sensor channel 2
//		#define SENSOR_CH3_PIN         PINC1									// (PCINT9) Pin for for sensor channel 2
//		#define SENSOR_CH3_PCIE        PCIE1									// pin change interrupt enable register for sensor channel 2
//		#define SENSOR_CH3_PCMSK       PCMSK1									// Pin change mask register for sensor channel 2
//		#define SENSOR_CH2_INT         PCINT9									// Pin change interrupt

		//#define CH4
		//#define CH5
		//#define CH6


		// Timer 2 (8 bit Timer) for Refex-Coupler impulse generating
		#define TIMER_SENSOR_TCCRA     TCCR2A
		#define TIMER_SENSOR_TCCRB     TCCR2B
		#define TIMER_SENSOR_TIMSK     TIMSK2
		#define TIMER_SENSOR_OCR       OCR2A
		#define TIMER_SENSOR_BIT_OCIE  OCIE2A
		#define TIMER_SENSOR_BIT_WGM   WGM21
		#define TIMER_SENSOR_CLOCKSEL  (_BV(CS21))								// Prescaler 8
		#define TIMER_SENSOR_PRESCALER 8
//		#define TIMER_SENSOR_CLOCKSEL  (_BV(CS21)|_BV(CS20))					// Prescaler 32
//		#define TIMER_SENSOR_PRESCALER 32
//		#define TIMER_SENSOR_CLOCKSEL  (_BV(CS22))								// Prescaler 64
//		#define TIMER_SENSOR_PRESCALER 64
		#define TIMER_SENSOR_VECT      TIMER2_COMPA_vect

		#define TIMER_SENSOR_OCR_LOW   ((F_CPU / TIMER_SENSOR_PRESCALER) / 1000)		// Timer overflow every 1000 milliseconds
		#define TIMER_SENSOR_OCR_HIGH  ((F_CPU / TIMER_SENSOR_PRESCALER) / 100000)		// Timer overflow every 10 microseconds

	#endif

#endif

