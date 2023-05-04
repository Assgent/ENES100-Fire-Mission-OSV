#include <Arduino.h>

#include "Utilities.hpp"
#include "Motor.hpp"

Motor::Motor(int pin1In, int pin2In, int powerPinIn)
{
  initialized = 0;

  pin1 = pin1In;
  pin2 = pin2In;
  powerPin = powerPinIn;
}

/*
Initializes the BTS7960 Motor Controller
*/
int Motor::init()
{
  const int ALL_PINS[] = {pin1, pin2, powerPin};

  for (int i = 0; i < 3; i++) //Properly initialize our pins
  {
    pinMode(ALL_PINS[i], OUTPUT);
    digitalWrite(ALL_PINS[i], LOW);
  }

  initialized = 1;

  return 1;
}

/*
  Returns 1 if Motor was properly initialized; 0 otherwise.
*/
int Motor::isInitialized()
{
  return initialized;
}

/*
Accepts -1 or 1, indicating the respective reverse and forward directions.

Turns the motors in the specified directions.

(Our motor driver is only capable of running full power.)

Checks for initialization. Will do nothing if Motor was not initialized.
*/
void Motor::turn(short direction)
{
  if (initialized && (direction == 1 || direction == 0))
  {
    digitalWrite(pin1, direction);
    digitalWrite(pin2, !direction);

    analogWrite(powerPin, 255);
  }
}

/*
Stops the motor.

Checks for initialization. Will do nothing if Motor was not initialized.
*/
void Motor::stop()
{
  if (initialized)
  {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
}

