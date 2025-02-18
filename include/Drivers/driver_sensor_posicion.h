#ifndef SensorPosicion_h
#define SensorPosicion_h

//#include "MPU6050.h"

#define MPU_UPDATE_INTERVAL 20 // Intervalo de actualización en milisegundos

class SensorPosicion {
  public:
    SensorPosicion();

    void begin();
    void update();
    float getAccelerationX();
    float getAccelerationY();
    float getAccelerationZ();
    float getTemperature();
    float getRotationX();
    float getRotationY();
    float getRotationZ();

  private:
    //MPU6050 mpu;
    
    //int16_t ax, ay, az;
    //int16_t gx, gy, gz;

    unsigned long lastUpdateTime;
};

#endif
