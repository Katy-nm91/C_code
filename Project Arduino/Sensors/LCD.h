
#ifndef LCD_H
#define LCD_H
#include "Arduino.h"
#include "LiquidCrystal_I2C.h"
#include "RTClib.h"

 extern LiquidCrystal_I2C lcd;  //20 colum 4 filas 
 extern RTC_DS3231 rtc; 
 extern byte circle[8];
 extern byte moon[8];
 extern byte sun[8];
 
#endif
