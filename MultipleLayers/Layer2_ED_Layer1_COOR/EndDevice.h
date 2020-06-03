#ifndef EndDevice_h
#define EndDevice_h
#include <StandardCplusplus.h>
#include<vector>
#include<Arduino.h>
using namespace std;
class EndDevice{
    public:
      EndDevice();
      EndDevice(String id,uint32_t address,int location,int angle,vector<uint16_t> ext_len);
      String _id;
      uint32_t _address;
      int _location;
      int _angle;
      void set_ext_len(vector<uint16_t> new_ext_len);
      int get_data_size();
      vector<uint16_t> _ext_len;
      String info(); // return all information of ED in string

  };
#endif // EndDevice_h
