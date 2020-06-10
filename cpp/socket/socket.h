#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H
class ServerTCP {
    public:
        void initSocketServer();
        int acceptConnection();
        char* readSocket(int client);
        void sendMsg(const char* data);
        int getFD();
        int getClientFD();
        void closeSocket();

    private:
        int server_fd;
        int new_socket;
        int valread;
};
#endif