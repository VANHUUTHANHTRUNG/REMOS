#include <StandardCplusplus.h>
#include<vector>
#include<string>
#include <iterator>
#include <algorithm>
#include "EndDevice.h"
#include "Data.h"
using namespace std;

typedef vector<EndDevice> Container; // User defined data base for network
typedef vector<Data> DataPack;
Container init_network = {
  {16,"0x41512860",1,30,NAN},
  {17,"0x41512873",1,45,NAN},
  {19,"0x41512B36",1,60,NAN},
  {20,"0x41512620",2,30,NAN},
  {21,"0x41512921",2,45,NAN},
  {22,"0x41512422",2,60,NAN},
  {23,"0x41512723",3,30,NAN},
  {24,"0x41512324",3,45,NAN},
  {25,"0x41512425",3,60,NAN}
  };
  
DataPack simulatedData ={ // simulate data with shuffled order and 1 ED is out of service
  {"0x41512860",34.56},
  {"0x41512620",42.56},
  {"0x41512873",142.556},
  {"0x41512921",13.6},
  {"0x41512422",14.5},
  {"0x41512B36",3.56},
  {"0x41512425",55.84},
//  {23,"0x41512723",3,30,21.456},
  {"0x41512324",7.84},
  };

//------------------------------------------Help functions------------------------------------------


//----------------------------------------Methods for database--------------------
void printAll(const Container& database){
  vector<String> final_ED_list;
  for(auto& ed:database){
    final_ED_list.push_back(ed.deviceInfo());
    }
   for(auto& edinfor : final_ED_list){Serial.print(edinfor);}
  }

EndDevice* find_device(Container& database, String address){
  for(auto& ed : database){
    if(address == ed._address){return &ed;}
    }
   return nullptr;
  };

void update_data(Container& cur_database,const DataPack& pack){ // problem: does not change value of current network 
  for(auto& p: pack){
    EndDevice* existed_ED = find_device(cur_database, p._address);
    if(existed_ED != nullptr){
      existed_ED->_strain = p._data;
      }
    else Serial.println("Can not find corresponding addres");
    }
  }

Container check_data(const Container& cur_database){ // check if there is an ED with NAN strain value, return list of failed ED
  Container failed_ED = {};
  for(auto& ed : cur_database){
    if(isnan(ed._strain)){
      failed_ED.push_back(ed);
      }
    }
  for(auto& ed: failed_ED) {
    Serial.print("Failed ED: ");
    Serial.println(ed._id_num);
    }
  return failed_ED;
  }



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  Container cur_network = init_network; // current network need to be reset to init_network every time so program can detect if new data was received
  Serial.println("Initial network:");
  printAll(cur_network);
  update_data(cur_network,simulatedData);
  Container failed_ED = check_data(cur_network); // failed ED list mush be reinitialized again after used
  Serial.println("After data update:");
  printAll(cur_network);
  

  // Check if all EDs have reported data, notify the broken EDs 
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
