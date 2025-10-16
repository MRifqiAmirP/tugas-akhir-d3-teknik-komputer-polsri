#include <ArduinoJson.h>

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  
  Serial.println("ESP32 Ready - Waiting for JSON data...");
}

void loop() {
  if (Serial2.available() > 0) {
    String jsonString = Serial2.readStringUntil('\n');
    jsonString.trim();
    
    Serial.println("Received JSON:");
    Serial.println(jsonString);

    // Parse JSON
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, jsonString);
    
    if (error) {
      Serial.print("JSON parsing failed: ");
      Serial.println(error.c_str());
      return;
    }
    
    // Ekstrak data dari JSON
    const char* device = doc["device"];
    const char* sensor = doc["sensor"];
    float temperature = doc["temperature"];
    float humidity = doc["humidity"];
    bool status = doc["status"];
    int id = doc["id"];
    
    // Tampilkan data yang di-parse
    Serial.println("\nParsed Data:");
    Serial.print("Device: "); Serial.println(device);
    Serial.print("Sensor: "); Serial.println(sensor);
    Serial.print("Temperature: "); Serial.println(temperature);
    Serial.print("Humidity: "); Serial.println(humidity);
    Serial.print("Status: "); Serial.println(status ? "ON" : "OFF");
    Serial.print("ID: "); Serial.println(id);
  }
  
  delay(10);
}