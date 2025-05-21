#include "rutinas_atencion.h"

//Funciones para rutinas de atencion por comandos.
/*
* Esta funciones son las que se asocian a cada comando y son llamadas cada vez que se recibe / envia
* el comando con el que fueron asociadas.
* Para mas informacion sobre cada comando dirigirse a comunicacion.cpp en donde esta el listado de comandos
* con su descripcion.
*/



// Rutina de atencion para comando: RX_MS_ANGULO
void servo_estado(int * arg, int *cant_arg){
    agente.enviarComando(TX_ANGULO);
}

// Rutina de atencion para comando: TX_ANGULO
void leer_angulo_servo(int * arg, int *cant_arg){
    *arg = (int)servo.getAngle();
    *cant_arg = 1;
}

// Rutina de atencion para comando: RX_MOV_SERVO
void mov_servo(int * arg, int *cant_arg){
    servo.setAngle((int) *arg);
    *cant_arg = 1;
}

// Rutina de atencion para comando: RX_RECORRIDO_SERVO
void recorrido_servo_estado(int * arg, int *cant_arg){
    servo.SetSweep((bool) *arg);
    *cant_arg = 1;
}

// Rutina de atencion para comando: RX_MS_SENSOR_ULTRA_SONIDO_REGULAR
void sensor_ultra_sonido_regular(int * arg, int *cant_arg){

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
void sensor_optico_regular(int * arg, int *cant_arg){
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
void leer_sensor_ultrasonido(int * arg, int *cant_arg){
    *arg = us.getDistance_mm();
    *cant_arg = 1;
}

// Rutina de atencion para comando: TX_OPTICO
void leer_sensor_optico(int * arg, int *cant_arg){
    *arg = opt.getDistance_mm();
    *cant_arg = 1;
}

// Rutina de atencion para comando: RX_MS_SENSOR_ULTRA_SONIDO_ONETIME
void sensor_ultra_sonido_medicion(int * arg, int *cant_arg){
    agente.enviarComando(TX_ULTRA_SONIDO);
}

// Rutina de atencion para comando: RX_MS_SENSOR_OPTICO_ONETIME
void sensor_optico_medicion(int * arg, int *cant_arg){
    agente.enviarComando(TX_OPTICO);
}

// Rutina de atencion para comando RX_TEST

int argumentos_test[CANTIDAD_ARGUMENTOS_MAX];
int cantidad_argumentos_test = 0;

void recibir_test(int * arg, int *cant_arg){
    cantidad_argumentos_test = *cant_arg;
    for(int i = 0; i < cantidad_argumentos_test; i++){
        argumentos_test[i] = arg[i];
    }
    agente.enviarComando(TX_TEST);
    
}   

// Rutina para enviar comando TX_TEST
void enviar_test(int * arg, int *cant_arg){
    for(int i = 0; i < cantidad_argumentos_test; i++){
        arg[i] = 100 + argumentos_test[cantidad_argumentos_test - i - 1];
    }
    *cant_arg = cantidad_argumentos_test;
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
    AgenteComandos::asignarFuncion(TX_TEST,enviar_test);
    AgenteComandos::asignarFuncion(RX_TEST,recibir_test);

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

    //Medir tiempos en uS
   
    //unsigned long lastUpdateTime_1 = micros();
    //Serial.println((double)(micros() - lastUpdateTime_1),2);

    //Update de objetos
    
    servo.update(); // Seteado en 80ms // 17ms en ejecutarse
    opt.update();   // Seteado en 40ms //0.2ms en ejecutarse
    us.update();    // Seteado en 80ms // 3ms en ejecutarse
  
    //   pos.update();
    
    // Actualizacion Agente comandos
    
    agente.update();   // Seteado en 1ms // 400us cuando recibe comando
    
   
}