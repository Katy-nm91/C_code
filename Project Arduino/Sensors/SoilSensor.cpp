
#include "Arduino.h"
#include "SoilSensor.h"

 unsigned int valueHumSoil;
 int valueDry = 500;
 int valueWet = 400; 
 String dryOrwet;
 String valueDryWet;
 int pinSoil = 1;

/*
 * Funcion que devuelve la medida del pin analogico
 */
 int soilSensor() {
  
  valueHumSoil = analogRead(pinSoil);
  return valueHumSoil;
 }

/*
 * Funcion que devuelve un String con el valor del sensor 
 * e indica el estado 
 */
 String getsoilSensor() {
  
  if (soilSensor() > 400) { // 500
    // digitalWrite(LED_BUILTIN, HIGH);
     dryOrwet = "ON";
  }
  else { // 400 if (soilSensor() < valueWet)
    //digitalWrite(LED_BUILTIN, LOW);
    dryOrwet = "OFF";   
  }

  return valueDryWet = String(valueHumSoil) + " " + dryOrwet;
 }
 
