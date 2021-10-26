
#ifndef LDR_H
#define LDR_H
#include "Arduino.h"

 // Funciones
 extern String getLDRsensor();
 extern float LDRsensor();
 // Variables
 extern const int pinLDR;
 extern unsigned int fixedPercentage;
 extern float voltage;
 extern float LDRpercentage;
 extern float max_reg_voltage;
 extern String OnOffValue;
 extern String LDRvalue;
 extern byte flagSunMoon;
 
#endif
