/*
This is an ".hpp" file, meaning that it stores defnitions, constants, and prototypes.

Don't put actual code here!
*/

#include "VisionSystemClient.hpp"
#include "Button.hpp"
#include "Motor.hpp"

#define ARUCO_Y_OFFSET 0.065 //6.5cm -> (to meters)

#define TURN_DEGREES_ACCEPTABLE_ERROR 4.5 //In degrees
#define TURN_MAXIMUM_TIME 35000 //In milliseconds
#define TURN_TIME_INCREMENT 60 //In milliseconds

#define MOVE_ACCEPTABLE_DEVIATION 0.31 //In meters squared
#define MOVE_MAXIMUM_TIME 20000 //In milliseconds

#define ATTEMPT_MOVE_TIMEOUT 3500 //In milliseconds

#define FLAME_THRESHOLD 820


#define X_MAX 3.94
#define X_MIN 0.07
#define Y_MAX 1.97
#define Y_MIN 0.06

#define L1 1.46
#define L2 2.34

#if !defined(NAVIGATION_HPP)
#define NAVIGATION_HPP
class Navigation
{
  public:
	  Navigation(char *name, int teamID, int markerID, int rxPin, int txPin, Motor *leftMotor, Motor *rightMotor);
    
    int init();

    //=== Location Functions:

    double getRawX();

    double getRawY();

    double getVehicleX();

    double getVehicleY();

    void passRawCoordinates(Coordinate *coordinate);

    void passVehicleCoordinates(Coordinate *coordinate);

    double getRawAngle();

    double getRadiansAngle();

    double getDegreesAngle();

    //=== Movement functions:

    int turnToDegrees(double degrees);

    void moveDistance(double distance);

    void moveToX(double targetX);

    void moveToY(double targetY);

    void goToCoordinates(Coordinate target);

    void moveTime(short direction, long milliseconds);

    int attemptToMove(long timeout);
  
  private:
    char *name; 
    int teamID; 
    int markerID; 
    int rxPin; 
    int txPin;
    Motor *leftMotor;
    Motor *rightMotor;

    void centerCoordinateToVehicleCenter(Coordinate *coordinate);
};

void printCoordinate(Coordinate coordinate);
void analyzeFlames(int pin1, int pin2, int pin3, int pin4);
void analyzeButtons(Button *b1, Button *b2);

#endif
