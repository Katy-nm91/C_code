#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <SoftwareSerial.h>
#include "string.h"
#include "define.h"

SoftwareSerial Node(D2,D1); // RX TX
ESP8266WebServer server (80); // puerto para la comunicación

const char* ssid = "vodafone7000";
const char* password = "4D2MMCAET679HK";

void setup() {

  // RX TX 
  pinMode(D2, INPUT);
  pinMode(D1, OUTPUT);
  Node.begin(115200); 
  Serial.begin(115200);

  // Inicializamos servidor 
  server.begin();
  pinMode(led,OUTPUT);
  pinMode(lightbulb,OUTPUT); 
  pinMode(waterPum,OUTPUT);
  pinMode(valve,OUTPUT);
  pinMode(fan,OUTPUT);
  digitalWrite(led, HIGH); 
  digitalWrite(lightbulb, HIGH); //D5
  digitalWrite(waterPum, HIGH); //D6
  digitalWrite(valve, LOW); //D7
  digitalWrite(fan, HIGH); 
      
  // Establecimiento de la conexión WiFi
  WiFi.begin(ssid, password);
  Serial.println("Conectando con la red: ");
  Serial.println(ssid);
  
   while( WiFi.status()  !=  WL_CONNECTED) {
      Serial.print(".");
      delay(300);
       if (WiFi.status() == WL_CONNECT_FAILED) {
          Serial.println("Error en la conexión");
       }  
    }
  
  // Aviso de Wifi conectada
  Serial.println("WiFi conectada");
  Serial.println("La dirección IP es:");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
  delay(500);

  // Pagina Principal
  server.on("/", MainWeb);  
  server.on("/MainFan", MainFan);  
  server.on("/ManualMode", ManualMode);
  server.on("/AutomaticMode", AutomaticMode);  
  server.on("/Lighting", Lighting);   
  server.on("/TempHum", TempHum);  
  server.on("/Detector", Detector); 
  server.on("/Irrigation", Irrigation);  
  server.on("/IrrigationONOFF", IrrigationONOFF);
}

 /*
 * Funcion para el sensor de distancia en HTML
 */
void Detector() {
   String content;  
    content = "<html><head><style type=\"text/css\">body { background-image: url(https://pbs.twimg.com/media/DW0L-9-XcAAigP1.jpg)}</style></head><body><p>&nbsp;</p>";  
    content += "<p>&nbsp;</p><p style=\"text-align: center;\"><span style=\"font-size: 40px;\"><a href=\"/\"><span style=\"text-decoration: underline; color: #000000;\"><strong><img src=\"https://pbs.twimg.com/media/DV_2gi2W4AAWxk4.png\" width=\"31\" height=\"31\"/></strong></span></a><span style=\"color: #000000;\"><strong>&nbsp;&nbsp;</strong></span></span><span style=\"text-decoration: underline; font-size: 40px; color: #000000;\"><strong>Alarma</strong></span></p>";
    content += "<p>&nbsp;&nbsp;&nbsp;</p><div align=\"center\">&nbsp;<table style=\"width: 504px; height: 532px;\" cellspacing=\"5\" cellpadding=\"0\"><tbody>";
    content += "<tr style=\"height: 50.75px; text-align: center;\"><th style=\"text-align: center; width: 232.890625px; height: 50.75px;\" colspan=\"1\">&nbsp;</th></tr><tr style=\"height: 160px;\">";
    content += "<td style=\"width: 232.890625px; height: 160px; text-align: center;\" bgcolor=\"#CD5C5C\"><p><span style=\"font-size: 26px;\"><strong><span style=\"color: #ffdab9; font-family: monospace;\">Distancia</span></strong></span></p>";
    content += "<p><span style=\"font-size: 23px;\"><strong><span style=\"color: #ffdab9; font-family: monospace;\">";
    content += distance;
    content += "</span></strong></span></p></td><td style=\"width: 250.125px; height: 160px; text-align: center;\">&nbsp;<img src=\"https://pbs.twimg.com/media/DWq71KuXUAA8-oC.png\" alt=\"\" width=\"211\" height=\"211\" /></td>";
    content += "</tr><tr style=\"height: 195px;\"><td style=\"width: 232.890625px; height: 195px; text-align: center;\">&nbsp;</td><td style=\"width: 250.125px; height: 195px; text-align: center;\">";
    if (numDist < 100) {  
    content += "<img src=\"https://media.giphy.com/media/o4lCfVK06ah2M/giphy.gif\" width=\"243\" height=\"200\"/></td></tr></tbody></table></div>";               
    }
    else {  
    content += "&nbsp;</td></tr></tbody></table></div>";       
    }
    content += "<meta http-equiv=\"refresh\" content=\"2;URL=http://192.168.0.157/Detector\">";
    server.send(200, "text/html", content); 
    delay(0);       
}

 /*
 * Funcion para el sensor de temperatura y humedad en HTML
 */
void TempHum() {
   String content;  
    content = "<html><head><style type=\"text/css\">body { background-image: url(https://pbs.twimg.com/media/DW0L-9-XcAAigP1.jpg)}</style></head><body><p>&nbsp;</p>";   
    content += "<p>&nbsp;</p><p style=\"text-align: center;\"><span style=\"font-size: 40px;\"><a href=\"/\"><span style=\"text-decoration: underline; color: #000000;\"><strong><img src=\"https://pbs.twimg.com/media/DV_2gi2W4AAWxk4.png\" width=\"31\" height=\"31\"/></strong></span></a><span style=\"color: #000000;\"><strong>&nbsp;&nbsp;</strong></span></span><span style=\"text-decoration: underline; font-size: 40px; color: #000000;\"><strong>Temperatura y Humedad</strong></span></p>";
    content += "<p>&nbsp;&nbsp;&nbsp;</p><div align=\"center\"><table style=\"width: 503px; height: 592px;\" cellspacing=\"5\" cellpadding=\"0\"><tbody>";
    content += "<tr style=\"height: 89px; text-align: center;\"><th style=\"text-align: center; width: 242.8125px; height: 89px;\" colspan=\"1\"><img src=\"https://nergiza.com/wp-content/uploads/temperatura-y-humedad.png\" width=\"217\" height=\"195\"/></th>";
    content += "</tr><tr style=\"height: 155.78125px;\"><td style=\"width: 242.8125px; height: 155.78125px; text-align: center;\" bgcolor=\"#FFF8DC\">";
    content += "<p><span style=\"font-size: 25px;\"><strong><span style=\"color: #87ceeb; font-family: monospace;\">Temperatura</span></strong></span></p><p><span style=\"font-size: 22px;\"><strong><span style=\"color: #87ceeb; font-family: monospace;\">";
    content += temperature;
    content += "</span></strong></span></p><p>&nbsp;</p></td></tr><tr style=\"height: 160px;\"><td style=\"width: 242.8125px; height: 160px; text-align: center;\">&nbsp;</td><td style=\"width: 239.203125px; height: 160px; text-align: center;\" bgcolor=\"#AFEEEE\">";
    content += "<p><span style=\"font-size: 25px;\"><strong><span style=\"color: #ffffe0; font-family: monospace;\">Humedad</span></strong></span></p><p><span style=\"font-size: 22px;\"><strong><span style=\"color: #ffffe0; font-family: monospace;\">";
    content += humidity;
    content += "</span></strong></span></p><p>&nbsp;</p></td></tr></tbody></table></div>";
    content += "<meta http-equiv=\"refresh\" content=\"2;URL=http://192.168.0.157/TempHum\">";
    server.send(200, "text/html", content); 
    delay(0);      
}

 /*
 * Funcion para el riego en HTML
 */
void Irrigation() { // Control de la pantalla
   String content;  
    if (flagR == 1) {
     content = "<html><head><style type=\"text/css\">body { background-image: url(https://pbs.twimg.com/media/DW0L-9-XcAAigP1.jpg)}</style></head><body><p>&nbsp;</p>";
     content += "<p style=\"text-align: center;\"><span style=\"font-size: 40px;\"><a href=\"/\"><span style=\"text-decoration: underline; color: #000000;\"><strong><img src=\"https://pbs.twimg.com/media/DV_2gi2W4AAWxk4.png\" width=\"31\" height=\"31\" /></strong></span></a><span style=\"color: #000000;\"><strong>&nbsp;&nbsp;</strong></span></span><span style=\"text-decoration: underline; font-size: 40px; color: #000000;\"><strong>Sistema de Riego</strong></span></p>";
     content += "<p>&nbsp;&nbsp;&nbsp;</p><div align=\"center\">&nbsp;<table style=\"width: 512px; height: 561px;\" cellspacing=\"5\" cellpadding=\"0\"><tbody><tr style=\"height: 50.75px; text-align: center;\"><th style=\"text-align: center; width: 236.75px; height: 50.75px;\" colspan=\"1\">&nbsp;</th>";
     content += "</tr><tr style=\"height: 160px;\"><td style=\"width: 236.75px;\"><p>&nbsp;</p></td><td style=\"width: 254.265625px; height: 160px; text-align: center;\">&nbsp;<img src=\"https://pbs.twimg.com/media/DYSBI3PWAAEDjgv.jpg\" width=\"260\" height=\"243\" /></td>";
     content += "</tr><tr style=\"height: 195px;\"><td style=\"width: 236.75px; height: 195px; text-align: center;\">";
    if (strcmp(valueReceivedSoil, "ON") == 0 ) {
      content += "<img src=\"https://pbs.twimg.com/media/DYR_f9HX4AAQGn1.jpg\" width=\"240\" height=\"280\" /></td>";        
     }
     else {
      content += "<img src=\"https://pbs.twimg.com/media/DYR_qHHW0AAkq3e.jpg\" width=\"240\" height=\"280\" /></td>";
     }      
     content += "<td style=\"width: 254.265625px; height: 160px; text-align: center;\" bgcolor=\"#3CB371\">&nbsp;<p><span style=\"font-size: 36px;\"><a href=\"IrrigationONOFF\"><strong><span style=\"color: #008000; font-family: monospace;\">RIEGO</span></strong></a></span></p></td></tr></tbody></table></div>";  
     content += "<meta http-equiv=\"refresh\" content=\"3;URL=http://192.168.0.157/Irrigation\">";        
     server.send(200, "text/html", content); 
     delay(0);   
    } 
    else {
     content = "<html><head><style type=\"text/css\">body { background-image: url(https://pbs.twimg.com/media/DW0L-9-XcAAigP1.jpg)}</style></head><body><p>&nbsp;</p>";
     content += "<p style=\"text-align: center;\"><span style=\"font-size: 40px;\"><a href=\"/\"><span style=\"text-decoration: underline; color: #000000;\"><strong><img src=\"https://pbs.twimg.com/media/DV_2gi2W4AAWxk4.png\" width=\"31\" height=\"31\" /></strong></span></a><span style=\"color: #000000;\"><strong>&nbsp;&nbsp;</strong></span></span><span style=\"text-decoration: underline; font-size: 40px; color: #000000;\"><strong>Sistema de Riego</strong></span></p>";
     content += "<p>&nbsp;&nbsp;&nbsp;</p><div align=\"center\">&nbsp;<table style=\"width: 512px; height: 561px;\" cellspacing=\"5\" cellpadding=\"0\"><tbody><tr style=\"height: 50px; text-align: center;\"><th style=\"text-align: center; width: 236.75px; height: 50px;\" colspan=\"1\">&nbsp;</th></tr><tr style=\"height: 160px;\">";
     content += "<td style=\"width: 236.75px; height: 160px;\"><p>&nbsp;</p></td><td style=\"width: 254.265625px; height: 160px; text-align: center;\">&nbsp;<img src=\"https://pbs.twimg.com/media/DYSBI3PWAAEDjgv.jpg\" width=\"260\" height=\"243\" /></td></tr><tr style=\"height: 273px;\">";
     content += "<td style=\"width: 236.75px; height: 273px; text-align: center;\">&nbsp;</td><td style=\"width: 254.265625px; height: 273px; text-align: center;\" bgcolor=\"#3CB371\">&nbsp;<p><span style=\"font-size: 36px;\"><a href=\"IrrigationONOFF\"><strong><span style=\"color: #008000; font-family: monospace;\">RIEGO</span></strong></a></span></p></td></tr></tbody></table></div>";
     server.send(200, "text/html", content);  
     delay(0);             
    }    
}

 /*
 * Funcion para la activacion y desactivacion del riego en HTML
 */
void IrrigationONOFF() { // Act.Desact Riego
   String content; 
    if (flagR == 0) {
     flagR = 1;       
     // Encendido de RIEGO
     server.send(200, "text/html", "<meta http-equiv=\"refresh\" content=\"0;URL=http://192.168.0.157/Irrigation\">");  
     delay(0);   
    } 
    else {
     flagR = 0; 
    // Apagado de RIEGO
     server.send(200, "text/html", "<meta http-equiv=\"refresh\" content=\"0;URL=http://192.168.0.157/Irrigation\">");       
     delay(0);             
    }          
}

 /*
 * Funcion para la bombilla en HTML
 */
void Lighting() {
   String content;
   if (flagManual == 1 ) {  
    content = "<html><head><style type=\"text/css\">body { background-image: url(https://pbs.twimg.com/media/DW0L-9-XcAAigP1.jpg)}</style></head><body><p>&nbsp;</p>";
    content += "<p>&nbsp;</p><p style=\"text-align: center;\"><span style=\"font-size: 40px;\"><a href=\"/\"><span style=\"text-decoration: underline; color: #000000;\"><strong><img src=\"https://pbs.twimg.com/media/DV_2gi2W4AAWxk4.png\" width=\"31\" height=\"31\" /></strong></span></a><span style=\"color: #000000;\"><strong>&nbsp;&nbsp;</strong></span></span><span style=\"text-decoration: underline; font-size: 40px; color: #000000;\"><strong>Iluminaci&oacute;n</strong></span></p>";
    content += "<p>&nbsp;&nbsp;&nbsp;</p><div align=\"center\"><table style=\"width: 473px; height: 213px;\" cellspacing=\"5\" cellpadding=\"0\"><tbody><tr style=\"height: 118px;\"><th style=\"text-align: center; width: 219px; height: 118px;\" colspan=\"1\"><img src=\"https://contemporaneaeventi.com/wp-content/uploads/2016/06/iluminacion.jpg\" width=\"210\" height=\"189\" />&nbsp;</th>";
    content += "<th style=\"width: 254px; height: 118px;\">&nbsp;</th></tr><tr style=\"height: 149px;\"><th style=\"width: 219px; height: 163px;\"><img src=\"https://pbs.twimg.com/media/DU53PwzW4AENwQY.png\" width=\"151\" height=\"163\"/></th>";
    content += "<th style=\"width: 254px; height: 163px;\" bgcolor=\"#87CEEB\"><span style=\"font-size: 24px;\"><a href=\"ManualMode\"><span style=\"color: #000000; font-family: monospace;\">Modo Manual</span></a></span></th>";
    content += "</tr><tr style=\"height: 163px;\"><td style=\"width: 219px; height: 160px; text-align: center;\"><img src=\"https://pbs.twimg.com/media/DU53Q8UXcAAR0Hj.png\" width=\"151\" height=\"163\"/></td>";
    content += "<td style=\"width: 254px; height: 160px; text-align: center;\" bgcolor=\"#FFA07A\"><span style=\"font-size: 24px;\"><a href=\"AutomaticMode\"><strong><span style=\"color: #000000; font-family: monospace;\">Modo Autom&aacute;tico</span></strong></a></span></td></tr></tbody></table></div>";    
    server.send(200, "text/html", content);             
   }
   else if(flagAutomatic == 1) {
    content = "<html><head><style type=\"text/css\">body { background-image: url(https://pbs.twimg.com/media/DW0L-9-XcAAigP1.jpg)}</style></head><body><p>&nbsp;</p>";
    content += "<p>&nbsp;</p><p style=\"text-align: center;\"><span style=\"font-size: 40px;\"><a href=\"/\"><span style=\"text-decoration: underline; color: #000000;\"><strong><img src=\"https://pbs.twimg.com/media/DV_2gi2W4AAWxk4.png\" width=\"31\" height=\"31\" /></strong></span></a><span style=\"color: #000000;\"><strong>&nbsp;&nbsp;</strong></span></span><span style=\"text-decoration: underline; font-size: 40px; color: #000000;\"><strong>Iluminaci&oacute;n</strong></span></p>";
    content += "<p>&nbsp;&nbsp;&nbsp;</p><div align=\"center\"><table style=\"width: 450px; height: 213px;\" cellspacing=\"5\" cellpadding=\"0\"><tbody><tr style=\"height: 118px;\">";
    content += "<th style=\"text-align: center; width: 219.703125px; height: 118px;\" colspan=\"1\"><img src=\"https://contemporaneaeventi.com/wp-content/uploads/2016/06/iluminacion.jpg\" width=\"210\" height=\"189\" />&nbsp;</th>";
    content += "<th style=\"width: 243.296875px; height: 118px;\">&nbsp;</th></tr><tr style=\"height: 149px;\">";
    content += "<th style=\"width: 219.703125px; height: 163px;\"><img src=\"https://pbs.twimg.com/media/DU53Q8UXcAAR0Hj.png\" width=\"151\" height=\"163\" /></th><th style=\"width: 243.296875px; height: 163px;\" bgcolor=\"#87CEEB\"><span style=\"font-size: 24px;\"><a href=\"ManualMode\"><span style=\"color: #000000; font-family: monospace;\">Modo Manual</span></a></span></th></tr><tr style=\"height: 163px;\">";
    if (strcmp(valueReceivedLDR, "ON") == 0 ) {
     content += "<td style=\"width: 219.703125px; height: 160px; text-align: center;\"><img src=\"https://pbs.twimg.com/media/DU53PwzW4AENwQY.png\" width=\"151\" height=\"163\" /></td>";          
    }
    else {
     content += "<td style=\"width: 219.703125px; height: 160px; text-align: center;\"><img src=\"https://pbs.twimg.com/media/DU53Q8UXcAAR0Hj.png\" width=\"151\" height=\"163\" /></td>";  
    }       
    content += "<td style=\"width: 243.296875px; height: 160px; text-align: center;\" bgcolor=\"#FFA07A\"><span style=\"font-size: 24px;\"><a href=\"AutomaticMode\"><strong><span style=\"color: #000000; font-family: monospace;\">Modo Autom&aacute;tico</span></strong></a></span></td>";
    content += "</tr><tr style=\"height: 163px;\"><td style=\"height: 163px; text-align: center; width: 219.703125px;\">&nbsp;</td><td style=\"width: 243.296875px;\"><table style=\"margin: auto; box-shadow: #000000 1px 1px 5px; height: 177px; width: 233px;\" border=\"1\">";
    content += "<tbody><tr style=\"border-top-width: 2px; border-top-style: solid; border-top-color: #555555; height: 24.765625px;\">";
    content += "<td style=\"border: 2px dashed #ffa07a; height: 24.765625px; width: 107.109375px; text-align: center;\"><span style=\"font-size: 15px;\"><strong><span style=\"color: #000000; font-family: monospace;\">% Actual</span></strong></span></td>";
    content += "<td style=\"border: 2px dashed #ffa07a; height: 24.765625px; width: 111.890625px; text-align: center;\"><span style=\"font-size: 15px;\"><strong><span style=\"color: #000000; font-family: monospace;\">% Programado</span></strong></span></td></tr>";
    content += "<tr style=\"background-color: rgba(255, 160, 122, 0.701961); height: 25px;\"><td style=\"height: 25px; width: 107.109375px; text-align: center;\"><span style=\"font-size: 21px;\"><span style=\"font-family: monospace;\">";
    content += LDRpercentage;
    content += "</span></span></td><td style=\"height: 25px; width: 111.890625px; text-align: center;\"><span style=\"font-size: 21px;\"><span style=\"font-family: monospace;\">";
    content += fixedPercentage;
    content += "</span></span></td></tr></tbody></table></td></tr></tbody></table></div>";
    content += "<meta http-equiv=\"refresh\" content=\"2;URL=http://192.168.0.157/Lighting\">";
    server.send(200, "text/html", content);   
    delay(0);                          
   }
   else {
    content = "<html><head><style type=\"text/css\">body { background-image: url(https://pbs.twimg.com/media/DW0L-9-XcAAigP1.jpg)}</style></head><body><p>&nbsp;</p>";
    content += "<p>&nbsp;</p><p style=\"text-align: center;\"><span style=\"font-size: 40px;\"><a href=\"/\"><span style=\"text-decoration: underline; color: #000000;\"><strong><img src=\"https://pbs.twimg.com/media/DV_2gi2W4AAWxk4.png\" width=\"31\" height=\"31\" /></strong></span></a><span style=\"color: #000000;\"><strong>&nbsp;&nbsp;</strong></span></span><span style=\"text-decoration: underline; font-size: 40px; color: #000000;\"><strong>Iluminaci&oacute;n</strong></span></p>";
    content += "<p>&nbsp;&nbsp;&nbsp;</p><div align=\"center\"><table style=\"width: 473px; height: 213px;\" cellspacing=\"5\" cellpadding=\"0\"><tbody><tr style=\"height: 118px;\"><th style=\"text-align: center; width: 219px; height: 118px;\" colspan=\"1\"><img src=\"https://contemporaneaeventi.com/wp-content/uploads/2016/06/iluminacion.jpg\" width=\"210\" height=\"189\" />&nbsp;</th>";
    content += "<th style=\"width: 254px; height: 118px;\">&nbsp;</th></tr><tr style=\"height: 149px;\"><th style=\"width: 219px; height: 163px;\"><img src=\"https://pbs.twimg.com/media/DU53Q8UXcAAR0Hj.png\" width=\"151\" height=\"163\"/></th>";
    content += "<th style=\"width: 254px; height: 163px;\" bgcolor=\"#87CEEB\"><span style=\"font-size: 24px;\"><a href=\"ManualMode\"><span style=\"color: #000000; font-family: monospace;\">Modo Manual</span></a></span></th>";
    content += "</tr><tr style=\"height: 163px;\"><td style=\"width: 219px; height: 160px; text-align: center;\"><img src=\"https://pbs.twimg.com/media/DU53Q8UXcAAR0Hj.png\" width=\"151\" height=\"163\"/></td>";
    content += "<td style=\"width: 254px; height: 160px; text-align: center;\" bgcolor=\"#FFA07A\"><span style=\"font-size: 24px;\"><a href=\"AutomaticMode\"><strong><span style=\"color: #000000; font-family: monospace;\">Modo Autom&aacute;tico</span></strong></a></span></td></tr></tbody></table></div>"; 
    server.send(200, "text/html", content); 
   }
      ESP.wdtFeed();       
  }

 /*
 * Funcion para el modo manual de la bombilla
 */
void ManualMode() { 
  String content;
   if (flagManual == 0 && flagAutomatic == 0) {  
    content = "<html><head><style type=\"text/css\">body { background-image: url(https://pbs.twimg.com/media/DW0L-9-XcAAigP1.jpg)}</style></head><body><p>&nbsp;</p>";
    content += "<p>&nbsp;</p><p style=\"text-align: center;\"><span style=\"font-size: 40px;\"><a href=\"/\"><span style=\"text-decoration: underline; color: #000000;\"><strong><img src=\"https://pbs.twimg.com/media/DV_2gi2W4AAWxk4.png\" width=\"31\" height=\"31\" /></strong></span></a><span style=\"color: #000000;\"><strong>&nbsp;&nbsp;</strong></span></span><span style=\"text-decoration: underline; font-size: 40px; color: #000000;\"><strong>Iluminaci&oacute;n</strong></span></p>";
    content += "<p>&nbsp;&nbsp;&nbsp;</p><div align=\"center\"><table style=\"width: 473px; height: 213px;\" cellspacing=\"5\" cellpadding=\"0\"><tbody><tr style=\"height: 118px;\"><th style=\"text-align: center; width: 219px; height: 118px;\" colspan=\"1\"><img src=\"https://contemporaneaeventi.com/wp-content/uploads/2016/06/iluminacion.jpg\" width=\"210\" height=\"189\" />&nbsp;</th>";
    content += "<th style=\"width: 254px; height: 118px;\">&nbsp;</th></tr><tr style=\"height: 149px;\"><th style=\"width: 219px; height: 163px;\"><img src=\"https://pbs.twimg.com/media/DU53PwzW4AENwQY.png\" width=\"151\" height=\"163\"/></th>";
    content += "<th style=\"width: 254px; height: 163px;\" bgcolor=\"#87CEEB\"><span style=\"font-size: 24px;\"><a href=\"ManualMode\"><span style=\"color: #000000; font-family: monospace;\">Modo Manual</span></a></span></th>";
    content += "</tr><tr style=\"height: 163px;\"><td style=\"width: 219px; height: 160px; text-align: center;\"><img src=\"https://pbs.twimg.com/media/DU53Q8UXcAAR0Hj.png\" width=\"151\" height=\"163\"/></td>";
    content += "<td style=\"width: 254px; height: 160px; text-align: center;\" bgcolor=\"#FFA07A\"><span style=\"font-size: 24px;\"><a href=\"AutomaticMode\"><strong><span style=\"color: #000000; font-family: monospace;\">Modo Autom&aacute;tico</span></strong></a></span></td></tr></tbody></table></div>";
    server.send(200, "text/html", content); 
    flagManual = 1;
    digitalWrite(led, LOW); //ENCENDER LUZ 
    digitalWrite(lightbulb, LOW); // ENCENDER       
    delay(0);
   }
   else if (flagManual == 1 && flagAutomatic == 0) {
    content = "<html><head><style type=\"text/css\">body { background-image: url(https://pbs.twimg.com/media/DW0L-9-XcAAigP1.jpg)}</style></head><body><p>&nbsp;</p>";
    content += "<p>&nbsp;</p><p style=\"text-align: center;\"><span style=\"font-size: 40px;\"><a href=\"/\"><span style=\"text-decoration: underline; color: #000000;\"><strong><img src=\"https://pbs.twimg.com/media/DV_2gi2W4AAWxk4.png\" width=\"31\" height=\"31\" /></strong></span></a><span style=\"color: #000000;\"><strong>&nbsp;&nbsp;</strong></span></span><span style=\"text-decoration: underline; font-size: 40px; color: #000000;\"><strong>Iluminaci&oacute;n</strong></span></p>";
    content += "<p>&nbsp;&nbsp;&nbsp;</p><div align=\"center\"><table style=\"width: 473px; height: 213px;\" cellspacing=\"5\" cellpadding=\"0\"><tbody><tr style=\"height: 118px;\"><th style=\"text-align: center; width: 219px; height: 118px;\" colspan=\"1\"><img src=\"https://contemporaneaeventi.com/wp-content/uploads/2016/06/iluminacion.jpg\" width=\"210\" height=\"189\" />&nbsp;</th>";
    content += "<th style=\"width: 254px; height: 118px;\">&nbsp;</th></tr><tr style=\"height: 149px;\"><th style=\"width: 219px; height: 163px;\"><img src=\"https://pbs.twimg.com/media/DU53Q8UXcAAR0Hj.png\" width=\"151\" height=\"163\"/></th>";
    content += "<th style=\"width: 254px; height: 163px;\" bgcolor=\"#87CEEB\"><span style=\"font-size: 24px;\"><a href=\"ManualMode\"><span style=\"color: #000000; font-family: monospace;\">Modo Manual</span></a></span></th>";
    content += "</tr><tr style=\"height: 163px;\"><td style=\"width: 219px; height: 160px; text-align: center;\"><img src=\"https://pbs.twimg.com/media/DU53Q8UXcAAR0Hj.png\" width=\"151\" height=\"163\"/></td>";
    content += "<td style=\"width: 254px; height: 160px; text-align: center;\" bgcolor=\"#FFA07A\"><span style=\"font-size: 24px;\"><a href=\"AutomaticMode\"><strong><span style=\"color: #000000; font-family: monospace;\">Modo Autom&aacute;tico</span></strong></a></span></td></tr></tbody></table></div>";
    server.send(200, "text/html", content); 
    flagManual = 0;    
    digitalWrite(led, HIGH);  //APAGAR LUZ
    digitalWrite(lightbulb, HIGH); // ENCENDER       
    delay(0);     
   }  
   else {
    server.send(200, "text/html", "<meta http-equiv=\"refresh\" content=\"0;URL=http://192.168.0.157/Lighting\">"); 
    delay(0); 
   }
  }

 /*
 * Funcion para el modo automatico de la bombilla
 */
void AutomaticMode() { 
  String content;
   if (flagManual == 0 && flagAutomatic == 0) {  
    flagAutomatic = 1;       
    server.send(200, "text/html", "<meta http-equiv=\"refresh\" content=\"0;URL=http://192.168.0.157/Lighting\">"); 
    delay(0);     
   }   
   else if  (flagManual == 0 && flagAutomatic == 1) {
    content = "<html><head><style type=\"text/css\">body { background-image: url(https://pbs.twimg.com/media/DW0L-9-XcAAigP1.jpg)}</style></head><body><p>&nbsp;</p>";
    content += "<p>&nbsp;</p><p style=\"text-align: center;\"><span style=\"font-size: 40px;\"><a href=\"/\"><span style=\"text-decoration: underline; color: #000000;\"><strong><img src=\"https://pbs.twimg.com/media/DV_2gi2W4AAWxk4.png\" width=\"31\" height=\"31\" /></strong></span></a><span style=\"color: #000000;\"><strong>&nbsp;&nbsp;</strong></span></span><span style=\"text-decoration: underline; font-size: 40px; color: #000000;\"><strong>Iluminaci&oacute;n</strong></span></p>";
    content += "<p>&nbsp;&nbsp;&nbsp;</p><div align=\"center\"><table style=\"width: 473px; height: 213px;\" cellspacing=\"5\" cellpadding=\"0\"><tbody><tr style=\"height: 118px;\"><th style=\"text-align: center; width: 219px; height: 118px;\" colspan=\"1\"><img src=\"https://contemporaneaeventi.com/wp-content/uploads/2016/06/iluminacion.jpg\" width=\"210\" height=\"189\" />&nbsp;</th>";
    content += "<th style=\"width: 254px; height: 118px;\">&nbsp;</th></tr><tr style=\"height: 149px;\"><th style=\"width: 219px; height: 163px;\"><img src=\"https://pbs.twimg.com/media/DU53Q8UXcAAR0Hj.png\" width=\"151\" height=\"163\"/></th>";
    content += "<th style=\"width: 254px; height: 163px;\" bgcolor=\"#87CEEB\"><span style=\"font-size: 24px;\"><a href=\"ManualMode\"><span style=\"color: #000000; font-family: monospace;\">Modo Manual</span></a></span></th>";
    content += "</tr><tr style=\"height: 163px;\"><td style=\"width: 219px; height: 160px; text-align: center;\"><img src=\"https://pbs.twimg.com/media/DU53Q8UXcAAR0Hj.png\" width=\"151\" height=\"163\"/></td>";
    content += "<td style=\"width: 254px; height: 160px; text-align: center;\" bgcolor=\"#FFA07A\"><span style=\"font-size: 24px;\"><a href=\"AutomaticMode\"><strong><span style=\"color: #000000; font-family: monospace;\">Modo Autom&aacute;tico</span></strong></a></span></td></tr></tbody></table></div>";
    server.send(200, "text/html", content);  
    flagAutomatic = 0;                
    delay(0);        
   }
   else { 
    server.send(200, "text/html", "<meta http-equiv=\"refresh\" content=\"0;URL=http://192.168.0.157/Lighting\">"); 
    delay(0);   
   }
  }  

 /*
 * Funcion para la pagina princial 
 */
void MainWeb() {  
  String content;
    if (flagFan == 1) {
    content = "<html><head><style type=\"text/css\">body{background-image:url(https://images2.alphacoders.com/506/506335.png)})}</style></head><body>";
    content += "<p>&nbsp;&nbsp;</p><hr /><p style=\"text-align: center;\"><span style=\"color: #000000;\">&nbsp;<span style=\"font-size: 55px;\"><strong>Smart Home</strong></span></span></p><hr /><p>&nbsp;</p><div align=\"center\">";
    content += "<table style=\"width: 1199px; height: 653px;\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\"><tbody><tr style=\"height: 55px;\">";
    content += "<th style=\"text-align: center; width: 589px; height: 55px;\" colspan=\"2\"><span style=\"color: #000000; font-family: monospace; font-size: 28px;\">CASA</span></th><th style=\"width: 10px; height: 55px;\">&nbsp;</th>";
    content += "<th style=\"width: 96px; height: 55px;\">&nbsp;</th><th style=\"width: 221px; height: 55px;\">&nbsp;</th>";
    content += "<th style=\"width: 12px; height: 55px;\">&nbsp;</th><th style=\"text-align: center; width: 263px; height: 55px;\" colspan=\"1\"><span style=\"color: #000000; font-family: monospace; font-size: 28px;\">EXTERIOR</span></th></tr><tr style=\"height: 1px;\">";
    content += "<th style=\"width: 293.890625px; height: 1px;\"><span style=\"color: #000000; font-family: monospace; font-size: 21px;\">Iluminaci&oacute;n</span></th>";
    content += "<th style=\"width: 295.109375px; height: 1px;\"><span style=\"color: #000000; font-family: monospace; font-size: 21px;\">&nbsp;Temperatura y Humedad</span></th>";
    content += "<th style=\"width: 10px; height: 1px;\">&nbsp;</th><th style=\"width: 96px; height: 1px;\">&nbsp;</th><th style=\"width: 221px; height: 1px;\">&nbsp;</th><th style=\"width: 12px; height: 1px;\">&nbsp;</th><td style=\"width: 263px; height: 1px;\">&nbsp;&nbsp;&nbsp;</td>";
    content += "</tr><tr style=\"height: 7px;\">";
    content += "<td style=\"width: 293.890625px; height: 7px;\"><a href=\"Lighting\"><img style=\"display: block; margin-left: auto; margin-right: auto;\" src=\"https://pbs.twimg.com/media/DWq8z2jX0AEHcja.png\" width=\"190\" height=\"190\"/></a></td>";
    content += "<td style=\"width: 295.109375px; height: 7px;\"><a href=\"TempHum\"><img style=\"display: block; margin-left: auto; margin-right: auto;\" src=\"https://pbs.twimg.com/media/DWq-yTuX0AAuIXo.png\" width=\"190\" height=\"190\"/></a></td>";
    content += "<td style=\"width: 10px; height: 7px;\">&nbsp;</td><td style=\"width: 96px; height: 7px;\">&nbsp;</td><td style=\"width: 221px; height: 7px;\">&nbsp;</td><td style=\"width: 12px; height: 7px;\">&nbsp;</td><td style=\"width: 263px; height: 7px;\">";
    content += "</td></tr><tr style=\"height: 58.140625px;\">";
    content += "<th style=\"width: 293.890625px; height: 58.140625px;\"><span style=\"color: #000000; font-family: monospace; font-size: 21px;\">Ventilador</span></th><th style=\"width: 295.109375px; height: 58.140625px;\"><span style=\"font-family: monospace; font-size: 21px; color: #000000;\">Alarma</span></th>";
    content += "<th style=\"width: 10px; height: 58.140625px;\">&nbsp;</th><th style=\"width: 96px; height: 58.140625px;\">&nbsp;</th><th style=\"width: 221px; height: 58.140625px;\">&nbsp;</th><th style=\"width: 12px; height: 58.140625px;\">&nbsp;</th>";
    content += "<th style=\"width: 263px; height: 58.140625px;\"><span style=\"color: #000000; font-family: monospace; font-size: 21px;\">Sistema de Riego</span></th></tr><tr style=\"height: 142px;\">";
    content += "<td style=\"width: 293.890625px; height: 142px;\"><a href=\"MainFan\"><img style=\"display: block; margin-left: auto; margin-right: auto;\" src=\"http://www.infoplc.net/blog2/wp-content/uploads/2010/12/Ventilador.gif\" width=\"190\" height=\"190\"/></a></td>";
    content += "<td style=\"width: 295.109375px; height: 142px;\"><a href=\"Detector\"><img style=\"display: block; margin-left: auto; margin-right: auto;\" src=\"https://pbs.twimg.com/media/DWq71KuXUAA8-oC.png\" width=\"190\" height=\"190\"/></a></td>";
    content += "<td style=\"width: 10px; height: 142px;\">&nbsp;</td><td style=\"width: 96px; height: 142px;\">&nbsp;</td><td style=\"width: 221px; height: 142px;\">&nbsp;</td><td style=\"width: 12px; height: 142px;\">&nbsp;</td>";
    content += "<td style=\"width: 263px; height: 142px;\"><a href=\"Irrigation\"><img style=\"display: block; margin-left: auto; margin-right: auto;\" src=\"https://pbs.twimg.com/media/DWrvkxKWkAA14cQ.png\" width=\"190\" height=\"190\"/></td></tr></tbody></table></div>";        
    server.send(200, "text/html", content); 
    delay(0);          
    }
    else {
    content = "<html><head><style type=\"text/css\">body{background-image:url(https://images2.alphacoders.com/506/506335.png)})}</style></head><body>";
    content += "<p>&nbsp;&nbsp;</p><hr /><p style=\"text-align: center;\"><span style=\"color: #000000;\">&nbsp;<span style=\"font-size: 55px;\"><strong>Smart Home</strong></span></span></p><hr /><p>&nbsp;</p><div align=\"center\">";
    content += "<table style=\"width: 1199px; height: 653px;\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\"><tbody><tr style=\"height: 55px;\">";
    content += "<th style=\"text-align: center; width: 589px; height: 55px;\" colspan=\"2\"><span style=\"color: #000000; font-family: monospace; font-size: 28px;\">CASA</span></th><th style=\"width: 10px; height: 55px;\">&nbsp;</th>";
    content += "<th style=\"width: 96px; height: 55px;\">&nbsp;</th><th style=\"width: 221px; height: 55px;\">&nbsp;</th>";
    content += "<th style=\"width: 12px; height: 55px;\">&nbsp;</th><th style=\"text-align: center; width: 263px; height: 55px;\" colspan=\"1\"><span style=\"color: #000000; font-family: monospace; font-size: 28px;\">EXTERIOR</span></th></tr><tr style=\"height: 1px;\">";
    content += "<th style=\"width: 293.890625px; height: 1px;\"><span style=\"color: #000000; font-family: monospace; font-size: 21px;\">Iluminaci&oacute;n</span></th>";
    content += "<th style=\"width: 295.109375px; height: 1px;\"><span style=\"color: #000000; font-family: monospace; font-size: 21px;\">&nbsp;Temperatura y Humedad</span></th>";
    content += "<th style=\"width: 10px; height: 1px;\">&nbsp;</th><th style=\"width: 96px; height: 1px;\">&nbsp;</th><th style=\"width: 221px; height: 1px;\">&nbsp;</th><th style=\"width: 12px; height: 1px;\">&nbsp;</th><td style=\"width: 263px; height: 1px;\">&nbsp;&nbsp;&nbsp;</td>";
    content += "</tr><tr style=\"height: 7px;\">";
    content += "<td style=\"width: 293.890625px; height: 7px;\"><a href=\"Lighting\"><img style=\"display: block; margin-left: auto; margin-right: auto;\" src=\"https://pbs.twimg.com/media/DWq8z2jX0AEHcja.png\" width=\"190\" height=\"190\"/></a></td>";
    content += "<td style=\"width: 295.109375px; height: 7px;\"><a href=\"TempHum\"><img style=\"display: block; margin-left: auto; margin-right: auto;\" src=\"https://pbs.twimg.com/media/DWq-yTuX0AAuIXo.png\" width=\"190\" height=\"190\"/></a></td>";
    content += "<td style=\"width: 10px; height: 7px;\">&nbsp;</td><td style=\"width: 96px; height: 7px;\">&nbsp;</td><td style=\"width: 221px; height: 7px;\">&nbsp;</td><td style=\"width: 12px; height: 7px;\">&nbsp;</td><td style=\"width: 263px; height: 7px;\">";
    content += "</td></tr><tr style=\"height: 58.140625px;\">";
    content += "<th style=\"width: 293.890625px; height: 58.140625px;\"><span style=\"color: #000000; font-family: monospace; font-size: 21px;\">Ventilador</span></th><th style=\"width: 295.109375px; height: 58.140625px;\"><span style=\"font-family: monospace; font-size: 21px; color: #000000;\">Alarma</span></th>";
    content += "<th style=\"width: 10px; height: 58.140625px;\">&nbsp;</th><th style=\"width: 96px; height: 58.140625px;\">&nbsp;</th><th style=\"width: 221px; height: 58.140625px;\">&nbsp;</th><th style=\"width: 12px; height: 58.140625px;\">&nbsp;</th>";
    content += "<th style=\"width: 263px; height: 58.140625px;\"><span style=\"color: #000000; font-family: monospace; font-size: 21px;\">Sistema de Regad&iacute;o&nbsp;</span></th></tr><tr style=\"height: 142px;\">";
    content += "<td style=\"width: 293.890625px; height: 142px;\"><a href=\"MainFan\"><img style=\"display: block; margin-left: auto; margin-right: auto;\" src=\"https://pbs.twimg.com/media/DZUvHhOXkAIO4ar.png\" width=\"190\" height=\"190\"/></a></td>";
    content += "<td style=\"width: 295.109375px; height: 142px;\"><a href=\"Detector\"><img style=\"display: block; margin-left: auto; margin-right: auto;\" src=\"https://pbs.twimg.com/media/DWq71KuXUAA8-oC.png\" width=\"190\" height=\"190\"/></a></td>";
    content += "<td style=\"width: 10px; height: 142px;\">&nbsp;</td><td style=\"width: 96px; height: 142px;\">&nbsp;</td><td style=\"width: 221px; height: 142px;\">&nbsp;</td><td style=\"width: 12px; height: 142px;\">&nbsp;</td>";
    content += "<td style=\"width: 263px; height: 142px;\"><a href=\"Irrigation\"><img style=\"display: block; margin-left: auto; margin-right: auto;\" src=\"https://pbs.twimg.com/media/DWrvkxKWkAA14cQ.png\" width=\"190\" height=\"190\"/></td></tr></tbody></table></div>";                
    server.send(200, "text/html", content); 
    delay(0);      
    }
  }

 /*
 * Funcion para el control del ventilador en HTML 
 */
void MainFan() {
  
    if (flagFan == 0) {  
    server.send(200, "text/html", "<meta http-equiv=\"refresh\" content=\"0;URL=http://192.168.0.157\">"); 
    flagFan = 1;
    digitalWrite(fan, LOW); // ENCENDER   
    delay(0);          
    }
    else if (flagFan == 1) {
    flagFan = 0;  
    digitalWrite(fan, HIGH); // APAGAR
    server.send(200, "text/html", "<meta http-equiv=\"refresh\" content=\"0;URL=http://192.168.0.157\">");       
    }
}

void loop() {
  server.handleClient();
  yield();  

  // Control Luz Automatico
  if (flagAutomatic == 1) { // si esta en automatico tenemos que ver el estado
    if (strcmp(valueReceivedLDR, "ON") == 0 ) {
     digitalWrite(led, LOW); // ENCENDER 
     digitalWrite(lightbulb, LOW); // ENCENDER            
    }
    else {
     digitalWrite(led, HIGH); // APAGAR
     digitalWrite(lightbulb, HIGH); 
    }  
  }
  else if (flagAutomatic == 0 && flagManual == 0) {
     digitalWrite(led, HIGH); // APAGAR otra vez   
     digitalWrite(lightbulb, HIGH);    
   } 
   
  // Control de Riego Automatico
  if (flagR == 1) {
    if (strcmp(valueReceivedSoil, "ON") == 0 ) {
      digitalWrite(waterPum, LOW); // 6
      delay(1);
      digitalWrite(valve, HIGH); // 7      
     }
     else {
     digitalWrite(waterPum, HIGH); // 6  
     delay(1);      
     digitalWrite(valve, LOW); // 7 // APAGAR
     }      
  }
  else if (flagR == 0) {
     digitalWrite(waterPum, HIGH); // 6
     delay(1);     
     digitalWrite(valve, LOW); // 7 // APAGAR    
  }

   // Comunicacion Unidireccional Arduino - NodeMCU
   // Puerto serie escuchando
   if (Node.available()) { 
      letra = Node.read();
        while ( letra != '\n') {
              cadena = cadena + letra;
              letra = Node.read();
              delay(0);
              ESP.wdtFeed();
        } 
                
      cadena_web = cadena; 
      Serial.println(cadena);             // si no borro cadena lo q hace es sacar por el serial todo el dato encadenado mas el nuevo
   
      // Division de la cadena de datos recibida
      flag = 1;               //Flag para token      
      char *search = " ";
      char *token;
      char line [55];         // Almacenamiendo de la cadena en un array
      for (i=0; i<55; i++) {
        line[i] = cadena[i]; 
        delay(0);
       }
       i = 0;                                     
       token = strtok(line, search); 

       while ( token != NULL ) {   
         if (flag == 1) {
            flag++;
            LDRpercentage = token;
            Serial.println(LDRpercentage);          
         }
         else if (flag == 2) {
            fixedPercentage = token;
            Serial.println(fixedPercentage);
            flag++;          
         }  
         else if (flag == 3) {
            OnOffValueLDR = token;        // Tengo q comparar con las posiciones de la palabra (2 = ON) para que se cambie de imagen.         
            valueReceivedLDR[0] = OnOffValueLDR[0];
            valueReceivedLDR[1] = OnOffValueLDR[1];
            Serial.println(valueReceivedLDR);     
            flag++;             
         }
         else if (flag == 4) {
           temperature = token;
           Serial.println(temperature);
           flag++;
         }
          else if (flag == 5) {
            humidity = token;
            Serial.println(humidity);
            flag++;
          }
          else if (flag == 6) {
            distance = token;
            DistReceived [0] = distance[0];
            DistReceived [1] = distance[1];
            DistReceived [2] = distance[2];
            numDist = atoi(DistReceived);
            Serial.println(distance);
            flag++;
          }
          else if (flag == 7) {
            soil = token;
            Serial.println(soil);
            flag++;
          }
          else if (flag == 8) {
            OnOffValueSoil = token;
            valueReceivedSoil[0] = OnOffValueSoil[0];
            valueReceivedSoil[1] = OnOffValueSoil[1];
            Serial.println(valueReceivedSoil);            
            flag = 0;
          }
            
          token = strtok( NULL, " " );   
          delay(0); 
          }                  // Fin while
          
     cadena = "";  
     ESP.wdtFeed();                      
  }                         // Fin de escucha del puerto serie

}

