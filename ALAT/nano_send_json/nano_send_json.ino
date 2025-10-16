#include <ArduinoJson.h>

void setup() {
  Serial.begin(115200);
  while (!Serial);
}

void loop() {
  // Buat objek JSON
  StaticJsonDocument<200> doc;
  
  // Isi data ke JSON
  doc["device"] = "Arduino Nano";
  doc["sensor"] = "DHT22";
  doc["temperature"] = 25.3;
  doc["humidity"] = 65.2;
  doc["status"] = true;
  doc["id"] = 1;

  // Serialize JSON ke string
  String output;
  serializeJson(doc, output);

  // Kirim JSON ke ESP32
  Serial.println(output); // Gunakan println untuk menambahkan newline

  // Cek jika ada data dari ESP32
  if (Serial.available() > 0) {
    String response = Serial.readStringUntil('\n');
    Serial.print("Response from ESP32: ");
    Serial.println(response);
  }

  delay(2000); // Kirim data setiap 2 detik
}