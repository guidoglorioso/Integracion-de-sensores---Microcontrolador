#include "Drivers/driver_sensor_ultra_sonido.h"

#include <Arduino.h>

#define TIME_ACT 70//ms Tiempo entre cada medicion del sensor

SensorUltraSonido::SensorUltraSonido(int triggerPin, int echoPin)
  : ultrasonic(triggerPin, echoPin) {
  lastMeasurementTime = 0;
  _ptrRegularTransmision = nullptr;
  _regular_tx = 0;
  _cant_update_regular_tx = 1;
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
        _regularTxCheck();
    }
}


void SensorUltraSonido::_regularTxCheck(){
    static int _actualizaciones = 0;
    if(_regular_tx){
        if(_actualizaciones >= _cant_update_regular_tx){
            _actualizaciones = 0;
            if (_ptrRegularTransmision != nullptr)
            {
                _ptrRegularTransmision(nullptr);
            }            
        }
        else{
            _actualizaciones++;
        }
    }
}