/**
* @file myapp_uart.cpp
* @brief Implementaciones de la API de comunicación UART
* @author Nicolás Almaraz
* @version rev 1.0
* @date 28/06/2024
*/

// ==================== Dependencias

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "mbed.h"

#include "myapp_leds.h"
#include "myapp_uart.h"

//====================================================================
// Variables Globales Privadas UART
//==================================================================== 

/**
* @brief Objeto handler de la UART
*/
static UnbufferedSerial g_uart_handler(GPIO_UART_TX, GPIO_UART_RX);

//====================================================================
// Funciones Privadas UART
//==================================================================== 

/**
* @brief Lee la UART y retorna el valor recuperado (funcion bloquante)
* @retval Retorna el valor leido de la UART
*/
static uint8_t uartApi_leerUart() {
    uint8_t data;
    g_uart_handler.read(&data, 1);
    return data;
}

/**
* @brief Se fija si hay un nuevo dato disponible que leer de la UART
* @retval Retorna 1 si hay información nueva, sino retorna 0
*/
static bool uartApi_hay_nuevo_mensaje() {
    return g_uart_handler.readable();
}

/**
* @brief Interpreta el valor del símbolo recibido
* @retval Retorna true si llega un '1' y sino retorna false
*/
static bool uartApi_getValue(const char c) {
    bool retval = false;
    if(c=='1')
        retval = true;
    return retval;
}

//====================================================================
// Funciones publicas de la UART
//==================================================================== 

/**
* @brief Inicializa la UART con la configuración de los "defines" de la API
*/
void uartApi_init() {
    g_uart_handler.baud(UART_BAUDRATE);
    g_uart_handler.format(UART_DATA_SIZE, UART_SERIAL_BASE, UART_STOP_BIT);
    
    uartApi_sendUart("Init API UART\r\n");
}

/**
* @brief Interpreta los mensajes recibidos por UART
* @warning Tener en cuenta que cuando se espera una palabra binaria, todo lo que sea distinto al caracter ASCII '1' será considerado como '0'.
* @retval Retorna el comando recibido por UART
*/
msg_uart_t uartApi_mde_recepcion() {
    static estado_mde_uart_t estado = ESTADO_IDLE;
    static msg_uart_t mensaje_aux;
    static rgb_color_t color_aux;
    
    //Creo mensaje de retorno
    msg_uart_t ret_msg;
    ret_msg.type = NO_UART_MSG;

    //Si no hay nada que leer retorno idle
    if( !uartApi_hay_nuevo_mensaje() )
        return ret_msg;

    //Leo UART
    uint8_t c = uartApi_leerUart();
    c = toupper(c);
    
    //Interpreto datos recibidos con mde
    
    //Transiciones comunes a todos los estados
    if(c=='G') {
        mensaje_aux.type = GET_CONFIG;
        estado = ESTADO_CHECK_OK;
        return ret_msg;
    }
    if(c=='S') {
        mensaje_aux.type = SET_LEDS;
        estado = ESTADO_NUM_R;
        return ret_msg; 
    }

    //Maquina de estados
    switch(estado) {
        default:
        case ESTADO_IDLE:
            break;

        case ESTADO_NUM_R:
            color_aux.red = uartApi_getValue(c);
            estado = ESTADO_NUM_G;
            break;

        case ESTADO_NUM_G:
            color_aux.green = uartApi_getValue(c);
            estado = ESTADO_NUM_B;
            break;

        case ESTADO_NUM_B:
            color_aux.blue = uartApi_getValue(c); 
            estado = ESTADO_CHECK_OK;
            mensaje_aux.data = color_aux;
            break;

        case ESTADO_CHECK_OK:
            if(c=='$') {
                ret_msg = mensaje_aux;
            }
            estado = ESTADO_IDLE;
            break;        
    }
    return ret_msg;
}

/**
* @brief Envia la configuracion actual por uart
* @param color Configuración de leds a enviar
*/
void uartApi_sendConfig(rgb_color_t color) {
    char msg[4];
    sprintf(msg, "%d%d%d",(int)color.red, (int)color.green, (int)color.blue);
    uartApi_sendUart(msg);
}

/**
* @brief Envia un mensaje por UART
* @param str String con el mensaje a enviar
*/
void uartApi_sendUart(const char* str) {
    g_uart_handler.write(str, strlen(str)); //Al paraecer esta linea la marca el keil studio cloud pero el compilador no tiene drama :) 
}