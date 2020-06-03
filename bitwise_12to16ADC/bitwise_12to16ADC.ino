//uint8_t payload[] = {0,0};

uint8_t payload[6];
uint16_t init_payload[] = {0x3ff,0x3fe,0x3f0};

void setup() {
Serial.begin(9600);  
int data = 4090;
//Serial.println(data);
//payload[0] = data >> 8 & 0xff;
//payload[1] = data & 0xff;
//Serial.println(payload[0],HEX);
//Serial.println(payload[1],HEX);
//uint32_t address = 0x41512B36;
//
//Serial.println(address,HEX);
//Serial.println(address >> 16, HEX);

//int arr[] = {1,3,5,7,9,11};
//for(int i =0;i< 6;i++){  
//  Serial.println(*(arr+i));
//  }
//
//*arr = update_arr(arr,6);
//
//for(int i =0;i< 6;i++){
//  Serial.println(*(arr+i));
//  }
//}
//
//int* update_arr(int* payload,int payload_size){
//  for(int i = 0;i < payload_size;i++){
//    *(payload+i) = *(payload+i) + 2; 
//    }
//    return payload;

for(int i = 0; i < 3;i++){
  Serial.println(init_payload[i],HEX);
  }
change_arr(payload,init_payload,3);
for(int i = 0;i < 6;i++){
  Serial.println(payload[i],HEX);
  }
  }

void loop() {
}

void change_arr(uint8_t* payload,const uint16_t* init_payload, int payload_size){
  for(int i = 0; i < payload_size;i++){
    *(payload + i*2 ) = *init_payload >> 8 & 0xff;
    *(payload+ i*2+ 1) = *init_payload & 0xff;
    }
  }
