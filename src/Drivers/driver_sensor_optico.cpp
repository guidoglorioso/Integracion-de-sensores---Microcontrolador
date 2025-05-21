#include "Drivers/driver_sensor_optico.h"
#include <Arduino.h>

#define TIME_ACT 30 //Tiempo de actualizacion en mS
#define NUMBER_MEASURES 5

SensorOptico::SensorOptico(int sensorPin) {
  pin = sensorPin;
  lastMeasurementTime = 0;
  pinMode(pin, INPUT);
  
  _ptrRegularTransmision = nullptr;
  _regular_tx = 0;
  _cant_update_regular_tx = 1;
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
    
    static int adc_value[NUMBER_MEASURES];
    static int num_med =0;
    currentTime = millis();
  
    if (currentTime - lastMeasurementTime >= TIME_ACT) {
        num_med++;
        num_med %=NUMBER_MEASURES; 
        
        adc_value[num_med] = analogRead(pin);
        lastMeasurementTime = currentTime;
        float value =0;

        for(int i=0;i<NUMBER_MEASURES;i++){
          value += adc_value[i];
        }
        value /=NUMBER_MEASURES; 
        
        float distance = 31.0 * ((3000 / (value + 1) - 0.8)); // Calcula la distancia en mm

        medicion = distance;
        _regularTxCheck();
    }
    
}

void SensorOptico::_regularTxCheck(){
  static int _actualizaciones = 0;
  if(_regular_tx){
      if(_actualizaciones >= _cant_update_regular_tx){
          _actualizaciones = 0;
          if (_ptrRegularTransmision != nullptr)
          {
              _ptrRegularTransmision(nullptr,nullptr);
          }            
      }
      else{
          _actualizaciones++;
      }
  }
}