#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Configuramos el nombre de la red y la contraseña*/
const char *ssid = "Introduce un nombre para tu Red WLAN";
const char *password = "Introduce una contraseña para tu Red WLAN";
int guess = 0;
String nguess;
ESP8266WebServer server(80);

void handleRoot() 
  {
      
      
      server.send(200, "text/html", "Hola gentita");
      Serial.print("Nuevo visitante ");
     
  }

void setup() 
  {
    delay(1000);
    Serial.begin(115200);
    Serial.println();
    Serial.print("Configurando el punto de acceso");
    
    
    WiFi.softAP(ssid, password);

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP Direccion IP: ");
    Serial.println(myIP);
    server.on("/", handleRoot);
    server.begin();
    Serial.println("HTTP servidor iniciado");
  }

void loop() {
  server.handleClient();
}
