/**
* @file myapp_main_controller.cpp
* @brief Implementaciones de la API de main controller
* @author Nicolás Almaraz
* @version rev 1.0
* @date 28/06/2024
*/

//====================================================================
// Dependencias
//====================================================================

#include <stdbool.h>

#include "mbed.h"

#include "myapp_main_controller.h"
#include "myapp_uart.h"
#include "myapp_pulsadores.h"
#include "myapp_leds.h"

//====================================================================
// Funciones privadas API Main Controller
//==================================================================== 

/**
 * @brief Ejecuta los mensajes que se solicitan desde la UART
 * @param msg Mensaje a ejecutar
 */
static void main_controller_ejecutar_msg_uart(msg_uart_t msg) {
    switch(msg.type) {
        default:
            break;

        case SET_LEDS:
            //Le digo a la api de leds que cambie de color
            ledsApi_setLeds(msg.data);
            break;

        case GET_CONFIG:
            //Le pido a la API de leds la config actual
            rgb_color_t color = ledsApi_getLedsConfig();

            //Retorno via uart la config
            uartApi_sendConfig(color);
            break;
    }
}

/**
 * @brief Se encarga de verificar si hay un flanco ascendente en alguno de los pulsadores y cambia los estados de los leds
 */
static void main_controller_ejecutar_msg_pulsadores(estado_pulsadores_t pulsadores, rgb_color_t current_config) {
    static bool f_primera_ejecucion = true;
    static estado_pulsadores_t estado_anterior;

    //Primera ejecucion
    if(f_primera_ejecucion) {
        f_primera_ejecucion = false;
        estado_anterior = pulsadoresApi_getPulsadores();
        return;
    }

    //Me fijo si hay algún flanco positivo
    bool f_rising_edge_red = (estado_anterior.pulsador_red == false && pulsadores.pulsador_red == true);
    bool f_rising_edge_green = (estado_anterior.pulsador_green == false && pulsadores.pulsador_green == true);
    bool f_rising_edge_blue = (estado_anterior.pulsador_blue == false && pulsadores.pulsador_blue == true);
    
    //Guardo estado anterior
    estado_anterior = pulsadores;

    if(!f_rising_edge_red && !f_rising_edge_green && !f_rising_edge_blue)
        return;

    //Leo la configuración actual
    bool config_bin[3] = {0,0,0};
    if(current_config.red==1)
        config_bin[0] = 1;
    if(current_config.green==1)
        config_bin[1] = 1;
    if(current_config.blue==1)
        config_bin[2] = 1;

    //Cargo cambios
    rgb_color_t new_color;
    new_color.red = (uint8_t) (config_bin[0] + f_rising_edge_red)%2;
    new_color.green = (uint8_t) (config_bin[1] + f_rising_edge_green)%2;
    new_color.blue = (uint8_t) (config_bin[2] + f_rising_edge_blue)%2;
    ledsApi_setLeds(new_color);
}

//====================================================================
// Funciones Públicas API Main Controller
//==================================================================== 

/**
 * @brief Inicializa todos los perifericos y recursos de hardware
 */
void mainControllerApi_init() {
    uartApi_init();
    ledsApi_init();
    pulsadoresApi_init();
    uartApi_sendUart("Init Main Controller\r\n");
}

/**
 * @brief Contiene la aplicacion
 */
void mainControllerApi_loop() {
    //Leo la Uart y ejecuto mensajes
    msg_uart_t msg;
    msg = uartApi_mde_recepcion();
    main_controller_ejecutar_msg_uart(msg);

    //Leo pulsadores y me fijo si hay que modificar algo
    rgb_color_t current_config = ledsApi_getLedsConfig();
    estado_pulsadores_t pulsadores = pulsadoresApi_getPulsadores();
    main_controller_ejecutar_msg_pulsadores(pulsadores, current_config);
}
