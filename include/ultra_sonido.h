#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <UltrasonicHCSR04.h>

class SensorUltraSonido {

public:
    SensorUltraSonido(int triggerPin, int echoPin);

    // Metodo para obtener la distancia en cm  
    float getDistance_cm();

    // Metodo para obtener la distancia en mm
    int getDistance_mm();

    //Metodo para setear el estado del sensor (si debe enviar datos o no).
    inline void SetState(bool state){estado = state;};

    //Metodo para obtener el estado del sensor (si debe enviar datos o no).
    inline bool GetState(){return estado;};

    //Metodo para actualizar el estado del sensorOptico
    void update();

private:
    UltrasonicHCSR04 ultrasonic;  // Objeto del sensor
    unsigned long lastMeasurementTime;  // Último momento en que se realizó una medición
    float medicion;
    bool estado;
};

#endif
