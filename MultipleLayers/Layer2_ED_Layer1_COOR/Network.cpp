#include"Network.h"
#include <iterator>
#include <algorithm>
#include "EndDevice.h"
using namespace std;

Network::Network(){
    _net = {};
}

Network::Network(vector<EndDevice> deviceList){
//    for(int i = 0; i < deviceList.size();i++){
//        _net.push_back(deviceList[i]);
//    } 
    for(auto& d : deviceList){
       _net.push_back(d);
      }
    
}

String Network::info(){
    String info_str = "";
    for(const auto& n : _net){
        info_str += n.info();
        info_str += "\n";
    }
    return info_str;
}

int Network::get_size(){
  return(_net.size());
  }

EndDevice* Network::find_device(uint32_t address){
  for(auto& n : _net){
    if(address == n._address){return &n;}
    }
    return nullptr;
  }
  
void Network::update_data(uint32_t address, vector<uint16_t> new_data){
  EndDevice* existed_ED = find_device(address);
  if(existed_ED != nullptr){
    Serial.println("Found address of new data");
    existed_ED->_ext_len = new_data;
    }
  else{
    Serial.println("Can not find corresponding address");
    }
  }
  
int Network::get_payload_size(){
  return _net[0].get_data_size() * get_size();
  }

int Network::get_data_size(){
  return _net[0].get_data_size();
  }

void Network::construct_payload(uint8_t* payload){
  for(int i = 0;i<get_size();i++){
    for(int j = 0; j < get_data_size();j++){
      *(payload+ (i*get_data_size() + j)*2) = _net[i]._ext_len[j] >> 8 & 0xff;
      *(payload+ (i*get_data_size() + j)*2 + 1) = _net[i]._ext_len[j] & 0xff;
      }
    }
  return payload;
  }
