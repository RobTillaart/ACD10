
[![Arduino CI](https://github.com/RobTillaart/ACD10/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/ACD10/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/ACD10/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/ACD10/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/ACD10/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/ACD10.svg)](https://github.com/RobTillaart/ACD10/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ACD10/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ACD10.svg?maxAge=3600)](https://github.com/RobTillaart/ACD10/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/ACD10.svg)](https://registry.platformio.org/libraries/robtillaart/ACD10)


# ACD10

Arduino library for the ACD10 CO2 sensor.


## Description

This library is experimental.

Assong ACD10 CO2 and temperature sensor.
TODO: range?



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

TODO: Does it support other addresses?

TODO: include section about I2C multiplexer, multi devices.


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

TODO

#### Calibration

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


