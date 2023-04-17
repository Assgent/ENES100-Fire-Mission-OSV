/*
This is an ".hpp" file, meaning that it stores defnitions, constants, and prototypes.

Don't put actual code here!
*/

#include "VisionSystemClient.hpp"
#include "Motor.hpp"

#define ARUCO_CROSS_OFFSET 0.065 //6.5cm -> (to meters)

#define TURN_MOTOR_POWER 60
#define TURN_DEGREES_ACCEPTABLE_ERROR 10 //In degrees
#define TURN_MAXIMUM_TIME 5000 //In milliseconds

#define X_MAX 3.94
#define X_MIN 0.07
#define Y_MAX 1.97
#define Y_MIN 0.06

#define L1 1.46
#define L2 2.34

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

    void turnToDegrees(double degrees);
  
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


