// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include "socket.h"

#define PORT 8080 
#define THIS this->

struct sockaddr_in address; 
int opt = 1; 
int addrlen = sizeof(address); 
char buffer[1024] = {0}; 
const char *hello = "Hello from server";
 
void ServerTCP::initSocketServer() {
    // Creating socket file descriptor 
    if ((THIS server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(THIS server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
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

char* ServerTCP::readSocket() {
  if ((THIS new_socket = accept(THIS server_fd, (struct sockaddr *)&address,  
                      (socklen_t*)&addrlen))<0) 
  { 
      perror("accept"); 
      exit(EXIT_FAILURE); 
  } 
  THIS valread = read(THIS new_socket , buffer, 1024); 
  return buffer;
}

void ServerTCP::sendMsg(char* data) {
      send(THIS new_socket , data , strlen(data) , 0 ); 
}

int ServerTCP::getFD() {
    return THIS server_fd;
}
