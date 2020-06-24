#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H
class ClientSocket {
    public:
        void initConection(char *host, int port, bool useTCP);
        std::string readSocket(int client);
        void sendMsg(const char* data);
        int getFD();
        int getClientFD();
        void closeSocket();

    private:
        int client_fd;
        int valread;
};
#endif