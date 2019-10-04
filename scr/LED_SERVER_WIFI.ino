/* MODULO ESP8266  */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
//HTML
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<center>
<h1> CONTROL LED WIFI </h1><br>
Tocame para <a href="ledOn" target="myIframe"> Encenderme </a><br>
Tocame para <a href="ledOff" target="myIframe"> Apagarme </a><br>
Estoy :<iframe name="myIframe" width="100" height="25" frameBorder="0"><br>
<hr>
<a href="aprendiendo"> </a>
</center>
 
</body>
</html>
)=====";



#define LED 2  
 

const char* ssid = "Introducimos la red Wifi";
const char* password = "Introducimos la contraseña del Wifi";
 
ESP8266WebServer server(80); //Puerto del servidor
 

void handleRoot() {
 Serial.println("You called root page");
 String s = MAIN_page; 
 server.send(200, "text/html", s); 
}
 
void handleLEDon() { 
 Serial.println("LED on page");
 digitalWrite(LED,LOW); 
 server.send(200, "text/html", "Caliente"); 
}
 
void handleLEDoff() { 
 Serial.println("LED off page");
 digitalWrite(LED,HIGH); 
 server.send(200, "text/html", "Frio"); 
}

void setup(void){
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);     
  Serial.println("");
  pinMode(LED,OUTPUT); 
  digitalWrite(LED,HIGH);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
 
  server.on("/", handleRoot);      
  server.on("/ledOn", handleLEDon); 
  server.on("/ledOff", handleLEDoff);
 
  server.begin();                  // Iniciamos nuestro servidor
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}
