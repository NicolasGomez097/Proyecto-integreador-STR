from SocketClient import SocketClient
from time import sleep


HOST = '181.90.60.24'
PORT = 5678

def printMsg(msg):
    print(msg)

def main():
    
    socket = SocketClient(HOST, PORT, 'UDP')
    socket.send('torque,0')
    sleep(3)

    for i in range(100):
        socket.send('torque,'+str(i))
        sleep(0.1)
    
    for i in range(100):
        socket.send('torque,'+str(100 - i))
        sleep(0.1)

    socket.send('torque,0')
    socket.close()

if __name__ == '__main__':
    main()
