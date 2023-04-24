/*
This is an ".hpp" file, meaning that it stores defnitions, constants, and prototypes.

Don't put actual code here!
*/

//Constants which are used everywhere

#define MAX_ANALOG 1023

//Macros (tools)

#define LEN(array) = sizeof(array) / sizeof(*array)
#define IN_RANGE(number, min, max) number >= min && number <= max
#define RADIANS_TO_DECIMAL(radians) radians * (180 / M_PI)
#define FIX_RAD_ORIENTATION(radians) radians < 0 ? -1.0 * radians + 2 * (M_PI + radians) : radians
#define DISTANCE_FROM_ORIGIN(x, y) sqrt(x*x + y*y)