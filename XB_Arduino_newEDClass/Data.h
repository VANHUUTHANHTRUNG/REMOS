#ifndef Data_h
#define Data_h
#include<Arduino.h>
#include <StandardCplusplus.h>
#include<vector>

using namespace std;
class Data{
  public:
    Data();
    Data(uint32_t address, vector<float> data);
    uint32_t _address;
    vector<float> _data;
  };

#endif // Data_h
