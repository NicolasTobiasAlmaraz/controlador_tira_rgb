/**
* @file main.cpp
* @brief Punto de entrada
* @author Nicolás Almaraz
* @version rev 1.0
* @date 28/06/2024
*
* Curso Sistemas Embebidos - TP1
* Esta aplicación permite el control de una tira LED RGB. Para setear colores
* cuenta con una interfaz UART y a través de pulsadores.
* Por otro lado, por UART se le puede consultar cuál es la configuración actual.
* Para todo esto hace uso de las APIs:
*   - Leds
*   - UART
*   - Pulsadores
*   - Main Controller
*/

//====================================================================
// Dependencias
//====================================================================

 #include "myapp_main_controller.h"

//====================================================================
// Main Loop
//====================================================================

/**
* @brief: Inicializa perifericos y corre la app general
*/
int main() {
    mainControllerApi_init();
    while (true) {
        mainControllerApi_loop();
    }
}
