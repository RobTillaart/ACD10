//
//    FILE: ACD10.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-09-25
// VERSION: 0.1.0
// PUPROSE: Arduino library for for I2C ACD10 CO2 sensor
//     URL: https://github.com/RobTillaart/ACD10
//          http://www.aosong.com/en/products-77.html


#include "ACD10.h"


ACD10::ACD10(uint8_t address, uint8_t psi, TwoWire *wire)
{
  _address = address;
  _wire    = wire;
}


#if defined (ESP8266) || defined(ESP32)
bool ACD10::begin(uint8_t sda, uint8_t scl)
{
  _wire->begin(sda, scl);
  if (! isConnected())
  {
    return false;
  }
  return true;
}
#endif


bool ACD10::begin()
{
  reset();
  _wire->begin();
  if (! isConnected())
  {
    return false;
  }
  return true;
}


uint8_t ACD10::getAddress()
{
  return _address;
}


bool ACD10::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}



uint8_t ACD10::getLastError()
{
  uint8_t e = _error;
  _error = 0;
  return e;
}



///////////////////////////////////////////////
//
//  PRIVATE
//





//  -- END OF FILE --
