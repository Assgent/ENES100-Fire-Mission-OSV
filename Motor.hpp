/*
This is an ".hpp" file, meaning that it stores defnitions, constants, and prototypes.

Don't put actual code here!
*/

class Motor
{
  public:
	  Motor(int RWPMIn, int LWPMIn, int L_ENIn, int R_ENIn);
    
    int init();

    void setPower(short power);
    void stop();

  private:
    int RWPM;
    int LWPM;
    int L_EN;
    int R_EN;

    int currentDirection;
};


