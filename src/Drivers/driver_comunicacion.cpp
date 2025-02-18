#include "Drivers/driver_comunicacion.h"


// Constructor
Comunicacion::Comunicacion(long int baudRate) {
    InitComunicacion(baudRate,SERIAL_8N1);
}
Comunicacion::Comunicacion(void) {
    InitComunicacion( (long) 115200,SERIAL_8N1);
}

// Método para establecer la comunicación serie
void Comunicacion::InitComunicacion(long baudRate,SerialConfig config_extra = SERIAL_8N1) {
    Serial.setTimeout(10);
    Serial.begin(baudRate, config_extra);
}


String Comunicacion::recibirComandoString(){
 
    // Detecto si hay datos en serie (como minimo que haya 4 bytes)
    if (Serial.available() > 4) {
        
        String receivedText = Serial.readStringUntil('#') + "#";
        // Detecto parte importantes del comando
        int inicio_trama = receivedText.indexOf("$");
        int fin_trama = receivedText.indexOf("#");

        //Chequeo de errores
        if(inicio_trama == -1 || fin_trama == -1 || inicio_trama > fin_trama){
            return ""; // String vacio indica falla en la recepcion.
        }
        return receivedText.substring(inicio_trama,fin_trama+1);
    }
    return "";
}


void Comunicacion::enviarComandoString(String mensaje){

    Serial.println(mensaje);
}
