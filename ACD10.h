#pragma once
//
//    FILE: ACD10.h
//  AUTHOR: Rob Tillaart
//    DATE: 2023-09-25
// VERSION: 0.1.0
// PUPROSE: Arduino library for for I2C ACD10 CO2 sensor
//     URL: https://github.com/RobTillaart/ACD10
//          http://www.aosong.com/en/products-77.html


#include "Arduino.h"
#include "Wire.h"


#define ACD10_LIB_VERSION         (F("0.1.0"))
#define ACD10_DEFAULT_ADDRESS     0x2A

class ACD10
{
public:
  ACD10(uint8_t address = ACD10_DEFAULT_ADDRESS, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool     begin(uint8_t sda, uint8_t scl);
#endif
  bool     begin();
  bool     isConnected();
  uint8_t  getAddress();


  //  READ
  bool     preHeatDone();
  uint32_t preHeatMillisLeft();


  //  CALIBRATION


  //  MISC
  void     factoryReset();
  bool     readFactorySet();
  uint32_t readFirmwareVersion();   //  TODO
  uint32_t readSensorCode();        //  TODO


  //  DEBUG
  int  getLastError();


private:
  uint8_t  _address;
  TwoWire* _wire;

  int      _command(uint8_t * arr, uint8_t size);
  int      _request(uint8_t * arr, uint8_t size);
  uint8_t  _crc8(uint8_t * arr, uint8_t size);

  uint32_t _start = 0;
  uint32_t _concentration = 0;
  uint16_t _temperature   = 0;

  uint8_t  _error;
};


//  -- END OF FILE --





