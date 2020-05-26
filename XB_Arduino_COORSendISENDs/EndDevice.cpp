#include "EndDevice.h"
#include<Arduino.h>
EndDevice::EndDevice(){
    _id_num = 0;
    _address = "";
    _location= 0;
    _angle = 0 ;
    _strain= 0;
  }
EndDevice::EndDevice(int id_num,String address,int location,int angle,float strain){
  _id_num = id_num;
  _address = address;
  _location = location;
  _angle = angle;
  _strain = strain;
  };

String EndDevice::deviceInfo(){
   String _info = "id: " + String(_id_num) + 
                "\taddress: " + String(_address) +
                "\tlocation: " + String(_location) + 
                "\tangle: " + String(_angle) + 
                "\tstrain data: " + String(_strain) + "\n";
  return _info;
  };
