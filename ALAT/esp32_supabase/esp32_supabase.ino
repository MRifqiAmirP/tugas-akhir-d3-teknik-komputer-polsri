#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "TECNO POVA 5";
const char* password = "12345678";
const char* supabaseUrl = "https://ywgvilqklobqfsyldcpo.supabase.co/rest/v1/log_sensor";
const char* supabaseKey = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Inl3Z3ZpbHFrbG9icWZzeWxkY3BvIiwicm9sZSI6ImFub24iLCJpYXQiOjE3NDYwNjYyNjUsImV4cCI6MjA2MTY0MjI2NX0.kmVl0XGkZc5Hkx14s7KIz5E4MY0vAP-zEIvV4bqg0i4";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  postDataToSupabase(4);
}

void loop() {}

void postDataToSupabase(int nama_sensor) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(supabaseUrl);
    
    http.addHeader("apikey", supabaseKey);
    http.addHeader("Authorization", "Bearer " + String(supabaseKey));
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Prefer", "return=minimal");

    StaticJsonDocument<200> doc;
    doc["sensor_id"] = nama_sensor;
    
    String requestBody;
    serializeJson(doc, requestBody);

    int httpCode = http.POST(requestBody);

    if (httpCode == HTTP_CODE_CREATED) {
      Serial.println("Data berhasil dikirim ke Supabase!");
    } else {
      Serial.printf("Error: %s\n", http.errorToString(httpCode).c_str());
      Serial.println("Response: " + http.getString());
    }

    http.end();
  } else {
    Serial.println("WiFi tidak terhubung!");
  }
}