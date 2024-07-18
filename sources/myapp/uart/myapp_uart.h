/**
* @file myapp_uart.h
* @brief API que controla la comunicación UART
* @author Nicolás Almaraz
* @version rev 1.0
* @date 28/06/2024
*
* Esta API se encarga de proveer las funcionalidades de recepción de datos y escritura por UART.
* Para ello contamos con las funciones:
*   - mde_msg_t uartApi_mde_recepcion(): Interpreta los datos recibidos y retorna la solicitud interpretada
*   - void uartApi_sendConfig(rgb_color_t color): Envia la configuración de los leds indicada
*   - void uartApi_sendUart(const char* str): Envia mensaje de debug o reporte
*/

#ifndef MYAPP_UART_H
#define MYAPP_UART_H

// ==================== Dependencias

#include <stdbool.h>

#include "mbed.h"
#include <UnbufferedSerial.h>

#include "myapp_leds.h"

//====================================================================
// Defines UART
//==================================================================== 

#define GPIO_UART_TX USBTX                  ///< GPIO del microcontrolador de Tx
#define GPIO_UART_RX USBRX                  ///< GPIO del microcontrolador de Rx
#define UART_BAUDRATE 115200                ///< Baudrate de 115200 bauds
#define UART_DATA_SIZE 8                    ///< 8 bits de datos 
#define UART_SERIAL_BASE SerialBase::None   ///< Sin paridad
#define UART_STOP_BIT 1                     ///< 1 bit de stop

//====================================================================
// Tipos de datos UART
//==================================================================== 

/**
* @brief Posibles tipos de mensajes que pueden enviar por UART
*/
typedef enum {
    NO_UART_MSG=0,  ///< No hay ningún mensaje
    SET_LEDS,       ///< Hay que modificar los leds
    GET_CONFIG,     ///< Pedido de configuracion
} request_uart_t;

/**
* @brief Estados mde recepcion UART que interpretan solicitud
*/
typedef enum {
    ESTADO_IDLE=0,
    ESTADO_NUM_R,
    ESTADO_NUM_G,
    ESTADO_NUM_B,
    ESTADO_CHECK_OK,
} estado_mde_uart_t;

//====================================================================
// Estructuras de la API UART
//==================================================================== 

/**
* @brief: Mensaje que se recibe por UART
*/
typedef struct {
    request_uart_t type;    /**< Tipo de solicitud **/
    rgb_color_t data;       /**< Argumento auxiliar **/
} msg_uart_t;


//====================================================================
// Funciones Públicas
//==================================================================== 

/**
* @brief Inicializa la UART con la configuración de los "defines" de la API
*/
void uartApi_init();

/**
* @brief Interpreta los mensajes recibidos por UART
* @warning Tener en cuenta que cuando se espera una palabra binaria, todo lo que sea distinto al caracter ASCII '1' será considerado como '0'.
* @retval Retorna el comando recibido por UART
*/
msg_uart_t uartApi_mde_recepcion();

/**
* @brief Envia la configuracion actual por uart
* @param color Configuración de leds a enviar
*/
void uartApi_sendConfig(rgb_color_t color);

/**
* @brief Envia un mensaje por Uart
* @param str String a enviar
*/
void uartApi_sendUart(const char* str);

#endif