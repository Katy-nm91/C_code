
#include "Arduino.h"
#include "LDR.h"

 const int pinLDR = 0;
 unsigned int fixedPercentage = 40;
 float voltage;
 float LDRpercentage;
 float max_reg_voltage = 4.96;
 String OnOffValue;
 String LDRvalue; 
 byte flagSunMoon;

 /*
  * Funcion que devuelve el valor del pin analogico
  */
 float LDRsensor() {

  voltage = 0.00489*analogRead(pinLDR);
  LDRpercentage = (voltage*100.0)/max_reg_voltage;
   if (LDRpercentage > fixedPercentage) {
    flagSunMoon = 1;
   }
   else {
    flagSunMoon = 0;
   }
     
  return LDRpercentage; 
 }

 /*
  * Funcion que devuelve un String con el valor del sensor 
  * e indica el estado 
  */  
 String getLDRsensor() {
   
  if (LDRsensor() < fixedPercentage) {   
   digitalWrite(LED_BUILTIN, HIGH);
   OnOffValue = "ON";
  }
  else {
   digitalWrite(LED_BUILTIN, LOW);
   OnOffValue = "OFF";    
  }

  return LDRvalue = String(LDRpercentage) + "%" + " " + String(fixedPercentage) + "%" + " " + OnOffValue + " ";
  
 }

