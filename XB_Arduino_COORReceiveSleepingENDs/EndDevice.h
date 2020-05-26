#ifndef EndDevice_h
#define EndDevice_h
#include<Arduino.h>
class EndDevice{
    public:
      EndDevice();
      EndDevice(int id_num,String address,int location,int angle,float strain);
      int _id_num;
      String _address;
      int _location;
      int _angle;
      float _strain;
      String deviceInfo(); // return all information of ED in string
  };
#endif // EndDevice_h
