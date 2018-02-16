// WiNoIO-GetConfigDecaWiNo
// This sketch shows how to use the WiNoIO library to get a valid configuration for the DecaWiNo
// and use it to configure the transceiver. Then a sniffer is executed on the node
// by Adrien van den Bossche <vandenbo@univ-tlse2.fr>

#include <SPI.h>
#include <DecaDuino.h>
#include <WiNoIO.h>

DecaDuino decaduino;
WiNoIO wino;

#define MAX_FRAME_LEN 120
uint8_t rxData[MAX_FRAME_LEN];
uint16_t rxLen;
int rxFrames;


void setup()
{ 
  if (!wino.loadConfig() ) while (1);
  SPI.setSCK(wino.getTrxSckPin());
  Serial.begin(115200);

  if (!decaduino.init()){
      Serial.printf("init decaduino failed\n");
      exit(1);
  }

  wino.rgbDraw(128,128,0); // Yellow

  // Set RX buffer and enable RX
  decaduino.setRxBuffer(rxData, &rxLen);
  decaduino.plmeRxEnableRequest();
}

void loop()
{  
  // If a message has been received, print it and re-enable receiver
  if ( decaduino.rxFrameAvailable() ) {
    digitalWrite(13, HIGH);
    Serial.print("#"); Serial.print(++rxFrames); Serial.print(" ");
    Serial.print(rxLen);
    Serial.print("bytes received: |");
    for (int i=0; i<rxLen; i++) {
      Serial.print(rxData[i], HEX);
      Serial.print("|");
    }
    Serial.println();
    decaduino.plmeRxEnableRequest(); // Always renable RX after a frame reception
    digitalWrite(13, LOW);
  }
}
