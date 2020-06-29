# Proyecto-integreador-STR
Proyecto para el control de un motor remoto.

## Grupo
* Giuliano Alessandro.
* Gomez Nicolas.

## Utilizacion
#### C++
* Ejecutar el comando `make pid_server` para la conexión del motor UDP o `make pid_server_sim` para el motor simulado.
* Ejecutar el archivo `server` generado con el comando anterior.
#### Python
* Ejecutar el archivo `main3_gui.py`.
* utilizar el deslizador para determinar la velocidad deseada del motor, kp, ki y kd.

## Clases Python
* **MotorControl**: Se encarga de los deslizadores y de mostrar el valor de la velocidad y el torque actual.
* **Graph**: Clase que se encarga del manejo del grafico temporal para la representacion de la velocidad y el torque.

## Clases C++
* **rtc**: se encarga de gestionar la configuracion del rtc.
* **PID**: se encarga de realizar todos los controles y ajustes necesarios para obtener la velocidad deseada.
* **ServerScoket**: se encarga de gestionar las conexiones, de enviar y recibir datos para facilitar la utilizacion de sockets.
* **ClientScoket**: se encarga de gestionar las conexiones para enviar y recibir datos.
* **Motor**: se encarga de la simulacion del motor.
* **Motor_UDP**: se encarga de la comunicacion a travez de UDP con el motor remoto.
