
#ifndef SOILSENSOR_H
#define SOILSENSOR_H
#include "Arduino.h"

 // Funciones
 extern int soilSensor();
 extern String getsoilSensor();
 //Variables 
 extern unsigned int valueHumSoil;
 extern int valueDry;
 extern int valueWet; 
 extern int pinSoil;
 extern String dryOrwet;
 extern String valueDryWet;
 
#endif
