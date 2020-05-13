#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

from MotorControl import MotorControl
from Graph import Graph
from Motor_Simulated import Motor_Simulated as Motor

class MainWindow(Gtk.Window):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.connect("destroy", lambda x: Gtk.main_quit())
        self.set_default_size(800, 400)

        self.show_all()

    def run(self):
        Gtk.main()

def on_frame(graph, control, motor):
    motor.set_torque(control.get_value())
    velocidad = motor.get_velocidad()
    graph.set_value(velocidad)
    control.set_velocidad_txt(velocidad)

def main(args):
    mainwdw = MainWindow()
    grid = Gtk.Grid(hexpand = True, vexpand = True)
    
    motor = Motor(210, 7/255)

    graph = Graph((0, 255), 10, 30)
    graph.init_animation()
    grid.attach(graph, 2, 1, 1, 1)

    control = MotorControl(0, 255)

    graph.add_on_frame(on_frame, graph, control, motor)

    grid.attach(control, 1, 1, 1, 1)

    

    mainwdw.add(grid)
    mainwdw.show_all()
    mainwdw.run()

    return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
