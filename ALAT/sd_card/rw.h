#include <ArduinoJson.h>

void writeConfig() {
  StaticJsonDocument<256> doc;
  doc["pzem1"] = 0;
  doc["pzem2"] = 0;
  doc["pzem3"] = 0;
  doc["pzem4"] = 0;

  File file = SD.open("/config/config.json", FILE_WRITE);
  if (!file) {
    Serial.println("Gagal membuka file untuk menulis");
    return;
  }

  if (serializeJson(doc, file)) {
    Serial.println("Konfigurasi disimpan.");
  } else {
    Serial.println("Gagal menyimpan konfigurasi.");
  }

  file.close();
}

void writeLogSensor() {
  StaticJsonDocument<256> doc;
  doc["kwh1"] = 0.561531;
  doc["kwh2"] = 0;
  doc["kwh3"] = 0;
  doc["kwh4"] = 0.586332;

  // File file = SD.open("/database/kwh_harian.json", FILE_WRITE);
  File file = SD.open("/database/kwh_harian_bulanan.json", FILE_WRITE);

  if (!file) {
    Serial.println("Gagal membuka file untuk menulis");
    return;
  }

  if (serializeJson(doc, file)) {
    Serial.println("Konfigurasi disimpan.");
  } else {
    Serial.println("Gagal menyimpan konfigurasi.");
  }

  file.close();
}

void readConfig() {
  File file = SD.open("/config/config.json");
  if (!file) {
    Serial.println("Gagal membuka file untuk membaca");
    return;
  }

  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, file);
  if (error) {
    Serial.print("Gagal parse JSON: ");
    Serial.println(error.c_str());
    return;
  }

  int ssid = doc["pzem1"];
  int password = doc["pzem2"];
  int deviceName = doc["pzem3"];
  int interval = doc["pzem4"];

  Serial.println("== Konfigurasi ==");
  Serial.println(ssid);
  Serial.println(password);
  Serial.println(deviceName);
  Serial.println(interval);

  file.close();
}