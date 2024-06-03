#include <Arduino.h>
#include "servomotor.h"
#include "ultra_sonido.h"
#include "sensor_optico.h"
#include "comunicacion.h"

//Instancio los distintos modulos y la comunicacion serie
Comunicacion com(115200);       
ServoMotor servo(D7);           //Servo data: D7
SensorUltraSonido us(D6, D5);   //Trig: D6 -  Echo: D5
SensorOptico opt(PIN_A0);       //Salida sensor: A0 (se mide por ADC)



//Funciones para rutinas de atencion por comandos.
/*
* Esta funciones son las que se asocian a cada comando y son llamadas cada vez que se recibe / envia
* el comando con el que fueron asociadas.
* Para mas informacion sobre cada comando dirigirse a comunicacion.cpp en donde esta el listado de comandos
* con su descripcion.
*/

// Rutina de atencion para comando: RX_MOV_SERVO
void mov_servo(int * arg){
    servo.setAngle((int) *arg);
}

// Rutina de atencion para comando: RX_RECORRIDO_SERVO
void recorrido_servo_estado(int * arg){
    servo.SetSweep((bool) *arg);
}

// Rutina de atencion para comando: RX_MS_SENSOR_ULTRA_SONIDO
void sensor_ultra_sonido_estado(int * arg){
    us.SetState((bool) *arg);
}

// Rutina de atencion para comando: RX_MS_SENSOR_OPTICO
void sensor_optico_estado(int * arg){
    opt.SetState((bool) *arg);
}

// Rutina de atencion para comando: TX_ULTRA_SONIDO
void leer_sensor_ultrasonido(int * arg){
    *arg = us.getDistance_mm();
}

// Rutina de atencion para comando: TX_OPTICO
void leer_sensor_optico(int * arg){
    *arg = opt.getDistance_mm();
}

// Rutina de atencion para comando: RX_MS_SENSOR_ULTRA_SONIDO_ONETIME
void sensor_ultra_sonido_medicion(int * arg){
    com.enviarComando(TX_ULTRA_SONIDO);
}

// Rutina de atencion para comando: RX_MS_SENSOR_OPTICO_ONETIME
void sensor_optico_medicion(int * arg){
    com.enviarComando(TX_OPTICO);
}

// Funciones de inicializacion

 // Funcion que asigna todas las rutinas de atencion a cada uno de los comandos
void asignar_rutinas_atencion(){

    Comunicacion::asignarFuncion(RX_MOV_SERVO,mov_servo);
    Comunicacion::asignarFuncion(RX_RECORRIDO_SERVO,recorrido_servo_estado);
    Comunicacion::asignarFuncion(RX_MS_SENSOR_ULTRA_SONIDO,sensor_ultra_sonido_estado);
    Comunicacion::asignarFuncion(RX_MS_SENSOR_OPTICO,sensor_optico_estado);
    Comunicacion::asignarFuncion(RX_MS_SENSOR_ULTRA_SONIDO_ONETIME,sensor_ultra_sonido_medicion);
    Comunicacion::asignarFuncion(RX_MS_SENSOR_OPTICO_ONETIME,sensor_optico_medicion);
    Comunicacion::asignarFuncion(TX_ULTRA_SONIDO,leer_sensor_ultrasonido);
    Comunicacion::asignarFuncion(TX_OPTICO,leer_sensor_optico);
    //Comunicacion::asignarFuncion(RX_MS_SENSOR_ACELEROMETRO,);
    //Comunicacion::asignarFuncion(RX_MS_SENSOR_GIROSCOPO,);
    // Comunicacion::asignarFuncion(TX_ACELEROMETRO_X,);
    // Comunicacion::asignarFuncion(TX_ACELEROMETRO_Y,);
    // Comunicacion::asignarFuncion(TX_ACELEROMETRO_Z,);
    // Comunicacion::asignarFuncion(TX_GIROSCOPO_X,);
    // Comunicacion::asignarFuncion(TX_GIROSCOPO_Y,);
    // Comunicacion::asignarFuncion(TX_GIROSCOPO_Z,);
}

// Mainloop


void setup() {

    // inicializacion
    asignar_rutinas_atencion();
}

void loop() {

    //Update de clases
    servo.update(); // Seteado en 100ms
    com.update();   // Seteado en 50ms
    opt.update();   // Seteado en 40ms
    us.update();    // Seteado en 70ms

    //Setear si se transmite en forma continua o no un mensaje
    Comunicacion::SetTransmitir(TX_ULTRA_SONIDO,us.GetState());
    Comunicacion::SetTransmitir(TX_OPTICO,opt.GetState());

}

