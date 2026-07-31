
#include <Wire.h>

void setup() {
  #include <Wire.h>
  #include "ICM_20948.h"
  #include <ICM_20948.h>

  ICM_20948_I2C myICM;

  Serial.begin(115200);
  while (!Serial);
  Serial.println("ICM-20948 Example");

  Wire.begin();
  myICM.begin(Wire, 0x69); // 0x69 = AD0 high, 0x68 = AD0 low
    bool ad0 = true; // true pour 0x69, false pour 0x68
    myICM.begin(Wire, ad0);
  if (myICM.status != ICM_20948_Stat_Ok) {
    Serial.print("IMU non détecté. Code erreur: ");
    Serial.println(myICM.status);
    while (1);
  }
  Serial.println("IMU détecté !");
}

void loop() {
  if (myICM.dataReady()) {
    myICM.getAGMT(); // Accel, Gyro, Mag, Temp
    Serial.print("Acc X: "); Serial.print(myICM.accX());
    Serial.print("\tAcc Y: "); Serial.print(myICM.accY());
    Serial.print("\tAcc Z: "); Serial.print(myICM.accZ());
    Serial.print("\tGyro X: "); Serial.print(myICM.gyrX());
    Serial.print("\tGyro Y: "); Serial.print(myICM.gyrY());
    Serial.print("\tGyro Z: "); Serial.print(myICM.gyrZ());
    Serial.print("\tTemp: "); Serial.println(myICM.temp());
  }
  delay(100);
}
