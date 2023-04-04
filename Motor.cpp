#include <Arduino.h>

#include "Utilities.hpp"
#include "Motor.hpp"

Motor::Motor(int RWPMIn, int LWPMIn, int L_ENIn, int R_ENIn)
{
  RWPM = RWPMIn;
  LWPM = LWPMIn;
  L_EN = L_ENIn;
  R_EN = R_ENIn;

  currentDirection = RWPM;
}

/*
Initializes the BTS7960 Motor Controller
*/
int Motor::init()
{
  const int ALL_PINS[] = {RWPM, LWPM, L_EN, R_EN};

  for (int i = 0; i < 4; i++) //Properly initialize our pins
  {
    pinMode(ALL_PINS[i], OUTPUT);
    digitalWrite(ALL_PINS[i], LOW);
  }

  //Enable "Right" and "Left" movement on the HBridge
  //Notice use of digitalWrite to simply turn it on and keep it on.
  digitalWrite(R_EN, HIGH);  
  digitalWrite(L_EN, HIGH);

  return 1;
}

/*
Accepts a power value from [-100, 100], where 100 represents the highest motor power possible

NOTE: Below power values of 51, the motor may struggle to turn in one direction but not the other.
*/
void Motor::setPower(short power)
{
  short powerValue = map(abs(power), 0, 100, 0, 255);
  int requestedDirectionPin = power >= 0 ? RWPM : LWPM;

  if (requestedDirectionPin != currentDirection)
  {
    analogWrite(currentDirection, 0); //Stop the motor turning the other way if we need to
  }

  analogWrite(requestedDirectionPin, powerValue); //Finally, set our motor power 

  currentDirection = requestedDirectionPin; //update our direction
}

/*
Stops the motor.
*/
void Motor::stop()
{
  analogWrite(currentDirection, 0);
}

