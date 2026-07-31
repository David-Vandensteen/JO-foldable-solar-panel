# Câblage MPU6500 avec Arduino Uno

| MPU6500 | Arduino Uno |
|---------|-------------|
| VCC     | 5V          |
| GND     | GND         |
| SCL     | A5          |
| SDA     | A4          |
| INT     | A1 (optionnel) |

- La broche INT n'est pas nécessaire pour un test simple de lecture des données.
- Utilisez la bibliothèque "Adafruit_MPU6050" pour la compatibilité I2C.

## Prérequis
- Installer la bibliothèque "Adafruit_MPU6050" (Adafruit) via le gestionnaire de bibliothèques Arduino.
- Pour un test simple, la bibliothèque Adafruit_MPU6050 fonctionne avec le MPU6500 pour lire accéléromètre et gyroscope.
- Pour des fonctions avancées du MPU6500, utiliser une bibliothèque dédiée ou Wire.h.

## Exemple de branchement

```
MPU6500    Arduino Uno
----------------------
VCC     -> 5V
GND     -> GND
SCL     -> A5
SDA     -> A4
INT     -> A1 (optionnel)
```

## Remarques
- Le code de test lit les valeurs via I2C sans utiliser l'interruption.
- Connectez INT à A1 uniquement si vous souhaitez gérer les interruptions dans votre code.
