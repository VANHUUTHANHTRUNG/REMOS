#ifndef Network_h
#define Network_h
#include <StandardCplusplus.h>
#include<vector>
#include "EndDevice.h"


using namespace std;
class Network{
    public:
    Network();
    Network(vector<EndDevice> deviceList);
    vector<EndDevice> _net;
    String info();
//    int get_size();
//    void update_data(const vector<uint16_t>& new_data);
    private:
    EndDevice* find_device(uint32_t address);
};






#endif
