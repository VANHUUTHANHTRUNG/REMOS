// Layer 2 coordinator or MASTER Device, receives data from Layer 1 Coordinator
// Rx 
#include <XBee.h>


XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
// create reusable response objects for responses we expect to handle 
Rx64Response rx64 = Rx64Response();

uint8_t data[2] = {0,0};

void setup() {
  // start serial
  Serial.begin(9600);
  Serial1.begin(9600);
  xbee.setSerial(Serial1);
}

void loop() {
    
    xbee.readPacket();
    
    if (xbee.getResponse().isAvailable()) {
      // got something
      
      if ( xbee.getResponse().getApiId() == RX_64_RESPONSE) {
        // got a rx packet
          xbee.getResponse().getRx64Response(rx64);
          for(int i = 0;i < rx64.getDataLength();i++){
            data[i] = rx64.getData(i);
            }
          for(int i = 0;i < rx64.getDataLength();i++){
            Serial.println(data[i]);
            }
          

      } else {
        // not something we were expecting
        Serial.println("Something unexpected");
      }
    } else if (xbee.getResponse().isError()) {
      Serial.print("Error reading packet.  Error code: ");  
      Serial.println(xbee.getResponse().getErrorCode());
      // or flash error led
    } 
}
