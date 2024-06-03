#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include <Arduino.h>
#include <Servo.h>


class ServoMotor {
public:
    // Constructor
    ServoMotor(int pin);

    // Metodo que fija el angulo del servomotor
    void setAngle(int angle);

    // Metodo que devuelve el angulo actual del servomotor
    int getAngle() const;

    // Metodo que setea el sweep del motor en activo o apagado. (Barre desde un angulo incial a un angulo final).
    void SetSweep(bool estado);
    
    // Metodo que define el rango de Sweep del servo
    void SetSweepInterval(int angle_i, int angle_f);

    // Metodo que actualiza el estado del servomotor.
    void update();

private:
    // Miembros privados
 
    Servo servo;
    int currentAngle;
    int relativeAngle;
    bool sweeping;
    int _angleSweep_start, _angleSweep_end;
    unsigned long lastUpdateTime;
    int sweepDirection;
};

#endif // SERVOMOTOR_H
