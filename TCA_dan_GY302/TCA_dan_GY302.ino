#include <Arduino.h>
#include "TCA9548A.h"
#include <BH1750.h>

TCA9548A I2CMux;     // Address can be passed into the constructor

BH1750 lightMeter1;
BH1750 lightMeter2;
BH1750 lightMeter3;
BH1750 lightMeter4;
BH1750 lightMeter5;

void setup() {
  Serial.begin(115200);             // Define baud rate
  I2CMux.begin(Wire);             // TwoWire isntance can be passed here as 3rd argument
  lightMeter1.begin();
  lightMeter2.begin();
  lightMeter3.begin();
  lightMeter4.begin();
  lightMeter5.begin();
  I2CMux.closeAll();              // Set a base state which we know (also the default state on power on)
}

void loop() 
{
  I2CMux.openChannel(0);
  float lux1 = lightMeter1.readLightLevel();
  I2CMux.closeChannel(0);
  
  I2CMux.openChannel(1);
  float lux2 = lightMeter2.readLightLevel();
  I2CMux.closeChannel(1);

  I2CMux.openChannel(2);
  float lux3 = lightMeter3.readLightLevel();
  I2CMux.closeChannel(2);

  I2CMux.openChannel(3);
  float lux4 = lightMeter4.readLightLevel();
  //I2CMux.closeChannel(3);

  I2CMux.openChannel(4);
  float lux5 = lightMeter5.readLightLevel();
 // I2CMux.closeChannel(4);
 // I2CMux.openChannel(5);
 // I2CMux.closeChannel(5);
  
  Serial.print(lux1); Serial.print(" | "); 
  Serial.print(lux2); Serial.print(" | "); 
  Serial.print(lux3); Serial.print(" | "); 
  Serial.print(lux4); Serial.print(" | "); 
  Serial.println(lux5);
  delay(500);
  /* Code  to interactive with revealed addresses on bus */
  I2CMux.closeAll();
}
