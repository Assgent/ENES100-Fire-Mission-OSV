/*
This is an ".hpp" file, meaning that it stores defnitions, constants, and prototypes.

Don't put actual code here!
*/

//Constants which are used everywhere

#define MAX_ANALOG 1023

//Macros (tools)

#define LEN(array) = sizeof(array) / sizeof(*array)
#define IN_RANGE(number, min, max) number >= min && number <= max
#define RADIANS_TO_DECIMAL(radians) (radians / 2*PI) * 360