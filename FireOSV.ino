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
#include "Navigation.hpp"
#include "Button.hpp"

//============================================= Settings
#define PUSH_BUTTON_1_ANALOG_PORT A0
#define PUSH_BUTTON_2_ANALOG_PORT A1

#define RX_PIN 2
#define TX_PIN 3
#define FIRE_TEAM 3
#define ARUCO_ID 12
#define TEAM_NAME "Notre Dame"

//=============================================

extern Photoresistor p1 = Photoresistor(A1);
extern Button b1 = Button(PUSH_BUTTON_1_ANALOG_PORT);
extern Button b2 = Button(PUSH_BUTTON_2_ANALOG_PORT);

extern Navigation nav = Navigation(TEAM_NAME, FIRE_TEAM, ARUCO_ID, TX_PIN, RX_PIN);

void setup() 
{
  Serial.begin(9600);

  Serial.println(TEAM_NAME);
  Serial.println("Initializing robot!");
  Serial.println(nav.init() ? "Navigation initalized" : "[Error] Navigation initalization failed!");
}

Coordinate coordinate = Coordinate();

void loop() 
{
  nav.passRawCoordinates(&coordinate);

  printCoordinate(coordinate);
}
