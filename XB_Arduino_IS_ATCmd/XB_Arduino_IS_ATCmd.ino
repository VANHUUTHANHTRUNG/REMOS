#include <XBee.h>


XBee xbee = XBee();

uint8_t incomingByte = 0;

uint8_t ISCmd[] = {'I','S'};

uint32_t addressList[] = { 0x41512740,
                           0x41512747};


// SH + SL of your remote radio
XBeeAddress64 remoteAddress = XBeeAddress64(0x0013a200, 0x41512740);
// Create a remote AT request with the IS command
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(remoteAddress, ISCmd);
  
// Create a Remote AT response object
RemoteAtCommandResponse remoteAtResponse = RemoteAtCommandResponse();

void setup() { 
  Serial.begin(9600);
  Serial1.begin(9600);
  xbee.begin(Serial1);
  delay(5000);
}

void loop() {
//  sendRemoteAtCommand();
//  remoteAtRequest.clearCommandValue();
//  for(int i = 0; i < 2;i++){
//    XBeeAddress64 remoteAddress = XBeeAddress64(0x0013a200, addressList[i]);
//    RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(remoteAddress, ISCmd);
//    sendRemoteAtCommand();
//    remoteAtRequest.clearCommandValue();
//    }
  
  // enter "1" to start force sampling data
  if(Serial.available() > 0){
    incomingByte = Serial.read();
    if(incomingByte != 10){
      if(incomingByte == 49){
        Serial.println("Query data:");
          for(int i = 0; i < 2;i++){
            XBeeAddress64 remoteAddress = XBeeAddress64(0x0013a200, addressList[i]);
            RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(remoteAddress, ISCmd);
            sendRemoteAtCommand();
            remoteAtRequest.clearCommandValue();
         }
        }
      }
    }
}

void sendRemoteAtCommand() {
  Serial.println("Sending command to the XBee");

  // send the command
  xbee.send(remoteAtRequest);

  // wait up to 5 seconds for the status response
  if (xbee.readPacket(5000)) {
    // got a response!

    // should be an AT command response
    if (xbee.getResponse().getApiId() == REMOTE_AT_COMMAND_RESPONSE) {
      xbee.getResponse().getRemoteAtCommandResponse(remoteAtResponse);

      if (remoteAtResponse.isOk()) {
        Serial.print("Command [");
        Serial.print(remoteAtResponse.getCommand()[0]);
        Serial.print(remoteAtResponse.getCommand()[1]);
        Serial.println("] was successful!");

        if (remoteAtResponse.getValueLength() > 0) {
          Serial.print("Command value length is ");
          Serial.println(remoteAtResponse.getValueLength(), DEC);

          Serial.print("Command value: ");
          
          for (int i = 0; i < remoteAtResponse.getValueLength(); i++) {
            Serial.print(remoteAtResponse.getValue()[i], HEX);
            Serial.print(" ");
          }

          Serial.println("");
        }
      } else {
        Serial.print("Command returned error code: ");
        Serial.println(remoteAtResponse.getStatus(), HEX);
      }
    } else {
      Serial.print("Expected Remote AT response but got ");
      Serial.print(xbee.getResponse().getApiId(), HEX);
    }    
  } else if (xbee.getResponse().isError()) {
    Serial.print("Error reading packet.  Error code: ");  
    Serial.println(xbee.getResponse().getErrorCode());;
  } else {
    Serial.print("No response from radio");  
  }
}
