/*
This is an ".hpp" file, meaning that it stores defnitions, constants, and prototypes.

Don't put actual code here!
*/

class Photoresistor
{
  public:
	Photoresistor(int analogPinIn);

    int rawValue();

    double lightPercentage();

    int balloonGone();

  private:
    int analogPin;
};

