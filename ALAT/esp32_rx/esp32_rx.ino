void setup() {
  Serial.begin(115200);   // Serial Monitor
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
}

void loop() {
  if (Serial2.available() > 0) {
    String receivedData = Serial2.readStringUntil('\n');
    receivedData.trim();
    
    if (receivedData.length() > 0) {
      Serial.print("Received from Serial2: ");
      Serial.println(receivedData);
    }
  }
}