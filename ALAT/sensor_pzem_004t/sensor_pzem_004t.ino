#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>
// #define RXD2 16 
// #define TXD2 17
// #define RXD2 25
// #define TXD2 26
#define RXD1 19
#define TXD1 18
#define RXD2 2
#define TXD2 15
#define SOFT_RX3 21
#define SOFT_TX3 22
#define SOFT_RX4 4
#define SOFT_TX4 5

SoftwareSerial ss3(SOFT_RX3, SOFT_TX3);
SoftwareSerial ss4(SOFT_RX4, SOFT_RX4);

PZEM004Tv30 pzem1(Serial1, RXD1, TXD1);
PZEM004Tv30 pzem2(Serial3, RXD2, TXD2);
PZEM004Tv30 pzem3(ss3);
PZEM004Tv30 pzem4(ss4);

float v1, i1, pf1, f1, p1, e1;
float v2, i2, pf2, f2, p2, e2;
float v3, i3, pf3, f3, p3, e3;
float v4, i4, pf4, f4, p4, e4;

void setup() {
  Serial.begin(115200);

  Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1);
  Serial3.begin(9600, SERIAL_8N1, RXD2, TXD2);
  ss3.begin(9600);
  ss4.begin(9600);
}

void loop() {
  baca_pzem1();
  Serial.println("=== Sensor 1 ===");
  tampilkanData(v1, i1, pf1, p1, e1, f1);

  baca_pzem2();
  Serial.println("=== Sensor 2 ===");
  tampilkanData(v2, i2, pf2, p2, e2, f2);

  baca_pzem3();
  Serial.println("=== Sensor 3 ===");
  tampilkanData(v3, i3, pf3, p3, e3, f3);
  
  baca_pzem4();
  Serial.println("=== Sensor 4 ===");
  tampilkanData(v4, i4, pf4, p4, e4, f4);

  Serial.println();
  delay(2000);
}

void baca_pzem1() {
  v1 = pzem1.voltage();
  i1 = pzem1.current();
  pf1 = pzem1.pf();
  f1 = pzem1.frequency();
  p1 = pzem1.power();
  e1 = pzem1.energy();
}

void baca_pzem2() {
  v2 = pzem2.voltage();
  i2 = pzem2.current();
  pf2 = pzem2.pf();
  f2 = pzem2.frequency();
  p2 = pzem2.power();
  e2 = pzem2.energy();
}

void baca_pzem3() {
  v3 = pzem3.voltage();
  i3 = pzem3.current();
  pf3 = pzem3.pf();
  f3 = pzem3.frequency();
  p3 = pzem3.power();
  e3 = pzem3.energy();
}

void baca_pzem4() {
  v4 = pzem4.voltage();
  i4 = pzem4.current();
  pf4 = pzem4.pf();
  f4 = pzem4.frequency();
  p4 = pzem4.power();
  e4 = pzem4.energy();
}

void tampilkanData(float v, float i, float pf, float p, float e, float f) {
  Serial.print("Volt: "); Serial.print(v, 2); Serial.print(" V, ");
  Serial.print("Curr: "); Serial.print(i, 3); Serial.print(" A, ");
  Serial.print("PF: "); Serial.print(pf); Serial.print(", ");
  Serial.print("Power: "); Serial.print(p); Serial.print(" W, ");
  Serial.print("Energy: "); Serial.print(e, 3); Serial.print(" kWh, ");
  Serial.print("Freq: "); Serial.print(f, 1); Serial.println(" Hz");
}