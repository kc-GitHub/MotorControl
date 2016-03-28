//- -----------------------------------------------------------------------------------------------------------------------
// AskSin driver implementation
// 2013-08-03 <trilu@gmx.de> Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
//- -----------------------------------------------------------------------------------------------------------------------
//- AskSin relay class ----------------------------------------------------------------------------------------------------
//- with a lot of support from martin876 at FHEM forum
//- -----------------------------------------------------------------------------------------------------------------------

#ifndef _cmSensor_H
#define _cmSensor_H

#include "AS.h"
#include "HAL.h"

class cmSensor {
  //- user code here ------------------------------------------------------------------------------------------------------
  public://----------------------------------------------------------------------------------------------------------------

  protected://-------------------------------------------------------------------------------------------------------------

  private://---------------------------------------------------------------------------------------------------------------
	struct s_lstCnl {
		// 0x08,
		uint8_t  sign                :1;     // 0x08, s:0, e:1
		uint8_t                      :7;     //
	} lstCnl;

  public://----------------------------------------------------------------------------------------------------------------
  //- user defined functions ----------------------------------------------------------------------------------------------
	
	void (*fInit)(uint8_t);																	// pointer to init function in main sketch
	void (*fSensor)(uint8_t,uint8_t);														// pointer to sensor function in main sketch

	void      config(void Init(uint8_t), void xSwitch(uint8_t,uint8_t));					// handover for jump addresses

  //- mandatory functions for every new module to communicate within AS protocol stack ------------------------------------
	uint8_t modBatteryStatus;																// module low battery byte
	uint8_t regCnl;																			// holds the channel for the module

	AS      *hm;																			// pointer to HM class instance

	void    configCngEvent(void);															// list1 on registered channel had changed
	void    poll(void);																		// poll function, driven by HM loop

	//- predefined, no reason to touch ------------------------------------------------------------------------------------
	void    regInHM(uint8_t cnl, uint8_t lst, AS *instPtr);									// register this module in HM on the specific channel
	void    hmEventCol(uint8_t by3, uint8_t by10, uint8_t by11, uint8_t *data, uint8_t len);// call back address for HM for informing on events
};

#endif
