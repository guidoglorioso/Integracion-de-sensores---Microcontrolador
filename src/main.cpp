#include "rutinas_atencion.h"

/*
¿Como agrego un nuevo sensor o actuador?
Paso 1: Crear los drivers del sensor o actuador en la carpeta Drivers
    * Requisitos: 
        + metodo obj.update() 
            Ejemplo: void sensor::update() {
                        unsigned long currentTime ;
                        currentTime = millis();
                        if (currentTime - lastMeasurementTime >= TIME_ACT) {
                            lastMeasurementTime = currentTime; 
                            
                            (Actualizar informacion del sensor)
                        }
                    }
        + Definir TIME_ACT como el tiempo entre cada actualizacion en ms
        + metodos "get" y "set" del sensor/actuador.
Paso 2: En el archivo main.cpp instanciar el objeto que interactua con el hardware (driver). 
Paso 2: En la carpeta "userDefines" en el archivo "comandos.h" seguir las instrucciones y definir los comandos para interactuar con el objeto
Paso 3: En el archivo "rutinas_atencion.cpp" definir las rutinas de atencion para los comandos definidos en el paso 2  
Paso 4: En el archivo "rutinas_atencion.cpp" en la funcion "asignar_rutinas_atencion()" agregar la siguiente linea:
    - AgenteComandos::asignarFuncion(Comando::NOMBRE_COMANDO, NOMBRE_RUTINA);
Paso 5: En el archivo "rutinas_atencion.cpp" en la funcion "update()" agregar el metodo "obj.update()" para actualizar el sensor/actuador 

*/
//Instancio los distintos modulos y al agente de comandos 
AgenteComandos agente{};       
ServoMotor servo(D7);           //Servo data: D7
SensorUltraSonido us(D6, D5);   //Trig: D6 -  Echo: D5
SensorOptico opt(PIN_A0);       //Salida sensor: A0 (se mide por ADC)
//SensorPosicion pos;



// Mainloop

void setup() {

    // inicializacion
    asignar_rutinas_atencion();
}

void loop() {

    update();

}

