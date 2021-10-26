
#include "Arduino.h"
#include "LCD.h"
#include "LiquidCrystal_I2C.h"
#include "RTClib.h"

 LiquidCrystal_I2C lcd(0x27,20,4);  //20 colum 4 filas
 RTC_DS3231 rtc; 

/*
 * Representacion del LCD
 */
  byte circle[8] = {
   0b00010,
   0b00101,
   0b00101,
   0b00010,
   0b00000,
   0b00000, 
   0b00000, 
   0b00000,
  };

 byte moon[8] = {
   0b00100,
   0b01000,
   0b11000,
   0b11000,
   0b11000,
   0b01000, 
   0b00100, 
   0b00000,
  };

 byte sun[8] = {
   0b00000,
   0b01100,
   0b11110,
   0b11110,
   0b11110,
   0b01100, 
   0b00000, 
   0b00000,
  };
