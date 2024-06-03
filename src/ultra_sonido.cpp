#include "ultra_sonido.h"

#include <Arduino.h>

#define TIME_ACT 70//ms Tiempo entre cada medicion del sensor

SensorUltraSonido::SensorUltraSonido(int triggerPin, int echoPin)
  : ultrasonic(triggerPin, echoPin) {
  lastMeasurementTime = 0;
  estado = 0;
}

float SensorUltraSonido::getDistance_cm() {
    return medicion;
}

int SensorUltraSonido::getDistance_mm() {
    return (int) (medicion*10);
}

void SensorUltraSonido::update() {
    unsigned long currentTime ;


    currentTime = millis();
    if (currentTime - lastMeasurementTime >= TIME_ACT) {
        lastMeasurementTime = currentTime;

        // Realiza la medición de distancia
        float distance = ultrasonic.measureDistanceCM();

        medicion = distance;
    }
}
