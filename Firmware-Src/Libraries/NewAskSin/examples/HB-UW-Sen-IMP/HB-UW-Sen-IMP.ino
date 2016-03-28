
#define SER_DBG

//- load library's --------------------------------------------------------------------------------------------------------
#include "register.h"																// device configuration file
#include <AS.h>
#include "HB-UW-Sen-IMP.h"

// device settings
uint8_t  triggerFreq              = 200;							// trigger frequency in Hz * 2;				2 ( 4 Hz) - 200 ( 400 Hz)

// channel settings
uint8_t  channelMode              = CHANNEL_MODE_OPTICAL;
uint8_t  triggerLenUs10           = 100;							// length of trigger in microseconds * 10;	2 (20 µs) - 250 (2500 µs)
uint8_t  triggerCount             = (100000 / (triggerFreq * 2));
uint8_t  triggerOnBothEdgeChanges = 1;								// 1 = increase counter on falling and rising edge
uint16_t countsPerUnit            = 2;
uint8_t  showPulse                = 1;

volatile uint16_t countUnit       = 0;
volatile uint16_t countUnitOld    = 0;

/**
 * @brief This is the Arduino Setup-Function
 *
 * TODO: maybe we move the main parts to own setup/init function?
 */
void setup() {
	// TODO: Maybe we should enable timer0 and SPI internally?
	power_timer0_enable();
	power_spi_enable();																// enable only needed functions

	// enable only what is really needed
	#ifdef SER_DBG
		dbgStart();																	// serial setup
		dbg << F("Starting sketch for HB-UW-Sen-IMP ...\n\n");
		dbg << F(LIB_VERSION_STRING);
	#endif

	initInputChannels();

	hm.init();																		// init the asksin framework

	// TODO: Maybe we should enable global interrupts internally at AS::init?
	sei();																			// enable interrupts

	#ifdef SER_DBG
		dbg << F("HMID:  ") << _HEX(HMID,3) << F(", MAID: ") << _HEX(MAID,3) << "\n\n";		// some debug
		dbg << F("HmKey: ") << _HEX(HMKEY, 16) << '\n';
		dbg << F("KeyId: ") << _HEX(hmKeyIndex, 1) << '\n';

		for (uint8_t i = 1; i <= devDef.cnlNbr; i++) {											// check if AES activated for any channel
			if (hm.ee.getRegAddr(i, 1, 0, AS_REG_L1_AES_ACTIVE)) {
				dbg << F("AES active for channel: ") << _HEXB(i) << '\n';
			}
		}
		dbg << '\n';
	#endif

	// Initialize sensor timer for generating reflex coupler led impulse
	TIMER_SENSOR_TCCRA = _BV(TIMER_SENSOR_BIT_WGM);
	TIMER_SENSOR_TCCRB = TIMER_SENSOR_CLOCKSEL;
	TIMER_SENSOR_TIMSK = _BV(TIMER_SENSOR_BIT_OCIE);
	TIMER_SENSOR_OCR   = TIMER_SENSOR_OCR_HIGH;										// low timer frequency at start

	// Init IR-LED Supply-Pin
	pinOutput(SENSOR_LED_TIGGER_DDR, SENSOR_LED_TIGGER_PIN);						// init the config key pin
	power_timer2_enable();

	if (showPulse) {
		countsPerUnit = 1;
		triggerOnBothEdgeChanges = 1;
	}

	/*
	 * At this point you can write your own code
	 */

//	setPinHigh(LED_RED_PORT, LED_RED_PIN);
//	_delay_ms(5000);
//	setPinLow(LED_RED_PORT, LED_RED_PIN);
}

/**
 * @brief This is the Arduino Forever-Loop
 */
void loop() {
	hm.poll();																		// poll the asksin main loop

	/*
	 * At this point you can write your own code
	 */

	if (countUnit != countUnitOld) {
		if (showPulse)   setPinHigh(LED_RED_PORT, LED_RED_PIN);
		Serial << F("IR: ") << countUnit << F("\n");
		countUnitOld = countUnit;
		if (showPulse)   setPinLow(LED_RED_PORT, LED_RED_PIN);
	}

}

/**
 * @brief Initialize the channel module
 */
void init(uint8_t channel) {
	dbg << "init pwm\n";
}

/**
 * @brief This function was called at every action
 */

void updateChannel(uint8_t channel, uint8_t state) {
	#ifdef SER_DBG
		dbg << F("Ch: ") << channel << F(", State: ") << state << '\n';
	#endif
}

/**
 * @brief Initialize all input channels
 *        ToDo: We need config for:
 *              - Channel trigger level (high or low).
 *                For trigger low, pullup need activated
 *              -
 */
void initInputChannels() {
	pinInput(SENSOR_CH1_DDR, SENSOR_CH1_PIN);									// set channel to input
	regPCIE(SENSOR_CH1_PCIE);													// set the pin change interrupt
	regPCINT(SENSOR_CH1_PCMSK, SENSOR_CH1_INT);									// description is in hal.h
}

ISR(TIMER_SENSOR_VECT) {
	if (microsecs == 1) {
		setPinHigh(SENSOR_LED_TIGGER_PORT, SENSOR_LED_TIGGER_PIN);				// Activate IR-LED pulse

	} else if (microsecs == triggerLenUs10) {
		if ( (PINC & _BV(PINC2)) && irState == 0) {								// Check if IR pulse reflected
			irState = 1;
			irCount++;
		} else if ( ((PINC & _BV(PINC2)) == 0) && irState == 1) {
			irState = 0;
			if (triggerOnBothEdgeChanges == 1) {
				irCount++;
			}
		}

		if (irCount == countsPerUnit) {
			countUnit ++;
			irCount = 0;
		}

		setPinLow(SENSOR_LED_TIGGER_PORT, SENSOR_LED_TIGGER_PIN);				// Deactivate IR-LED pulse

	} else if (microsecs >= triggerCount) {
		microsecs=0;
	}

	++microsecs;
}
