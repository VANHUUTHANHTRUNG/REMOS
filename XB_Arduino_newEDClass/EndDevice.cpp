#include "EndDevice.h"
#include<Arduino.h>
EndDevice::EndDevice(){
    _id_num = 0;
    _address = "";
    _location= 0;
    _angle = 0 ;
    _ext_len = {};
  }
EndDevice::EndDevice(int id_num,uint32_t address,int location,int angle,vector<float> ext_len){
  _id_num = id_num;
  _address = address;
  _location = location;
  _angle = angle;
  _ext_len = ext_len;
  }

String EndDevice::device_info(){
   String _info = "id: " + String(_id_num) + 
                "\taddress: " + String(_address,HEX) +
                "\tlocation: " + String(_location) + 
                "\tangle: " + String(_angle);
  String ext_len_str = "\treported lengths:";
  for(int i = 0; i < _ext_len.size();i++){
    ext_len_str += " (" + String(i+1) + ") " + String(_ext_len[i]);
    }
  ext_len_str += "\n";
  _info += ext_len_str;
  return _info;
  }
void EndDevice::set_ext_len(vector<float> new_ext_len){
  _ext_len = new_ext_len;
  }