#include "EndDevice.h"
#include "Network.h"
#include "Data.h"

vector<uint16_t> len_0 = {0x00, 0x00, 0x00, 0x00 , 0x00, 0x00};
vector<uint16_t> len = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06}; // synthetic data for extensometer lengths 

//EndDevice ED1 = EndDevice("16",0x41512860,1,30,len_0);
//EndDevice ED2 = EndDevice("17",0x41512873,1,45,len);
//EndDevice ED3 = EndDevice("19",0x41512B36,1,60,len);
//vector<EndDevice> deviceList = {ED1, ED2, ED3}; 
vector<EndDevice> init_list = {
  {"16",0x41512860,1,30,len_0},
  {"17",0x41512873,1,45,len_0},
  {"19",0x41512B36,1,60,len_0}
  };

vector<Data> simulatedData ={ // simulate data with shuffled order and 1 ED is out of service
  {0x41512860,len},
  {0x41512620,len},   
  {0x41512873,len}
};

//Network network = Network(deviceList);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  Serial.println(network.get_size());
//  Serial.println(network.info());
  for(const auto& s : simulatedData){
    Serial.println(s._address);
    for(auto& d : s._data){Serial.println(d);}
    }
    uint16_t* arr[6] = len_0.data();
}

void loop() {
  // put your main code here, to run repeatedly:
}
