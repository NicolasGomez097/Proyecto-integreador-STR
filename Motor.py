#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#

class Motor() :
    """
        Clase principal con los 3 metodos principales del motor
    """
    def __init__(self, velocidad_maxima, sensibilidad) :
        self.velocidad_maxima = velocidad_maxima
        self.sensibilidad = sensibilidad
        self.velocidad = 0

    def set_torque (self, torque) :
        self.torque = torque

    def get_torque (self) :
        return self.torque

    def get_velocidad (self) :
        return self.velocidad
