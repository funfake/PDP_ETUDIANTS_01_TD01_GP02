#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define SENSOR 33
#define LED 26

// Définir le type de capteur (DHT22)
#define DHTTYPE DHT11

DHT_Unified dht(SENSOR, DHTTYPE);

uint32_t delayMS;

void setup() {
  Serial.begin(9600);

  // Initialiser le capteur DHT
  dht.begin();

  Serial.println(F("DHTxx Unified Sensor Example"));

  // Initialiser la broche LED comme sortie
  pinMode(LED, OUTPUT);

  // Configurer le délai entre les mesures
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  delayMS = 5000;
}

void loop() {
  // Effectuer une mesure toutes les 5s
  delay(delayMS);

  // Obtenir l'événement de température
  sensors_event_t event;
  dht.temperature().getEvent(&event);

  // Vérifier si la mesure de température est valide
  if (!isnan(event.temperature)) {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  } else {
    Serial.println(F("Error reading temperature!"));
  }

  // Obtenir l'événement d'humidité
  dht.humidity().getEvent(&event);

  // Vérifier si la mesure d'humidité est valide
  if (!isnan(event.relative_humidity)) {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  } else {
    Serial.println(F("Error reading humidity!"));
  }
}