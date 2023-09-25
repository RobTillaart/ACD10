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

class ACD10
{
public:
  explicit ACD10(const uint8_t deviceAddress, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool     begin(int sda, int scl);
#endif
  bool     begin();
  bool     isConnected();

  uint8_t  getAddress();

  int      read();


  //  ERROR
  uint8_t  getLastError();


private:
  uint8_t  _address;
  TwoWire* _wire;

  uint8_t  writeReg(uint8_t reg, uint8_t value);
  uint8_t  readReg(uint8_t reg);

  uint8_t  _error;
};


//  -- END OF FILE --





