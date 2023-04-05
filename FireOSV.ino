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
#include "Motor.hpp"

//=============================================
//OSV Settings (Pins, values, etc.)
//=============================================
#define PUSH_BUTTON_1_ANALOG_PORT A0
#define PUSH_BUTTON_2_ANALOG_PORT A1

#define RX_PIN 2
#define TX_PIN 3
#define FIRE_TEAM 3
#define ARUCO_ID 10
#define TEAM_NAME "Notre Dame"

#define RIGHT_RWPM 9
#define RIGHT_LWPM 10
#define LEFT_RWPM 5
#define LEFT_LWPM 6
#define L_EN 0 //We direct-wire the 5v "_EN" connections to 5v bus instead of arduino
#define R_EN 0 //Use 0 to essentially discard values

//=============================================
//Global OSV Controls
//=============================================

//extern const Photoresistor p1 = Photoresistor(A1);
extern const Button BUTTON_RIGHT = Button(PUSH_BUTTON_1_ANALOG_PORT);
extern const Button BUTTON_CENTER = Button(PUSH_BUTTON_2_ANALOG_PORT);

extern const Navigation NAV = Navigation(TEAM_NAME, FIRE_TEAM, ARUCO_ID, TX_PIN, RX_PIN);

extern const Motor RIGHT_MOTOR = Motor(RIGHT_RWPM, RIGHT_LWPM, L_EN, R_EN);
extern const Motor LEFT_MOTOR = Motor(LEFT_RWPM, LEFT_LWPM, L_EN, R_EN);

//=============================================

void setup() 
{
  Serial.begin(9600);

  Serial.println(TEAM_NAME);
  Serial.println("Initializing robot!");
  //Serial.println(NAV.init() ? "Navigation initalized" : "[Error] Navigation initalization failed!");
  RIGHT_MOTOR.init();
  LEFT_MOTOR.init();
}

void loop() 
{

}
