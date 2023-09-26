//
//    FILE: ACD10.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2023-09-25
// VERSION: 0.1.0
// PUPROSE: Arduino library for for I2C ACD10 CO2 sensor
//     URL: https://github.com/RobTillaart/ACD10
//          http://www.aosong.com/en/products-77.html


#include "ACD10.h"


ACD10::ACD10(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire    = wire;
  _error   = 0;
  _start   = millis();
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
  _wire->begin();
  if (! isConnected())
  {
    return false;
  }
  return true;
}


bool ACD10::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


uint8_t ACD10::getAddress()
{
  return _address;
}


/////////////////////////////////////////////
//
//  READ CO2
//
bool ACD10::preHeatDone()
{
  return preHeatMillisLeft() == 0;
}


uint32_t ACD10::preHeatMillisLeft()
{
  uint32_t delta = millis() - _start;
  if (delta >= 120000UL) return 0;
  return 120000UL - delta;
}



/////////////////////////////////////////////
//
//  CALIBRATION
//



/////////////////////////////////////////////
//
//  MISC
//
void ACD10::factoryReset()
{
  uint8_t buf[10] = { 0x52, 0x02, 0x00};
  _command(buf, 3);
}


bool ACD10::readFactorySet()
{
  uint8_t buf[10] = { 0x52, 0x02 };
  _command(buf, 2);
  _request(buf, 3);

  return (buf[1] == 0x01);
}


uint32_t ACD10::readFirmwareVersion()
{
  uint8_t buf[10] = { 0xD1, 0x00 };
  _command(buf, 2);
  _request(buf, 10);

  //  what does FWV look like?
  for (int i = 0; i < 10; i++)
  {
    if (buf[i] < 0x10) Serial.println("0");
    Serial.print(buf[i], HEX);
  }
  Serial.println();
  return 0;
}


uint32_t ACD10::readSensorCode()
{
  uint8_t buf[10] = { 0xD2, 0x01 };
  _command(buf, 2);
  _request(buf, 10);

  //  what does it look like?
  for (int i = 0; i < 10; i++)
  {
    if (buf[i] < 0x10) Serial.println("0");
    Serial.print(buf[i], HEX);
  }
  Serial.println();
  return 0;
}


/////////////////////////////////////////////
//
//  DEBUG
//
int ACD10::getLastError()
{
  int e = _error;
  _error = 0;
  return e;
}


///////////////////////////////////////////////
//
//  PRIVATE
//

int ACD10::_command(uint8_t * arr, uint8_t size)
{
  _wire->beginTransmission(_address);
  for (int i = 0; i < size; i++)
  {
    _wire->write(arr[i]);
  }
  _error = _wire->endTransmission();
  return _error;
}


int ACD10::_request(uint8_t * arr, uint8_t size)
{
  int bytes = _wire->requestFrom(_address, size);
  if (bytes == 0)  
  {
    _error = -1;
    return _error;
  }
  if (bytes < size) 
  {
    _error = -2;
    return _error;
  }
  
  for (int i = 0; i < size; i++)
  {
    arr[i] = _wire->read();
  }
  _error = 0;
  return _error;
}


uint8_t ACD10::_crc8(uint8_t * arr, uint8_t size)
{
  uint8_t crc = 0xFF;
  for (int b = 0; b < size; b++)
  {
    crc ^= arr[b];
    if (crc & 0x80)
    {
      crc <<= 1;
      crc ^= 0x31;
    }
    else
    {
      crc <<= 1;
    }
  }
  return crc;
}


//  -- END OF FILE --

