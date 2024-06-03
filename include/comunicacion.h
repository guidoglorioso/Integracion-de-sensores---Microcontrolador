#ifndef COMUNICACION_H
#define COMUNICACION_H

#include <Arduino.h>


/*
Para agregar un nuevo comando se deben seguir los siguiente pasos:
1) - Definir comando en la lista de comando (dentro del enum). Aca debemos poner
el nombre con el que asociaremos el comando.
2) - En el archivo comunicacion.cpp en la variable estatica correspondiente al comando,
        - si es comando Tx en la variable lista_de_comandos_TX
        - si es comando Rx en la variable lista_de_comandos_RX
asignar la trama asociada a ese comando. No incluir inicio ni fin de trama solo el codigo del comando.
3) - En el main asociar con el metodo estatico "asignarFuncion(const Comando cmd, void (*funcion)(int*))",
asignar la funcion de atencion cuando ese comando deba ser enviado o recibido.
Si el comando es Tx, la funcion podra incluir en el argumento *arg el valor que se quiera enviar.
Si el comando es Rx, la funcion podra obtener el valor del argumento en la trama 
que se recibio usando el argumento *arg.
NOTA: si el comando no se supone que reciba un parametro no usarlo.

El comando ya se encuentra definido.
EXTRA:
En caso de que el comando se pretenda que envie datos periodicamente (solo comandos Tx), se debe 
usar el metodo: "SetTransmitir(Comando comandos,bool state)" para setear el estado en 1 y que se envie
periodicamente en forma automatica.

TRAMAS DE COMANDOS

La trama a enviar es: 
Comandos con argumento ${comando}{argumento}#
NOTA: todos los comandos Tx son con argumento

La trama a recibir es:
Comandos con argumento ${comando}-{argumento}#
Comandos sin argumento ${comando}#


*/

// Comandos definidos
enum Comando{
    // Comandos para recibir
    RX_MOV_SERVO,                       // Permite mover el servo a una posicion determinada trabajando con angulo
    RX_RECORRIDO_SERVO,                 // Permite activar/desactivar la secuencia de movimiento fija del servomotor (barrido de 0 a 180 grados)
    RX_MS_SENSOR_ULTRA_SONIDO,          // Permite activar/desactivar mediciones constantemente del sensor de ultra sonido
    RX_MS_SENSOR_ULTRA_SONIDO_ONETIME,  // Permite pedir la ultima medicion hecha.
    RX_MS_SENSOR_OPTICO,                // Permite activar/desactivar mediciones constantemente del sensor optico
    RX_MS_SENSOR_OPTICO_ONETIME,        // Permite pedir la ultima medicion hecha.
    RX_MS_SENSOR_ACELEROMETRO,          // Permite activar/desactivar mediciones constantemente del sensor acelerometro
    RX_MS_SENSOR_GIROSCOPO,             // Permite activar/desactivar mediciones constantemente del sensor giroscopo
    
    //Comandos para enviar
    TX_ACELEROMETRO_X,      // Enviar aceleracion eje X.
    TX_ACELEROMETRO_Y,      // Enviar aceleracion eje Y.
    TX_ACELEROMETRO_Z,      // Enviar aceleracion eje Z.
    TX_ULTRA_SONIDO,        // Enviar medicion ultrasonido.
    TX_OPTICO,              // Envia medicion sensor optico.
    TX_GIROSCOPO_X,         // Enviar aceleracion angular eje X.
    TX_GIROSCOPO_Y,         // Enviar aceleracion angular eje Y.
    TX_GIROSCOPO_Z,         // Enviar aceleracion angular eje Z.
};

//Estructura de cada comando
struct Comandos_t {
    const Comando cmd;      // Nombre del comando
    const char* trama;      // Trama asociada que se recibe
    void (*funcion)(int*);  // Funcion que se invoca al enviar o recibir el comando
    bool transmitir;        // Define si se debe enviar periodicamente un comando. Unicamente se usa para comandos Tx
};


class Comunicacion {
public:
    // Constructor
    Comunicacion(long int baudRate);

    // Método para establecer la comunicación serie
    void iniciarComunicacion(long int baudRate,SerialConfig config_extra);

    // Método para enviar tramas por puerto serie
    char enviarComando(Comando comando);

    // Método para enviar por puerto serie un mensaje cualquiera
    void enviarSerie(String mensaje); 

    //Metodo que fija el valor de "transmitir" en un determinado comando Tx (define si debe enviar o no por serie constantemente)
    static void SetTransmitir(Comando comandos,bool state);

    // Metodo que permite asignar una funcion a un comando.
    static void asignarFuncion(const Comando cmd, void (*funcion)(int*));
    
    // Metodo para actualizar los estados de la comunicacion
    void update();

private:

    // Metodo que chequea si hay comandos disponibles y ejecuta sus funciones asociadas. Debe ser actualizada constantemente.
    void recibirComandos();

    //Metodo que envia todos los comandos de Tx que esten con el estado "transmitir" = 1
    void Transmitir();

    // Variables privadas 
    unsigned long lastUpdateTime; 
    static Comandos_t lista_de_comandos_RX[];
    static Comandos_t lista_de_comandos_TX[];
};

#endif // COMUNICACION_H
