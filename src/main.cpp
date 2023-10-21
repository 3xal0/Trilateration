#include <SPI.h>
#include <WiFi.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <string>
using namespace std;

float rssi;
boolean CONNECTED = false;


// --------------- > Definition d'un point (X,Y)
struct point
{
  float x, y;
};

// --------------- > Definition d'une ancre 
struct anchor
{
  char* ssid ;
  char* pass;
  point position;
  float RSSI;
  int parameter;
};

float norm(point p) // get the norm of a vector
{
  return pow(pow(p.x, 2) + pow(p.y, 2), .5);
}



void Connexion(anchor x)
{

  Serial.print(" Connexion à : ");
  Serial.println(x.ssid);
  char* ssid = x.ssid;
  char* pass = x.pass;

  WiFi.begin(ssid, pass);

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connexion échouée");
  }
  else
  {
    CONNECTED = true;
  }
}

void Deconnexion()
{
  if (CONNECTED)
  {
    WiFi.end();
    CONNECTED = false;
    Serial.println("Deconnexion effectuée");
  }
  else
  {
    Serial.println("Votre appareil n'est pas connecté");
  }
}

float RSSI(anchor x)
{
  if (CONNECTED)
  {
    int echantillon = 0;
    float value[5];
    while (echantillon != 5)
    {

      rssi = WiFi.RSSI();
      Serial.println(rssi);

      value[echantillon] = rssi;
      

      delay(2000);
      echantillon++;
    }

    for (int boucle = 0; boucle <= 5; boucle++)
    {
      x.RSSI = x.RSSI + value[boucle];
    }
    x.RSSI = x.RSSI / 5.0;
    Serial.println(x.RSSI);
    return x.RSSI;
    
  }
  else
  {
    Serial.println("Relevé impossible sans ancre connectée");
  }
}

point trilateration(point point1, point point2, point point3, double r1, double r2, double r3)
{
  point resultPose;
  // unit vector in a direction from point1 to point 2
  double p2p1Distance = pow(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2), 0.5);
  point ex = {(point2.x - point1.x) / p2p1Distance, (point2.y - point1.y) / p2p1Distance};
  point aux = {point3.x - point1.x, point3.y - point1.y};
  // signed magnitude of the x component
  double i = ex.x * aux.x + ex.y * aux.y;
  // the unit vector in the y direction.
  point aux2 = {point3.x - point1.x - i * ex.x, point3.y - point1.y - i * ex.y};
  point ey = {aux2.x / norm(aux2), aux2.y / norm(aux2)};
  // the signed magnitude of the y component
  double j = ey.x * aux.x + ey.y * aux.y;
  // coordinates
  double x = (pow(r1, 2) - pow(r2, 2) + pow(p2p1Distance, 2)) / (2 * p2p1Distance);
  double y = (pow(r1, 2) - pow(r3, 2) + pow(i, 2) + pow(j, 2)) / (2 * j) - i * x / j;
  // result coordinates
  double finalX = point1.x + x * ex.x + y * ey.x;
  double finalY = point1.y + x * ex.y + y * ey.y;
  resultPose.x = finalX;
  resultPose.y = finalY;
  return resultPose;
}


// char ssid[] = "Iphone de Uol"; -37
// char ssid2[] = "Iphone de Alex"; -49

// password of your WPA Network
// char pass[] = "SY25tpRT";
// char pass2[] = "Lexouille";

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  point Position;
  anchor a1 = {"SY25_A1", "", {0, 0}, 0, -34};
  anchor a2 = {"SY25_A2", "", {6.5,0 }, 0, -34};
  anchor a3 = {"SY25_A3", "", {6.5, 10}, 0, -37};

  // -------------- > Boucle de connexion aux 3 ancres ainsi que des relevés des distances
  //while (a1.RSSI==0 || a2.RSSI==0 || a3.RSSI==0)
  //{
    Connexion(a1);
    a1.RSSI=RSSI(a1);
    Deconnexion();

    delay(1000);

    Connexion(a2);
    a2.RSSI=RSSI(a2);
    Deconnexion();

    delay(1000);

    Connexion(a3);
    a3.RSSI=RSSI(a3);;
    Deconnexion();
 // }

  // -------------- > Calcul des distances 
  Serial.println("Calcul des distances ...");
  a1.RSSI = pow(10, ((a1.parameter - a1.RSSI) / (10 * 2.7)));
  Serial.println(a1.RSSI);
  a2.RSSI = pow(10, ((a2.parameter - a2.RSSI) / (10 * 2.7)));
   Serial.println(a2.RSSI);
  a3.RSSI = pow(10, ((a3.parameter - a3.RSSI) / (10 * 2.1)));
   Serial.println(a3.RSSI);
  Serial.println("Fin du Calcul ...");

  // -------------- > Mise en route de l'algorithme de trilatération 2D
  Serial.println("Début de trilatération ...");
  Position = trilateration(a1.position, a2.position, a3.position, static_cast<double>(a1.RSSI), static_cast<double>(a2.RSSI), static_cast<double>(a3.RSSI));
  Serial.println("Fin de trilatération ...");
  Serial.print(" X: ");
  Serial.print (Position.x);
  Serial.print(" /  Y:");
  Serial.println(Position.y);

  delay(2000);
}
