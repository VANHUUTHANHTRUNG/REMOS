#include "Data.h"
#include<Arduino.h>
#include <iterator>
#include <algorithm>
using namespace std;
Data::Data(){
  _address = 0x00;
  _data = {};
  }
  
Data::Data(uint32_t address, vector<int> data){
  _address = address;
  for(auto& d: data){
    _data.push_back(d);
    }
  }
