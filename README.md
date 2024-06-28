# Controlador de Tira LED RGB


## TP1 - Curso Sistemas Embebidos
Alumno: Nicolás Almaraz
Profesores: 
- Ariel Lutenberg
- Segio Caprile
- Juan Manuel Reta
- Eduardo Filomena

## Estructura de archivos fuente
/sources
|-- main.cpp
|-- uart
| |-- myapp_uart.h
| |-- myapp_uart.c
|-- pulsadores
| |-- myapp_pulsadores.h
| |-- myapp_pulsadores.c
|-- leds
| |-- myapp_leds.h
| |-- myapp_leds.c
|-- main_controller
|-- myapp_main_controller.h
|-- myapp_main_controller.c

## Descripcion
En este trabajo presento un controlador de luces LED RGB que tiene una interfaz de usuario UART o mediante tres pulsadores.
La idea es que permita establecer estados binarios (encendido / apagado) para cada LED.


## Desarrollos a futuro
Permitir manejar los leds con señales PWM para así tener un mayor control sobre el color de la tira.
