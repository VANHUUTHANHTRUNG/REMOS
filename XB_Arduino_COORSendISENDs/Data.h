#ifndef Data_h
#define Data_h
#include<Arduino.h>
class Data{
  public:
    Data();
    Data(String address, float data);
    String _address;
    float _data;
  };

#endif // Data_h