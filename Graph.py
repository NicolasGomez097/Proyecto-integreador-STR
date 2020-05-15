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
        
        self.fig = plt.figure()
        self.ax = self.fig.add_subplot(111)
        self.xdata, self.ydata = [], []
        self.ln, = plt.plot([], [])
        self.ax.grid(True)
        self.range = xrange
        self.interval = update_interval
        self.fixed_time = 1000 / self.interval
        self.last_value = 0
        self.on_frame_callback = []

        self.ax.set_xlim(-self.range, 0)
        self.ax.set_ylabel('Velocidad')
        self.ax.set_ylim(yrange[0], yrange[1])

        self.ax.set_xlabel('Segundos')
        
        self.canvas = FigureCanvas(self.fig)
        self.add(self.canvas)

    def update(self, frame):
        for callback, *args in self.on_frame_callback:
            callback(*args)

        x = frame / self.fixed_time

        if(x > self.range):
            self.xdata.pop(0)
            self.ydata.pop(0)

        if (frame != 0):
            self.ax.set_xlim(x - self.range, x)

        self.xdata.append(x)
        self.ydata.append(self.last_value)        
        
        self.ln.set_data(self.xdata, self.ydata)

        return self.ln,

    def set_value(self, value):
        self.last_value = value
        
    def get_value(self):
        return self.last_value

    def init_animation(self):
        FuncAnimation(self.fig, self.update, frames=None, blit=True, interval = self.interval)

    def add_on_frame(self, callback, *args):
        self.on_frame_callback.append(
            (
                callback,
                *args
            )
        )