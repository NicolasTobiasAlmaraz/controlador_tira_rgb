/**
* @file myapp_leds.cpp
* @brief Implementaciones de la API LEDs
* @author Nicolás Almaraz
* @version rev 1.0
* @date 28/06/2024
*/

//====================================================================
// Dependencias
//====================================================================

#include <stdbool.h>

#include "mbed.h"

#include "myapp_leds.h"
#include "myapp_uart.h"

//==================================================================== 
// Variables globales privadas API LEDs
//==================================================================== 

/**
* @brief: Objeto handler del led rojo
*/
static DigitalOut g_led_red(GPIO_LED_RED);
/**
* @brief: Objeto handler del led verde
*/
static DigitalOut g_led_green(GPIO_LED_GREEN);

/**
* @brief: Objeto handler del led azul
*/
static DigitalOut g_led_blue(GPIO_LED_BLUE);

/**
* @brief: Variable global que almacena la configuración actual de los LEDs
*/
static rgb_color_t g_config_leds;


//==================================================================== 
// Funciones privadas de la API LEDs
//==================================================================== 

/**
* @brief: Enciende el led rojo
*/
static void ledsApi_prenderRojo() {
    g_led_red = false;
    g_config_leds.red = 1;
}

/**
* @brief: Enciende el led verde
*/
static void ledsApi_prenderVerde() {
    g_led_green = false;
    g_config_leds.green = 1;
}

/**
* @brief: Enciende el led azul
*/
static void ledsApi_prenderAzul() {
    g_led_blue = false;
    g_config_leds.blue = 1;
}

/**
* @brief: Apaga el led rojo
*/
static void ledsApi_apagarRojo() {
    g_led_red = true;
    g_config_leds.red = 0;
}

/**
* @brief: Apaga el led verde
*/
static void ledsApi_apagarVerde() {
    g_led_green = true;
    g_config_leds.green = 0;
}

/**
* @brief: Apaga el led azul
*/
static void ledsApi_apagarAzul() {
    g_led_blue = true;
    g_config_leds.blue = 0;
}

//==================================================================== 
// Funciones publicas de la API LEDs
//==================================================================== 
 
/**
* @brief Setea un color rgb en los leds
* @param color Color a setear
*/
void ledsApi_setLeds(rgb_color_t color) {
    //Led rojo
    if(color.red != 0)
        ledsApi_prenderRojo();
    else
        ledsApi_apagarRojo();

    //Led verde
    if(color.green != 0)
        ledsApi_prenderVerde();
    else
        ledsApi_apagarVerde();

    //Led azul
    if(color.blue != 0)
        ledsApi_prenderAzul();
    else
        ledsApi_apagarAzul();
}

/**
* @brief Retorna la configuracion actual de los leds
* @retval configuracion actual de los leds
*/
rgb_color_t ledsApi_getLedsConfig() {
    return g_config_leds;
}

/**
* @brief Inicializa GPIOs en color blanco
*/
void ledsApi_init() {
    ledsApi_prenderRojo();
    ledsApi_prenderVerde();
    ledsApi_prenderAzul();

    uartApi_sendUart("Init API LEDS\r\n");
}
