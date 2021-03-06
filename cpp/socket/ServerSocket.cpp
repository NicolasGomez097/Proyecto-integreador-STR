// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <string> 
#include "ServerSocket.h"

#define DEFAULT_PORT 8080 
#define THIS this->

struct sockaddr_in address; 
int addrlen = sizeof(address); 

void ServerSocket::initSocketServer() {
    if ((THIS server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 

    int opt = 1;        
    if (setsockopt(THIS server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    }

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( DEFAULT_PORT ); 
       
    if (bind(THIS server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(THIS server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    }  
}

int ServerSocket::acceptConnection() {
    if ((
            THIS client_fd = accept(
            THIS server_fd, (struct sockaddr *)&address,  
            (socklen_t*)&addrlen)
        ) < 0
    ){ 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    return THIS client_fd;
}

std::string ServerSocket::readSocket(int client) {
    char buffer[1024] = {0}; 
    THIS valread = read(client , buffer, 1024); 
    std::string aux = buffer;
    return aux;
}

void ServerSocket::sendMsg(const char* data) {
    send(THIS client_fd , data , strlen(data) , 0 ); 
}

int ServerSocket::getFD() {
    return THIS server_fd;
}

int ServerSocket::getClientFD() {
    return THIS client_fd;
}

void ServerSocket::closeSocket() {
    close(THIS server_fd);
    if(THIS server_fd != -1){
        close(THIS server_fd);
        THIS server_fd = -1;
    }  
    if(THIS client_fd != -1){
        close(THIS client_fd);
        THIS client_fd = -1;
    }  
}
