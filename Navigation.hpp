/*
This is an ".hpp" file, meaning that it stores defnitions, constants, and prototypes.

Don't put actual code here!
*/

#include "VisionSystemClient.hpp"

#define X_MAX 3.94
#define X_MIN 0.07
#define Y_MAX 1.97
#define Y_MIN 0.06

#define L1 1.46
#define L2 2.34

class Navigation
{
  public:
	  Navigation(char *name, int teamID, int markerID, int rxPin, int txPin);
    
    int init();

    double getRawX();

    double getRawY();

    double getVehicleX();

    double getVehicleY();

    void passRawCoordinates(Coordinate *coordinate);

    void passVehicleCoordinates(Coordinate *coordinate);

    double getAngle();

  private:
    char *name; 
    int teamID; 
    int markerID; 
    int rxPin; 
    int txPin;
};

void printCoordinate(Coordinate coordinate);

