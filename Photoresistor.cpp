#include <Arduino.h>

#include "Utilities.hpp"
#include "Photoresistor.hpp"

//============================================================
#define BALLOON_THRESHOLD 0.80
//============================================================

Photoresistor::Photoresistor(int analogPinIn)
{
  analogPin = analogPinIn;
}

int Photoresistor::rawValue()
{
  return analogRead(analogPin);
}

double Photoresistor::lightPercentage()
{
  return (1023 - rawValue()) / MAX_ANALOG;
}

int Photoresistor::balloonGone()
{
  return lightPercentage() <= BALLOON_THRESHOLD;
}

