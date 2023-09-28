
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

**Experimental**

This library is to use the Aosong ACD10 CO2 sensor.
Besides CO2 concentration it also provides a temperature reading.

The sensor can be read over I2C and over Serial, however this library
only support the I2C interface.
The device has a fixed I2C address of 0x2A (42). 

The CO2 concentration supported by the sensor has a range from 400 ~ 5000 ppm ±(50ppm + 5% reading).
This makes the sensor applicable for outdoor and indoor measurements in
a normal building setting. It is not suitable for CO2 heavy "industrial" environments.

When the sensor starts up it has a pre-heat period of 120 seconds.
The library provides functions to check the time since the constructor is called,
but note that this not necessarily implies the sensor is ON.
During the preheat period one can make measurements but one should use those
carefully as these are less accurate than after the preheat period.

Also important is the calibration of the sensor, although done in the factory,
a CO2 sensor needs regular calibration. See datasheet for details.

The temperature range it can measure is: **TODO UNKNOWN YET**

The sensor must be powered with 5V and usese about 225 mW.
This implies it uses 50 mA and needs a separate power supply. (Do not forget to connect GND.)
The I2C communication supports 3-5V so any 3.3V MCU should be able to connect.
(Do not forget pull up resistors).


#### Datasheet warning

Do not apply this product to safety protection devices or emergency stop equipment, and any other
applications that may cause personal injury due to the product's failure.


#### Operating conditions

- temperature: 0°C~ +50°C ==> so keep away from freezing cold or direct sunlight.
- humidity: 0% ~ 95% RH ==> non-condensing conditions.
- Data refresh frequency: 2 seconds


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


#### Related

- https://emariete.com/en/sensor-co2-mh-z19b/
- https://emariete.com/en/sensor-co2-low-consumption-mh-z1311a-winsen/
- https://revspace.nl/MHZ19
- https://www.co2.earth/ - current outdoor CO2 level can be used for calibrating.
- https://keelingcurve.ucsd.edu/ - historical outdoor CO2 level.
- https://github.com/RobTillaart/MTP40C
- https://github.com/RobTillaart/MTP40F
- https://github.com/RobTillaart/Cozir


#### Tested

TODO: Test on Arduino UNO and ESP32 ?



## I2C

The device has a fixed I2C address of 0x2A (42). 
The I2C communication supports 3-5V so any 3.3V - 5.0V MCU should be able to connect.
Do not forget pull up resistors on SDA and SCL lines.


#### Multiple sensors.

The ACD10 sensor has a fixed I2C address 0x2A (42) so only
one sensor per I2C bus can be used.
If one needs more sensors there are some options.
- One could use an I2C multiplexer - https://github.com/RobTillaart/TCA9548  (I2C 8 channel multiplexer)
- One could use an MCU with multiple I2C buses.
- One could use a Two-Wire compatible SW I2C (outside scope of this library).

Using the VCC as a Chip Select is not advised as the ACD10
has a preheat time of 2 minutes.


#### Performance I2C

Only test **readSensor()** as that is the main function.


|  Clock     |  time (us)  |
|:----------:|:-----------:|
|   100 KHz  |             |
|   200 KHz  |             |
|   300 KHz  |             |
|   400 KHz  |             |
|   500 KHz  |             |
|   600 KHz  |             |


TODO: run performance sketch.


## Interface

```cpp
#include "ACD10.h"
```

#### Constructor

- **ACD10(uint8_t address = ACD10_DEFAULT_ADDRESS, TwoWire \*wire = &Wire)**
- **bool begin(uint8_t sda, uint8_t scl)** (ESP32) initializes I2C, 
and checks if device is visible on the I2C bus.
- **bool begin()** initializes I2C, and checks if device is visible on the I2C bus.
- **bool isConnected()** Checks if device address can be found on I2C bus.
- **uint8_t getAddress()** Returns address set in the constructor.


#### PreHeat

PreHeat functions assume the sensor is (and stays) connected to power.

- **bool preHeatDone()** returns true 120 seconds after constructor is called.
- **uint32_t preHeatMillisLeft()** returns the time in milliseconds
left before preHeat is complete.


#### Request and Read

The interface of the sensor is made asynchronous as there is a delay needed
of around 80 milliseconds between a request for new data and the availability
of that new data.

- **int requestSensor()** request a new measurement / data.
This must be called before the sensor can be read by **readSensor()**
- **bool requestReady()** has enough time passed since **requestSensor()**
 to call **readSensor()**?
- **int readSensor()** read the values from the sensor.
Returns status, 0 == OK, other values are error-codes.
- **uint32_t getCO2Concentration()** get the last read CO2 measurement in 
PPM from the device.
Multiple calls will give the same value until new measurement is made.
- **uint16_t getTemperature()** get the last read temperature from the device.
Multiple calls will give the same value until new measurement is made.
- **uint32_t lastRead()** returns the moment of last **readSensor()** in milliseconds
since start.
Note the sensor can be read only once every two seconds, less often is better.
- **void setRequestTime(uint8_t milliseconds = 80)** set the time to make a measurement.
Default = 80 milliseconds.
This can be used to tweak / optimize performance a bit. 
Use 5~10 milliseconds above the minimal value the sensor still works.
- **uint8_t getRequestTime()** returns the current request time in milliseconds.


#### Calibration

Read the datasheet about calibration process (twice).
Incorrect calibration leads to incorrect output.

- **bool setCalibrationMode(uint8_t mode)** 0 = manual mode, 1 = automatic mode.
returns false if mode out of range.
- **uint8_t readCallibrationMode()** return set mode. 
- **void setManualCalibration(uint16_t value)** as the range of the device is 
from 400 to 5000, the parameter value should be in this range.
- **uint16_t readManualCalibration()** read back the set manual calibration value.

Note: One should wait 5 milliseconds between the calibration calls (see datasheet).


#### Miscellaneous

- **void factoryReset()** idem.
- **bool readFactorySet()** Read back if factory reset was successful.
- **uint32_t readFirmwareVersion(char \* arr)** copies firmware version in array.
Minimum length is 11.
- **uint32_t readSensorCode(char \* arr)** copies sensor code in array.
Minimum length is 11.


#### Debug

- **uint8_t getLastError()** returns last error of low level communication.


## Future

#### Must

- improve documentation
- get hardware to test


#### Should

- improve error handling


#### Could

- rethink function names?
- create unit tests if possible


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


