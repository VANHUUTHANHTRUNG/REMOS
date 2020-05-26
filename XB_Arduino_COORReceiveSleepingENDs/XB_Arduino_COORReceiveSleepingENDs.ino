#include <XBee.h>

XBee xbee = XBee();

Rx64IoSampleResponse ioSample = Rx64IoSampleResponse();

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); // Start Serial1, connected to Xbee
  xbee.setSerial(Serial1);
  
}

void loop() {
 //attempt to read a packet    
  xbee.readPacket();

  if (xbee.getResponse().isAvailable()) {
    // got something

    if (xbee.getResponse().getApiId() == RX_64_IO_RESPONSE) {
      xbee.getResponse().getRx64IoSampleResponse(ioSample);

      Serial.print("Received I/O Sample from: ");
      Serial.println(ioSample.getRemoteAddress64().getLsb(), HEX);  

      Serial.print("Sample size is ");
      Serial.println(ioSample.getSampleSize(), DEC);

      if (ioSample.containsAnalog()) {
        Serial.println("Sample contains analog data");
      }

      if (ioSample.containsDigital()) {
        Serial.println("Sample contains digtal data");
      }
      
      for (int k = 0; k < ioSample.getSampleSize(); k++) {
        Serial.print("Sample "); 
        Serial.print(k + 1, DEC);   
        Serial.println(":");    
        
        for (int i = 0; i <= 5; i++) {
          if (ioSample.isAnalogEnabled(i)) {
            Serial.print("Analog (AI");
            Serial.print(i);
            Serial.print(") is ");
            Serial.println(ioSample.getAnalog(i, k));  
          }
        }
        
        for (int i = 0; i <= 8; i++) {
           if (ioSample.isDigitalEnabled(i)) {
            Serial.print("Digtal (DI");
            Serial.print(i, DEC);
            Serial.print(") is ");
            Serial.println(ioSample.isDigitalOn(i, k));
          }
        }
      }
    } 
    else {
      Serial.print("Expected I/O Sample, but got ");
      Serial.print(xbee.getResponse().getApiId(), HEX);
    }    
  } 
  else if (xbee.getResponse().isError()) {
    Serial.print("Error reading packet.  Error code: ");  
    Serial.println(xbee.getResponse().getErrorCode());
  }
}
