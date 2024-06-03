#include "Sensor_Optico.h"
#include <Arduino.h>

#define TIME_ACT 40 //Tiempo de actualizacion en mS

SensorOptico::SensorOptico(int sensorPin) {
  pin = sensorPin;
  lastMeasurementTime = 0;
  pinMode(pin, INPUT);
  estado = 0;
}

//Devuelve la distancia en CM
float SensorOptico::getDistance_cm() {
  return medicion/10;
}

//Devuelve la distancia en mm
int SensorOptico::getDistance_mm() {
  return int(medicion);
}
//Devuelve la distancia en mm
void SensorOptico::getDistance_mm(int* medicion_return) {
    *medicion_return = int(medicion);
}

//TODO: hacer que no se este actualizando todo el tiempo el sensor si no se usa.
void SensorOptico::update() {
    unsigned long currentTime ;
   
    currentTime = millis();
    if (currentTime - lastMeasurementTime >= TIME_ACT) {
        lastMeasurementTime = currentTime;
        int adc_value = analogRead(pin);
        float distance = 31.0 * ((3000 / (adc_value + 1) - 0.8)); // Calcula la distancia en mm

        medicion = distance;
    }
    
}

