/**
* @file myapp_pulsadores.h
* @brief API de pulsadores
* @author Nicolás Almaraz
* @version rev 1.0
* @date 28/06/2024
*
* Esta API se encarga de leer los tres pulsadores eliminando los rebotes y glitches de cada uno de ellos.
* Para ello cuenta con una función de "lectura validada":
* estado_pulsadores_t pulsadoresApi_getPulsadores();
*
* Cabe destacar que por hardware los pulsadores en estado IDLE hacen que la placa reciba 0V y cuando son presionados 3.3V
*/

#ifndef MYAPP_PULSADORES_H
#define MYAPP_PULSADORES_H

// ==================== Dependencias

#include "mbed.h"

#include "myapp_leds.h"

//====================================================================
// Defines API Pulsadores
//==================================================================== 

#define TIEMPO_ANTIRREBOTE_MS 50        //< Tiempo de seguridad antirrebote y antiglithces
#define GPIO_PULSADOR_RED D5            //< GPIO pulsador que controla led R
#define GPIO_PULSADOR_GREEN D6          //< GPIO pulsador que controla led G
#define GPIO_PULSADOR_BLUE D7           //< GPIO pulsador que controla led B
#define RED_RESISTOR_MODE PullDown      //< Uso resistencia de Pull Down Interna 
#define GREEN_RESISTOR_MODE PullDown    //< Uso resistencia de Pull Down Interna 
#define BLUE_RESISTOR_MODE PullDown     //< Uso resistencia de Pull Down Interna 

//====================================================================
// Tipos de datos API Pulsadores
//==================================================================== 

/**
* @brief Estados de la MdE de pulsadores
*/
typedef enum {
    ESTABLE_BAJO=0,
    ESTABLE_ALTO,
    CHEQUEANDO_TRANSICION,
}estado_mde_pulsador_t;

/**
* @brief Tipo de dato de función que lee un gpio y retorna un bool
*/
typedef bool (*gpio_read_func_t)();

//====================================================================
// Estructuras de la API Pulsaores
//==================================================================== 

/**
* @brief Almacena los estados de los pulsadores
*/
typedef struct {
    bool pulsador_red;
    bool pulsador_green;
    bool pulsador_blue;
} estado_pulsadores_t;

/**
* @brief Almacena las variables necesarias para la mde de pulsadores que elimina rebote y glitches
*/
typedef struct {
    estado_mde_pulsador_t estado; /*< Estado de la mde*/
    bool mem_pulsador;            /*< Ultimo estado estable del pulsador*/
} arg_mde_pulsadores_t;

//====================================================================
// Funciones Públicas API Pulsadores
//==================================================================== 

/**
*@brief: Inicializa a los GPIO de los pulsadores
*/
void pulsadoresApi_init();

/**
* @brief: Retorna el valor de los pulsadores sin rebote ni glitches
* @warning Bloquea TIEMPO_ANTIRREBOTE_MS ms para verificar transicion
* @retval: Valor de los pulsadores sin rebote ni glitches
*/
estado_pulsadores_t pulsadoresApi_getPulsadores();

#endif