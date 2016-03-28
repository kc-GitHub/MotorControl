#ifndef _REGISTER_h
	#define _REGISTER_h//- load library's --------------------------------------------------------------------------------------------------------

	#include <AS.h>
	#include "hardware.h"																				// hardware definition
	#include <cmBlind.h>

	AS hm;																								// asksin framework
	cmBlind cmBlind[1];																					// create instances of channel module
	extern void initBlind(uint8_t channel);																// declare function to jump in
	extern void switchBlind(uint8_t channel, uint8_t status);											// declare function to jump in

	/*
	 * Default HM id, serial key data
	 * At first start of the sketch, this data was copied to EEprom.
	 * So next time you can flash firmware without changing the data.
	 */
	const uint8_t HMSerialData[] PROGMEM = {
		0x01, 0x02, 0x06,																				// default HMID
		't', 'l', 'u', '1', '0', '0', '1', '2', '3', '6',												// default HMSerial
	//	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x00, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F	// dummy key
		0xA4, 0xE3, 0x75, 0xC6, 0xB0, 0x9F, 0xD1, 0x85, 0xF2, 0x7C, 0x4E, 0x96, 0xFC, 0x27, 0x3A, 0xE4	// HM default key
	};

	// AES-Key LXCCU: Text=test0815 Hex=F0 1C 20 61 05 C4 D0 D7 B3 12 8F D9 F5 A5 BE E6

	//- ----------------------------------------------------------------------------------------------------------------------
	//- ----------------------------------------------------------------------------------------------------------------------
	//                                   FW  moID   serial                         ST  devInfo
	// <- 1A 01 A4 00 01 02 05 63 19 63  15  00 6C  74 6C 75 31 30 30 31 32 33 35  10  11 01 00
	// FW   -> Firmware, sometimes given in xml files of hm config software
	// moID -> Model ID, important for identification in hm config software
	// ST   -> Subtype, identifier if device is a switch or a blind or a remote
	// devInfo -> Device Info -> sometimes hm config files are refering on byte 23 for the amount of channels, other bytes not known
	//                           23:0 0.4, means first four bit of byte 23 reflecting the amount of channels
	//
	//- settings of HM device for AS class -----------------------------------------------------------------------------------
	const uint8_t devIdnt[] PROGMEM = {
	    /* Firmware version 1 byte */  0x25,
//	    /* Firmware version 1 byte */  0x01,
	    /* Model ID         2 byte */  0x00, 0x05,
	    /* Sub Type ID      1 byte */  0x30,
	    /* Device Info      3 byte */  0x01, 0x01, 0x00,
	};


	#define REG_MASTER_ID             0x01
	#define REG_LOCAL_RESET_DISABLE   0x02
	#define REG_INTERNAL_KEYS_VISIBLE 0x03
	#define REG_BURST_RX              0x04
	#define REG_AES_ACTIVE            0x05

	// ggf. müssen wir INTERNAL_KEYS_VISIBLE beahten wenn ein keychange ansteht?
	// INTERNAL_KEYS_VISIBLE	index="2.7" size="0.1"		default="true"						ui_flags="internal"	??

	// CONF_BUTTON_TIME			index="0x15" size="1"		default="5"		special_value id="PERMANENT" value="255"
	// LOW_BAT_LIMIT			index="18" size="1"			default="10.5"
	// BURST_RX					index="1" size="1.0"		default="false"

	// CYCLIC_INFO_MSG			index="9" size="1"			default="false"
	// TRANSMIT_DEV_TRY_MAX		index="20" size="1"

	// DEVICE_LED_MODE			index="5.6" size="0.2		default="true"
	// BUTTON_LOCK				index="15" size="1.0"		default="false"

	// LIVE_MODE_RX				ks550


	const uint8_t registerMapList0[] PROGMEM = {
		// Register              id(addr), bitPos, bitLength
		REG_MASTER_ID,           0x01,     0,      24,
		REG_BURST_RX,            0x01,     0,      8,     //  1 (decimal)
		REG_LOCAL_RESET_DISABLE, 0x18,     1,      1,     // 24 (decimal)
	};

	const uint8_t registerMapList1[] PROGMEM = {
		REG_AES_ACTIVE,    0x08, 3,     1,
	};

	struct s_regDevL0 {
		// 0x01,0x02,0x0a,0x0b,0x0c,0x18,
		uint8_t burstRx; // 0x01, s:0, e:0
		uint8_t :7; // l:0, s:7
		uint8_t intKeyVisib :1; // 0x02, s:7, e:8
		uint8_t pairCentral[3]; // 0x0a, s:0, e:0
		uint8_t localResDis; // 0x18, s:0, e:0
	};



	//- ----------------------------------------------------------------------------------------------------------------------
	//- channel slice address definition -------------------------------------------------------------------------------------
	const uint8_t cnlAddr[] PROGMEM = {
	    0x02, 0x0a, 0x0b, 0x0c,0x12,0x18,
	    0x0b, 0x0d, 0x0f, 0x10,
	    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0f, 0x11, 0x1c, 0x1d, 0x1e, 0x1f, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8f, 0x91, 0x9c, 0x9d, 0x9e, 0x9f,
	};  // 48 byte

	//- channel device list table --------------------------------------------------------------------------------------------
	EE::s_cnlTbl cnlTbl[] = {
	    // cnl, lst, sIdx, sLen, pAddr;
	    {  0,  0, 0x00,  6,  0x001f, 0, },
	    {  1,  1, 0x06,  4,  0x0025, 0, },
	    {  1,  3, 0x0a, 38,  0x0029, 0, },
	};  // 18 byte

	//- peer device list table -----------------------------------------------------------------------------------------------
	EE::s_peerTbl peerTbl[] = {
	    // cnl, pMax, pAddr;
	    {  1,  6, 0x010d, },
	};  // 4 byte

	//- handover to AskSin lib -----------------------------------------------------------------------------------------------
	EE::s_devDef devDef = {
	    1, 3, devIdnt, cnlAddr,
	};  // 6 byte

	//- module registrar -----------------------------------------------------------------------------------------------------
	RG::s_modTable modTbl[1];

//- ----------------------------------------------------------------------------------------------------------------------
//- first time and regular start functions -------------------------------------------------------------------------------

	void everyTimeStart(void) {
		// place here everything which should be done on each start or reset of the device
		// typical use case are loading default values or user class configurations

		// init the homematic framework
		hm.confButton.config(1, CONFIG_KEY_PCIE, CONFIG_KEY_INT);           // configure the config button, mode, pci byte and pci bit
		hm.ld.init(2, &hm);                                                 // set the led
		hm.ld.set(welcome);                                                 // show something
		hm.bt.set(30, 3600000);                                             // set battery check, internal, 2.7 reference, measurement each hour
		hm.pw.setMode(0);                                                   // set power management mode

	    // register user modules
	    cmBlind[0].regInHM(1, 3, &hm);                                     // register user module
	    cmBlind[0].config(&initBlind, &switchBlind);                       // configure user module

	}

	void firstTimeStart(void) {
		// place here everything which should be done on the first start or after a complete reset of the sketch
		// typical use case are default values which should be written into the register or peer database

	}
#endif
