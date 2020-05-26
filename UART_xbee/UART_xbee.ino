void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Serial is ready");
}

int incomingByte = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
    incomingByte = Serial.read();

    Serial.print("I received: ");
    Serial.println(incomingByte,HEX);
    }
  delay(100);
}
