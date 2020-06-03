// Free Serial port for a period of time to get data from xbee.( Arduino to Arduino)

#include <XBee.h>
XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
uint8_t command = 0;

unsigned long start_query_time;
unsigned long current_time;
int query_time = 10000;
uint8_t data[240];
Rx64Response rx64 = Rx64Response();
int count = 0;


void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  xbee.setSerial(Serial1);
}

void loop() {
  if(Serial.available() > 0){
    command = Serial.read();
    if(command != 10){
      if(command == 49){
      Serial.println("Start query data");
      start_query_time = millis();
      current_time = millis();
      while(current_time - start_query_time <= query_time){
          xbee.readPacket();
          if(xbee.getResponse().isAvailable()){
            Serial.println("Got something");
            if(xbee.getResponse().getApiId() == RX_64_RESPONSE){
              xbee.getResponse().getRx64Response(rx64);
              int dataLength = rx64.getDataLength();
              for(int i = 0; i < dataLength;i++){
                data[i] = rx64.getData(i);
                Serial.println(data[i]);
                }
              }
          }else if(xbee.getResponse().isError()){
              Serial.print("Error reading packet. Error code:");
              Serial.println(xbee.getResponse().getErrorCode());
              }
          
          current_time = millis();
        }
        Serial.println("End of data querying");
      }
    else{
      Serial.println(command);
      }
      }
    }
  }




















 
