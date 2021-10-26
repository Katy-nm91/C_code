               #ifndef DEFINE_H
#define DEFINE_H

 #define led D0
 // Pines para: bombilla, bomba, válvula y ventilador
 #define lightbulb D5
 #define waterPum D6
 #define valve D7
 #define fan D3
 
 // Variables
 String cadena_web;
 String LDRpercentage;
 String fixedPercentage;
 String OnOffValueLDR;
 String temperature;
 String humidity;
 String distance;
 String soil;
 String OnOffValueSoil;

 byte flag;
 byte flagManual;
 byte flagAutomatic;
 byte flagR;
 byte flagFan;
 
 int i;
 String cadena;
 char letra;
 char valueReceivedLDR [4];
 char valueReceivedSoil [4]; 
 char DistReceived [4]; 
 int numDist;
 
#endif
