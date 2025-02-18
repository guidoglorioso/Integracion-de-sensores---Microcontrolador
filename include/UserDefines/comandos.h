#ifndef COMANDOS_DEFINES_H
#define COMANDOS_DEFINES_H

/*
En este archivo se configuran los comandos que se pueden enviar y recibir. 

Para agregar un nuevo comando:
1) Definir el comando en el enum "Comando" con el nombre que se le quiera asignar.
2) Asignar al comando definido en el paso 1 la trama asociada. Hay dos posibilidades:
    - Si el comando es para enviar, se debe asignar la trama en la lista de comandos Tx
    - Si el comando es para recibir, se debe asignar la trama en la lista de comandos Rx
3) Definir en el archivo "rutinas_atencion.cpp" la rutina que se debe ejecutar al recibir el comando
4) En el archivo "rutinas_atencion.cpp" agregar en la funcion asignar_rutinas_atencion() la siguiente linea:
    - AgenteComandos::asignarFuncion(Comando::NOMBRE_COMANDO, NOMBRE_RUTINA);
*/


// Comandos definidos
enum Comando{
    // Comandos para recibir
    RX_MOV_SERVO,                       // (ok)Permite mover el servo a una posicion determinada trabajando con angulo
    RX_RECORRIDO_SERVO,                 // Permite activar/desactivar la secuencia de movimiento fija del servomotor (barrido de 0 a 180 grados)
    RX_MS_SENSOR_ULTRA_SONIDO,          // (ok)Permite activar/desactivar mediciones constantemente del sensor de ultra sonido
    RX_MS_SENSOR_ULTRA_SONIDO_ONETIME,  // (ok)Permite pedir la ultima medicion hecha.
    RX_MS_SENSOR_OPTICO,                // (ok)Permite activar/desactivar mediciones constantemente del sensor optico
    RX_MS_SENSOR_OPTICO_ONETIME,        // (ok)Permite pedir la ultima medicion hecha.
    RX_MS_SENSOR_ACELEROMETRO,          // Permite activar/desactivar mediciones constantemente del sensor acelerometro
    RX_MS_SENSOR_GIROSCOPO,             // Permite activar/desactivar mediciones constantemente del sensor giroscopo
    RX_MS_ANGULO,                       // Permite pedir la ultima medicion

    //Comandos para enviar
    TX_ACELEROMETRO_X,      // Enviar aceleracion eje X.
    TX_ACELEROMETRO_Y,      // Enviar aceleracion eje Y.
    TX_ACELEROMETRO_Z,      // Enviar aceleracion eje Z.
    TX_ULTRA_SONIDO,        // (ok)Enviar medicion ultrasonido.
    TX_OPTICO,              // (ok)Envia medicion sensor optico.
    TX_GIROSCOPO_X,         // Enviar aceleracion angular eje X.
    TX_GIROSCOPO_Y,         // Enviar aceleracion angular eje Y.
    TX_GIROSCOPO_Z,         // Enviar aceleracion angular eje Z.
    TX_ANGULO          // Enviar angulo servo.
};

//Estructura de cada comando
struct Comandos_t {
    const Comando cmd;      // Nombre del comando
    const char* trama;      // Trama asociada que se recibe
    void (*funcion)(int*);  // Funcion que se invoca al enviar o recibir el comando
    bool transmitir;        // Define si se debe enviar periodicamente un comando. Unicamente se usa para comandos Tx
};

/*
    Defines para la trama de los comandos que se recibe/envia.
*/

#define DEFINE_COMANDO_RX { \
    {RX_MS_SENSOR_ULTRA_SONIDO_ONETIME, "SENUS1", nullptr, false}, \
    {RX_MS_SENSOR_OPTICO_ONETIME, "SENOP1", nullptr, false}, \
    {RX_MOV_SERVO, "MOV1", nullptr, false}, \
    {RX_RECORRIDO_SERVO, "MOVR", nullptr, false}, \
    {RX_MS_SENSOR_ULTRA_SONIDO, "SENUS", nullptr, false}, \
    {RX_MS_SENSOR_OPTICO, "SENOP", nullptr, false}, \
    {RX_MS_SENSOR_ACELEROMETRO, "SENAC", nullptr, false}, \
    {RX_MS_SENSOR_GIROSCOPO, "SENGI", nullptr, false}, \
    {RX_MS_ANGULO, "ANG", nullptr, false} \
}

#define DEFINE_COMANDO_TX { \
    {TX_ACELEROMETRO_X, "SENACX", nullptr, false}, \
    {TX_ACELEROMETRO_Y, "SENACY", nullptr, false}, \
    {TX_ACELEROMETRO_Z, "SENACZ", nullptr, false}, \
    {TX_ULTRA_SONIDO, "SENUSD", nullptr, false}, \
    {TX_OPTICO, "SENOPD", nullptr, false}, \
    {TX_GIROSCOPO_X, "SENGIX", nullptr, false}, \
    {TX_GIROSCOPO_Y, "SENGIY", nullptr, false}, \
    {TX_GIROSCOPO_Z, "SENGIZ", nullptr, false}, \
    {TX_ANGULO, "SENANG", nullptr, false} \
}

#endif // COMANDOS_DEFINES_H