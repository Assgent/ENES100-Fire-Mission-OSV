#include <Arduino.h>

#include "Utilities.hpp"

//============================================================
#define BALLOON_THRESHOLD 0.80
//============================================================

class Photoresistor
{
  public:
	  Photoresistor(int analogPinIn)
    {
      analogPin = analogPinIn;
    }

    int rawValue()
    {
      return analogRead(analogPin);
    }

    double lightPercentage()
    {
      return (1023 - rawValue()) / MAX_ANALOG;
    }

    int balloonGone()
    {
      return lightPercentage() <= BALLOON_THRESHOLD;
    }

  private:
    int analogPin;
};

