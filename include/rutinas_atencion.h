#ifndef RUTINAS_ATENCION_H
#define RUTINAS_ATENCION_H

#include <Arduino.h>
#include "Drivers/driver_servomotor.h"
#include "Drivers/driver_sensor_ultra_sonido.h"
#include "Drivers/driver_sensor_optico.h"
#include "agente_comandos.h"

extern AgenteComandos agente;
extern ServoMotor servo;
extern SensorUltraSonido us;
extern SensorOptico opt;   


//Funciones para rutinas de atencion por comandos.
/*
* Esta funciones son las que se asocian a cada comando y son llamadas cada vez que se recibe / envia
* el comando con el que fueron asociadas.
* Para mas informacion sobre cada comando dirigirse a comunicacion.cpp en donde esta el listado de comandos
* con su descripcion.
*/


// Rutina de atencion para comando: RX_MS_ANGULO
void servo_estado(int * arg, int *cant_arg);

// Rutina de atencion para comando: TX_ANGULO
void leer_angulo_servo(int * arg, int *cant_arg);

// Rutina de atencion para comando: RX_MOV_SERVO
void mov_servo(int * arg, int *cant_arg);

// Rutina de atencion para comando: RX_RECORRIDO_SERVO
void recorrido_servo_estado(int * arg, int *cant_arg);

// Rutina de atencion para comando: RX_MS_SENSOR_ULTRA_SONIDO
void sensor_ultra_sonido_estado(int * arg, int *cant_arg);

// Rutina de atencion para comando: RX_MS_SENSOR_OPTICO
void sensor_optico_estado(int * arg, int *cant_arg);

// Rutina de atencion para comando: TX_ULTRA_SONIDO
void leer_sensor_ultrasonido(int * arg, int *cant_arg);

// Rutina de atencion para comando: TX_OPTICO
void leer_sensor_optico(int * arg, int *cant_arg);

// Rutina de atencion para comando: RX_MS_SENSOR_ULTRA_SONIDO_ONETIME
void sensor_ultra_sonido_medicion(int * arg, int *cant_arg);

// Rutina de atencion para comando: RX_MS_SENSOR_OPTICO_ONETIME
void sensor_optico_medicion(int * arg, int *cant_arg);

// Rutina de atencion para comando: RX_TEST
void recibir_test(int * arg, int *cant_arg);

// Rutina de atencion para comando: TX_TEST
void enviar_test(int * arg, int *cant_arg);

// Funciones de inicializacion

 // Funcion que asigna todas las rutinas de atencion a cada uno de los comandos
void asignar_rutinas_atencion();

void update();

#endif // RUTINAS_ATENCION_H