//
//    FILE: ACD10_readSensor.ino
//  AUTHOR: Rob Tillaart
// PUPROSE: test basic behaviour and performance


#include "Wire.h"
#include "ACD10.h"


ACD10 mySensor;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ACD10_LIB_VERSION: ");
  Serial.println(ACD10_LIB_VERSION);

  Wire.begin();
  mySensor.begin();
}


void loop()
{
  if (millis() - mySensor.lastRead() > 10000)  //  millis
  {
    mySensor.readSensor();
    Serial.print(mySensor.getCO2Concentration());
    Serial.print("\t");
    Serial.print(mySensor.getTemperature());
    Serial.println();
  }
}


//  -- END OF FILE --
