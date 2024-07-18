/**
* @file myapp_pulsadores.cpp
* @brief Implementaciones de la API de pulsadores
* @author Nicolás Almaraz
* @version rev 1.0
* @date 28/06/2024
*/

// ==================== Dependencias
#include <stdbool.h>

#include "myapp_pulsadores.h"
#include "myapp_uart.h"

//==================================================================== 
// Variables globales API Pulsadores
//==================================================================== 

/**
* @brief Objeto handler del pulsador del led rojo
*/
static DigitalIn g_pulsador_red(GPIO_PULSADOR_RED);

/**
* @brief Objeto handler del pulsador del led verde
*/
static DigitalIn g_pulsador_green(GPIO_PULSADOR_GREEN);

/**
* @brief Objeto handler del pulsador del led azul
*/
static DigitalIn g_pulsador_blue(GPIO_PULSADOR_BLUE);

//====================================================================
// Funciones Privadas API Pulsadores
//==================================================================== 

/**
* @brief Lee el GPIO del pulsador del led rojo
* @retval Estado del pulsador, 1 presionado 0 suelto
*/
static bool pulsadoresApi_getPulsadorRed() {
    bool state = g_pulsador_red.read();
    return state;
}

/**
* @brief Lee el GPIO del pulsador del led verde
* @retval Estado del pulsador, 1 presionado 0 suelto
*/
static bool pulsadoresApi_getPulsadorGreen() {
    return g_pulsador_green.read();
}

/**
* @brief Lee el GPIO del pulsador del led azul
* @retval Estado del pulsador, 1 presionado 0 suelto
*/
static bool pulsadoresApi_getPulsadorBlue() {
    return g_pulsador_blue.read();
}

/**
* @brief Lee el pulsador y retorna un estado estable (sin glitches ni rebote). Esta funcion sirve para cualquier pulsador del sistem
* @param args Puntero a una estructura del tipo arg_mde_pulsadores_t que se reserve para ser utilizada con el pulsdaor en cuestion
* @param func_lectura Puntero a la función que se encarga de leer el GPIO del pulsador en cuestion, se espera que retorne true o false
* @param f_primera_ejecucion Flag para indicar si es la primera vez que se ejecuta
* @retval Estado estable
*/
static bool pulsadoresApi_leerPulsadorAntirrebote(arg_mde_pulsadores_t *args, gpio_read_func_t func_lectura) {
    estado_mde_pulsador_t estado = args->estado;
    bool mem_pulsador = args->mem_pulsador;

    //Leo Pulsador
    bool pulsador_actual = func_lectura();

    //Mde anti-rebote y anti-glitches
    switch(estado) {
        default:
            estado = ESTABLE_ALTO;
        case ESTABLE_ALTO:
            //Me fijo si cambia de estado
            if(pulsador_actual == false) {
                mem_pulsador = true;
                estado = CHEQUEANDO_TRANSICION;
            }
            break;
        case ESTABLE_BAJO:
            //Me fijo si cambia de estado
            if(pulsador_actual == true) {
                mem_pulsador = false;
                estado = CHEQUEANDO_TRANSICION;
            }
            break;
        case CHEQUEANDO_TRANSICION:
            //Espero tiempo
            thread_sleep_for(TIEMPO_ANTIRREBOTE_MS);
            
            //Valido lectura
            pulsador_actual =  func_lectura();
            
            //Glitches --> Vuelvo al estado estable anterior
            if(pulsador_actual==true && mem_pulsador==true) {
                estado = ESTABLE_ALTO;
                mem_pulsador = true;
            }
            if(pulsador_actual==false && mem_pulsador==false) {
                estado = ESTABLE_BAJO;
                mem_pulsador = false;
            }
    
            //Validado --> Cambio al nuevo estado estable
            if(pulsador_actual==true && mem_pulsador==false) {
                estado = ESTABLE_ALTO;
                mem_pulsador = true;
            }
            if(pulsador_actual==false && mem_pulsador==true) {
                estado = ESTABLE_BAJO;
                mem_pulsador = false;
            }
            break;
    }

    //Guardo argumentos y salgo
    args->estado = estado;
    args->mem_pulsador = mem_pulsador;

    //Retorno el estado estable
    return mem_pulsador;
}

//====================================================================
// Funciones Públicas API Pulsadores
//==================================================================== 

/**
* @brief: Inicializa a los GPIO de los pulsadores
*/
void pulsadoresApi_init() {
    g_pulsador_red.mode(RED_RESISTOR_MODE);
    g_pulsador_green.mode(GREEN_RESISTOR_MODE);
    g_pulsador_blue.mode(BLUE_RESISTOR_MODE);
    
    uartApi_sendUart("Init API pulsadores\r\n");    
}

/**
* @brief: Retorna el valor de los pulsadores sin rebote ni glitches
* @warning Bloquea TIEMPO_ANTIRREBOTE_MS ms para verificar transicion
* @retval: Valor de los pulsadores sin rebote ni glitches
*/
estado_pulsadores_t pulsadoresApi_getPulsadores() {
    //Creo variables de mis mde de pulsadores
    static arg_mde_pulsadores_t arg_red;
    static arg_mde_pulsadores_t arg_green;
    static arg_mde_pulsadores_t arg_blue;
    
    //Leo pulsadores
    estado_pulsadores_t estado_validado;
    estado_validado.pulsador_red = pulsadoresApi_leerPulsadorAntirrebote(&arg_red, &pulsadoresApi_getPulsadorRed);
    estado_validado.pulsador_green = pulsadoresApi_leerPulsadorAntirrebote(&arg_green,  &pulsadoresApi_getPulsadorGreen);
    estado_validado.pulsador_blue = pulsadoresApi_leerPulsadorAntirrebote(&arg_blue, &pulsadoresApi_getPulsadorBlue);
    
    //Retorno los estados de los pulsadores sin rebote ni glitches
    return estado_validado;
}
