#ifndef COMUNICACION_H
#define COMUNICACION_H

#include <Arduino.h>


class Comunicacion {
public:
    // Constructor
    Comunicacion(long int baudRate);
    Comunicacion(void);

    // Método para establecer la comunicación serie
    void InitComunicacion(long int baudRate,SerialConfig config_extra);

    // Método para recibir leer un string en formato de comando, Devuelve null si no se reconocio un formato de comando.
    String recibirComandoString();

    // Método para enviar por puerto serie un mensaje cualquiera
    void enviarComandoString(String mensaje); 


private:

};

#endif // COMUNICACION_UART_H
