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
    int get_size(); // get number of ED in network
    int get_data_size(); // get number of extensometer lengths per ED
    int get_payload_size(); // get total length of payload array
    void update_data(uint32_t address, vector<uint16_t> new_data);
    void construct_payload(uint16_t* payload);
    private:
    EndDevice* find_device(uint32_t address);
};






#endif
