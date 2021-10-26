#include "DHT.h"
#include "LDR.h"
#include "LCD.h"
#include "DistanceSensor.h"
#include "HumTempSensor.h"
#include "LiquidCrystal_I2C.h"
#include "RTClib.h"
#include "SoilSensor.h"
#include "Arduino.h"
 
 char letra;
 char caracterReceived[4];
 String data;
 String ldrLCD;
 String tempLCD;
 String humLCD;
  
 void setup() {
  // Inicializacion
  Serial.begin(115200);
  Serial1.begin(115200);  
  // Configuracion de pines  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pinLDR, INPUT);    
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(pinSoil, INPUT); 
  // Inicializacion
  dht.begin();
  attachInterrupt(digitalPinToInterrupt(pinEcho), detectDistanceSensor, CHANGE);
  rtc.begin();
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.createChar(0,circle);
  lcd.createChar(1,moon);
  lcd.createChar(2,sun);
  rtc.adjust(DateTime(2018, 5, 3, 23, 59, 50));

 }

 void loop() { 

  // Datos sensores para LCD.
  UpdateTime();
  LdrLCD(); 
  TempHumLCD(); 

  //Envio al nodemcu.
  startDistanceSensor();  
  Serial1.print(getLDRsensor());
  Serial1.print(getTemperatureHumidity()); 
  Serial1.print(getDistance(distance)); 
  Serial1.println(getsoilSensor());
  Serial1.flush(); 

  Serial.print(getLDRsensor());
  Serial.print(getTemperatureHumidity()); 
  Serial.print(getDistance(distance)); 
  Serial.println(getsoilSensor());
  Serial.flush(); 
  delay(300);
        
 }
 
// Actualiza el tiempo cada segundo
 void UpdateTime() { 
  
   DateTime currentTime = rtc.now(); 
   // Fecha
   if (currentTime.day() < 10) {
    lcd.setCursor(1,0);
    lcd.print("0");
    lcd.setCursor(2,0);
    lcd.print(currentTime.day());  
   }
   else {
    lcd.setCursor(1,0);   
    lcd.print(currentTime.day());      
   }     

   if (currentTime.month() < 10) {
    lcd.setCursor(3,0);    
    lcd.print("/"); 
    lcd.setCursor(4,0);
    lcd.print("0");
    lcd.setCursor(5,0);
    lcd.print(currentTime.month());  
   }
   else {
    lcd.setCursor(3,0);    
    lcd.print("/");  
    lcd.setCursor(4,0);    
    lcd.print(currentTime.month());      
   }  
 
  lcd.setCursor(6,0); 
  lcd.print("/");  
  lcd.print(currentTime.year());  
  lcd.print(" "); 
  //Hora 
  if (currentTime.hour() < 10) {   
   lcd.setCursor(12,0);
   lcd.print("0");
   lcd.setCursor(13,0);
   lcd.print(currentTime.hour());  
  }
  else {
   lcd.setCursor(12,0);   
   lcd.print(currentTime.hour());      
  }  
  if (currentTime.minute() < 10) {
   lcd.setCursor(14,0);   
   lcd.print(":");  //////////////////    
   lcd.setCursor(15,0);
   lcd.print("0");
   lcd.setCursor(16,0);
   lcd.print(currentTime.minute());  
  } 
  else {
   lcd.setCursor(14,0);   
   lcd.print(":");  //////////////////      
   lcd.setCursor(15,0);   
   lcd.print(currentTime.minute());      
  } 
  if (currentTime.second() < 10) {
   lcd.setCursor(17,0);   
   lcd.print(":");  //////////////////        
   lcd.setCursor(18,0);
   lcd.print("0");
   lcd.setCursor(19,0);
   lcd.print(currentTime.second());  
  } 
  else {   
   lcd.setCursor(17,0);   
   lcd.print(":");  //////////////////             
   lcd.setCursor(18,0);    
   lcd.print(currentTime.second());      
  }  
 delay(300);   
 } 

// Actualiza luminosidad 
 void LdrLCD() {
  
  lcd.setCursor(3,2);
  ldrLCD = String(LDRsensor()) + "%"; 
  lcd.print(ldrLCD); 
  if (flagSunMoon) {    // Sun
   lcd.setCursor(1,2);
   lcd.write(byte(2));   
  }
  else {                // Moon 
   lcd.setCursor(1,2);
   lcd.write(byte(1));     
  }
 }
 
// Actualiza Temperatura y Humedad cada segundo
 void TempHumLCD() {
  
  lcd.setCursor(11,2); 
  lcd.print("T:");
  getTemperatureHumidity();
  lcd.setCursor(13,2);
  tempLCD = String(temperature);
  lcd.print(tempLCD);
  lcd.setCursor(18,2);   
  lcd.write(byte(0)); 
  lcd.setCursor(19,2);
  lcd.print("C");
    
  lcd.setCursor(11,3); 
  lcd.print("H:");
  lcd.setCursor(13,3);    
  humLCD = String(humidity) + "%";        
  lcd.print(humLCD);   
 }

