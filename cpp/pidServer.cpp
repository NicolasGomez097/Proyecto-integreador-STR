#include <stdio.h>
#include <sys/select.h>
#include <string>
#include <vector>
#include <unistd.h>

#include "rtc/rtc.h"
#include "pid/PID.h"
#include "socket/socket.h"
#include "socket/socketClient.h"
#include "motor/motor.h"

#define MOTOR_MAX_SPEED 210.0
#define MOTOR_SENSITIVITY 7.0/255.0
#define MOTOR_UPDATE_TIMES 100
//#define MOTOR_UPDATE_TIMES 10

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

vector<string> substring(string text) {
    vector<string> strings;
    string aux = "";
    for(int i = 0; i < text.length(); i++) {
        if(text[i] == ',') {
            strings.push_back(aux);
            aux = "";
        } else {
            aux.push_back(text[i]);
        }
    }
    if(aux.compare("") != 0) {
        strings.push_back(aux);
    }
    return strings;
}

string processRequest(string request, PID& pid);

int main() {
    // Definicion variables.
    int cant = 30;
    int i, tick_fd, res;
    int max_fd;
    int count = 0;
    int client_fd = 0;
    float actualSpeed;
    float actualTorque;
    fd_set readfds;

    PID pid(100.0/40.0, 0.0, 0.0);
    pid.setDt(1000.0 / MOTOR_UPDATE_TIMES);
    Motor motor(MOTOR_MAX_SPEED, MOTOR_SENSITIVITY);
    ServerTCP server;
    //ClientSocket motorSocket;

    struct timeval timeout = {1, 0};
    tick_fd = rtc_init(MOTOR_UPDATE_TIMES);

    // inicializacion socket TCP
    server.initSocketServer();
    
    // Conexion con el motor UDP
    /*char *host = "181.90.60.24";
    motorSocket.initConection(host,5678,false);
    motorSocket.sendMsg("torque,0");
    usleep(3000000);*/

    printf("Server FD: %d\n", server.getFD());
    fflush(stdout); 

    while (true)
    {
        // Inicializando el SET para el select
        FD_ZERO(&readfds);
        FD_SET(tick_fd, &readfds);
        FD_SET(server.getFD(), &readfds);
        max_fd = server.getFD() + 1;
        if(client_fd != 0) {
            FD_SET(client_fd, &readfds); 
            max_fd = client_fd + 1; 
        }

        res = select(max_fd, &readfds, NULL, NULL, NULL);
 
        if(FD_ISSET(tick_fd, &readfds)) {
            actualSpeed = motor.getSpeed();
            pid.setActualSpeed(actualSpeed);
            actualTorque = pid.calculateTorque();
            motor.setTorque(actualTorque);
            /*string msg = "torque,";
            msg.append(to_string(count));
            count++;
            motorSocket.sendMsg(msg.c_str());
            msg.append("\n");
            printf(msg.c_str());
            fflush(stdout); */
            rtc_tick();
        }
        if (FD_ISSET(server.getFD(), &readfds)) {
            client_fd = server.acceptConnection();
            string msg = server.readSocket(client_fd);
            string response = processRequest(msg, pid);     
            
            server.sendMsg(response.c_str());
        }
        if (FD_ISSET(client_fd, &readfds)) {
            string msg = server.readSocket(client_fd);
            string response = processRequest(msg, pid);            
            server.sendMsg(response.c_str());
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
