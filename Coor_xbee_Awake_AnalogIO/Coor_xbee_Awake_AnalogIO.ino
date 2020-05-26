c/**
 * Copyright (c) 2009 Andrew Rapp. All rights reserved.
 *
 * This file is part of XBee-Arduino.
 *
 * XBee-Arduino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XBee-Arduino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XBee-Arduino.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <XBee.h>

/*
This example is for Series 1 XBee (802.15.4)
Receives either a RX16 or RX64 packet and sets a PWM value based on packet data.
Error led is flashed if an unexpected packet is received
*/

XBee xbee = XBee();
Rx16IoSampleResponse ioSample = Rx16IoSampleResponse();

// create reusable response objects for responses we expect to handle 


int statusLed = 11;
int errorLed = 12;
int dataLed = 10;

uint8_t option = 0;
uint8_t data = 0;

void flashLed(int pin, int times, int wait) {
    
    for (int i = 0; i < times; i++) {
      digitalWrite(pin, HIGH);
      delay(wait);
      digitalWrite(pin, LOW);
      
      if (i + 1 < times) {
        delay(wait);
      }
    }
}

void setup() {
  pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  pinMode(dataLed,  OUTPUT);
  
  // start serial
  Serial.begin(9600);
  xbee.setSerial(Serial);
  
  flashLed(statusLed, 3, 50);
}

// continuously reads packets, looking for RX16 or RX64
void loop() {
    
    xbee.readPacket();
    
    if (xbee.getResponse().isAvailable()) {
      // got something
      
      if (xbee.getResponse().getApiId() == RX_16_IO_RESPONSE ) {
        // got a rx packet
        xbee.getResponse().getRx16IoSampleResponse(ioSample);
        
        Serial.print("Received I/O Sample from: ");
        Serial.println(ioSample.getRemoteAddress16(), HEX);

        for (int k = 0; k < ioSample.getSampleSize(); k++) {
          Serial.print("Sample "); 
          Serial.print(k + 1, DEC);   
          Serial.println(":");    
        
        for (int i = 0; i <= 5; i++) {
          if (ioSample.isAnalogEnabled(i)) {
            Serial.print("Analog (AI");
            Serial.print(i, DEC);
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







        // set dataLed PWM to value of the first byte in the data
        analogWrite(dataLed, data);
      } else {
        // not something we were expecting
        flashLed(errorLed, 3, 50);
        Serial.print("Error reading packet.  Error code: ");  
        Serial.println(xbee.getResponse().getErrorCode());    
      }
    } else if (xbee.getResponse().isError()) {
//      Serial.print("Error reading packet.  Error code: ");  
//      Serial.println(xbee.getResponse().getErrorCode());
      // or flash error led
    } 
}
