generating new hm ID...
parameter: 0f06



#ifndef _REGISTER_h
   #define _REGISTER_h

   #include <AS.h>                                                       // the asksin framework
   #include "hardware.h"                                                 // hardware definition
   #include <cmBlind.h>
   #include "hmkey.h"

   AS hm;                                                               // asksin framework
   cmBlind cmBlind[1];                                                  // create instances of channel module
   extern void initBlind(uint8_t channel);                              // declare function to jump in
   extern void switchBlind(uint8_t channel, uint8_t status);            // declare function to jump in

   /*
   * HMID, Serial number, HM-Default-Key, Key-Index
   */
   const uint8_t HMSerialData[] PROGMEM = {
      /* HMID */            0xb9,0x95,0xfd,
      /* Serial number */   'X','M','S','2','3','4','5','6','7','8',    // XMS2345678
      /* Default-Key */     HM_DEVICE_AES_KEY,
      /* Key-Index */       HM_DEVICE_AES_KEY_INDEX
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
      /* firmwareVersion 1 byte */  0x11,
      /* modelID         2 byte */  0x0f,0x06,
      /* subTypeID       1 byte */  0x30,
      /* deviceInfo      3 byte */  0x01,0x01,0x00,
   };

   /* 
   * Register definitions
   * The values are offset adresses in relation to the start adress defines in cnlTbl
   * Register values can found in related Device-XML-File.
      
   * Spechial register list 0: 0x0A, 0x0B, 0x0C
   * Spechial register list 1: 0x08
   *  
   * @See Defines.h
   *  
   * @See: cnlTbl
   */ 
   const uint8_t cnlAddr[] PROGMEM = {
      // channel: 0, list: 0 
      0x02,0x0a,0x0b,0x0c,0x12,0x18,
      // channel: 1, list: 1 
      0x08,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,
      // channel: 1, list: 3 
      0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0f,0x11,0x1c,0x1d,0x1e,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8f,0x91,0x9c,0x9d,0x9e,
   }; // 49 byte

   /* 
   * Channel - List translation table
   * channel, list, startIndex, start address in EEprom, hidden
   */
   EE::s_cnlTbl cnlTbl[] = {
      // cnl, lst, sIdx, sLen, pAddr,  hidden
      {  0,   0,   0x00,  6,   0x0020, 0, },
      {  1,   1,   0x06,  7,   0x0026, 0, },
      {  1,   3,   0x0d, 36,   0x002d, 0, },
   }; // 21 byte

   /* 
   * Peer-Device-List-Table 
   * channel, maximum allowed peers, start address in EEprom 
   */ 
   EE::s_peerTbl peerTbl[] = {
      // cnl, pMax, pAddr;
      { 1, 6, 0x0105, },
   }; // 4 byte

   /* 
   * Device definition table 
   * Parameter: amount of user channel(s), amount of lists, 
   * pointer to device identification string and pointer to the channel table 
   */ 
   EE::s_devDef devDef = {
      1, 3, devIdnt, cnlAddr,
   }; // 6 byte

   /* 
   * module registrar 
   * size table to register and access channel modules 
   */ 
   RG::s_modTable modTbl[1];

   /** 
   * @brief First time and regular start functions 
   */ 
   void everyTimeStart(void) {
      /* 
      * Place here everything which should be done on each start or reset of the device. 
      * Typical use case are loading default values or user class configurations. 
      */ 

      // init the homematic framework
      hm.confButton.config(2, CONFIG_KEY_PCIE, CONFIG_KEY_INT);           // configure the config button, mode, pci byte and pci bit
      hm.ld.init(2, &hm);                                                 // set the led
      hm.ld.set(welcome);                                                 // show something
      hm.bt.set(30, 3600000);                                             // set battery check, internal, 2.7 reference, measurement each hour
      hm.pw.setMode(0);                                                   // set power management mode

      // register user modules
      cmBlind[0].regInHM(1, 3, &hm);                                    // register user module
      cmBlind[0].config(&initBlind, &switchBlind);                      // configure user module

   }

   void firstTimeStart(void) {
      /* 
      * place here everything which should be done on the first start or after a complete reset of the sketch
      * typical usecase are default values which should be written into the register or peer database
      */ 

      const uint8_t cnl0lst0[] = { 
         0x80,0x00,0x00,0x00,0x69,0x00,
      };

      const uint8_t cnl1lst1[] = { 
         0x00,0xf4,0x01,0xf4,0x01,0x05,0x00,
      };

      const uint8_t cnl1lst3[] = { 
         0x00,0x00,0x00,0x32,0x64,0x00,0xff,0x00,0xff,0x01,0x88,0x88,0x88,0x00,0xc8,0x00,0xff,0x88,0x00,0x00,0x00,0x32,0x64,0x00,0xff,0x00,0xff,0x21,0x88,0x88,0x88,0x00,0xc8,0x00,0x05,0x88,
      };

   }

#endif
   struct s_cnl0lst0 { 
      uint8_t INTERNAL_KEYS_VISIBLE                :1;    // 0x02.7, 0x01
      uint8_t MASTER_ID_BYTE_1                     :8;    // 0x0a.0, 0x00
      uint8_t MASTER_ID_BYTE_2                     :8;    // 0x0b.0, 0x00
      uint8_t MASTER_ID_BYTE_3                     :8;    // 0x0c.0, 0x00
      uint8_t LOW_BAT_LIMIT                        :8;    // 0x12.0, 0x69
      uint8_t LOCAL_RESET_DISABLE                  :1;    // 0x18.0, 0x00
      uint8_t                                      :7;    // 0x18.1
   }; 

   struct s_cnl1lst1 { 
      uint8_t AES_FLAG                             :1;    // 0x08.0, 0x00
      uint8_t                                      :7;    // 0x08.1
      uint8_t REFERENCE_RUNNING_TIME_TOP_BOTTOM    :8;    // 0x0b.0, 0xf4
      uint8_t REFERENCE_RUNNING_TIME_TOP_BOTTOM    :8;    // 0x0c.0, 0x01
      uint8_t REFERENCE_RUNNING_TIME_BOTTOM_TOP    :8;    // 0x0d.0, 0xf4
      uint8_t REFERENCE_RUNNING_TIME_BOTTOM_TOP    :8;    // 0x0e.0, 0x01
      uint8_t CHANGE_OVER_DELAY                    :8;    // 0x0f.0, 0x05
      uint8_t REFERENCE_RUN_COUNTER                :8;    // 0x10.0, 0x00
   }; 

   struct s_cnl1lst3 { 
      uint8_t SHORT_CT_RAMPON                      :4;    // 0x01.0, 0x00
      uint8_t SHORT_CT_RAMPOFF                     :4;    // 0x01.4, 0x00
      uint8_t SHORT_CT_ONDELAY                     :4;    // 0x02.0, 0x00
      uint8_t SHORT_CT_OFFDELAY                    :4;    // 0x02.4, 0x00
      uint8_t SHORT_CT_ON                          :4;    // 0x03.0, 0x00
      uint8_t SHORT_CT_OFF                         :4;    // 0x03.4, 0x00
      uint8_t SHORT_COND_VALUE_LO                  :8;    // 0x04.0, 0x32
      uint8_t SHORT_COND_VALUE_HI                  :8;    // 0x05.0, 0x64
      uint8_t SHORT_ONDELAY_TIME                   :8;    // 0x06.0, 0x00
      uint8_t SHORT_ON_TIME                        :8;    // 0x07.0, 0xff
      uint8_t SHORT_OFFDELAY_TIME                  :8;    // 0x08.0, 0x00
      uint8_t SHORT_OFF_TIME                       :8;    // 0x09.0, 0xff
      uint8_t SHORT_ACTION_TYPE                    :2;    // 0x0a.0, 0x01
      uint8_t                                      :4;    // 0x0a.2
      uint8_t SHORT_OFF_TIME_MODE                  :1;    // 0x0a.6, 0x00
      uint8_t SHORT_ON_TIME_MODE                   :1;    // 0x0a.7, 0x00
      uint8_t SHORT_JT_ON                          :4;    // 0x0b.0, 0x08
      uint8_t SHORT_JT_OFF                         :4;    // 0x0b.4, 0x08
      uint8_t SHORT_JT_ONDELAY                     :4;    // 0x0c.0, 0x08
      uint8_t SHORT_JT_OFFDELAY                    :4;    // 0x0c.4, 0x08
      uint8_t SHORT_JT_RAMPON                      :4;    // 0x0d.0, 0x08
      uint8_t SHORT_JT_RAMPOFF                     :4;    // 0x0d.4, 0x08
      uint8_t SHORT_OFF_LEVEL                      :8;    // 0x0f.0, 0x00
      uint8_t SHORT_ON_LEVEL                       :8;    // 0x11.0, 0xc8
      uint8_t SHORT_CT_REFON                       :4;    // 0x1c.0, 0x00
      uint8_t SHORT_CT_REFOFF                      :4;    // 0x1c.4, 0x00
      uint8_t SHORT_MAX_TIME_FIRST_DIR             :8;    // 0x1d.0, 0xff
      uint8_t SHORT_JT_REFON                       :4;    // 0x1e.0, 0x08
      uint8_t SHORT_JT_REFOFF                      :4;    // 0x1e.4, 0x08
      uint8_t LONG_CT_RAMPON                       :4;    // 0x81.0, 0x00
      uint8_t LONG_CT_RAMPOFF                      :4;    // 0x81.4, 0x00
      uint8_t LONG_CT_ONDELAY                      :4;    // 0x82.0, 0x00
      uint8_t LONG_CT_OFFDELAY                     :4;    // 0x82.4, 0x00
      uint8_t LONG_CT_ON                           :4;    // 0x83.0, 0x00
      uint8_t LONG_CT_OFF                          :4;    // 0x83.4, 0x00
      uint8_t LONG_COND_VALUE_LO                   :8;    // 0x84.0, 0x32
      uint8_t LONG_COND_VALUE_HI                   :8;    // 0x85.0, 0x64
      uint8_t LONG_ONDELAY_TIME                    :8;    // 0x86.0, 0x00
      uint8_t LONG_ON_TIME                         :8;    // 0x87.0, 0xff
      uint8_t LONG_OFFDELAY_TIME                   :8;    // 0x88.0, 0x00
      uint8_t LONG_OFF_TIME                        :8;    // 0x89.0, 0xff
      uint8_t LONG_ACTION_TYPE                     :2;    // 0x8a.0, 0x01
      uint8_t                                      :3;    // 0x8a.2
      uint8_t LONG_MULTIEXECUTE                    :1;    // 0x8a.5, 0x01
      uint8_t LONG_OFF_TIME_MODE                   :1;    // 0x8a.6, 0x00
      uint8_t LONG_ON_TIME_MODE                    :1;    // 0x8a.7, 0x00
      uint8_t LONG_JT_ON                           :4;    // 0x8b.0, 0x08
      uint8_t LONG_JT_OFF                          :4;    // 0x8b.4, 0x08
      uint8_t LONG_JT_ONDELAY                      :4;    // 0x8c.0, 0x08
      uint8_t LONG_JT_OFFDELAY                     :4;    // 0x8c.4, 0x08
      uint8_t LONG_JT_RAMPON                       :4;    // 0x8d.0, 0x08
      uint8_t LONG_JT_RAMPOFF                      :4;    // 0x8d.4, 0x08
      uint8_t LONG_OFF_LEVEL                       :8;    // 0x8f.0, 0x00
      uint8_t LONG_ON_LEVEL                        :8;    // 0x91.0, 0xc8
      uint8_t LONG_CT_REFON                        :4;    // 0x9c.0, 0x00
      uint8_t LONG_CT_REFOFF                       :4;    // 0x9c.4, 0x00
      uint8_t LONG_MAX_TIME_FIRST_DIR              :8;    // 0x9d.0, 0x05
      uint8_t LONG_JT_REFON                        :4;    // 0x9e.0, 0x08
      uint8_t LONG_JT_REFOFF                       :4;    // 0x9e.4, 0x08
   }; 


