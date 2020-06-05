import socket as skt
from gi.repository import GLib as glib
import select


class SocketClient():
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.socket = skt.socket(skt.AF_INET, skt.SOCK_STREAM)

    def connect(self):
        self.socket.connect((self.host, self.port))

    def wait_input(self):
        return self.socket.recv(1024).decode('UTF-8')

    def send(self, msg):
        self.socket.send(msg.encode())
