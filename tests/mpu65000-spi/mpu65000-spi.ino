#include <SPI.h>

#define CS_PIN 10 // Broche NCS du module vers D10 Arduino

void setup() {
  Serial.begin(9600);
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH); // Désactive le capteur

  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.setDataMode(SPI_MODE0);

  delay(1000);
  Serial.println("Lecture WHO_AM_I du MPU6500 en SPI...");
  byte whoami = mpuReadRegister(0x75);
  Serial.print("WHO_AM_I = 0x");
  Serial.println(whoami, HEX);
}

void loop() {
  // Ajoute ici d'autres lectures si besoin
  delay(1000);
}

byte mpuReadRegister(byte reg) {
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(reg | 0x80); // Bit 7 à 1 pour lecture
  byte value = SPI.transfer(0x00);
  digitalWrite(CS_PIN, HIGH);
  return value;
}
