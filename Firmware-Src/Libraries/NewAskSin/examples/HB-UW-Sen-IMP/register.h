#ifndef _REGISTER_h
	#define _REGISTER_h

	//- load library's --------------------------------------------------------------------------------------------------------
	#include "hardware.h"
	#include <cmSensor.h>
	#include "hmkey.h"

	#define CHANNEL_MODE_OPTICAL          1
	#define CHANNEL_MODE_IMPLUSE_LOW      2
	#define CHANNEL_MODE_IMPLUSE_HIGH     3
	#define CHANNEL_MODE_VOLTAGE_MEASURE  3


	AS hm;																			// asksin framework
	cmSensor cmSensor[1];															// create 1 instances of channel module
	extern void init(uint8_t channel);											// declare function to jump in
	extern void updateChannel(uint8_t channel, uint8_t state);					// declare function to jump in

	/*
	 * HMID, Serial number, HM-Default-Key, Key-Index
	 */
	const uint8_t HMSerialData[] PROGMEM = {
		/* HMID */            0x01, 0x02, 0x08,
		/* Serial number */   'H', 'B', 'I', 'M', 'P', '0', '0', '0', '0', '8',		// HBIMP00001
		/* Default-Key */     HM_DEVICE_AES_KEY,
		/* Key-Index */       HM_DEVICE_AES_KEY_INDEX,
	};

	/*
	 * Settings of HM device
	 * firmwareVersion: The firmware version reported by the device
	 *                  Sometimes this value is important for select the related device-XML-File
	 *
	 * modelID:         Important for identification of the device.
	 *                  @See Device-XML-File /device/supported_types/type/parameter/const_value
	 *
	 * subType:         Identifier if device is a switch or a blind or a remote
	 * DevInfo:         Sometimes HM-Config-Files are referring on byte 23 for the amount of channels.
	 *                  Other bytes not known.
	 *                  23:0 0.4, means first four bit of byte 23 reflecting the amount of channels.
	 */
	const uint8_t devIdnt[] PROGMEM = {
		/* firmwareVersion 1 byte */  0x01,
		/* modelID         2 byte */  0xF1, 0x05,									// HB-UW-Sen-IMP
		/* modelID         2 byte */  //0x00, 0xDE,									// HB-UW-Sen-IMP
		/* subTypeID       1 byte */  0x00,											// To be defined
		/* deviceInfo      3 byte */  0x41, 0x01, 0x00,
	};

	/*
	 * Register definitions
	 * The values are adresses in relation to the start adress defines in cnlTbl
	 * Register values can found in related Device-XML-File.

	 * Spechial register list 0: 0x0A, 0x0B, 0x0C
	 * Spechial register list 1: 0x08
	 *
	 * @See Defines.h
	 *
	 * @See: cnlTbl
	 */
	const uint8_t cnlAddr[] PROGMEM = {
		// List0-Register
		0x0a,0x0b,0x0c,0x18

		// List1-Register
		0x08,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x30,0x57,

	};

	/*
	 * Channel - List translation table
	 * channel, list, startIndex, start address in EEprom, hidden
	 */
	EE::s_cnlTbl cnlTbl[] = {
		// cnl, lst, sIdx,  sLen, pAddr,  hidden
		{  0,    0,   0x00, 4,    0x000f, 0, },
	};

	/*
	 * Peer-Device-List-Table
	 * channel, maximum allowed peers, start address in EEprom
	 */
	EE::s_peerTbl peerTbl[] = {
		// cnl, peerMax, pAddr;
	};

	/*
	 * handover to AskSin lib
	 *
	 * TODO: Describe
	 */
	EE::s_devDef devDef = {
		0, 1, devIdnt, cnlAddr,
	};

	/*
	 * module registrar
	 *
	 * TODO: Describe
	 */
	RG::s_modTable modTbl[0];

	struct s_lst0Cnl0 {
	// 0x0a, 0x0b, 0x0c, 0x18,
	    uint8_t Master_ID_A               :8;       // 0x0a, s:0, e:8
	    uint8_t Master_ID_B               :8;       // 0x0b, s:0, e:8
	    uint8_t Master_ID_C               :8;       // 0x0c, s:0, e:8
	    uint8_t LOCAL_RESET_DISABLE       :1;       // 0x18, s:0, e:1
	    uint8_t                           :7;       // 0x18, s:1, l:7
	};  // 4 byte

	/**
	 * @brief First time and regular start functions
	 */
	void everyTimeStart(void) {
		/*
		 * Place here everything which should be done on each start or reset of the device.
		 * Typical use case are loading default values or user class configurations.
		 */

		// init the homematic framework
		hm.confButton.config(1, CONFIG_KEY_PCIE, CONFIG_KEY_INT);					// configure the config button, mode, pci byte and pci bit

		hm.ld.init(2, &hm);															// configure the led
		hm.ld.set(welcome);															// show a "hello" at the led

		// hm.bt.set(30, 3600000);													// set battery check, internal, 2.7 reference, measurement each hour
		hm.pw.setMode(POWER_MODE_NO_SLEEP);											// set power management mode

		// register user modules
		cmSensor[0].regInHM(1, 3, &hm);												// register user module
		cmSensor[0].config(&init, &updateChannel);									// configure user module
	}

	/**
	 * TODO: maybe we can delete this?
	 */
	void firstTimeStart(void) {
	}

#endif
