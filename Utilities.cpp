#include <Arduino.h>

#include "Utilities.hpp"
#include "Motor.hpp"

/*
Tests directional capability of both motors. 
*/
void motorTest(Motor* left, Motor* right)
{
  struct MotorArgs {
    unsigned short leftMotor : 1;
    unsigned short rightMotor : 1;
    unsigned int pad : 14;
  } args;

  for (int i = 0; i <= 3; i++)
  {
    args = *(struct MotorArgs*)&i; //Evil bit hack

    left->turn(args.leftMotor);
    right->turn(args.rightMotor);

    delay(1000);
  }

  left->stop();
  right->stop();
}

/*
Tests the turnToDegrees(angle) function.
*/
void turnTest(Navigation *nav)
{
  double angle;

  for (angle = 0.0; angle < 360.0; angle += 30)
  {
    nav->turnToDegrees(angle);
    delay(1000);    
  }

  for (; angle >= -1.0; angle -= 45)
  {
    nav->turnToDegrees(angle);
    delay(1000);    
  }
}

/*
Tests the moveDistance(distance) function.
*/
void moveTest(Navigation *nav)
{
  double distance;

  for (distance = 0.0; distance <= 0.30; distance += 0.10)
  {
    nav->moveDistance(distance);
    delay(1000);  
  }

  for (distance = 0.0; distance >= -0.30; distance -= 0.10)
  {
    nav->moveDistance(distance);
    delay(1000);  
  }
}

/*
Tests the goToCoordinates(Coordinate target) function.
*/
void locationMoveTest(Navigation *nav)
{
  const Coordinate COORDINATES[] = {
    Coordinate(0.5, 0.5, -1.0), 
    Coordinate(1.0, 0.5, -1.0), 
    Coordinate(1.0, 1.0, -1.0), 
    Coordinate(0.5, 1.0, -1.0)
  };

  for (int i = 0; i < LEN(COORDINATES); i++)
  {
    nav->goToCoordinates(COORDINATES[i]);
    delay(1000);
  }
}