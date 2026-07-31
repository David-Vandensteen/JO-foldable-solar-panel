# Câblage SPI pour MPU6500 avec Arduino Uno/Nano

| MPU6500 | Arduino | Fonction |
|---------|---------|----------|
| VCC     | 3.3V    | Alimentation (préféré en SPI) |
| GND     | GND     | Masse |
| NCS     | D10     | Chip Select (CS) |
| SCL     | D13     | SCK (horloge SPI) |
| SDA     | D11     | MOSI (données vers MPU) |
| SDO     | D12     | MISO (données vers Arduino) |
| FSYNC   | -       | Laisser non connecté |

**Instructions :**
- Relier NCS à D10 (ou une autre broche numérique, à adapter dans le code).
- Relier SCL/SCK à D13, SDA/MOSI à D11, SDO/MISO à D12.
- VCC à 3.3V (certains modules acceptent 5V, mais 3.3V recommandé en SPI).
- GND à GND.
- FSYNC reste non connecté.
- NCS doit être à GND au démarrage pour activer le mode SPI.

**Remarque :**
- Utilise le code fourni dans mpu65000-spi.ino pour tester la communication SPI (lecture du registre WHO_AM_I).
- La réponse attendue pour WHO_AM_I est 0x70 (pour MPU6500).
