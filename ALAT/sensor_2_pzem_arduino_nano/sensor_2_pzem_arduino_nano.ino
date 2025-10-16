#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>

// Definisi pin RX dan TX untuk masing-masing PZEM
SoftwareSerial ss1(2, 3); // RX, TX untuk PZEM 1
SoftwareSerial ss2(4, 5); // RX, TX untuk PZEM 2

PZEM004Tv30 pzem1(ss1); // Instance PZEM pertama
PZEM004Tv30 pzem2(ss2); // Instance PZEM kedua

void setup() {
  Serial.begin(9600);
  Serial.println("Mulai pembacaan dari dua PZEM");
}

void loop() {
  Serial.println("=== PZEM 1 ===");
  bacaPZEM(pzem1, ss1);

  delay(100);

  Serial.println("=== PZEM 2 ===");
  bacaPZEM(pzem2, ss2);

  Serial.println("==============\n");
  delay(1000);
}

void bacaPZEM(PZEM004Tv30 &pzem, SoftwareSerial &ss) {
  ss.listen(); // Aktifkan SoftwareSerial ini
  delay(100);  // Tunggu stabil

  float voltage = pzem.voltage();
  if (!isnan(voltage)) {
    Serial.print("Voltage: "); Serial.print(voltage); Serial.println(" V");
    Serial.print("Current: "); Serial.print(pzem.current()); Serial.println(" A");
    Serial.print("Power: "); Serial.print(pzem.power()); Serial.println(" W");
    Serial.print("Energy: "); Serial.print(pzem.energy()); Serial.println(" kWh");
    Serial.print("Frequency: "); Serial.print(pzem.frequency()); Serial.println(" Hz");
    Serial.print("Power Factor: "); Serial.println(pzem.pf());
  } else {
    Serial.println("Gagal membaca data. Cek koneksi PZEM.");
  }
}
