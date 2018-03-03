// WiNoIO-SetConfigTeensyWiNo
// This sketch shows how to use the WiNoIO library to set/get a valid configuration for the TeensyWiNo
// by Adrien van den Bossche <vandenbo@univ-tlse2.fr>

#include <EEPROM.h>
#include <WiNoIO.h>

WiNoIO wino;

void setup()
{
  Serial.begin(115200);
  delay(1000);

  if ( wino.loadConfig() )
  {
    Serial.print("A valid configuration has been found in EEPROM: ");
    wino.dumpCurrentConfig();
    wino.printCurrentConfig();   
  }
  else
  {
    Serial.println("No valid configuration has been found in EEPROM");
    Serial.println("Setting this config:");
    wino.setCurrentConfig(  0x91, // label 
                            0,    // antennaDelay
                            WiNoIO::LED_TYPE_NORMAL,
                            23,   // rgb Led Red Pin
                            5,    // rgb Led Green Pin
                            6,    // rgb Led Blue Pin
                            WiNoIO::TRX_TYPE_RFM22,
                            14    // trx Sck Pin
                         );
    wino.printCurrentConfig();
    wino.commitConfig();
  }
}

void loop()
{
  wino.rgbDraw(255,0,0); delay(500);
  wino.rgbDraw(0,255,0); delay(500);
  wino.rgbDraw(0,0,255); delay(500);
  wino.rgbDraw(0,0,0); delay(500);
}
