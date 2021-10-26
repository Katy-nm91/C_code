
#include "Arduino.h"
#include "HumTempSensor.h"
#include "DHT.h"

// Sensor de Temperatura y Humedad
 DHT dht (22, DHT22);
 float humidity;
 float temperature;
 String valueTempHumSensor;
 
 /*
 * Funcion que devuelve un String con el valor de temperatura y humedad
 */    
 String getTemperatureHumidity() {
  
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  return valueTempHumSensor = String(temperature) + char(0xB0) + "C " + String(humidity) + "%" +  " ";
     
 }

 
