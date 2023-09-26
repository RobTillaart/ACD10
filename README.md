
[![Arduino CI](https://github.com/RobTillaart/ACD10/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ACD10/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ACD10/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ACD10/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ACD10/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/ACD10.svg)](https://github.com/RobTillaart/ACD10/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ACD10/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ACD10.svg?maxAge=3600)](https://github.com/RobTillaart/ACD10/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/ACD10.svg)](https://registry.platformio.org/libraries/robtillaart/ACD10)


# ACD10

Arduino library for the ACD10 CO2 sensor (I2C).


## Description

This library is experimental.

Aosong ACD10 CO2 and temperature sensor.

CO2 range:  400 ~ 5000 ppm ±(50ppm + 5% reading)

Temperature range:

5 V device  (225 mW @ 5V ==> 50 mA separate power supply)

- preheat time 120 seconds  TODO

operating conditions: 
- temperature: 0°~+50°; 
- humidity: 0~95%RH (non-condensing)  


#### Hardware

```
             TOPVIEW ACD10
         +--------------------+
   pin 6 | o                  |
   pin 5 | o                o |  pin 1
         |                  o |  pin 2
         |                  o |  pin 3
         |                  o |  pin 4
         |                    |
         +--------------------+
```

|  pin  |   name   |  description      |  Notes  |
|:-----:|:--------:|:------------------|:-------:|
|   1   |  SDA/RX  |  I2C data         |  3-5V
|   2   |  SCL/TX  |  I2C clock        |  3-5V
|   3   |  GND     |  Ground           |
|   4   |  VCC     |  Power +5V        |
|   5   |  SET     |  select com mode  |  HIGH (or nc) => I2C, LOW => Serial
|   6   |   -      |  not connected    |

If pin 5 is not connected, the default (HIGH) is to select I2C.
If pin 5 is connected to GND, Serial / UART mode is selected.
This latter mode is **NOT** supported by this library.


#### related

- https://emariete.com/en/sensor-co2-mh-z19b/
- https://emariete.com/en/sensor-co2-low-consumption-mh-z1311a-winsen/
- https://revspace.nl/MHZ19
- https://www.co2.earth/ - current outdoor CO2 level can be used for calibrating.
- https://keelingcurve.ucsd.edu/ - historical outdoor CO2 level.
- https://github.com/RobTillaart/MTP40C
- https://github.com/RobTillaart/MTP40F
- https://github.com/RobTillaart/Cozir


#### Tested

TODO: Test on Arduino UNO and ESP32?


#### Performance

TODO: sketch - main functions performance @100KHz


## I2C

**ACD10_DEFAULT_ADDRESS** = 0x2A


#### Multiple sensors.

The ACD10 sensor has a fixed I2C address 0x2A (42) so only 
one sensor per I2C bus can be used. 
If one needs more, one should use an I2C multiplexer or an 
MCU with multiple I2C buses.

- https://github.com/RobTillaart/TCA9548  (I2C 8 channel multiplexer)

Using the VCC as a Chip Select is not advised as the ACD10 
has a preheat time of 2 minutes.



#### Performance I2C

TODO: clock speed?
TODO: sketch


## Interface

```cpp
#include "acd10.h"
```

#### Constructor

- **ACD10(uint8_t address = ACD10_DEFAULT_ADDRESS, TwoWire \*wire = &Wire)**
- **bool begin(uint8_t sda, uint8_t scl)** ESP32 (needed?)
- **bool begin()**
- **bool isConnected()** Checks if device address can be foound on I2C bus.
- **uint8_t getAddress()** Returns address set in the constructor.


#### Read 

PreHeat functions assume the sensor is (and stays) connected to power.

- **bool preHeatDone()** returns true 120 seconds after constructor is called.
- **uint32_t preHeatMillisLeft()** returns the time in milliseconds 
left before preHeat is complete.

TODO

#### Calibration

Read the datasheet about calibration process (twice).

TODO


#### Miscellaneous

- **void factoryReset()** idem.
- **bool readFactorySet()** Read back if factory reset was successful.
- **uint32_t readFirmwareVersion()** dumps firmware version to Serial (for now)
- **uint32_t readSensorCode()** dumps sensor code version to Serial (for now)


#### Debug

- **uint8_t getLastError()**


## Future

#### Must

- improve documentation
- get hardware to test


#### Should

- create unit tests if possible

#### Could


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


