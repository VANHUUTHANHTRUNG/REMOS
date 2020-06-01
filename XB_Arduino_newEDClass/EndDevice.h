#ifndef EndDevice_h
#define EndDevice_h
#include <StandardCplusplus.h>
#include<vector>
#include<Arduino.h>
using namespace std;
class EndDevice{
    public:
      EndDevice();
      EndDevice(String id,uint32_t address,int location,int angle,vector<int> ext_len);
      String _id;
      uint32_t _address;
      int _location;
      int _angle;
      void set_ext_len(vector<int> new_ext_len);
      vector<int> _ext_len;
      String info(); // return all information of ED in string
//      void update_data();
  };
#endif // EndDevice_h
