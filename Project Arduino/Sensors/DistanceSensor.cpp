
#include "Arduino.h"
#include "DistanceSensor.h"

 
 // Sensor de Distancia
 const int pinTrigger = 24;
 const int pinEcho = 2;
 unsigned long iniTime;
 unsigned long finalTime;
 unsigned long duration; 
 float distance;
 String valueDistance;
 
 /*
 * Funcion que inicializa un disparo para que el sensor
 * pueda tomar una medida
 */   
 void startDistanceSensor() {
   
  iniTime = 0;
  digitalWrite(pinTrigger, LOW); // Para generar un pulso limpio
  delayMicroseconds(4);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(12);
  digitalWrite(pinTrigger, LOW);
  
 } 

 /*
 * Funcion de llamada a una interrupcion,
 * mide la distancia del pulso que recibe el sensor, por flanco de subida y bajada
 */ 
 void detectDistanceSensor() {
  
  if (iniTime == 0) {
      iniTime = micros();
   }
  else {
     finalTime = micros();
     duration = finalTime - iniTime;
     distance = ((duration*1.0)/58.0);    
  }
         
 }

  /*
 * Funcion que devuelve un String con el valor de la distancia
 */    
  String getDistance(float distance) {

    return valueDistance = String(distance) + "Cm" +  " ";
  }

