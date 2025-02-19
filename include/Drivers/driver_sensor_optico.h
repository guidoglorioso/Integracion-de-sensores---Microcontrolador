#ifndef SHARP_SENSOR_H
#define SHARP_SENSOR_H

 
class SensorOptico {
private:
    int pin;  // Pin al que está conectado el sensor
    unsigned long lastMeasurementTime;  // Último momento en que se realizó una medición
    float medicion;

    void _regularTxCheck(); // Metodo que chequea si se debe enviar el dato en forma periodica

    void (*_ptrRegularTransmision)(int*); // Funcion a la que se invoca cuando el driver se actualizo _cant_update_regular_tx veces Y se debe enviar el dato.
    bool _regular_tx;                      // Flag para activar o desactivar la actualizacion en forma regular
    int _cant_update_regular_tx;           // Variable que indica cuantas actualizaciones se deben realizar para enviar el dato.


public:
  SensorOptico(int sensorPin);

  // Metodo para obtener la distancia en cm  
  float getDistance_cm();

  // Metodo para obtener la distancia en mm  
  int getDistance_mm();

  //Metodo para setear si se debe enviar en forma regular o no la medicion.
  inline void SetRegularTransmition(bool state){_regular_tx = state;};

  //Metodo para setear la funcion de envio de datos automatica.
  inline void SetRegularTransmitionCMD(void (*funcion)(int*)){_ptrRegularTransmision = funcion; };
  
  //Metodo para setear la cantidad de actualizaciones antes de enviar el dato medido.
  inline void SetCantUpdateRegularTx(int cant){_cant_update_regular_tx = cant;};

  // Metodo para obtener la distancia en mm por parametro 
  void getDistance_mm(int* medicion_return);

  //Metodo para obtener el estado del sensor (si debe enviar datos o no).
  inline bool GetState(){return _regular_tx;};

  //Metodo para actualizar el estado del sensorOptico
  void update();
};

#endif
