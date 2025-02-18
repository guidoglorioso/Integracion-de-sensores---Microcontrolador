# Integración de Sensores - Microcontrolador

En este repositorio se encuentran todos los avances relacionados con el código del microcontrolador para el proyecto de investigación "Integración de sensores para ambientes industriales".

## Descripción del Proyecto

El objetivo del proyecto es procesar datos de sensores en forma descentralizada y comunicar únicamente acciones o solicitudes. La comunicación puede ser cambiada por la que se desee, como WiFi, Bluetooth, etc., modificando las funciones del driver de comunicación.

## Estructura del Proyecto

La estructura del proyecto es la siguiente:

Integracion-de-sensores---Microcontrolador/ 
├── include/  <br>
    ├── Drivers/ <br>
        ├── driver_comunicacion.h <br>
        ├── driver_nuevo_sensor.h <br>
        ├── driver_sensor_optico.h <br>
        ├── driver_sensor_ultra_sonido.h <br>
        ├── driver_servomotor.h <br>
    ├── UserDefines/ <br>
        ├── comandos.h  <br>
    ├── agente_comandos.h <br>
    ├── rutinas_atencion.h <br>
├── src/ <br>
    ├── Drivers/ <br>
        ├── driver_nuevo_sensor.cpp <br>
        ├── driver_sensor_optico.cpp <br>
        ├── driver_sensor_ultra_sonido.cpp <br>
        ├── driver_servomotor.cpp <br>
    ├── agente_comandos.cpp<br>
    ├── main.cpp  <br>
    ├── rutinas_atencion.cpp <br>

## Pasos para Agregar un Nuevo Sensor o Actuador

1. **Crear los drivers del sensor o actuador en la carpeta Drivers**
    * Requisitos:
        + Método `obj.update()`
            ```cpp
            Ejemplo: void sensor::update() {
                unsigned long currentTime;
                currentTime = millis();
                if (currentTime - lastMeasurementTime >= TIME_ACT) {
                    lastMeasurementTime = currentTime;
                    
                    // Actualizar información del sensor
                }
            }
            ```
        + Definir `TIME_ACT` como el tiempo entre cada actualización en ms.
        + Métodos "get" y "set" del sensor/actuador.

2. **Instanciar el objeto que interactúa con el hardware (driver) en el archivo [main.cpp](http://_vscodecontentref_/3).**

3. **Definir los comandos para interactuar con el objeto en el archivo `comandos.h` en la carpeta `UserDefines`.**

4. **Definir las rutinas de atención para los comandos definidos en el paso 3 en el archivo `rutinas_atencion.cpp`.**

5. **Agregar la siguiente línea en la función [asignar_rutinas_atencion()](http://_vscodecontentref_/4) en el archivo `rutinas_atencion.cpp`:**
    ```cpp
    AgenteComandos::asignarFuncion(Comando::NOMBRE_COMANDO, NOMBRE_RUTINA);
    ```

6. **Agregar el método `obj.update()` para actualizar el sensor/actuador en la función [update()](http://_vscodecontentref_/5) en el archivo `rutinas_atencion.cpp`.**

## Pasos para Generar Nuevos Comandos

1. **Definir el comando**: En el archivo `comandos.h`, agregar el nuevo comando en el enum `Comando`.

    ```cpp
    // filepath: /path/to/comandos.h
    enum Comando {
        // Comandos existentes
        RX_NUEVO_COMANDO, // Nuevo comando
    };
    ```

2. **Asignar la trama del comando**: En el archivo `agente_comandos.cpp`, asignar la trama asociada al nuevo comando en el vector `lista_de_comandos_RX` o `lista_de_comandos_TX`.

    ```cpp
    // filepath: /path/to/agente_comandos.cpp
    Comandos_t AgenteComandos::lista_de_comandos_RX[] = {
        // Comandos existentes
        {RX_NUEVO_COMANDO, "NUEVO", nullptr, false}, // Nuevo comando
    };
    ```

3. **Asignar la función del comando**: En el archivo `rutinas_atencion.h`, declarar la función de atención para el nuevo comando.

    ```cpp
    // filepath: /path/to/rutinas_atencion.h
    void nuevo_comando_atencion(int *arg);
    ```

4. **Implementar la función del comando**: En el archivo `rutinas_atencion.cpp`, implementar la función de atención para el nuevo comando.

    ```cpp
    // filepath: /path/to/rutinas_atencion.cpp
    void nuevo_comando_atencion(int *arg) {
        // Código para atender el nuevo comando
    }
    ```

5. **Asignar la función al comando**: En el archivo `agente_comandos.cpp`, asignar la función de atención al nuevo comando en el método [asignar_rutinas_atencion](http://_vscodecontentref_/6).

    ```cpp
    // filepath: /path/to/agente_comandos.cpp
    void asignar_rutinas_atencion() {
        // Asignaciones existentes
        AgenteComandos::asignarFuncion(RX_NUEVO_COMANDO, nuevo_comando_atencion);
    }
    ```

## Información del Autor

Este proyecto forma parte del proyecto de investigación de la UTN PID "Integración de sensores para ambientes industriales".

Para más información sobre el autor, puedes visitar su perfil de LinkedIn: [Guido Glorioso](https://www.linkedin.com/in/guido-glorioso).
