uint8_t payload[] = {0,0};

void setup() {
Serial.begin(9600);  
int data = NAN;
Serial.println(data);
payload[0] = data >> 8 & 0xff;
payload[1] = data & 0xff;
Serial.println(payload[0],HEX);
Serial.println(payload[1],HEX);
uint32_t address = 0x41512B36;

Serial.println(address,HEX);
Serial.println(address >> 16, HEX);
}

void loop() {
}
