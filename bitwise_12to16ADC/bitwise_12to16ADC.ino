//uint8_t payload[] = {0,0};

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
int arr[] = {1,3,5,7,9,11};
for(int i =0;i< 6;i++){  
  Serial.println(*(arr+i));
  }

*arr = update_arr(arr,6);

for(int i =0;i< 6;i++){
  Serial.println(*(arr+i));
  }
}

int* update_arr(int* payload,int payload_size){
  for(int i = 0;i < payload_size;i++){
    *(payload+i) = *(payload+i) + 2; 
    }
    return payload;
  }

void loop() {
}
