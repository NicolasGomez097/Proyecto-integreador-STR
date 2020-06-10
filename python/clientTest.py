from SocketClient import SocketClient
from time import sleep


HOST = '127.0.0.1'
PORT = 8080

def printMsg(msg):
    print(msg)

def main():
    socket = SocketClient(HOST, PORT)
    socket.send('Hello from PYTHON3')
    socket.set_on_input(printMsg)
    while(True):
        pass
    socket.close()

if __name__ == '__main__':
    main()
