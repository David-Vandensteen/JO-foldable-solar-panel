# JO-sun-tracker

## Matériel pour deux groupes de panneaux solaire
- 1 carte ESP32
- 1 shield screw bornier pour ESP32
- 2 modules L298N (peut piloter 2 moteurs 12v par module)
- 4 modules LDR LM393 (photocellule) (prévoir l'étanchéité)
- 1 anémomètre (ref ?)
- 6 boutons poussoir (NO)
- 1 écran OLED
- 2 accéléromètre avec gyroscope MPU-6500
- 4 vérins 650mm 12v
- 3 LED verte
- 3 resistances

## Programme
Le code source est en cours de développement ici :

[Voir le code source principal](src/driver/driver.ino)

## Prérequis logiciels

- **Arduino IDE**
  [Télécharger l’Arduino IDE](https://www.arduino.cc/en/software)

- **Bibliothèques à installer via le Library Manager de l’IDE Arduino** :
  - **ArduinoLog** (Thijs Elenbaas)  
    (Outils → Gérer les bibliothèques… → Rechercher « ArduinoLog » → Installer)
  - **dv_led_blink** (David Vandensteen)  
    (Outils → Gérer les bibliothèques… → Rechercher « dv_led_blink » → Installer)
  - **dv_every_interval** (David Vandensteen)  
    (Outils → Gérer les bibliothèques… → Rechercher « dv_every_interval » → Installer)
  - **dv_average_accumulator8** (David Vandensteen)  
    (Outils → Gérer les bibliothèques… → Rechercher « dv_average_accumulator8 » → Installer)
  - **Adafruit MPU6050** (Adafruit)
    (Outils → Gérer les bibliothèques… → Rechercher « Adafruit MPU6050 » → Installer)

- Pour un test simple, la bibliothèque Adafruit_MPU6050 fonctionne avec le MPU6500 pour lire accéléromètre et gyroscope.
- Pour des fonctions avancées du MPU6500, utiliser une bibliothèque dédiée ou Wire.h.

- Paramétrage board dans l'IDE Arduino
  - **ESP32 Dev Module**
  - Tools -> Upload Speed -> 115200
  
## Scénarios de test (montage + code)
- [Fonctionnement basique du L298N](tests/L298N/01-basic)
- [Client WIFI basique sur ESP32](tests/wifi)
- [Serveur http sur ESP32](tests/http-server)
