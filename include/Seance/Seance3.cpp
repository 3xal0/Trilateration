#include <SPI.h>
#include <WiFi.h>

// SSID of your network
char ssid[] = "Iphone de Uol";
char ssid2[] = "Iphone de Alex";
int num_co = 0;

float DLOU = 1.0;
float Dalca = 0.1;

// password of your WPA Network
char pass[] = "SY25tpRT";
char pass2[] = "Lexouille";
float rssi;
int i = 0;
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (num_co == 0)
  {
    Serial.println(" Connexion à Lou : ");
    WiFi.begin(ssid, pass);

    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("Couldn't get a wifi connection");
      i = 1;
    }
    // if you are connected, print out info about the connection:
    else
    {
      // print the received signal strength:
      i = 0;
      rssi = WiFi.RSSI();
      Serial.print("RSSI:");
      Serial.println(rssi);
      num_co = 1;
    }
  }
  else
  {
    Serial.println(" Connexion à TEL DU PROF: ");
    WiFi.begin(ssid2, pass2);

    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("Couldn't get a wifi connection");
      i = 1;
    }
    // if you are connected, print out info about the connection:
    else
    {
      // print the received signal strength:
      i = 0;
      rssi = WiFi.RSSI();
      Serial.print("RSSI:");
      Serial.println(rssi);
      num_co = 0;
    }
  }

  int u = 0 ;
  float d = 0,d1,d2;
  float tab[5];
  if (i == 0)
  {
    while (u != 5)
    {

      rssi = WiFi.RSSI();
      Serial.println(rssi);

      tab[u] = rssi;
      Serial.println(tab[u]);

      delay(2000);
      u++;
    }
    for (int boucle = 0; boucle <= 5; boucle++)
    {
      d = d + tab[boucle];
    }
    Serial.println(d);
    d = d / 5;
    if (num_co == 1)
    {
      d = pow(10, ((-37 - d) / (10 * 2.7))); // 2 est N, il varie selon l'envrionnement
      d2 = d;
      Serial.print("La distance est de : ");
      Serial.println(d2);
    }
    else
    {
      d = pow(10, ((-49 - d) / (10 * 2))); // 2 est N, il varie selon l'envrionnement
       d1 = d;
      Serial.print("La distance est de : ");
      Serial.println(d1);
    }
    if (d1 && d2){
      d2= DLOU - d2;
      d1= DLOU + d1;
      Serial.print("Je me postionne à ");
      Serial.print(d2);
      Serial.print("DE LOU et à ");
      Serial.print(d1);
      Serial.println(" de ALCATEL");
    }
  }
  delay(2000);
  WiFi.end();
}