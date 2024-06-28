# Controlador de Tira LED RGB

## TP1 - Curso Sistemas Embebidos
### Alumno:
Nicolás Almaraz
### Profesores: 
- Ariel Lutenberg
- Segio Caprile
- Juan Manuel Reta
- Eduardo Filomena

## Video del Funcionamiento
[![Título del Video](https://img.youtube.com/vi/WTMURiHmbko/0.jpg)](https://www.youtube.com/watch?v=WTMURiHmbko)

## Estructura de archivos fuente
```
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
| |-- myapp_main_controller.h
| |-- myapp_main_controller.c
```

## Documentación
En la carpeta doc está la documentación generada con Doxygen del proyecto completo
Para acceder a ella ir al archivo index.html

## Objetivo:
Remodelar mí lámpara basada en una tira LED RGB.

## Descripcion
En mi cuarto tengo una lámpara casera que hice basándome en una vieja tira led RGB de 24V, tal como se muestr en la figura 1:

#### Figura 1:
![image](https://github.com/NicolasTobiasAlmaraz/tp1/assets/128346566/2dd5ba07-9623-439f-9620-f8e874b56752)

Tira led que utilizo como lámpara

La tira LED está conectada de tal manera que la alimentación de 24V (figura 2) va conectada directamente a las entradas R, G y B mediante un conector plug (figura 3). En consecuencia por cómo están hechas las conexiones funciona como una tira LED de luz blanca únicamente (no tiene un controlador, está en modo “color fijo”):

#### Figura 2:
![image](https://github.com/NicolasTobiasAlmaraz/tp1/assets/128346566/495da282-f0f5-47d2-a2f3-82cf2e8378de)

Fuente 24V DC

#### Figura 3:
![image](https://github.com/NicolasTobiasAlmaraz/tp1/assets/128346566/ed7f92ff-8842-4667-a142-fabd5e8682cc)

Entrada de alimentación de la tira LED. Tal como entra la línea de 24V alimenta las entradas R, G y B de la tira -> Queda luz blanca

#### Funcionamiento:
Entonces para este trabajo práctico propongo hacer un bloque controlador que esté entre la alimentación y las líneas de control de los leds R, G y B (Figura 4). Este controlador va a permitir cambiar el color formado. El esquema de funcionamiento sería el siguiente: 


#### Estado de reset:
El sistema inicia seteado como luz blanca 

### API LEDS:
Esta API se encarga de cargar la configuración a los leds. Para ello recibe como parámetro una palabra binaria de 3 bits XXX correspondientes al estado de los leds R, G y B respectivamente.
#### API UART:
Esta API se encarga de verificar si hay nuevos mensajes de UART y tomar una acción en consecuencia. Dichos mensajes pueden ser los siguientes:
##### Comando “Srgb”:
La “S” representa set y “rgb” es un número binario de 3 bits. Esta palabra se la enviaré a la API LEDS para que ajuste su nueva configuración. Cabe destacar que 0 significa apagado y 1 encendido
##### Comando “G”:
Si se recibe por UART una “G” significa que desde la PC nos están pidiendo que indiquemos el estado de los leds. Por lo tanto, le tenemos que pedir a la API LEDS que nos indique cuál es su estado actual y este valor se lo re-enviaremos a la PC. Entonces respondemos “rgb” (palabra binaria de 3 bits).
### API PULSADORES:
Se tienen 3 pulsadores para control manual:
- R: Cambia el estado del led rojo
- G: Cambia el estado del led verde
- B: Cambia el estado del led azul

Por ejemplo si tenía la configuración 010 y presiono el pulsador R, ahora voy a tener 110 Entonces esta API lee los pulsadores y le avisa a la API LEDS si tiene que modificar su estado de funcionamiento.

## Plataforma de desarrollo:
NUCLEO-F401RE

## Periféricos a utilizar:
3 DIGITAL IN: Pulsadores de cada color
3 DIGITAL OUT: Salidas para cada color
UART: Se utiliza para setear un estado de las luces y monitorear estado actual

## Diagrama en bloques del Hardware:
![image](https://github.com/NicolasTobiasAlmaraz/tp1/assets/128346566/bdb6d0ae-886c-49ea-88fa-40d11698e9b4)


## Desarrollos a futuro
Permitir manejar los leds con señales PWM para así tener un mayor control sobre el color de la tira.

