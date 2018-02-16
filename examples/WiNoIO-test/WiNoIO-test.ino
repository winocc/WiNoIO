// WiNoIO-test
// This sketch shows how to use the WiNoIO library to get a valid configuration from EEPROM
// by Adrien van den Bossche <vandenbo@univ-tlse2.fr>

#include <WiNoIO.h>

WiNoIO wino;

void setup()
{
  Serial.begin(115200);
  delay(2000);
  wino.setDebug(true);

  wino.loadConfig();
  wino.dumpCurrentConfig();
  wino.printCurrentConfig();
}

void loop()
{
  wino.rgbDraw(255,0,0); delay(500);
  wino.rgbDraw(0,255,0); delay(500);
  wino.rgbDraw(0,0,255); delay(500);
  wino.rgbDraw(0,0,0); delay(500);
}
