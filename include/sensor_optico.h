#ifndef SHARP_SENSOR_H
#define SHARP_SENSOR_H

 
class SensorOptico {
private:
    int pin;  // Pin al que está conectado el sensor
    unsigned long lastMeasurementTime;  // Último momento en que se realizó una medición
    float medicion;
    bool estado;

public:
  SensorOptico(int sensorPin);

  // Metodo para obtener la distancia en cm  
  float getDistance_cm();

  // Metodo para obtener la distancia en mm  
  int getDistance_mm();

  //Metodo para setear el estado del sensor (si debe enviar datos o no).
  inline void SetState(bool state){estado = state;};

  // Metodo para obtener la distancia en mm por parametro 
  void getDistance_mm(int* medicion_return);

  //Metodo para obtener el estado del sensor (si debe enviar datos o no).
  inline bool GetState(){return estado;};

  //Metodo para actualizar el estado del sensorOptico
  void update();
};

#endif
