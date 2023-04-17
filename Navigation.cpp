#include <Arduino.h>

#include "Utilities.hpp"
#include "Navigation.hpp"
#include "Motor.hpp"
#include "VisionSystemClient.hpp"
#include "Enes100.h"

Navigation::Navigation(char *nameIn, int teamIDIn, int markerIDIn, int rxPinIn, int txPinIn, Motor *leftMotorIn, Motor *rightMotorIn)
{
  name = nameIn; 
  teamID = teamIDIn; 
  markerID = markerIDIn; 
  rxPin = rxPinIn; 
  txPin = txPinIn;
  rightMotor = rightMotorIn;
  leftMotor = leftMotorIn;
}

/*
Initializes the aruco wifi module and checks if both Motor instances are initialized. 
Returns 1 on success, or 0 if wifi module could not connect to aruco system, or if either Motor was not initialized. (Motor.init() wasn't called)
*/
int Navigation::init()
{
  if (!Enes100.begin(name, teamID, markerID, rxPin, txPin) || !rightMotor->isInitialized() || !leftMotor->isInitialized())
    return 0;

  Enes100.println("Team Notre Dame says hi!");
  return 1;
}

/*
Get raw aruco X-position
Returns -1 if position cannot be obtained
*/
double Navigation::getRawX()
{
  if (!Enes100.updateLocation())
    return -1.0;
  
  return Enes100.location.x;
}

/*
Get raw aruco Y-position
Returns -1 if position cannot be obtained
*/
double Navigation::getRawY()
{
  if (!Enes100.updateLocation())
    return -1.0;
  
  centerCoordinateToVehicleCenter(&Enes100.location);

  return Enes100.location.y;
}

/*
Get X-position corrected for vehicle center
Returns -1 if position cannot be obtained
*/
double Navigation::getVehicleX()
{
  if (!Enes100.updateLocation())
    return -1.0;

  centerCoordinateToVehicleCenter(&Enes100.location);

  return Enes100.location.x;
}

/*
Get Y-position corrected for vehicle center
Returns -1 if position cannot be obtained
*/
double Navigation::getVehicleY()
{
  if (!Enes100.updateLocation())
    return -1.0;

  centerCoordinateToVehicleCenter(&Enes100.location);

  return Enes100.location.y;
}

/*
Get raw angle of OSV as transmitted from system in range [-pi, pi]
*/
double Navigation::getRawAngle()
{
  if (!Enes100.updateLocation())
    return -1.0;
  
  return Enes100.location.theta;
}

/*
Get angle of OSV converted to Radians [0, 2pi]
*/
double Navigation::getRadiansAngle()
{
  double rawAngle = getRawAngle();
  
  //Fix orientation of angle (radians) and store it; right now it comes in range [-pi, pi] 
  //and we convert it to [0, 2pi] with this code
  double radians = rawAngle < 0 ? -1.0 * rawAngle + 2 * (M_PI + rawAngle) : rawAngle;

  return radians;
}

/*
Get angle of OSV converted to degrees [0, 360]
*/
double Navigation::getDegreesAngle()
{
  return RADIANS_TO_DECIMAL(getRadiansAngle()); //This macro is from "Utilities.hpp"
}

/*
Accepts a Coordinate instance, as defined in "VisionSystemClient.hpp". 
Returns the raw coordinates of the aruco marker in the provided coordinate, after checking for location availability. 
*/
void Navigation::passRawCoordinates(Coordinate *coordinate)
{
  if (!Enes100.updateLocation())
    coordinate->x, coordinate->y, coordinate->theta = -1.0f;
  else
  {
    coordinate->x = Enes100.location.x;
    coordinate->y = Enes100.location.y;
    coordinate->theta = Enes100.location.theta;
  }
}

/*
Accepts a Coordinate instance, as defined in "VisionSystemClient.hpp". 
Returns the adjusted coordinates of the aruco marker in the provided coordinate, after checking for location availability. (for Public use)
*/
void Navigation::passVehicleCoordinates(Coordinate *coordinate)
{
  if (!Enes100.updateLocation())
    coordinate->x, coordinate->y, coordinate->theta = -1.0f;
  else
  {
    centerCoordinateToVehicleCenter(coordinate);
    coordinate->theta = Enes100.location.theta;
  }
}

/*
Accepts a Coordinate instance, as defined in "VisionSystemClient.hpp". 
Returns the adjusted coordinates of the aruco marker in the provided coordinate. (Private use only)
*/
void Navigation::centerCoordinateToVehicleCenter(Coordinate *coordinate)
{
  double radians = Enes100.location.theta < 0 ? -1.0 * Enes100.location.theta + 2 * (M_PI + Enes100.location.theta) : Enes100.location.theta;

  //We do some linear algebra here
  coordinate->x = Enes100.location.x + -ARUCO_CROSS_OFFSET * sin(radians);
  coordinate->y = Enes100.location.y +  ARUCO_CROSS_OFFSET * cos(radians);
}

/*
Turns the OSV to specified degrees from [0, 360].

Example:
0 degrees -> positive-x direction
90 degrees -> positive-y direction
*/
void Navigation::turnToDegrees(double degrees)
{
  delay(2000);

  double currentAngle = getDegreesAngle();
  int direction = degrees > currentAngle ? 1 : -1;

  leftMotor->setPower(-1 * direction * TURN_MOTOR_POWER);
  rightMotor->setPower(direction * TURN_MOTOR_POWER);

  long startTime = millis();
  //If we temporarily lose angle information (-1.0), keep going for a time
  while (currentAngle == -1.0 || abs(currentAngle - degrees) >= TURN_DEGREES_ACCEPTABLE_ERROR) //Block thread until we reached the angle
  {
    //Prevent us from turning forever if we lose degree information. This code times out the turn after specified time.
    if (millis() - startTime > TURN_MAXIMUM_TIME) 
      break;

    currentAngle = getDegreesAngle();
  }

  leftMotor->stop();
  rightMotor->stop();
}

/*
Prints the coordinates in text format (x, y, [Angle=theta])
*/
void printCoordinate(Coordinate coordinate)
{
  //printf() on arduino doesn't work with floats so we gotta do all this
  //(%s, %s, [Angle=%s])
  Serial.print('(');
  Serial.print(coordinate.x);
  Serial.print(", ");
  Serial.print(coordinate.y);
  Serial.print(", ");
  Serial.print("[Angle=");
  Serial.print(coordinate.theta);
  Serial.println("])");
}


