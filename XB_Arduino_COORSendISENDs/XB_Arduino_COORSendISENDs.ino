#include <StandardCplusplus.h>
#include<vector>
#include<string>
#include <iterator>
#include <algorithm>
#include "EndDevice.h"
#include "Data.h"
using namespace std;

#include <XBee.h>

typedef vector<EndDevice> Container; // User defined data base for network
typedef vector<Data> DataPack;

//----------------------------------------Methods for database--------------------
void printAll(const Container& database){
  vector<String> final_ED_list;
  for(auto& ed:database){
    final_ED_list.push_back(ed.deviceInfo());
    }
   for(auto& edinfor : final_ED_list){Serial.print(edinfor);}
  }

EndDevice* find_device(Container& database, String address){
  for(auto& ed : database){
    if(address == ed._address){return &ed;}
    }
   return nullptr;
  };

void update_data(Container& cur_database,const DataPack& pack){ // problem: does not change value of current network 
  for(auto& p: pack){
    EndDevice* existed_ED = find_device(cur_database, p._address);
    if(existed_ED != nullptr){
      existed_ED->_strain = p._data;
      }
    else Serial.println("Can not find corresponding addres");
    }
  }

Container check_data(const Container& cur_database){ // check if there is an ED with NAN strain value, return list of failed ED
  Container failed_ED = {};
  for(auto& ed : cur_database){
    if(isnan(ed._strain)){
      failed_ED.push_back(ed);
      }
    }
  for(auto& ed: failed_ED) {
    Serial.print("Failed ED: ");
    Serial.println(ed._id_num);
    }
  return failed_ED;
  }


Container init_network = {
  {16,"0x41512860",1,30,NAN},
  {17,"0x41512873",1,45,NAN},
  {19,"0x41512B36",1,60,NAN}
  };
XBee xbee = XBee();

Rx64IoSampleResponse ioSample = Rx64IoSampleResponse();

int incomingByte = 0;
unsigned long startMillis;
unsigned long currentMillis;
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); // Start Serial1, connected to Xbee
  xbee.setSerial(Serial1);
  
}

void loop() {
 //attempt to read a packet
 if(Serial.available() > 0){
  incomingByte = Serial.read();
  if(incomingByte == 49){
    Serial.println("Starit receiving data");
    receive_data(20000);
    Serial.println("Finished receiving data!");
    }
  }    
}

void receive_data(int waitingTime, Container& cur_database){
  startMillis = millis();
  currentMillis = millis();
  while(currentMillis - startMillis <= waitingTime){
      xbee.readPacket();
      
  if (xbee.getResponse().isAvailable()) {
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
    currentMillis = millis();
    }
  }
