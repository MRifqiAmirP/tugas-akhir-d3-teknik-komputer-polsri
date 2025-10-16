#include <SPI.h>
#include <TFT_eSPI.h> // Pastikan di User_Setup.h sudah #define ILI9488_DRIVER
#include <Wire.h>

TFT_eSPI tft = TFT_eSPI();

// Untuk jam digital
unsigned long lastUpdate = 0;
int hours = 12;
int minutes = 0;
int seconds = 0;

// Untuk teks berjalan
String scrollText = "Selamat Datang di Project ESP32 dan TFT ILI9488 ";
int scrollX;

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320

void setup() {
  Serial.begin(9600);
  tft.init();
  tft.setRotation(3); // Landscape mode
  tft.fillScreen(TFT_BLACK);

  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  scrollX = SCREEN_WIDTH;
}

void loop() {
  unsigned long currentMillis = millis();

  // Update jam digital setiap 1000 ms
  if (currentMillis - lastUpdate >= 1000) {
    lastUpdate = currentMillis;
    updateClock();
  }

  // Animasi teks berjalan
  scrollTextUpdate();

  delay(20); // supaya animasinya lebih halus
}

void updateClock() {
  seconds++;
  if (seconds >= 60) {
    seconds = 0;
    minutes++;
    if (minutes >= 60) {
      minutes = 0;
      hours++;
      if (hours >= 24) {
        hours = 0;
      }
    }
  }

  // Gambar background kotak jam
  tft.fillRect(140, 50, 200, 60, TFT_BLACK);

  // Tampilkan jam
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  char timeStr[9];
  sprintf(timeStr, "%02d:%02d:%02d", hours, minutes, seconds);
  tft.drawString(timeStr, SCREEN_WIDTH/2, 80, 4); // Font 4 cukup besar
}

void scrollTextUpdate() {
  // Hapus teks lama
  tft.fillRect(0, SCREEN_HEIGHT - 40, SCREEN_WIDTH, 30, TFT_BLACK);

  tft.setTextDatum(TL_DATUM);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawString(scrollText, scrollX, SCREEN_HEIGHT - 35, 2); // Font 2 untuk teks

  scrollX -= 2; // Kecepatan scroll

  if (scrollX < -tft.textWidth(scrollText)) {
    scrollX = SCREEN_WIDTH;
  }
}
