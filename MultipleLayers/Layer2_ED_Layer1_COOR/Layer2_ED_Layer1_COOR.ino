// Used for range test in tunnel, receive data from sleeping device when wake up
#include <XBee.h>
#include "EndDevice.h"
#include "Network.h"
#include "Data.h"

vector<uint16_t> len_0 = {0x00, 0x00, 0x00, 0x00 , 0x00, 0x00};
vector<EndDevice> init_list = {
  {"10",0x41512747,0,30,len_0},
  {"16",0x41512860,1,30,len_0},
  {"17",0x41512873,1,45,len_0},
  {"18",0x41512B36,1,60,len_0}
  };
Network network = Network(init_list);
//---------------------------------------------------------Xbee variables ------------------------------------------------------------
XBee xbee_L1 = XBee();
XBee xbee_L2 = XBee();
Rx64IoSampleResponse ioSample = Rx64IoSampleResponse();

XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x41512745);
TxStatusResponse txStatus = TxStatusResponse();
//------------------------------------------------------------Variables----------------------------------------------------------------
int io_receiving_time = 15000; // Time reserved for receiving analog IO from Xbee
int tx_sending_time = 5000;    // Time reserved for receiving response after sending Tx packet
int command = 0;
//----------------------------------------------------------- Functions----------------------------------------------------------------
void receive_io(int io_receiving_time); // Start reading packets from sleeping devices
//void send_payload(int tx_sending_time);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); // Start Serial1, connected to Xbee
  Serial2.begin(9600);
  xbee_L1.setSerial(Serial1); // Serial1 used for Layer 1(sensor ED)
  xbee_L2.setSerial(Serial2); // Serial2 used for Layer 2(network)
}

void loop() {
  if(Serial.available() > 0){
    command = Serial.read();
    if(command != 10){
      switch(command){
        case 114: // press "r" button and send
          Serial.println("Receive data command");
          receive_io(io_receiving_time);
        break;
        case 112: // press "p" button and send
          Serial.println("Print network command");
          Serial.println(network.info());
        break;
        case 99: // press "c" button and construct
          Serial.println("Construct payload array to send");
          uint16_t payload[network.get_payload_size()];
          network.construct_payload(payload);
          for(int i = 0;i< network.get_payload_size();i++){
            Serial.println(payload[i]);
          }
          
          break;
        default:
        Serial.println("Unknown command");
        break;
        }
      }
    }
}

void receive_io(int io_receiving_time){
  Serial.println("In 15s, Serial port will read data from awaken devices");
  int start_time = millis();
  int cur_time = millis();
  while(cur_time - start_time < io_receiving_time){
     //attempt to read a packet    
  xbee_L1.readPacket();

  if (xbee_L1.getResponse().isAvailable()) {
    // got something

    if (xbee_L1.getResponse().getApiId() == RX_64_IO_RESPONSE) {
      xbee_L1.getResponse().getRx64IoSampleResponse(ioSample);
      uint32_t temp_address = ioSample.getRemoteAddress64().getLsb();
      vector<uint16_t> temp_data;
      Serial.print("Received I/O Sample from: ");
      Serial.println(temp_address, HEX);     
      for (int k = 0; k < ioSample.getSampleSize(); k++) {
        for (int i = 0; i <= 5; i++) {
          if (ioSample.isAnalogEnabled(i)) {
            Serial.print("Analog (AI");
            Serial.print(i);
            Serial.print(") is ");
            Serial.println(ioSample.getAnalog(i, k));
            temp_data.push_back(ioSample.getAnalog(i, k));
          }
        }
      }
      network.update_data(temp_address, temp_data);
    } 
    else {
      Serial.print("Expected I/O Sample, but got ");
      Serial.print(xbee_L1.getResponse().getApiId(), HEX);
    }    
  } 
  else if (xbee_L1.getResponse().isError()) {
    Serial.print("Error reading packet.  Error code: ");  
    Serial.println(xbee_L1.getResponse().getErrorCode());
  }
    cur_time = millis();
    }
    Serial.println("Finished reading data");
  }

//void send_payload(int tx_sending_time){
//  Serial.println("Send payload in tx-packet, during 5s wait for tx status response");
//  uint16_t payload[network.get_payload_size()];
//  network.construct_payload(payload);
//  
//  }






















  
