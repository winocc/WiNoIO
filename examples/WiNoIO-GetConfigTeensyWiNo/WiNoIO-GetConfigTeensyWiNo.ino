// WiNoIO-GetConfigTeensyWiNo
// This sketch shows how to use the WiNoIO library to get a valid configuration for the TeensyWiNo
// and use it to configure the transceiver. Then a sniffer is executed on the node
// by Adrien van den Bossche <vandenbo@univ-tlse2.fr>

#include <RH_RF22.h>
#include <WiNoIO.h>

RH_RF22 rf22(SS,9);
WiNoIO wino;

uint8_t buf[RH_RF22_MAX_MESSAGE_LEN];
uint8_t len = sizeof(buf);

void setup()
{ 
  if (!wino.loadConfig() ) while (1);
  SPI.setSCK(wino.getTrxSckPin());
  Serial.begin(115200);

  if (!rf22.init()){
      Serial.printf("init rf22 failed\n");
      exit(1);
  }

  wino.rgbDraw(128,128,0); // Yellow
}

void loop()
{
  if (rf22.recv(buf, &len)) {
    Serial.printf("RF22\t%d\t", rf22.lastRssi());
    for (int i=0; i<len; i++) {
       Serial.printf("|%02x",buf[i]);
    }
    Serial.printf("| "); 
    for (int i=0; i<len; i++) {
      if ( buf[i] >= 0x30 ) {
        Serial.printf("%c",buf[i]);
      } else {
        Serial.printf(".");
      }
    }
    Serial.printf("\n"); 
  }
}
