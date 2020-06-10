import socket as skt
from gi.repository import GLib
import select


class SocketClient():
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.socket = skt.socket(skt.AF_INET, skt.SOCK_STREAM)
        GLib.io_add_watch(self.socket.fileno(), GLib.IO_IN, self.on_read)
        self.socket.connect((self.host, self.port))
        self.socket.setblocking(False)
        self.callback_on_response = None

    def on_read(self, socket, condition):
        msg = self.socket.recv(1024).decode('UTF-8')
        if self.callback_on_response != None:
            self.callback_on_response(msg, *self.args)
        return True

    # Funcion para establecer el callback cuando se recive un dato.
    def set_on_input(self, callback, *args):
        self.callback_on_response = callback
        self.args = args
    
    def wait_input(self):
        return self.socket.recv(1024).decode('UTF-8')

    def send(self, msg):
        self.socket.send(msg.encode())
        
    def close(self):
        self.socket.close()
