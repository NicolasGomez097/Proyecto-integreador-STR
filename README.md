# Proyecto-integreador-STR
Proyecto para el control de un motor simulado.

## Grupo
* Giuliano Alessandro
* Gomez Nicolas

### Utilizacion
* Ejecutar dentro de la carpeta cpp `make pid_server`.
* Ejecutar el archivo `server` generado con el comando anterior.
* En otra consola ejecutar dentro de la carpeta python el archivo `main3_gui.py`.
* utilizar el deslizador para determinar la velocidad deseada del motor simulado, kp, ki y kd.

### Clases Python
* **MotorControl**: Se encarga del deslizador y mostrar la velocidad.
* **Graph**: Clase que se encarga del manejo del grafico temporal.

### Clases C++
* **rtc**: se encarga de gestionar la configuracion del rtc.
* **PID**: se encarga de realizar todos los controles para obtener la velocidad deseada.
* **ServerTCP**: se encarga de gestionar las conexiones, de enviar y recibir datos para facilitar la utilizacion de sockets.
* **Motor**: se encarga de la simulacion del motor.