import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib.backends.backend_gtk3agg import (
    FigureCanvasGTK3Agg as FigureCanvas)
import numpy as np

class Graph(Gtk.ScrolledWindow): 
    def __init__(self, 
        yrange = (0, 1), xrange = 10,
        update_interval = 50
    ):
        super(Graph, self).__init__(hexpand = True, vexpand = True)

        self.range = xrange
        self.interval = update_interval
        self.last_velocidad = 0
        self.last_torque = 0
        self.last_vel_deseada = 0
        self.last_time = 0
        
        self.fig = plt.figure()
        self.ax = self.fig.subplots()

        self.xdata, self.ydata_velocidad = [], []
        self.ydata_torque = []
        self.ydata_vel_deseada = []

        self.ln_velocidad, = self.ax.plot([], [], label='Velocidad')
        self.ln_torque, = self.ax.plot([], [], label='Torque')
        self.ln_vel_deseada, = self.ax.plot([], [], 'r', label='Velocidad deseada')
        self.ax.legend()
        self.ax.grid(True)

        self.on_frame_callback = []

        self.ax.set_xlim(-self.range, 0)
        self.ax.set_ylabel('Velocidad / Torque')
        self.ax.set_ylim(yrange[0], yrange[1])

        self.ax.set_xlabel('Segundos')
        
        self.canvas = FigureCanvas(self.fig)
        self.add(self.canvas)

    def update(self, frame):
        for callback, *args in self.on_frame_callback:
            callback(*args)

        time = frame * self.interval / 1000

        if(time > self.range):
            self.xdata.pop(0)
            self.ydata_velocidad.pop(0)
            self.ydata_torque.pop(0)
            self.ydata_vel_deseada.pop(0)

        if (frame != 0):
            self.ax.set_xlim(time - self.range, time)

        self.xdata.append(time)
        self.ydata_velocidad.append(self.last_velocidad)        
        self.ydata_torque.append(self.last_torque)        
        self.ydata_vel_deseada.append(self.last_vel_deseada)        
        
        self.ln_velocidad.set_data(self.xdata, self.ydata_velocidad)
        self.ln_torque.set_data(self.xdata, self.ydata_torque)
        self.ln_vel_deseada.set_data(self.xdata, self.ydata_vel_deseada)

        self.last_time = time

        return self.ln_vel_deseada , self.ln_torque, self.ln_velocidad

    def set_velocidad(self, value):
        self.last_velocidad = value

    def set_torque(self, value):
        self.last_torque = value

    def set_vel_deseada(self, value):
        self.last_vel_deseada = value

    def init_animation(self):
        FuncAnimation(self.fig, self.update, frames=None, blit=True, interval = self.interval)
    
    def get_last_time(self):
        return self.last_time

    def add_on_frame(self, callback, *args):
        self.on_frame_callback.append(
            (
                callback,
                *args
            )
        )