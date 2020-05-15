#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, GLib

from MotorControl import MotorControl
from Graph import Graph
from Motor_Simulated import Motor_Simulated as Motor

# Intervalo de actualizacion del grafico.
UPDATE_INTERVAL = 20
READ_MOTOR_INTERVAL = 20
last_velocity = 0

class MainWindow(Gtk.Window):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.connect("destroy", lambda x: Gtk.main_quit())
        self.set_default_size(800, 400)

        self.show_all()

    def run(self):
        Gtk.main()

def update_motor(motor, control):
    motor.set_torque(control.get_value())
    global last_velocity
    last_velocity = motor.get_velocidad()
    return True

def on_frame(graph, control):
    graph.set_value(last_velocity)
    control.set_velocidad_txt(last_velocity)
    return True

def main(args):
    global last_velocity
    mainwdw = MainWindow()
    grid = Gtk.Grid(hexpand = True, vexpand = True)
    
    motor = Motor(210, 7/255)

    graph = Graph((0, 255), 10, UPDATE_INTERVAL)
    graph.init_animation()
    grid.attach(graph, 2, 1, 1, 1)

    control = MotorControl(0, 255)

    grid.attach(control, 1, 1, 1, 1)

    GLib.timeout_add(UPDATE_INTERVAL, on_frame, graph, control)
    GLib.timeout_add(READ_MOTOR_INTERVAL, update_motor, motor, control)

    mainwdw.add(grid)
    mainwdw.show_all()
    mainwdw.run()

    return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
