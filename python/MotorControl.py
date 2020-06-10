import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

class MotorControl(Gtk.Grid):
    def __init__(self, min, max):
        super(MotorControl, self).__init__()
        self.set_vexpand(True)

        # Control Velocidad
        text = Gtk.Label('Velocidad deseada')
        text.set_margin_top(20)
        self.attach(text, 1, 1, 1, 1)

        slider = Gtk.Scale.new_with_range(Gtk.Orientation.VERTICAL, min, max, 0.1)
        slider.set_margin_start(20)
        slider.set_margin_end(20)
        slider.set_margin_top(20)
        slider.set_margin_bottom(20)
        slider.set_inverted(True)
        slider.set_vexpand(True)

        self.sliderSpeed = slider
        self.attach(slider, 1, 2, 1, 1)

        # Control Kp
        text = Gtk.Label('Kp')
        text.set_margin_top(20)
        self.attach(text, 2, 1, 1, 1)

        sliderkp = Gtk.Scale.new_with_range(Gtk.Orientation.VERTICAL, 0.01, 0.99, 0.01)
        sliderkp.set_margin_start(20)
        sliderkp.set_margin_end(20)
        sliderkp.set_margin_top(20)
        sliderkp.set_margin_bottom(20)
        sliderkp.set_inverted(True)
        sliderkp.set_vexpand(True)

        self.sliderkp = sliderkp
        self.attach(sliderkp, 2, 2, 1, 1)

        # Control Ki
        text = Gtk.Label('Ki')
        text.set_margin_top(20)
        self.attach(text, 3, 1, 1, 1)

        sliderki = Gtk.Scale.new_with_range(Gtk.Orientation.VERTICAL, 0.00, 20.0, 0.01)
        sliderki.set_margin_start(20)
        sliderki.set_margin_end(20)
        sliderki.set_margin_top(20)
        sliderki.set_margin_bottom(20)
        sliderki.set_inverted(True)
        sliderki.set_vexpand(True)

        self.sliderki = sliderki
        self.attach(sliderki, 3, 2, 1, 1)

        # Control Kd
        text = Gtk.Label('Kd')
        text.set_margin_top(20)
        self.attach(text, 4, 1, 1, 1)

        sliderkd = Gtk.Scale.new_with_range(Gtk.Orientation.VERTICAL, 0.00, 20.0, 0.01)
        sliderkd.set_margin_start(20)
        sliderkd.set_margin_end(20)
        sliderkd.set_margin_top(20)
        sliderkd.set_margin_bottom(20)
        sliderkd.set_inverted(True)
        sliderkd.set_vexpand(True)

        self.sliderkd = sliderkd
        self.attach(sliderkd, 4, 2, 1, 1)

        text = Gtk.Label('Velocidad')
        text.set_margin_top(20)
        self.attach(text, 1, 3, 1, 1)

        self.velocidad = Gtk.Label('')
        self.velocidad.set_margin_bottom(20)
        self.attach(self.velocidad, 1, 4, 1, 1)

    def set_on_change(self, callback, *args):
        self.sliderSpeed.connect('value-changed', callback, *args)

    def get_value(self):
        return self.sliderSpeed.get_value()

    def set_velocidad_txt(self, velocidad):
        self.velocidad.set_text('{:.2f}'.format(velocidad))
    
    def get_desired_speed(self):
        return self.sliderSpeed.get_value()

    def get_kp(self):
        return self.sliderkp.get_value()
    
    def get_ki(self):
        return self.sliderki.get_value()

    def get_kd(self):
        return self.sliderkd.get_value()

    def set_kp(self, value):
        self.sliderkp.set_value(value)
