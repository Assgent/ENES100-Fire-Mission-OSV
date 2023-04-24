/*
This is an ".hpp" file, meaning that it stores defnitions, constants, and prototypes.

Don't put actual code here!
*/

class Button
{
  public:
	  Button(int analogPinIn);

    int rawValue();

    int pressed();

  private:
    int analogPin;
};

char getOrientation(Button b1, Button b2);


