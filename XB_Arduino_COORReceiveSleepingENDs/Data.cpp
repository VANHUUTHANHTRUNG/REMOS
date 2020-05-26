#include "Data.h"
#include<Arduino.h>
Data::Data(){
  _address = "";
  _data = NAN;
  }
  
Data::Data(String address, float data){
  _address = address;
  _data = data;
  }
