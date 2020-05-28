#ifndef EndDevice_h
#define EndDevice_h
#include <StandardCplusplus.h>
#include<vector>
#include<Arduino.h>
using namespace std;
class EndDevice{
    public:
      EndDevice();
      EndDevice(int id_num,uint32_t address,int location,int angle,vector<float> ext_len);
      int _id_num;
      uint32_t _address;
      int _location;
      int _angle;
      void set_ext_len(vector<float> new_ext_len);
      vector<float> _ext_len;
      String device_info(); // return all information of ED in string
//      void update_data();
  };
#endif // EndDevice_h
