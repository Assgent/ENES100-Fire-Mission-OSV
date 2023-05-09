#include <Arduino.h>

#include "Utilities.hpp"
#include "Button.hpp"

//============================================================
#define CLICK_BOUND_UPPER 660
#define CLICK_BOUND_LOWER 658
//============================================================

Button::Button(int analogPinIn)
{
  analogPin = analogPinIn;
}

int Button::rawValue()
{
  return digitalRead(analogPin);
}

int Button::pressed()
{
  return digitalRead(analogPin);
}

/*
Pre:
-Two buttons on front of OSV

Post:
-Returns "A", "B", or "C" for the orientation of the Fire Mission
*/
char getOrientation(Button b1, Button b2)
{
  int b1Pressed = b1.pressed();
  int b2Pressed = b2.pressed();

  if (b1Pressed && b2Pressed)
    return 'C';
  else if (b1Pressed)
    return 'A';
  else if (b2Pressed)
    return 'B';
  else
    return '\0';
}


