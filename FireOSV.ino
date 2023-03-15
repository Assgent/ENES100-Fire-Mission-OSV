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

#include "Photoresistor.hpp"
#include "Button.hpp"

//=============================================
#define PUSH_BUTTON_1_ANALOG_PORT A0
#define PUSH_BUTTON_2_ANALOG_PORT A1

//=============================================

//extern Photoresistor p1 = Photoresistor(A1);
extern Button b1 = Button(PUSH_BUTTON_1_ANALOG_PORT);
extern Button b2 = Button(PUSH_BUTTON_2_ANALOG_PORT);

void setup() 
{
  Serial.begin(9600);

  Serial.println("Initializing robot!");
}

void loop() 
{
  Serial.println(getOrientation(b1, b2));
}
