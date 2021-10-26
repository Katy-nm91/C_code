#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
int led = D0;
const char* ssid = "MOVISTAR_AA98";
const char* password = "paquito2012";
ESP8266WebServer server (80); // puerto para la comunicación
byte flag_modo_manual = 1;
byte flag_modo_manual_on;
byte flag_modo_automatico;

void setup() {
 
  Serial.begin(115200);
  server.begin();   // inicializamos servidor
  pinMode(led,OUTPUT);
  digitalWrite(led, HIGH);
      
  //Establecimiento de la conexión WiFi
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

   // Aviso de wifi conectada.
  Serial.println("WiFi conectada");
  Serial.println("La dirección IP es:");
  Serial.println(WiFi.localIP());

  server.on("/", lighting);
  server.on("/ManualMode", ManualMode);
  server.on("/AutomaticMode", AutomaticMode);

}

void lighting() {
   String content;
   if (flag_modo_manual_on == 1) { // manual encendida
    content  = "<h2 style=\"text-align: center;\"><span style=\"color: #cb4335;\"><strong>Control de Iluminaci&oacute;n</strong></span></h2>";
    content += "<p style=\"padding-left: 660px;\"><img src=\"http://revistacitylife.com/images/citylife_sitio/2016/julio/iluminacion_principal.jpg\" alt="" width=\"381\" height=\"267\" /></p>";
    content += "<p style=\"padding-left: 270px;\">&nbsp;</p>";
    content += "<table style=\"height: 75px; width: 179px; border-color: #ec7063;\" border=\"4\" cellspacing=\"0\" cellpadding=\"2\">";
    content += "<tbody>";
    content += "<tr>";
    content += "<td style=\"width: 165px; text-align: center;\">";
    content += "<p><a href=\"ManualMode\">Modo Manual</a></p>";
    content += "<p><img src=\"https://pbs.twimg.com/media/DO__cSgXUAAI1kh.jpg\" alt=\"onlight\" width=\"70\" height=\"107\" /></p>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>";
    content += "<p style=\"padding-left: 40px;\">&nbsp;</p>";
    content += "<p style=\"padding-left: 40px;\">&nbsp;</p>";
    content += "<table style=\"height: 5px; width: 181px; border-color: #ec7063;\" border=\"4\" cellspacing=\"0\" cellpadding=\"2\">";
    content += "<tbody>";
    content += "<tr>";
    content += "<td style=\"width: 147px; padding-left: 30px;\">";
    content += "<p><a href=\"AutomaticMode\">Modo Autom&aacute;tico (DESACTIVADO)</a></p>";
    content += "</td>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>";   
    server.send(200, "text/html", content); 
   }
   else if (flag_modo_automatico == 1) { // automatico on
    content = "<h2 style=\"text-align: center;\"><span style=\"color: #cb4335;\"><strong>Control de Iluminaci&oacute;n</strong></span></h2>";
    content += "<p style=\"padding-left: 660px;\"><img src=\"http://revistacitylife.com/images/citylife_sitio/2016/julio/iluminacion_principal.jpg\" alt="" width=\"381\" height=\"267\" /></p>";
    content += "<p style=\"padding-left: 270px;\">&nbsp;</p>";
    content += "<table style=\"height: 75px; width: 179px; border-color: #ec7063;\" border=\"4\" cellspacing=\"0\" cellpadding=\"2\">";
    content += "<tbody>";
    content += "<tr>";
    content += "<td style=\"width: 165px; text-align: center;\">";
    content += "<p><a href=\"ManualMode\">Modo Manual</a></p>";
    content += "<p><img src=\"https://pbs.twimg.com/media/DO__eVDW4AIUdXx.jpg\" alt=\"onlight\" width=\"60\" height=\"107\" /></p>";
    content += "</td>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>";
    content += "<p style=\"padding-left: 40px;\">&nbsp;</p>";
    content += "<p style=\"padding-left: 40px;\">&nbsp;</p>";
    content += "<table style=\"height: 5px; width: 181px; border-color: #ec7063;\" border=\"4\" cellspacing=\"0\" cellpadding=\"2\">";
    content += "<tbody>";
    content += "<tr>";
    content += "<td style=\"width: 147px; padding-left: 30px;\">";
    content += "<p style=\"text-align: left;\"><a href=\"AutomaticMode\">Modo Autom&aacute;tico </a></p>";
    content += "</td>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>";
    content += "<p>&nbsp;</p>";
    content += "<p><span style=\"font-family: 'Comic Sans MS', arial, verdana;\">&nbsp; El modo autom&aacute;tico se encuentra activado con los siguientes valores:</span></p>";
    content += "<table style=\"width: 465px; height: 97px;\" border=\"1\" cellspacing=\"0\" cellpadding=\"1\">";
    content += "<tbody>";
    content += "<tr align=\"center\" bgcolor=\"#4682B4\">";
    content += "<td style=\"width: 149.234375px; text-align: center;\"><strong><span style=\"color: #ffffff;\">% Actual de Luz</span></strong></td>";
    content += "<td style=\"width: 175.46875px; text-align: center;\"><strong><span style=\"color: #ffffff;\">% Encendido de Luz</span></strong></td>";
    content += "<td style=\"width: 126.328125px; text-align: center;\"><strong><span style=\"color: #ffffff;\">Estado Actual</span></strong></td>";
    content += "</tr>";
    content += "<tr>";
    content += "<td style=\"width: 149.234375px; text-align: center;\">actual</td>";
    content += "<td style=\"width: 175.46875px; text-align: center;\">num programado</td>";
    content += "<td style=\"width: 126.328125px; text-align: center;\">ONuOFF</td>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>"; 
    server.send(200, "text/html", content);
   }
   else {  // manual apagada y auto apagada (inicio)
    content  = "<h2 style=\"text-align: center;\"><span style=\"color: #cb4335;\"><strong>Control de Iluminaci&oacute;n</strong></span></h2>";
    content += "<p style=\"padding-left: 660px;\"><img src=\"http://revistacitylife.com/images/citylife_sitio/2016/julio/iluminacion_principal.jpg\" alt="" width=\"381\" height=\"267\" /></p>";
    content += "<p style=\"padding-left: 270px;\">&nbsp;</p>";
    content += "<table style=\"height: 75px; width: 179px; border-color: #ec7063;\" border=\"4\" cellspacing=\"0\" cellpadding=\"2\">";
    content += "<tbody>";
    content += "<tr>";
    content += "<td style=\"width: 165px; text-align: center;\">";
    content += "<p><a href=\"ManualMode\">Modo Manual</a></p>";
    content += "<p><img src=\"https://pbs.twimg.com/media/DO__eVDW4AIUdXx.jpg\" alt=\"offlight\" width=\"60\" height=\"107\" /></p>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>";
    content += "<p style=\"padding-left: 40px;\">&nbsp;</p>";
    content += "<p style=\"padding-left: 40px;\">&nbsp;</p>";
    content += "<table style=\"height: 5px; width: 181px; border-color: #ec7063;\" border=\"4\" cellspacing=\"0\" cellpadding=\"2\">";
    content += "<tbody>";
    content += "<tr>";
    content += "<td style=\"width: 147px; padding-left: 30px;\">";
    content += "<p><a href=\"AutomaticMode\">Modo Autom&aacute;tico (DESACTIVADO)</a></p>";
    content += "</td>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>";    
    server.send(200, "text/html", content); 
    flag_modo_manual = 0;  // ERROR FUTURO vale cero cuando entra por segunda vez pero le ponemos cero otra vez solo xa el inicio.
   }
}

void ManualMode() {
   String content;
   if (flag_modo_manual == 0 && flag_modo_automatico == 0) { // manual encendida
    flag_modo_manual = 1;
    flag_modo_manual_on = 1;
    content  = "<h2 style=\"text-align: center;\"><span style=\"color: #cb4335;\"><strong>Control de Iluminaci&oacute;n</strong></span></h2>";
    content += "<p style=\"padding-left: 660px;\"><img src=\"http://revistacitylife.com/images/citylife_sitio/2016/julio/iluminacion_principal.jpg\" alt="" width=\"381\" height=\"267\" /></p>";
    content += "<p style=\"padding-left: 270px;\">&nbsp;</p>";
    content += "<table style=\"height: 75px; width: 179px; border-color: #ec7063;\" border=\"4\" cellspacing=\"0\" cellpadding=\"2\">";
    content += "<tbody>";
    content += "<tr>";
    content += "<td style=\"width: 165px; text-align: center;\">";
    content += "<p><a href=\"ManualMode\">Modo Manual</a></p>";
    content += "<p><img src=\"https://pbs.twimg.com/media/DO__cSgXUAAI1kh.jpg\" alt=\"onlight\" width=\"70\" height=\"107\" /></p>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>";
    content += "<p style=\"padding-left: 40px;\">&nbsp;</p>";
    content += "<p style=\"padding-left: 40px;\">&nbsp;</p>";
    content += "<table style=\"height: 5px; width: 181px; border-color: #ec7063;\" border=\"4\" cellspacing=\"0\" cellpadding=\"2\">";
    content += "<tbody>";
    content += "<tr>";
    content += "<td style=\"width: 147px; padding-left: 30px;\">";
    content += "<p><a href=\"AutomaticMode\">Modo Autom&aacute;tico (DESACTIVADO)</a></p>";
    content += "</td>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>";   
    server.send(200, "text/html", content); 
    digitalWrite(led, LOW);    
   }
   else if (flag_modo_manual == 0 && flag_modo_automatico == 1) { // no se puede encender manual por automatica
    content = "<h2 style=\"text-align: center;\"><span style=\"color: #cb4335;\"><strong>Control de Iluminaci&oacute;n</strong></span></h2>";
    content += "<p style=\"padding-left: 660px;\"><img src=\"http://revistacitylife.com/images/citylife_sitio/2016/julio/iluminacion_principal.jpg\" alt="" width=\"381\" height=\"267\" /></p>";
    content += "<p style=\"padding-left: 270px;\">&nbsp;</p>";
    content += "<table style=\"height: 75px; width: 179px; border-color: #ec7063;\" border=\"4\" cellspacing=\"0\" cellpadding=\"2\">";
    content += "<tbody>";
    content += "<tr>";
    content += "<td style=\"width: 165px; text-align: center;\">";
    content += "<p><a href=\"ManualMode\">Modo Manual</a></p>";
    content += "<p><img src=\"https://pbs.twimg.com/media/DO__eVDW4AIUdXx.jpg\" alt=\"onlight\" width=\"60\" height=\"107\" /></p>";
    content += "</td>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>";
    content += "<p style=\"padding-left: 40px;\">&nbsp;<span style=\"font-family: 'Comic Sans MS', arial, verdana;\">&nbsp; &nbsp;&nbsp;</span></p>";
    content += "<p><em><span style=\"font-family: 'Comic Sans MS', arial, verdana;\">&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;<span style=\"color: #cb4335;\">Para activar modo manual, es necesario desactivar el modo autom&aacute;tico primero.</span></span></em></p>";
    content += "<p>&nbsp;</p>";
    content += "<table style=\"height: 5px; width: 181px; border-color: #ec7063;\" border=\"4\" cellspacing=\"0\" cellpadding=\"2\">";
    content += "<tbody>";
    content += "<tr>";
    content += "<td style=\"width: 147px; padding-left: 30px;\">";
    content += "<p style=\"text-align: left;\"><a href=\"AutomaticMode\">Modo Autom&aacute;tico </a></p>";
    content += "</td>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>";
    content += "<p>&nbsp;</p>";
    content += "<p><span style=\"font-family: 'Comic Sans MS', arial, verdana;\">&nbsp; El modo autom&aacute;tico se encuentra activado con los siguientes valores:</span></p>";
    content += "<table style=\"width: 465px; height: 97px;\" border=\"1\" cellspacing=\"0\" cellpadding=\"1\">";
    content += "<tbody>";
    content += "<tr align=\"center\" bgcolor=\"#4682B4\">";
    content += "<td style=\"width: 149.234375px; text-align: center;\"><strong><span style=\"color: #ffffff;\">% Actual de Luz</span></strong></td>";
    content += "<td style=\"width: 175.46875px; text-align: center;\"><strong><span style=\"color: #ffffff;\">% Encendido de Luz</span></strong></td>";
    content += "<td style=\"width: 126.328125px; text-align: center;\"><strong><span style=\"color: #ffffff;\">Estado Actual</span></strong></td>";
    content += "</tr>";
    content += "<tr>";
    content += "<td style=\"width: 149.234375px; text-align: center;\">actual</td>";
    content += "<td style=\"width: 175.46875px; text-align: center;\">num programado</td>";
    content += "<td style=\"width: 126.328125px; text-align: center;\">ONuOFF</td>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>";
    server.send(200, "text/html", content);
   }
   else {  // manual apagada (resto de casos siempre off)
    flag_modo_manual = 0; 
    flag_modo_manual_on = 0;
    content  = "<h2 style=\"text-align: center;\"><span style=\"color: #cb4335;\"><strong>Control de Iluminaci&oacute;n</strong></span></h2>";
    content += "<p style=\"padding-left: 660px;\"><img src=\"http://revistacitylife.com/images/citylife_sitio/2016/julio/iluminacion_principal.jpg\" alt="" width=\"381\" height=\"267\" /></p>";
    content += "<p style=\"padding-left: 270px;\">&nbsp;</p>";
    content += "<table style=\"height: 75px; width: 179px; border-color: #ec7063;\" border=\"4\" cellspacing=\"0\" cellpadding=\"2\">";
    content += "<tbody>";
    content += "<tr>";
    content += "<td style=\"width: 165px; text-align: center;\">";
    content += "<p><a href=\"ManualMode\">Modo Manual</a></p>";
    content += "<p><img src=\"https://pbs.twimg.com/media/DO__eVDW4AIUdXx.jpg\" alt=\"offlight\" width=\"60\" height=\"107\" /></p>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>";
    content += "<p style=\"padding-left: 40px;\">&nbsp;</p>";
    content += "<p style=\"padding-left: 40px;\">&nbsp;</p>";
    content += "<table style=\"height: 5px; width: 181px; border-color: #ec7063;\" border=\"4\" cellspacing=\"0\" cellpadding=\"2\">";
    content += "<tbody>";
    content += "<tr>";
    content += "<td style=\"width: 147px; padding-left: 30px;\">";
    content += "<p><a href=\"AutomaticMode\">Modo Autom&aacute;tico (DESACTIVADO)</a></p>";
    content += "</td>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>";   
    server.send(200, "text/html", content);
    digitalWrite(led, HIGH); 
   } 
  }

void AutomaticMode() {
  String content; 
   if (flag_modo_manual_on == 1) { // no se puede activar automatico
    content  = "<h2 style=\"text-align: center;\"><span style=\"color: #cb4335;\"><strong>Control de Iluminaci&oacute;n</strong></span></h2>";
    content += "<p style=\"padding-left: 660px;\"><img src=\"http://revistacitylife.com/images/citylife_sitio/2016/julio/iluminacion_principal.jpg\" alt="" width=\"381\" height=\"267\" /></p>";
    content += "<p style=\"padding-left: 270px;\">&nbsp;</p>";
    content += "<table style=\"height: 75px; width: 179px; border-color: #ec7063;\" border=\"4\" cellspacing=\"0\" cellpadding=\"2\">";
    content += "<tbody>";
    content += "<tr>";
    content += "<td style=\"width: 165px; text-align: center;\">";
    content += "<p><a href=\"ManualMode\">Modo Manual</a></p>";
    content += "<p><img src=\"https://pbs.twimg.com/media/DO__cSgXUAAI1kh.jpg\" alt=\"onlight\" width=\"70\" height=\"107\" /></p>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>";
    content += "<p style=\"padding-left: 40px;\">&nbsp;</p>";
    content += "<p style=\"padding-left: 40px;\">&nbsp;</p>";
    content += "<table style=\"height: 5px; width: 181px; border-color: #ec7063;\" border=\"4\" cellspacing=\"0\" cellpadding=\"2\">";
    content += "<tbody>";
    content += "<tr>";
    content += "<td style=\"width: 147px; padding-left: 30px;\">";
    content += "<p><a href=\"AutomaticMode\">Modo Autom&aacute;tico (DESACTIVADO)</a></p>";
    content += "</td>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>";  
    content += "<p><span style=\"font-family: 'Comic Sans MS', arial, verdana;\">&nbsp; &nbsp; &nbsp; &nbsp;&nbsp;</span></p>";
    content += "<p><em><span style=\"font-family: 'Comic Sans MS', arial, verdana;\">&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;<span style=\"color: #cb4335;\">Para activar modo autom&aacute;tico, es necesario desactivar el modo manual primero.</span></span></em></p>";
    content += "<p>&nbsp;</p>";  
    server.send(200, "text/html", content);  
   }  
   else if (flag_modo_automatico == 1) { // si esta activado, lo desactivo.
    flag_modo_automatico = 0;    
    content  = "<h2 style=\"text-align: center;\"><span style=\"color: #cb4335;\"><strong>Control de Iluminaci&oacute;n</strong></span></h2>";
    content += "<p style=\"padding-left: 660px;\"><img src=\"http://revistacitylife.com/images/citylife_sitio/2016/julio/iluminacion_principal.jpg\" alt="" width=\"381\" height=\"267\" /></p>";
    content += "<p style=\"padding-left: 270px;\">&nbsp;</p>";
    content += "<table style=\"height: 75px; width: 179px; border-color: #ec7063;\" border=\"4\" cellspacing=\"0\" cellpadding=\"2\">";
    content += "<tbody>";
    content += "<tr>";
    content += "<td style=\"width: 165px; text-align: center;\">";
    content += "<p><a href=\"ManualMode\">Modo Manual</a></p>";
    content += "<p><img src=\"https://pbs.twimg.com/media/DO__eVDW4AIUdXx.jpg\" alt=\"offlight\" width=\"60\" height=\"107\" /></p>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>";
    content += "<p style=\"padding-left: 40px;\">&nbsp;</p>";
    content += "<p style=\"padding-left: 40px;\">&nbsp;</p>";
    content += "<table style=\"height: 5px; width: 181px; border-color: #ec7063;\" border=\"4\" cellspacing=\"0\" cellpadding=\"2\">";
    content += "<tbody>";
    content += "<tr>";
    content += "<td style=\"width: 147px; padding-left: 30px;\">";
    content += "<p><a href=\"AutomaticMode\">Modo Autom&aacute;tico (DESACTIVADO)</a></p>";
    content += "</td>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>";    
    server.send(200, "text/html", content); 
   }
   else { // se puede activar automatico
    flag_modo_automatico = 1;
    content = "<h2 style=\"text-align: center;\"><span style=\"color: #cb4335;\"><strong>Control de Iluminaci&oacute;n</strong></span></h2>";
    content += "<p style=\"padding-left: 660px;\"><img src=\"http://revistacitylife.com/images/citylife_sitio/2016/julio/iluminacion_principal.jpg\" alt="" width=\"381\" height=\"267\" /></p>";
    content += "<p style=\"padding-left: 270px;\">&nbsp;</p>";
    content += "<table style=\"height: 75px; width: 179px; border-color: #ec7063;\" border=\"4\" cellspacing=\"0\" cellpadding=\"2\">";
    content += "<tbody>";
    content += "<tr>";
    content += "<td style=\"width: 165px; text-align: center;\">";
    content += "<p><a href=\"ManualMode\">Modo Manual</a></p>";
    content += "<p><img src=\"https://pbs.twimg.com/media/DO__eVDW4AIUdXx.jpg\" alt=\"onlight\" width=\"60\" height=\"107\" /></p>";
    content += "</td>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>";
    content += "<p style=\"padding-left: 40px;\">&nbsp;</p>";
    content += "<p style=\"padding-left: 40px;\">&nbsp;</p>";
    content += "<table style=\"height: 5px; width: 181px; border-color: #ec7063;\" border=\"4\" cellspacing=\"0\" cellpadding=\"2\">";
    content += "<tbody>";
    content += "<tr>";
    content += "<td style=\"width: 147px; padding-left: 30px;\">";
    content += "<p style=\"text-align: left;\"><a href=\"AutomaticMode\">Modo Autom&aacute;tico </a></p>";
    content += "</td>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>";
    content += "<p>&nbsp;</p>";
    content += "<p><span style=\"font-family: 'Comic Sans MS', arial, verdana;\">&nbsp; El modo autom&aacute;tico se encuentra activado con los siguientes valores:</span></p>";
    content += "<table style=\"width: 465px; height: 97px;\" border=\"1\" cellspacing=\"0\" cellpadding=\"1\">";
    content += "<tbody>";
    content += "<tr align=\"center\" bgcolor=\"#4682B4\">";
    content += "<td style=\"width: 149.234375px; text-align: center;\"><strong><span style=\"color: #ffffff;\">% Actual de Luz</span></strong></td>";
    content += "<td style=\"width: 175.46875px; text-align: center;\"><strong><span style=\"color: #ffffff;\">% Encendido de Luz</span></strong></td>";
    content += "<td style=\"width: 126.328125px; text-align: center;\"><strong><span style=\"color: #ffffff;\">Estado Actual</span></strong></td>";
    content += "</tr>";
    content += "<tr>";
    content += "<td style=\"width: 149.234375px; text-align: center;\">actual</td>";
    content += "<td style=\"width: 175.46875px; text-align: center;\">num programado</td>";
    content += "<td style=\"width: 126.328125px; text-align: center;\">ONuOFF</td>";
    content += "</tr>";
    content += "</tbody>";
    content += "</table>"; 
    server.send(200, "text/html", content);
   }
}

void loop() {
  
   // Aviso de wifi desconectada y encendido led azul.
   if (WiFi.status() == WL_DISCONNECTED) {
      Serial.println("WiFi desconectada");
      delay(500);
   }
  server.handleClient();
}
