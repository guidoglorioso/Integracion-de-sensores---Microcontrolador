#include "Comunicacion.h"

#define TIME_ACT 50 //ms Tiempo entre cada lectura del puerto serie


/*
    La trama a enviar es: 
    Comandos con argumento ${comando}{argumento}#
    NOTA: todos los comandos Tx son con argumento

    La trama a recibir es:
    Comandos con argumento ${comando}-{argumento}#
    Comandos sin argumento ${comando}#

*/
Comandos_t Comunicacion::lista_de_comandos_RX[] = {
    {RX_MS_SENSOR_ULTRA_SONIDO_ONETIME,"SENUS1",nullptr,0}, //ok
    {RX_MS_SENSOR_OPTICO_ONETIME,"SENOP1",nullptr,0},       //ok
    {RX_MOV_SERVO,"MOV1",nullptr,0},                        //ok
    {RX_RECORRIDO_SERVO,"MOVR",nullptr,0},                  
    {RX_MS_SENSOR_ULTRA_SONIDO,"SENUS",nullptr,0},          //ok
    {RX_MS_SENSOR_OPTICO,"SENOP",nullptr,0},                //ok
    {RX_MS_SENSOR_ACELEROMETRO,"SENAC",nullptr,0},
    {RX_MS_SENSOR_GIROSCOPO,"SENGI",nullptr,0},

};
Comandos_t Comunicacion::lista_de_comandos_TX[] = {
    {TX_ACELEROMETRO_X,"SENACX",nullptr,0},
    {TX_ACELEROMETRO_Y,"SENACY",nullptr,0},
    {TX_ACELEROMETRO_Z,"SENACZ",nullptr,0},
    {TX_ULTRA_SONIDO,"SENUSD",nullptr,0},                   //ok
    {TX_OPTICO,"SENOPD",nullptr,0},                         //ok
    {TX_GIROSCOPO_X,"SENGIX",nullptr,0},
    {TX_GIROSCOPO_Y,"SENGIY",nullptr,0},
    {TX_GIROSCOPO_Z,"SENGIZ",nullptr,0},
};

// Constructor
Comunicacion::Comunicacion(long int baudRate = 115200) {
    Serial.begin(baudRate, SERIAL_8N1);
}

// Método para establecer la comunicación serie
void Comunicacion::iniciarComunicacion(long baudRate,SerialConfig config_extra = SERIAL_8N1) {
    Serial.begin(baudRate, config_extra);
}


void Comunicacion::update(){

    if (millis() - lastUpdateTime >= TIME_ACT) { 
        lastUpdateTime = millis();
        recibirComandos();  // Chequeo si hay comandos a recibir
        Transmitir();       // Envio los datos que esten configurados para ser enviado en forma periodica.
    }
}

//TODO ver tema de que es bloqueante la comunicacion hasta que recibe "#"
void Comunicacion::recibirComandos(){
    String comando;
    int argumento;

    // Detecto si hay datos en serie (como minimo que haya 4 bytes)
    if (Serial.available() > 4) {
        
        String receivedText = Serial.readStringUntil('#') + "#";
        
        // Detecto parte importantes del comando
        int guion = receivedText.indexOf("-");
        int inicio_trama = receivedText.indexOf("$");
        int fin_trama = receivedText.indexOf("#");
        
        //Chequeo de errores
        if(inicio_trama == -1 || fin_trama == -1){
            return; // No llego bien la trama
        }

        // Detecto si es un comando sin argumento
        if(guion == -1){ 
            comando = receivedText.substring(inicio_trama+1,fin_trama);
            argumento = -1;
        }
        else{ // Si es un comando con argumento
            comando = receivedText.substring(inicio_trama+1,guion);
            argumento =  receivedText.substring(guion+1,fin_trama).toInt();
        }

        //En caso de ser un comando Rx valido se llama a su funcion asociada.
        for (int i = 0; i < (int)((float)sizeof(lista_de_comandos_RX) / sizeof(lista_de_comandos_RX[0])); ++i) {
            
            if (comando.equals(lista_de_comandos_RX[i].trama)) {
            // Ejecutar la función asociada al comando
                if(lista_de_comandos_RX[i].funcion !=nullptr)
                    lista_de_comandos_RX[i].funcion(&argumento);
                return;
            }
        }
    }
}

char Comunicacion::enviarComando(Comando comando){
    String mensaje;
    int argumento=0;

    //Busco si el comando es valido
    for (int i = 0; i < (int)((float)sizeof(lista_de_comandos_TX) / sizeof(lista_de_comandos_TX[0])); ++i) {
        if (lista_de_comandos_TX[i].cmd == comando) {
            
            // Ejecutar la función asociada al comando
            lista_de_comandos_TX[i].funcion(&argumento);
            
            // Formo la trama del comando
            String arg_ascci = "$" + String(lista_de_comandos_TX[i].trama) + String(argumento) + "#";
            enviarSerie(arg_ascci);
            return 1;
        }
    }
    return 0;
}


void Comunicacion::SetTransmitir(Comando comando,bool state){
    for (int i = 0; i < (int) ((float)sizeof(lista_de_comandos_TX) / sizeof(lista_de_comandos_TX[0])); ++i) {
        if ((lista_de_comandos_TX[i].cmd == comando) && (lista_de_comandos_TX[i].transmitir != state)) {
                lista_de_comandos_TX[i].transmitir = state;
        }
    }
}
void Comunicacion::Transmitir(){
    int argumento=0;
    
    for (int i = 0; i < (int)((float)sizeof(lista_de_comandos_TX) / sizeof(lista_de_comandos_TX[0])); ++i) {
        if (lista_de_comandos_TX[i].transmitir) { // Envio los comandos configurado para ser enviado en forma periodica
                lista_de_comandos_TX[i].funcion(&argumento);
                String arg_ascci = "$" + String(lista_de_comandos_TX[i].trama) + String(argumento) + "#";
                enviarSerie(arg_ascci);
        }
    }
}

void Comunicacion::enviarSerie(String mensaje){

    Serial.println(mensaje);
}


void Comunicacion::asignarFuncion(const Comando cmd, void (*funcion)(int*)) {
    // Recorrer el vector de comandos

    for (int i = 0; i <(int)((float)sizeof(lista_de_comandos_RX) / sizeof(lista_de_comandos_RX[0])); ++i) {
        
        // Comparar el comando con el cmd pasado como argumento
        if (lista_de_comandos_RX[i].cmd == cmd) {
            // Asignar la función al puntero de función en la estructura
            lista_de_comandos_RX[i].funcion = funcion;
            return; // Salir del bucle una vez asignada la función
        }
    }
    for (int i = 0; i < (int)((float)sizeof(lista_de_comandos_TX) / sizeof(lista_de_comandos_TX[0])); ++i) {
        // Comparar el comando con el cmd pasado como argumento
        if (lista_de_comandos_TX[i].cmd == cmd) {
            // Asignar la función al puntero de función en la estructura
            lista_de_comandos_TX[i].funcion = funcion;
            return; // Salir del bucle una vez asignada la función
        }
    }
}