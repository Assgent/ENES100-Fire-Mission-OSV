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
  if (!Enes100.begin(name, teamID, markerID, txPin, rxPin) || !rightMotor->isInitialized() || !leftMotor->isInitialized())
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

  if (rawAngle == -1.0)
    return -1.0;
  
  //Fix orientation of angle (radians) and store it; right now it comes in range [-pi, pi] 
  //and we convert it to [0, 2pi] with this code
  double radians = FIX_RAD_ORIENTATION(rawAngle);

  return radians;
}

/*
Get angle of OSV converted to degrees [0, 360]
*/
double Navigation::getDegreesAngle()
{
  double radiansAngle = getRadiansAngle();

  if (radiansAngle == -1.0)
    return -1.0;

  return RADIANS_TO_DECIMAL(radiansAngle); //This macro is from "Utilities.hpp"
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
  double radians = FIX_RAD_ORIENTATION(Enes100.location.theta);

  //We do some linear algebra here
  coordinate->x = Enes100.location.x + -ARUCO_Y_OFFSET * sin(radians);
  coordinate->y = Enes100.location.y +  ARUCO_Y_OFFSET * cos(radians);
}

/*
Turns the OSV to specified degrees from [0, 360].

Example:
0 degrees -> positive-x direction
90 degrees -> positive-y direction

Returns 1 on success, 0 if something goes wrong.
*/
int Navigation::turnToDegrees(double degrees)
{
  double currentAngle = getDegreesAngle();
  //If angle is unavailable, do nothing
  if (currentAngle == -1.0)
    return 0;

  short direction = degrees <= currentAngle ? FORWARD : REVERSE;
  int turnExpired = 0;
  long startTime = millis();
  //If we temporarily lose angle information (-1.0), keep going for a time
  while (currentAngle == -1.0 || abs(currentAngle - degrees) >= TURN_DEGREES_ACCEPTABLE_ERROR) //Block thread until we reached the angle
  {
    //Prevent us from turning forever if we lose degree information. This code times out the turn after specified time.
    if ((turnExpired = millis() - startTime > TURN_MAXIMUM_TIME)) 
      break;

    currentAngle = getDegreesAngle();

    /*Turn a little bit at a time*/
    leftMotor->turn(direction);
    rightMotor->turn(!direction);

    delay(TURN_TIME_INCREMENT);

    leftMotor->stop();
    rightMotor->stop();

    delay(100);
  }

  /*Ensure our motors are stopped*/
  leftMotor->stop();
  rightMotor->stop();

  //If our turn did NOT expire, return 1 to indicate success
  return !turnExpired;
}

/*
Moves the OSV in a straight line for the specified distance
*/
void Navigation::moveDistance(double distance)
{
  //First, get our current position
  Coordinate current = Coordinate();
  passVehicleCoordinates(&current);
  //If location is unavailable, do nothing
  if (current.x == -1.0)
    return;
  
  //Record our current position
  Coordinate origin = Coordinate();
  origin.x = current.x;
  origin.y = current.y;

  short direction = distance >= 0.0;
  leftMotor->turn(direction);
  rightMotor->turn(direction);

  double absDistance = abs(distance);
  long startTime = millis();
  //Block thread until we have traveled the specified distance
  while (current.x == -1.0 || \
  DISTANCE(current.x, current.y, origin.x, origin.y) < absDistance) 
  {
    /* //For debugging
    Enes100.println(current.y - origin.x);
    Enes100.print("         ");
    Enes100.println(DISTANCE(current.x, current.y, origin.x, origin.y));
    */
    //Prevent us from turning forever if we lose degree information. This code times out the turn after specified time.
    if (millis() - startTime > MOVE_MAXIMUM_TIME) 
      break;

    current = Coordinate();
    passVehicleCoordinates(&current);
  }

  leftMotor->stop();
  rightMotor->stop();
}

/*
Turns the OSV to face the target coordinate before moving in a straight line towards that location.
*/
void Navigation::goToCoordinates(Coordinate target)
{
  //First, get our current position
  Coordinate current = Coordinate();
  passVehicleCoordinates(&current);
  //If location is unavailable, do nothing
  if (current.x == -1.0)
    return;

  //Get the length of travel (magnitude of vector)
  double distance = DISTANCE(current.x, current.y, target.x, target.y);

  //Get the angle we need to turn to, in radians [0, 2pi]
  double xOffset = target.x - current.x;
  double yOffset = target.y - current.y;
  double sign = yOffset / abs(yOffset);
  double radians = FIX_RAD_ORIENTATION(sign * acos(xOffset / distance));
  //...then, get that same angle in degrees
  double degrees = RADIANS_TO_DECIMAL(radians);

  Enes100.print("Now moving to: "); Enes100.print(target.x); Enes100.print(", "); Enes100.println(target.y);
  Enes100.print("Degrees: "); Enes100.println(degrees);
  Enes100.print("Distance: "); Enes100.println(distance);
  Enes100.print("\n");

  //Finally, turn our OSV towards the origin point. If the turn succeeds, then move the vehicle.
  if (turnToDegrees(degrees))
    moveDistance(distance);
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


