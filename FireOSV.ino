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

#include <Servo.h>

#include "Photoresistor.hpp"
#include "Navigation.hpp"
#include "Button.hpp"
#include "Motor.hpp"
#include "Utilities.hpp"

//=============================================
//OSV Settings (Pins, values, etc.)
//=============================================
#define PUSH_BUTTON_1_ANALOG_PORT 9
#define PUSH_BUTTON_2_ANALOG_PORT 8

#define NAVIGATION_ENABLE 1 //Use for debugging w/o aruco system
#define WIFI_RX 13
#define WIFI_TX 12
#define FIRE_TEAM 3
#define ARUCO_ID 13
#define TEAM_NAME "Notre Dame"

#define RIGHT_PIN_1 5
#define RIGHT_PIN_2 4
#define RIGHT_POWER_PIN 10
#define LEFT_PIN_1 7
#define LEFT_PIN_2 6
#define LEFT_POWER_PIN 11

#define L_EN 0 //We direct-wire the 5v "_EN" connections to 5v bus instead of arduino
#define R_EN 0 //Use 0 to essentially discard values

#define SERVO_PIN 3
#define SERVO_DEPLOY 30
#define SERVO_RETRACT 145

//=============================================
//Global OSV Controls
//=============================================

//extern const Photoresistor p1 = Photoresistor(A1);
static const Button BUTTON_RIGHT = Button(PUSH_BUTTON_1_ANALOG_PORT);
static const Button BUTTON_CENTER = Button(PUSH_BUTTON_2_ANALOG_PORT);

static const Motor RIGHT_MOTOR = Motor(RIGHT_PIN_1, RIGHT_PIN_2, RIGHT_POWER_PIN);
static const Motor LEFT_MOTOR = Motor(LEFT_PIN_1, LEFT_PIN_2, LEFT_POWER_PIN);

static const Navigation NAV = Navigation(TEAM_NAME, FIRE_TEAM, ARUCO_ID, WIFI_RX, WIFI_TX, &RIGHT_MOTOR, &LEFT_MOTOR);

static const Servo SERVO = Servo();

//=============================================

void setup() 
{
  Serial.begin(9600);

  Serial.println(TEAM_NAME);
  Serial.println("Initializing robot!");

  RIGHT_MOTOR.init();
  LEFT_MOTOR.init();

  delay(2000);

  while (NAVIGATION_ENABLE && !NAV.init())
  {
    Serial.println("Initializing Navigation...");
    delay(500);
  }

  Serial.print("Navigation status: ");
  Serial.println(NAVIGATION_ENABLE ? "Success" : "[WARNING] DISABLED");
  
  SERVO.attach(SERVO_PIN);
}

static const Coordinate coord = Coordinate();

void loop() 
{
  if (NAV.getVehicleY() < 1.0)
    NAV.turnToDegrees(90.0);
  else
    NAV.turnToDegrees(270.0);

  LEFT_MOTOR.turn(FORWARD);
  RIGHT_MOTOR.turn(FORWARD);
  delay(6000);
  LEFT_MOTOR.stop();
  RIGHT_MOTOR.stop();

  //analyzeButtons(&BUTTON_CENTER, &BUTTON_RIGHT);

  analyzeFlames(A0, A1, A2, A3);

  delay(1000);

  /*

  LEFT_MOTOR.turn(REVERSE);
  RIGHT_MOTOR.turn(REVERSE);
  delay(1000);
  LEFT_MOTOR.stop();
  RIGHT_MOTOR.stop();

  NAV.turnToDegrees(0.0);

  NAV.moveDistance(4.0);

  NAV.turnToDegrees(90.0);

  NAV.moveDistance(0.5);

  NAV.turnToDegrees(0.0);

  NAV.moveDistance(2.0);*/


  delay(5000); //End delay
}
