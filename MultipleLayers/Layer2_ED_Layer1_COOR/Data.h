#ifndef Data_h
#define Data_h
#include<Arduino.h>
#include <StandardCplusplus.h>
#include<vector>

using namespace std;
class Data{
  public:
    Data();
    Data(uint32_t address, vector<uint16_t> data);
    uint32_t _address;
    vector<int> _data;
  };

#endif // Data_h
