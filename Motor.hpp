/*
This is an ".hpp" file, meaning that it stores defnitions, constants, and prototypes.

Don't put actual code here!
*/

#define FORWARD 1
#define REVERSE 0

#if !defined(MOTOR_HPP)
#define MOTOR_HPP
class Motor
{
  public:
	  Motor(int pin1In, int pin2In, int powerPinIn);
    
    int init();
    int isInitialized();

    void turn(short direction);
    void stop();

  private:
    int initialized;

    int pin1;
    int pin2;
    int powerPin;

    int currentDirection;
};
#endif


