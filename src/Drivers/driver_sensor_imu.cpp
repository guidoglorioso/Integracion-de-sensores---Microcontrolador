// #include "Drivers/sensor_imu.h"

// SensorPosicion::SensorPosicion() : mpu(0x68) {

//     Wire.begin();
//     Serial.println(F("Initializing I2C devices..."));
//     mpu.initialize();
//     Serial.println(F("Testing device connections..."));
//     Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
// }

// void SensorPosicion::begin() {
  
//   lastUpdateTime = 0;
// }

// void SensorPosicion::update() {
//   unsigned long currentTime = millis();
//   if (currentTime - lastUpdateTime >= MPU_UPDATE_INTERVAL) {
    
//     lastUpdateTime = currentTime;
//     mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
//   }
// }

// float SensorPosicion::getAccelerationX() {
//   return ax;
// }

// float SensorPosicion::getAccelerationY() {
//   return ay;
// }

// float SensorPosicion::getAccelerationZ() {
//   return az;
// }

// float SensorPosicion::getTemperature() {
//   return gx;
// }

// float SensorPosicion::getRotationX() {
//   return mpu.getRotationX();
// }

// float SensorPosicion::getRotationY() {
//   return mpu.getRotationY();
// }

// float SensorPosicion::getRotationZ() {
//   return mpu.getRotationZ();
// }
