#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H
class ServerSocket {
    public:
        void initSocketServer();
        int acceptConnection();
        std::string readSocket(int client);
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