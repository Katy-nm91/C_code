
#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H
#include "Arduino.h" 

 // Funciones
 extern void detectDistanceSensor();
 extern void startDistanceSensor(); 
 extern String getDistance(float distance);
 // Variables
 extern const int pinTrigger;
 extern const int pinEcho;
 extern unsigned long iniTime;
 extern unsigned long finalTime;
 extern unsigned long duration;
 extern float distance;
 extern String valueDistance;
 
#endif
