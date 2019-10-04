#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Configuramos el nombre de la red y la contraseña*/
const char *ssid = "AGETIC0001";
const char *password = "evoevopresidente";
int guess = 0;
String nguess;
ESP8266WebServer server(80);

void handleRoot() 
  {
      guess = guess + 1;
      nguess = (String)guess;
      server.send(200, "text/html", nguess);
      Serial.print("Nuevo visitante ");
      Serial.println(nguess);
  }

void setup() 
  {
    delay(1000);
    Serial.begin(115200);
    Serial.println();
    Serial.print("Configurando el punto de acceso");
    nguess = "0";
    
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
