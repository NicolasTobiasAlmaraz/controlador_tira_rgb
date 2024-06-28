/**
* @file myapp_leds.h
* @brief Esta API se encarga del manejo de leds
*
* Esta API se encarga del manejo de leds. Para eso cuenta con los métodos set de cada uno de los leds:
* void ledsApi_prenderRojo();
* void ledsApi_prenderVerde();
* void ledsApi_prenderAzul();
*
* Y también tiene una función para cargar una configuración
* void ledsApi_setLeds(rgb_leds_t);

* Por otro lado, cuenta con una función para obtener el estado de los leds
* rgb_leds_t ledsApi_getLedsConfig();
*
* Por hardware los Leds son activos por 0v
*/

#ifndef MYAPP_LEDS_H
#define MYAPP_LEDS_H

//====================================================================
// Dependencias
//====================================================================

#include "mbed.h"
#include <stdint.h>

//====================================================================
// Defines de la API LEDs
//====================================================================

#define GPIO_LED_RED D2     ///< GPIO del LED rojo
#define GPIO_LED_GREEN D3   ///< GPIO del LED verde
#define GPIO_LED_BLUE D4    ///< GPIO del LED azul

//====================================================================
// Estructuras de la API LEDs
//==================================================================== 

//TODO: Le puse uint8_t para poder escalarse en el futuro a un PWM almacenando el duty de cada color
/**
*@brief: Contiene un color rgb
*/
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} rgb_color_t;

//====================================================================
// Funciones públicas de la API LEDs
//==================================================================== 

/**
* @brief Inicializa GPIOs en color blanco
*/
void ledsApi_init();

/**
* @brief Retorna la configuracion actual de los leds
* @retval Configuracion actual de los leds
*/
rgb_color_t ledsApi_getLedsConfig();

/**
* @brief Setea un color rgb en los leds
* @param color Color a setear
*/
void ledsApi_setLeds(rgb_color_t color);

#endif
