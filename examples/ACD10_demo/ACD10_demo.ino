//
//    FILE: ACD10_demo.ino
//  AUTHOR: Rob Tillaart
// PUPROSE: test basic behaviour and performance


#include "Wire.h"
#include "ACD10.h"


ACD10 mySensor;  //   default address


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

}


//  -- END OF FILE --
