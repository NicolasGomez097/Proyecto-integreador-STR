#include <stdio.h>
#include <sys/select.h>
#include <string>
#include <vector>
#include <unistd.h>

#include "rtc/rtc.h"
#include "pid/PID.h"
#include "socket/ServerSocket.h"
#include "motor/motor_udp.h"
#include "utils/utils.h"
#include "select/SelectManager.h"

// Definiciones para el motor simulado.
//#define MOTOR_MAX_SPEED 210.0
//#define MOTOR_SENSITIVITY 7.0/255.0

// Cantidad de actualizaciones por segundo con el motor.
#define MOTOR_UPDATE_TIMES 64

// Definiciones para la conexion con el motor remoto.
#define MOTOR_HOST "181.90.115.214"
#define MOTOR_PORT 5678
#define MOTOR_IS_TCP false

using namespace std;
/*
    Protocolo de comunicacion
 El servidor PID espera que se envie un paquete TCP con
el contenido en formato texto plano y con las siguiente
informacion separado por ',':
    Velocidad deseada,Kp,Ki,Kd.
 
 Luego manda una respuesta con el mismo formato que contiene
las siguiente informacion:
    velocidad actual,torque actual.
*/
string processRequest(string request, PID& pid);

int main() {
    // Definicion variables.
    int cant = 30;
    int i, tick_fd, res;
    int max_fd;
    int client_fd = 0;
    float actualSpeed = 0;
    float actualTorque = 0;
    fd_set readfds;
    vector<int> fd_set;
   
    PID pid(100.0 / 40.0, 0.0, 0.0);
    pid.setDt(1.0 / MOTOR_UPDATE_TIMES);

    Motor motor(MOTOR_HOST, MOTOR_PORT, MOTOR_IS_TCP);

    ServerSocket server;

    SelectManager selectManager;

    // Configuracion RTC
    struct timeval timeout = {1, 0};
    tick_fd = rtc_init(MOTOR_UPDATE_TIMES);
    selectManager.addReadFD(tick_fd);

    // inicializacion socket TCP
    server.initSocketServer();
    selectManager.addReadFD(server.getFD());
    
    // Se agrega el FD del motor a la lista.
    selectManager.addReadFD(motor.getFD());

    printf("Se inicio el server\n");
    fflush(stdout); 

    while (true)
    {
        // Inicializando el SET para el select
        selectManager.waitForSelect();
 
        if(selectManager.wasTrigger(tick_fd)) {
            actualTorque = pid.calculateTorque();
            motor.setTorque(actualTorque);
            rtc_tick();
        }
        if (selectManager.wasTrigger(server.getFD())) {
            client_fd = server.acceptConnection();
            
            selectManager.addReadFD(client_fd);
            string msg = server.readSocket(client_fd);
            string response = processRequest(msg, pid);     
            
            server.sendMsg(response.c_str());
        }
        if (selectManager.wasTrigger(client_fd)) {
            string msg = server.readSocket(client_fd);
            string response = processRequest(msg, pid);            
            server.sendMsg(response.c_str());
        }
        if (selectManager.wasTrigger(motor.getFD())) {
            pid.setActualSpeed(motor.getSpeed());
        }
    }
    printf("\n");
    rtc_close();
    server.closeSocket();
}

string processRequest(string request, PID& pid) {
    vector<string> values = substring(request);

    pid.setDesiredSpeed(atof(values[0].c_str()));
    pid.setKp(atof(values[1].c_str()));
    pid.setKi(atof(values[2].c_str()));
    pid.setKd(atof(values[3].c_str()));

    string response = to_string(pid.getActualSpeed());
    response.push_back(',');
    response.append(to_string(pid.getTorque()));
    return response;
}
