#include "agente_comandos.h"

#define TIME_ACT 50 //ms Tiempo entre cada lectura del puerto serie


/*
    La trama a enviar es: 
    Comandos con argumento ${comando}{argumento}#
    NOTA: todos los comandos Tx son con argumento

    La trama a recibir es:
    Comandos con argumento ${comando}-{argumento}#
    Comandos sin argumento ${comando}#

*/

Comandos_t AgenteComandos::lista_de_comandos_RX[] =DEFINE_COMANDO_RX;
Comandos_t AgenteComandos::lista_de_comandos_TX[] = DEFINE_COMANDO_TX ;

// Constructor
AgenteComandos::AgenteComandos(void) : com(115200) {

}

void AgenteComandos::update(){

    if (millis() - lastUpdateTime >= TIME_ACT) { 
        lastUpdateTime = millis();
        recibirComandos();  // Chequeo si hay comandos a recibir
        Transmitir();       // Envio los datos que esten configurados para ser enviado en forma periodica.
    }
}

//TODO ver tema de que es bloqueante la comunicacion hasta que recibe "#"
// TODO implementar con maquina de estados.
void AgenteComandos::recibirComandos(){
    String comando;
    int argumento;

    // Detecto si hay datos en serie (como minimo que haya 4 bytes)
    String receivedText = com.recibirComandoString();
    if (!receivedText.isEmpty()) {
        
        // Detecto parte importantes del comando
        int guion = receivedText.indexOf("-");
        int inicio_trama = receivedText.indexOf("$");
        int fin_trama = receivedText.indexOf("#");
        
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

char AgenteComandos::enviarComando(Comando comando){
    String mensaje;
    int argumento=0;

    //Busco si el comando es valido
    for (int i = 0; i < (int)((float)sizeof(lista_de_comandos_TX) / sizeof(lista_de_comandos_TX[0])); ++i) {
        if (lista_de_comandos_TX[i].cmd == comando) {
            
            // Ejecutar la función asociada al comando
            lista_de_comandos_TX[i].funcion(&argumento);
            
            // Formo la trama del comando
            String arg_ascci = "$" + String(lista_de_comandos_TX[i].trama) + String(argumento) + "#";
            com.enviarComandoString(arg_ascci);
            return 1;
        }
    }
    return 0;
}


void AgenteComandos::SetTransmitir(Comando comando,bool state){
    for (int i = 0; i < (int) ((float)sizeof(lista_de_comandos_TX) / sizeof(lista_de_comandos_TX[0])); ++i) {
        if ((lista_de_comandos_TX[i].cmd == comando) && (lista_de_comandos_TX[i].transmitir != state)) {
                lista_de_comandos_TX[i].transmitir = state;
        }
    }
}
void AgenteComandos::Transmitir(){
    int argumento=0;
    
    for (int i = 0; i < (int)((float)sizeof(lista_de_comandos_TX) / sizeof(lista_de_comandos_TX[0])); ++i) {
        if (lista_de_comandos_TX[i].transmitir) { // Envio los comandos configurado para ser enviado en forma periodica
                lista_de_comandos_TX[i].funcion(&argumento);
                String arg_ascci = "$" + String(lista_de_comandos_TX[i].trama) + String(argumento) + "#";
                com.enviarComandoString(arg_ascci);
        }
    }
}



void AgenteComandos::asignarFuncion(const Comando cmd, void (*funcion)(int*)) {
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