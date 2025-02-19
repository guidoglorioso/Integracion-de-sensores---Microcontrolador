#include "Drivers/driver_servomotor.h"


#define TIME_ACT 80 // Tiempo de actualizacion mS


// Constructor
ServoMotor::ServoMotor(int pin) : currentAngle(0) {
    servo.attach(pin,600,2400,0);
    servo.write(currentAngle);
    _angleSweep_end = 180;
    _angleSweep_start = 0;
}



// Método para establecer el ángulo del servomotor
void ServoMotor::setAngle(int angle) {
    //if (angle >= 0 && angle <= 180) {
        currentAngle = angle;
    //}
}


// Método para obtener el ángulo actual del servomotor
int ServoMotor::getAngle() const {
    return currentAngle;
}

// Método para iniciar el barrido del servomotor
void ServoMotor::SetSweep(bool _regular_tx) {
    sweeping = _regular_tx;
    sweepDirection = 1; // Inicialmente barrer de 0 a 180
}

/*Funcion que permite establecer los angulos de giro del recorrido*/      
void ServoMotor::SetSweepInterval(int angle_i, int angle_f){
     
    angle_f = angle_f%180;
    angle_i = angle_i%180;
    
    if(angle_f == angle_i) 
        return;
    
    if(angle_i > angle_f){
        _angleSweep_start = angle_f;
        _angleSweep_end = angle_i;
    }
    else{
        _angleSweep_start = angle_i;
        _angleSweep_end = angle_f;
    }
}

// Método para actualizar el estado del servo
void ServoMotor::update() {

    if (millis() - lastUpdateTime >= TIME_ACT) { 
        lastUpdateTime = millis();

        // if (sweeping ){
        //     currentAngle += sweepDirection;
        //     if (currentAngle >= _angleSweep_end) {
        //         currentAngle = _angleSweep_end;
        //         sweepDirection = -1; // Cambiar dirección para barrer hacia atrás
        //     } else if (currentAngle <= _angleSweep_start) {
        //         currentAngle = _angleSweep_start;
        //         sweepDirection = 1; // Cambiar dirección para barrer hacia adelante
        //     }
        // }
        
        servo.write(currentAngle); // Escribo en el servo el angulo actual.
    }
    
}