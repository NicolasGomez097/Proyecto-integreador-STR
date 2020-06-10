#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, GLib

from MotorControl import MotorControl
from Graph import Graph
from Motor_Simulated import Motor_Simulated as Motor
from SocketClient import SocketClient

# Intervalo de actualizacion del grafico.
UPDATE_INTERVAL = 20
client = None

class MainWindow(Gtk.Window):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.connect("destroy", lambda x: Gtk.main_quit())
        self.set_default_size(800, 400)

        self.show_all()

    def run(self):
        Gtk.main()

def on_server_response(msg, graph, control):
    values = msg.split(',')
    graph.set_value(float(values[0]))
    control.set_velocidad_txt(float(values[0]))
    return True

def on_frame(graph, control):
    request = "{},{},{},{}".format(
        control.get_desired_speed(),
        control.get_kp(),
        control.get_ki(),
        control.get_kd()
    )
    client.send(request)

    
    return True

def main(args):
    global last_velocity
    global client
    
    mainwdw = MainWindow()
    grid = Gtk.Grid(hexpand = True, vexpand = True)
    
    graph = Graph((0, 255), 10, UPDATE_INTERVAL)
    graph.init_animation()
    grid.attach(graph, 2, 1, 1, 1)

    control = MotorControl(0, 210)
    control.set_kp(1.0/(150.0/40.0))

    grid.attach(control, 1, 1, 1, 1)

    GLib.timeout_add(UPDATE_INTERVAL, on_frame, graph, control)

    try:
        client = SocketClient('localhost',8080)
        client.set_on_input(on_server_response, graph, control)
    except:
        print('No se pudo conectar con el servidor PID.')
        return 0

    mainwdw.add(grid)
    mainwdw.show_all()
    mainwdw.run()

    client.close()

    return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
