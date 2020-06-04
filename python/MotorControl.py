import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

class MotorControl(Gtk.Grid):
    def __init__(self, min, max):
        super(MotorControl, self).__init__()
        self.set_vexpand(True)

        text = Gtk.Label('Torque')
        text.set_margin_top(20)
        self.attach(text, 1, 1, 1, 1)

        slider = Gtk.Scale.new_with_range(Gtk.Orientation.VERTICAL, min, max, 0.1)
        slider.set_margin_start(20)
        slider.set_margin_end(20)
        slider.set_margin_top(20)
        slider.set_margin_bottom(20)
        slider.set_inverted(True)
        slider.set_vexpand(True)

        self.slider = slider
        self.attach(slider, 1, 2, 1, 1)

        text = Gtk.Label('Velocidad')
        text.set_margin_top(20)
        self.attach(text, 1, 3, 1, 1)

        self.velocidad = Gtk.Label('')
        self.velocidad.set_margin_bottom(20)
        self.attach(self.velocidad, 1, 4, 1, 1)

    def set_on_change(self, callback, *args):
        self.slider.connect('value-changed', callback, *args)

    def get_value(self):
        return self.slider.get_value()

    def set_velocidad_txt(self, velocidad):
        self.velocidad.set_text('{:.2f}'.format(velocidad))
    
