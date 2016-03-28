
#define SER_DBG

//- load library's --------------------------------------------------------------------------------------------------------
#include "register.h"																// device configuration file
#include <AS.h>

#define MOTOR_STOP       0
#define MOTOR_LEFT       1
#define MOTOR_RIGHT      2

#define PIN_LOW          0
#define PIN_HIGH         1
#define PIN_GO_LOW       2
#define PIN_GO_HIGH      3

#define TRAVEL_COUNT_MAX 65535

void mototPoll();

uint8_t  motorState = 0;
uint8_t  motorStateLast = 0;
uint32_t nextMotorEvent = 0;
uint8_t  motorDirLast = MOTOR_LEFT;

int32_t travelTimeStart = 0;
int16_t travelTimeMax = 5000;
int32_t travelCount = 0;
int16_t travelMax = 0;

int32_t intervallTimeStart = 0;
int16_t intervallTimeMax = 4000;


/**
 * @brief This is the Arduino Setup-Function
 *
 * TODO: maybe we move the main parts to own setup/init function?
 */
void setup() {
	// We disable the Watchdog first
	wdt_disable();

	/*
	 * Hardware setup: everything off
	 * Without this block the code freeze after at first spi communication
	 */
	EIMSK = 0;																	// disable external interrupts
	ADCSRA = 0;																	// ADC off
	power_all_disable();														// and everything else

	DDRB = DDRC = DDRD = 0x00;													// everything as input
	PORTB = PORTC = PORTD = 0x00;												// pullup's off
	/* ********************************************************************** */

	// TODO: Maybe we should enable timer0 and SPI internally?
	power_timer0_enable();
	power_spi_enable();																// enable only needed functions

	#ifdef SER_DBG
		dbgStart();																	// serial setup
		dbg << F("Starting sketch for HM-LC-Bl1-FM_AES ...\n\n");
		dbg << F(LIB_VERSION_STRING);
	#endif
	
	hm.init();																		// init the asksin framework

	#ifdef SER_DBG
		dbg << F("HMID:  ") << _HEX(HMID,3) << F(", MAID: ") << _HEX(MAID,3) << "\n\n";		// some debug
		//dbg << F("HmKey: ") << _HEX(HMKEY, 16) << '\n';
		//dbg << F("KeyId: ") << _HEX(hmKeyIndex, 1) << '\n';

		for (uint8_t i = 1; i <= devDef.cnlNbr; i++) {											// check if AES activated for any channel
			if (hm.ee.getRegAddr(i, 1, 0, AS_REG_L1_AES_ACTIVE)) {
				dbg << F("AES active for channel: ") << _HEXB(i) << '\n';
			}
		}
		dbg << '\n';
	#endif

	/*
	 * At this point you can write your own code
	 */
	motorInit();
}

/**
 * @brief This is the Arduino Forever-Loop
 */
void loop() {
	hm.poll();																		// poll the asksin main loop

	/*
	 * At this point you can write your own code
	 */
	mototPoll();
}

/**
 * @brief Init the blind channel modul
 */
void initBlind(uint8_t channel) {
	dbg << "init initBlind\n";

	digitalWrite(A2, HIGH);
	pinInput(SW_IMPULSE_DDR, SW_IMPULSE_PIN);									// set channel to input
	regPCIE(SW_IMPULSE_PCIE);													// set the pin change interrupt
	regPCINT(SW_IMPULSE_PCMSK, SW_IMPULSE_INT);									// description is in hal.h

	digitalWrite(A3, HIGH);
	pinInput(SW_END_DDR, SW_END_PIN);											// set channel to input
	regPCIE(SW_END_PCIE);														// set the pin change interrupt
	regPCINT(SW_END_PCMSK, SW_END_INT);											// description is in hal.h
}

/**
 * @brief This function was called at every action
 */
void blindUpdateState(uint8_t channel, uint8_t state, uint16_t rrttb) {			// rrttb = REFERENCE_RUNNING_TIME_BOTTOM_TOP
	travelMax = rrttb / 1000;

	if ((state == 200 && motorStateLast == MOTOR_LEFT) || (state == 0 && motorStateLast == MOTOR_RIGHT)) {
		motorState = MOTOR_STOP;

	} else if (state == 200) {
		motorState = MOTOR_LEFT;
		travelTimeStart = getMillis();
		intervallTimeStart = getMillis();
		motorDirLast = MOTOR_LEFT;

	} else if (state == 0) {
		motorState = MOTOR_RIGHT;
		travelTimeStart = getMillis();
		intervallTimeStart = getMillis();
		motorDirLast = MOTOR_LEFT;

	} else if (state == 201) {							// toggle
		if (motorState > MOTOR_STOP) {
			motorState = MOTOR_STOP;

		} else if (motorDirLast == MOTOR_RIGHT) {
			motorState = MOTOR_LEFT;
			motorDirLast = MOTOR_LEFT;
			travelTimeStart = getMillis();
			intervallTimeStart = getMillis();

		} else if (motorDirLast == MOTOR_LEFT) {
			motorState = MOTOR_RIGHT;
			motorDirLast = MOTOR_RIGHT;
			travelTimeStart = getMillis();
			intervallTimeStart = getMillis();
		}
	}

	#ifdef SER_DBG
		dbg << F("Ch: ") << channel << F(", State: ") << state << ", motorState: " << motorState << ", motorDirLast: " << motorDirLast << '\n';
	#endif
}

void motorInit() {
	/** Debug start */
	pinMode(A0, OUTPUT);
	pinMode(A1, OUTPUT);

	motorState = MOTOR_STOP;
	motorStateLast = MOTOR_STOP;
}

void sendPosition() {
	cmBlind[0].setSendState( 200 - ((travelCount * 200) / travelMax) );			// send position
}

void mototPoll() {
	uint8_t endSwitchState = chkPCINT(SW_END_PCIE, SW_END_INT);

	if ((endSwitchState == PIN_GO_LOW || endSwitchState == PIN_LOW) && motorState == MOTOR_LEFT) {	// end switch reached
		motorState = MOTOR_STOP;
		travelCount = 0;
		dbg << F("end switch reached: ") << endSwitchState << '\n';
	}

	if (travelCount >= travelMax     && motorState == MOTOR_RIGHT) { 								// travel distance reached
		motorState = MOTOR_STOP;
		dbg << F("travel distance reached, travelMax: ") << travelMax << '\n';
	}

	if (motorState != MOTOR_STOP) {
		digitalWrite(5, HIGH);													// set green LED on at traveling
																				// led switched off by asksin module automaticly

		if ( (getMillis() - travelTimeStart) > travelTimeMax ) {				// travel impulse missing
			motorState = MOTOR_STOP;

			uint32_t tts = (getMillis() - travelTimeStart);
			dbg << F("travel impulse missing: ") << tts << ", " << travelTimeStart << '\n';
		}
	}

//	if ( (motorState == MOTOR_LEFT && motorStateLast == MOTOR_LEFT) || (motorState == MOTOR_LEFT && motorStateLast == MOTOR_LEFT) ) {
//		motorState = MOTOR_STOP;
//	}

	if (motorState != motorStateLast) {
		if        (motorState == MOTOR_STOP) {
			motorStop();
		} else if (motorState == MOTOR_LEFT) {
			motorLeft();
		} else if (motorState == MOTOR_RIGHT && travelCount < travelMax) {
			motorRight();
		}
	}

	uint8_t impulseSwitch = chkPCINT(SW_IMPULSE_PCIE, SW_IMPULSE_INT);
	if (impulseSwitch == PIN_GO_LOW) {
		if (motorState == MOTOR_RIGHT && travelCount < TRAVEL_COUNT_MAX) {
			travelCount++;
		} else if (motorState == MOTOR_LEFT && travelCount > 0) {
			travelCount--;
		}

		dbg << F("travelCount: ") << travelCount << '\n';

		// reset travelTimeStart
		travelTimeStart = getMillis();
	}

	if (motorState != motorStateLast) {
		motorStateLast = motorState;
	}

	if (motorState != MOTOR_STOP && (getMillis() - intervallTimeStart) > intervallTimeMax) {
		intervallTimeStart = getMillis();
		sendPosition();
	}
}

void motorLeft() {
	motorStop();
	digitalWrite(A0, 0);
	digitalWrite(A1, 1);
}

void motorRight() {
	motorStop();
	digitalWrite(A0, 1);
	digitalWrite(A1, 0);
}

void motorStop() {
	digitalWrite(A0, 0);
	digitalWrite(A1, 0);

	sendPosition();

	_delay_ms(100);
}

void motorBreak() {
	motorStop();
	digitalWrite(A0, 0);
	digitalWrite(A1, 0);
}
