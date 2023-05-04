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
#define PUSH_BUTTON_1_ANALOG_PORT A0
#define PUSH_BUTTON_2_ANALOG_PORT A1

#define NAVIGATION_ENABLE 1 //Use for debugging w/o aruco system
#define WIFI_RX 12
#define WIFI_TX 13
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

  Serial.println("Navigation initialized!");
  
  SERVO.attach(SERVO_PIN);
}

static const Coordinate coord = Coordinate();

void loop() 
{
  locationMoveTest(&NAV);

  /*
  LEFT_MOTOR.setPower(-90);
  delay(1000);

  NAV.turnToDegrees(0.0);
  delay(1000);
  NAV.turnToDegrees(45.0);
  delay(1000);
  NAV.turnToDegrees(180.0);
  delay(1000);
  NAV.turnToDegrees(315.0);
  delay(1000);
  
  RIGHT_MOTOR.setPower(-100);
  LEFT_MOTOR.setPower(100);
  
  NAV.turnToDegrees(1.0);
  delay(1000);
  
  for (double i = 45.0; i <= 135.0; i += 45.0)
  {
    NAV.turnToDegrees(i);
    delay(1000);
  }

  NAV.turnToDegrees(1.0);
  delay(1000);*/
  /*
  RIGHT_MOTOR.setPower(100);
  LEFT_MOTOR.setPower(100);

  delay(3000);

  RIGHT_MOTOR.stop();
  LEFT_MOTOR.stop();

   for (int i = 30; i < 146; i++) {
    SERVO.write(i);
    delay(20);
  }
  delay(2000);
  for (int i = 145; i > 30; i--) {
    SERVO.write(i);
    delay(20);
  }
  delay(2000);

  RIGHT_MOTOR.setPower(-100);
  LEFT_MOTOR.setPower(-100);

  delay(1000);

  RIGHT_MOTOR.stop();
  LEFT_MOTOR.stop();

  RIGHT_MOTOR.setPower(100);
  LEFT_MOTOR.setPower(-100);

  delay(2000);

  RIGHT_MOTOR.setPower(100);
  LEFT_MOTOR.setPower(100);

  delay(8000);

  RIGHT_MOTOR.stop();
  LEFT_MOTOR.stop();

  RIGHT_MOTOR.setPower(-60);
  LEFT_MOTOR.setPower(60);

  delay(4000);

  RIGHT_MOTOR.setPower(100);
  LEFT_MOTOR.setPower(100);

  delay(3500);

  RIGHT_MOTOR.setPower(30);
  LEFT_MOTOR.setPower(-30);

  delay(4000);

  RIGHT_MOTOR.stop();
  LEFT_MOTOR.stop();
  */
  /*NAV.moveDistance(0.5, 100);
  NAV.turnToDegrees(90);  
  NAV.moveDistance(0.3, 100);
  NAV.turnToDegrees(0.0);
  NAV.moveDistance(0.5, 100);*/
}
