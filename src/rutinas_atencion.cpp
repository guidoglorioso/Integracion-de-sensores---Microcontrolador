#include "rutinas_atencion.h"

//Funciones para rutinas de atencion por comandos.
/*
* Esta funciones son las que se asocian a cada comando y son llamadas cada vez que se recibe / envia
* el comando con el que fueron asociadas.
* Para mas informacion sobre cada comando dirigirse a comunicacion.cpp en donde esta el listado de comandos
* con su descripcion.
*/


// Rutina de atencion para comando: RX_MS_ANGULO
void servo_estado(int * arg){
    agente.enviarComando(TX_ANGULO);
}

// Rutina de atencion para comando: TX_ANGULO
void leer_angulo_servo(int * arg){
    *arg = (int)servo.getAngle();
}

// Rutina de atencion para comando: RX_MOV_SERVO
void mov_servo(int * arg){
    servo.setAngle((int) *arg);
}

// Rutina de atencion para comando: RX_RECORRIDO_SERVO
void recorrido_servo_estado(int * arg){
    servo.SetSweep((bool) *arg);
}

// Rutina de atencion para comando: RX_MS_SENSOR_ULTRA_SONIDO_REGULAR
void sensor_ultra_sonido_regular(int * arg){

    if(*arg <= 0){
        us.SetRegularTransmition((bool) false);
        us.SetRegularTransmitionCMD( nullptr );
    }
    else{
        us.SetRegularTransmition((bool) true);
        us.SetCantUpdateRegularTx(*arg);
        us.SetRegularTransmitionCMD( sensor_ultra_sonido_medicion );
    }

}


// Rutina de atencion para comando: RX_MS_SENSOR_OPTICO_REGULAR
void sensor_optico_regular(int * arg){
    if(*arg <= 0){
        opt.SetRegularTransmition((bool) false);
        opt.SetRegularTransmitionCMD( nullptr );
    }
    else{
        opt.SetRegularTransmition((bool) true);
        opt.SetCantUpdateRegularTx(*arg);
        opt.SetRegularTransmitionCMD( sensor_optico_medicion );
    }

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
    agente.enviarComando(TX_ULTRA_SONIDO);
}

// Rutina de atencion para comando: RX_MS_SENSOR_OPTICO_ONETIME
void sensor_optico_medicion(int * arg){
    agente.enviarComando(TX_OPTICO);
}

// Funciones de inicializacion

 // Funcion que asigna todas las rutinas de atencion a cada uno de los comandos
void asignar_rutinas_atencion(){

    AgenteComandos::asignarFuncion(RX_MOV_SERVO,mov_servo);
    AgenteComandos::asignarFuncion(RX_MS_SENSOR_ULTRA_SONIDO_REGULAR,sensor_ultra_sonido_regular);
    AgenteComandos::asignarFuncion(RX_MS_SENSOR_OPTICO_REGULAR,sensor_optico_regular);
    AgenteComandos::asignarFuncion(RX_MS_SENSOR_ULTRA_SONIDO_ONETIME,sensor_ultra_sonido_medicion);
    AgenteComandos::asignarFuncion(RX_MS_SENSOR_OPTICO_ONETIME,sensor_optico_medicion);
    AgenteComandos::asignarFuncion(TX_ULTRA_SONIDO,leer_sensor_ultrasonido);
    AgenteComandos::asignarFuncion(TX_OPTICO,leer_sensor_optico);
    AgenteComandos::asignarFuncion(TX_ANGULO,leer_angulo_servo);
    AgenteComandos::asignarFuncion(RX_MS_ANGULO,servo_estado);
    //AgenteComandos::asignarFuncion(RX_MS_SENSOR_ACELEROMETRO,);
    //AgenteComandos::asignarFuncion(RX_MS_SENSOR_GIROSCOPO,);
    // AgenteComandos::asignarFuncion(TX_ACELEROMETRO_X,);
    // AgenteComandos::asignarFuncion(TX_ACELEROMETRO_Y,);
    // AgenteComandos::asignarFuncion(TX_ACELEROMETRO_Z,);
    // AgenteComandos::asignarFuncion(TX_GIROSCOPO_X,);
    // AgenteComandos::asignarFuncion(TX_GIROSCOPO_Y,);
    // AgenteComandos::asignarFuncion(TX_GIROSCOPO_Z,);
}

void update(){
    //Update de objetos
    servo.update(); // Seteado en 100ms
    agente.update();   // Seteado en 50ms
    opt.update();   // Seteado en 40ms
    us.update();    // Seteado en 70ms
    //   pos.update();
}