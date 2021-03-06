#include <unistd.h> 
#include <sys/socket.h> 
#include <string.h> 
#include <string> 
#include <arpa/inet.h> 

#include "ClientSocket.h"

#define THIS this->
struct sockaddr_in servaddr; 
 
void ClientSocket::initConection(char *host, int port, bool useTCP) {
    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_addr.s_addr = inet_addr(host); 
    servaddr.sin_port = htons(port); 
    servaddr.sin_family = AF_INET; 

    // Creando el socket   
    if(useTCP) {
        if ((THIS client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
        { 
            perror("socket failed"); 
            exit(EXIT_FAILURE); 
        }
    }else {
        if ((THIS client_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0) 
        { 
            perror("socket failed"); 
            exit(EXIT_FAILURE); 
        }
    }

    // Realizando la conexion
    if(connect(THIS client_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
    { 
        printf("\n Error : Connect Failed \n"); 
        exit(0); 
    } 
}

std::string ClientSocket::readSocket(int client) {
    char buffer[1024]; 
    THIS valread = read(client , buffer, 1024); 
    std::string aux = buffer;
    return aux;
}

void ClientSocket::sendMsg(const char* data) {
    sendto(THIS client_fd, data, strlen(data), NULL, (struct sockaddr*)NULL, sizeof(servaddr));
}

int ClientSocket::getFD() {
    return THIS client_fd;
}

int ClientSocket::getClientFD() {
    return THIS client_fd;
}

void ClientSocket::closeSocket() {
    if(THIS client_fd != -1){
        close(client_fd);
        client_fd = -1;
    }  
}
