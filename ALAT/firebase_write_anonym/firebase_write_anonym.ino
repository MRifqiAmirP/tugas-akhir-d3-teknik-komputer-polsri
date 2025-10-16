/*
project by makerindo
minggu 7 sepetember 2021
menulis data integer dan float di firebase
*/

#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "TECNO POVA 5"
#define WIFI_PASSWORD "12345678"

// #define API_KEY "AIzaSyA04jMqZXF7wNEWXhrz1m8Zqx3KRlfyVQQ"
// #define DATABASE_URL "https://test-c64fa-default-rtdb.asia-southeast1.firebasedatabase.app" 

#define API_KEY "AIzaSyDxQ3_vF8Ubt6UpEYvFBN4xG5wnokIlTGU"
#define DATABASE_URL "https://monitoring-listrik-c5958-default-rtdb.asia-southeast1.firebasedatabase.app" 

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

void setup(){
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;

  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop(){
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.setInt(&fbdo, "data/id", count)){
      // Serial.println("PASSED");
      // Serial.println("PATH: " + fbdo.dataPath());
      // Serial.println("TYPE: " + fbdo.dataType());
      Serial.print("Berhasil mengirim id ke Firebase: "); Serial.println(count);
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    count++;
    
    if (Firebase.RTDB.setFloat(&fbdo, "data/temperatur", 0.01 + random(0,100))){
      // Serial.println("PASSED");
      // Serial.println("PATH: " + fbdo.dataPath());
      // Serial.println("TYPE: " + fbdo.dataType());
      Serial.println("Berhasil mengirim tempertaur ke Firebase");
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
}
