
#ifndef TEMPHUMSENSOR_H
#define TEMPHUMSENSOR_H
#include "Arduino.h" 
#include "DHT.h"

 // Funciones
 extern String getTemperatureHumidity();
 //Variables
 extern DHT dht;
 extern float humidity;
 extern float temperature;
 extern String valueTempHumSensor;
 
#endif
