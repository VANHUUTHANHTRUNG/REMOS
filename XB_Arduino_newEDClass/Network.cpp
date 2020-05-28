#include"Network.h"
#include <iterator>
#include <algorithm>
#include "EndDevice.h"
using namespace std;

Network::Network(){
    _net = {};
}

Network::Network(vector<EndDevice> deviceList){
    for(int i = 0; i < deviceList.size();i++){
        _net.push_back(deviceList[i]);
    }
    
}

String Network::info(){
    String info_str = "";
    for(const auto& n : _net){
        info_str += n.device_info();
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

//void update_data(const vector<float> new_data){
//  for(const auto& n : new_data){
//    EndDevice* existed_ED = find_device();
//    if(existed_ED != nullptr){
//      n->_ext_len = n._data;
//      }
//    else{
//      else Serial.println("Can not find corresponding addres");
//      }
//    }
//  }
