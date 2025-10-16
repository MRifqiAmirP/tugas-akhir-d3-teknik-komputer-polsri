#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>

// Definisi 4 SoftwareSerial untuk masing-masing PZEM
SoftwareSerial ss1(3, 2);
SoftwareSerial ss2(5, 4);
SoftwareSerial ss3(8, 7);
SoftwareSerial ss4(10, 11);

// Buat 4 instance PZEM
PZEM004Tv30 pzem1(ss1);
PZEM004Tv30 pzem2(ss2);
PZEM004Tv30 pzem3(ss3);
PZEM004Tv30 pzem4(ss4);

void setup() {
  Serial.begin(9600);
  Serial.println("Mulai pembacaan dari 4 PZEM");
}

void loop() {
  Serial.println("=== PZEM 1 ===");
  bacaPZEM(pzem1, ss1);

  Serial.println("=== PZEM 2 ===");
  bacaPZEM(pzem2, ss2);

  Serial.println("=== PZEM 3 ===");
  bacaPZEM(pzem3, ss3);

  Serial.println("=== PZEM 4 ===");
  bacaPZEM(pzem4, ss4);

  Serial.println("==============\n");
  delay(500); // Jeda antar siklus
}

void bacaPZEM(PZEM004Tv30 &pzem, SoftwareSerial &ss) {
  ss.listen(); // Aktifkan port serial ini
  delay(100);  // Beri waktu switching

  float voltage = pzem.voltage();
  if (!isnan(voltage)) {
    Serial.print("Voltage: "); Serial.print(voltage); Serial.println(" V");
    Serial.print("Current: "); Serial.print(pzem.current()); Serial.println(" A");
    Serial.print("Power: "); Serial.print(pzem.power()); Serial.println(" W");
    Serial.print("Energy: "); Serial.print(pzem.energy()); Serial.println(" kWh");
    Serial.print("Frequency: "); Serial.print(pzem.frequency()); Serial.println(" Hz");
    Serial.print("Power Factor: "); Serial.println(pzem.pf());
  } else {
    Serial.println("Gagal membaca data. Cek koneksi.");
  }

  delay(100); // Delay antar pembacaan, bisa disesuaikan
}
