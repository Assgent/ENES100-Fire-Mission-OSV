/*
============================================================
                 ENES100 Fire Team OSV Code
============================================================

Source, documentation, and tutorial: https://github.com/Assgent/ENES100-Fire-Mission-OSV (please update!!!)

Tips:
-Use "int" for integers
-Use "double" for decimals
-Please indent and keep it clean!
*/

#include "Photoresistor.cpp"

extern Photoresistor p1 = Photoresistor(A1);

void setup() 
{
  Serial.begin(9600);

  Serial.println("Initializing robot!");
}

void loop() 
{
  Serial.println(p1.balloonGone());
}
