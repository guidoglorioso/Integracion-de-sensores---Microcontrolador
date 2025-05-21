#include "agente_comandos.h"

#define TIME_ACT 1 //ms Tiempo entre cada lectura del puerto serie


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

    unsigned long currentTime = millis();
    if (currentTime - lastUpdateTime >= TIME_ACT) { 
        lastUpdateTime = currentTime;
        recibirComandos();  // Chequeo si hay comandos a recibir
    }
}

//TODO ver tema de que es bloqueante la comunicacion hasta que recibe "#"
// TODO implementar con maquina de estados.
// Limito la cantidad de datos a recibir a un maximo de CANTIDAD_ARGUMENTOS_MAX valores 
void AgenteComandos::recibirComandos(){
    String comando;
    int argumento[CANTIDAD_ARGUMENTOS_MAX];
    int cant_arg = 0;
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
            argumento[0] = -1;
        }
        else{ // Si es un comando con argumento

            comando = receivedText.substring(inicio_trama+1,guion);
            do{
                int siguiente_guion = receivedText.indexOf("-",guion+1);
                if(siguiente_guion != -1){
                    argumento[cant_arg] = receivedText.substring(guion+1,siguiente_guion).toInt();
                }
                else{
                // Si no hay mas guiones, significa que es el ultimo argumento
                // y se debe tomar el argumento hasta el final de la trama
                    argumento[cant_arg] = receivedText.substring(guion+1,fin_trama).toInt();
                }
                guion = siguiente_guion;
                cant_arg++;
            }while(guion != -1 && cant_arg < 20);

        }
    }

    //En caso de ser un comando Rx valido se llama a su funcion asociada.
    for (int i = 0; i < (int)((float)sizeof(lista_de_comandos_RX) / sizeof(lista_de_comandos_RX[0])); ++i) {
        
        if (comando.equals(lista_de_comandos_RX[i].trama)) {
        // Ejecutar la función asociada al comando
            if(lista_de_comandos_RX[i].funcion !=nullptr)
                lista_de_comandos_RX[i].funcion(argumento,&cant_arg);
            return;
        }
    }
}


char AgenteComandos::enviarComando(Comando comando){
    String mensaje;
    int argumento[CANTIDAD_ARGUMENTOS_MAX];
    int cantidad_argumentos = 0;
    //Busco si el comando es valido
    for (int i = 0; i < (int)((float)sizeof(lista_de_comandos_TX) / sizeof(lista_de_comandos_TX[0])); ++i) {
        if (lista_de_comandos_TX[i].cmd == comando) {
            
            // Ejecutar la función asociada al comando
            lista_de_comandos_TX[i].funcion(argumento,&cantidad_argumentos);
            
            // Formo la trama del comando
            
            String argumentos = "";
            for(int i2 =0;i2<cantidad_argumentos;i2++){
                argumentos += "-" + String(argumento[i2]);
            }
            String arg_ascci = "$" + String(lista_de_comandos_TX[i].trama) + argumentos + "#";
            com.enviarComandoString(arg_ascci);
            return 1;
        }
    }
    return 0;
}


void AgenteComandos::asignarFuncion(const Comando cmd, void (*funcion)(int*,int*)) {
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