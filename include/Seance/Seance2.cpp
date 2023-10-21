#include <SPI.h>
#include <WiFi.h>

//SSID of your network
char ssid[] = "Iphone de Uol";

//password of your WPA Network
char pass[] = "SY25tpRT";
float rssi;
int i = 0 ;
void setup()
{
  Serial.begin(9600);
Serial.println(" Connexion à SSID2 : ");
 WiFi.begin(ssid, pass);

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    i=1;
   
  }
  // if you are connected, print out info about the connection:
  else {
   // print the received signal strength:
   rssi = WiFi.RSSI();
  Serial.print("RSSI:");
  Serial.println(rssi);
  }
    

}

void loop () {
  if(i==1){
    WiFi.begin(ssid, pass);
  i=0;
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    i=1;
   
  }
  // if you are connected, print out info about the connection:
  else {
   // print the received signal strength:
   rssi = WiFi.RSSI();
  Serial.print("RSSI:");
  Serial.println(rssi);
  }
  }
  int u=0;
  float d=0;
 float tab [5];
 if (i==0){
  while(u!=5){
 

rssi = WiFi.RSSI();
Serial.println(rssi);

tab [u] = rssi;
Serial.println(tab[u]);

delay(2000);
   u++;
  }
  for(int boucle=0;boucle<=5;boucle++){
    d= d+ tab[boucle];
  }
  Serial.println(d);
  d=d/5;
  d= pow(10,((-37-d)/(10*2.7)));// 2 est N, il varie selon l'envrionnement
  Serial.print("La distance est de : ");
Serial.println(d);
 }
delay(2000);
}