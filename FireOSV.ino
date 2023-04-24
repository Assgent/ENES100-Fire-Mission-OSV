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

//=============================================
//OSV Settings (Pins, values, etc.)
//=============================================
#define PUSH_BUTTON_1_ANALOG_PORT A0
#define PUSH_BUTTON_2_ANALOG_PORT A1

#define WIFI_RX 3
#define WIFI_TX 4
#define FIRE_TEAM 3
#define ARUCO_ID 13
#define TEAM_NAME "Notre Dame"

#define RIGHT_RWPM 9
#define RIGHT_LWPM 10
#define LEFT_RWPM 5
#define LEFT_LWPM 6
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

static const Motor RIGHT_MOTOR = Motor(RIGHT_RWPM, RIGHT_LWPM, L_EN, R_EN);
static const Motor LEFT_MOTOR = Motor(LEFT_RWPM, LEFT_LWPM, L_EN, R_EN);

static const Navigation NAV = Navigation(TEAM_NAME, FIRE_TEAM, ARUCO_ID, WIFI_TX, WIFI_RX, &RIGHT_MOTOR, &LEFT_MOTOR);

static const Servo SERVO = Servo();

//=============================================

void setup() 
{
  Serial.begin(9600);

  Serial.println(TEAM_NAME);
  Serial.println("Initializing robot!");

  RIGHT_MOTOR.init();
  LEFT_MOTOR.init();

  Serial.println(NAV.init() ? "Navigation initialized!" : "[Error] Navigation Initialization Failed!");
  
  SERVO.attach(SERVO_PIN);
}

static const Coordinate coord = Coordinate();

void loop() 
{
  RIGHT_MOTOR.setPower(-100);
  LEFT_MOTOR.setPower(100);
  /*
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
