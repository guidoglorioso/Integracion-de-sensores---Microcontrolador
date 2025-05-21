#ifndef AGENTE_COMANDOS_H
#define AGENTE_COMANDOS_H


#include "UserDefines/comandos.h"
#include "Drivers/driver_comunicacion.h"

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
#define CANTIDAD_ARGUMENTOS_MAX 20



class AgenteComandos {
public:
    // Constructor
    AgenteComandos(void);

    // Método para enviar tramas por puerto serie
    char enviarComando(Comando comando);

    // Método para enviar por puerto serie un mensaje cualquiera
    void enviarSerie(String mensaje); 

    // Metodo que permite asignar una funcion a un comando.
    static void asignarFuncion(const Comando cmd, void (*funcion)(int*,int*));
    
    // Metodo para actualizar los estados de la comunicacion
    void update();

private:

    // Metodo que chequea si hay comandos disponibles y ejecuta sus funciones asociadas. Debe ser actualizada constantemente.
    void recibirComandos();

    // Variables privadas 
    unsigned long lastUpdateTime; 
    static Comandos_t lista_de_comandos_RX[];
    static Comandos_t lista_de_comandos_TX[];
    Comunicacion com;
};

#endif // AGENTE_COMANDOS
