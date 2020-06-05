#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H
class ServerTCP {
    public:
        void initSocketServer();
        char* readSocket();
        void sendMsg(char* data);
        int getFD();

    private:
        int server_fd;
        int new_socket;
        int valread;
};
#endif