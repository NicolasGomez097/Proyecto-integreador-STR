#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#

from Motor import Motor
from math import exp

class Motor_Simulated(Motor):
    """
        Clase que hereda de Motor y sobrescribe el metodo 'get_Velocidad'
    """
    def __init__(self, velocidad_maxima, sensibilidad) :
        super().__init__(velocidad_maxima, sensibilidad)
        

    def get_velocidad_estatica (self) :
        self.velocidad = self.velocidad_maxima * (1 - exp(-self.torque * self.sensibilidad))     
        return self.velocidad

    #Override
    def get_velocidad (self) :
        # Se obtiene la velocidad con la formula dada en el PDF.
        velocidad_final = self.velocidad_maxima * (1 - exp(-self.torque * self.sensibilidad))

        # Se realiza una interpolacion lineal con el valor de velocidad actual y correspondiente
        #con un valor probado de 0.01
        self.velocidad = self.lerp(
            self.velocidad,
            velocidad_final,
            0.01
        )
        return self.velocidad

    
    def lerp(self, value, final_value, porcentaje):
        """
            Funcion de interpolacion lineal.
        """
        return (porcentaje * final_value) + ((1-porcentaje) * value)

