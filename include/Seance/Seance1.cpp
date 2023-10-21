#include <SPI.h>
#include <WiFi.h>

//SSID of your network
char ssid[] = "Iphone de Uol";
char ssid2[] = "Alcatel 1S";

//password of your WPA Network
char pass[] = "SY25tpRT";
long rssi;
void setup()
{
  Serial.begin(9600);
Serial.println(" Connexion à SSID2 : ");
 WiFi.begin(ssid2, pass);

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
   
  }
  // if you are connected, print out info about the connection:
  else {
   // print the received signal strength:
   rssi = WiFi.RSSI();
  Serial.print("RSSI:");
  Serial.println(rssi);
  }
    
  WiFi.end();
}

void loop () {
  Serial.println("Yo les ptits lou");

Serial.println(" Connexion à SSID : ");
 WiFi.begin(ssid, pass);

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
   
  }
  // if you are connected, print out info about the connection:
  else {
   // print the received signal strength:
   rssi = WiFi.RSSI();
  Serial.print("RSSI:");
  Serial.println(rssi);
  }
  WiFi.end();

Serial.println(" Connexion à SSID2 : ");
 WiFi.begin(ssid2, pass);

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    
  }
  // if you are connected, print out info about the connection:
  else {
   // print the received signal strength:
   rssi = WiFi.RSSI();
  Serial.print("RSSI:");
  Serial.println(rssi);
  }
    
  WiFi.end();
}