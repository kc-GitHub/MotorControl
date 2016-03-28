//- -----------------------------------------------------------------------------------------------------------------------
// AskSin driver implementation
// 2013-08-03 <trilu@gmx.de> Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
//- -----------------------------------------------------------------------------------------------------------------------
//- AskSin relay class ----------------------------------------------------------------------------------------------------
//- with a lot of support from martin876 at FHEM forum
//- -----------------------------------------------------------------------------------------------------------------------

//#define CM_SENSOR_DBG																	// debug message flag
#include "cmSensor.h"

//-------------------------------------------------------------------------------------------------------------------------
//- user defined functions -
//-------------------------------------------------------------------------------------------------------------------------
void cmSensor::config(void Init(uint8_t), void xSensor(uint8_t,uint8_t)) {
	fInit = Init;
	fSensor = xSensor;

	// execute init function
	fInit(regCnl);

	// send initial counter ??
}

/**
 * @brief Notify for config change event.
 *        It's only for information purpose while something in the channel config
 *        was changed (List0/1 or List3/4)
 */
void cmSensor::configCngEvent(void) {
	#ifdef CM_SENSOR_DBG
		dbg << F("CM_SENSOR_DBG, lst1: ") << _HEX(((uint8_t*)&lstCnl), sizeof(s_lstCnl)) << '\n';
	#endif
}

void cmSensor::poll(void) {
	//sensorPoll();
}

//-------------------------------------------------------------------------------------------------------------------------
//- predefined, no reason to touch -
//-------------------------------------------------------------------------------------------------------------------------
void cmSensor::regInHM(uint8_t cnl, uint8_t lst, AS *instPtr) {
	hm = instPtr;																			// set pointer to the HM module
//	hm->rg.regInAS(cnl, lst, s_mod_dlgt(this,&cmSensor::hmEventCol), (uint8_t*)&lstCnl,(uint8_t*)&lstPeer);
	regCnl = cnl;																			// stores the channel we are responsible fore
}

void cmSensor::hmEventCol(uint8_t by3, uint8_t by10, uint8_t by11, uint8_t *data, uint8_t len) {
	// dbg << "by3:" << by3 << " by10:" << by10 << " d:" << pHex(data, len) << '\n'; _delay_ms(100);
	if      ((by3 == 0x00) && (by10 == 0x00)) poll();
	else if ((by3 == 0x01) && (by11 == 0x06)) configCngEvent();								// config end
	else return;
}
