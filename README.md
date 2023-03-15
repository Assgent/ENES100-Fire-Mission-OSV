# ENES100-Fire-Mission-OSV

Arduino code for *Team Notre Dame*'s OSV robot, Spring 2023 UMD.

Please update this document when you make a change!

# Documentation

## Defnitions 

Aruco Marker:

`#define X_MAX 3.94` - 

`#define X_MIN 0.07` -

`#define Y_MAX 1.97` -

`#define Y_MIN 0.06` -

## Classes

*(How OUR code works - see below to make sense of what we have so far)*

### `Button(int analogPinIn)`

Relevant library push buttons - also includes getOrientation()

### `Motor()`

Represents an individual motor on the OSV

### `Photoresistor(int analogPinIn)`

Represents an individual photo resistor on the OSV

## Coding Helpsheet

**ENES100 Aruco Library Docs:** https://enes100.umd.edu/libraries/enes100

__**Examples of correct syntax:**__
  ```C
  
  int my_array[] = {1, 2, 3, 4, 5}; //This is an array
  double my_decimal = 0.1; //This is a decimal value
  int my_int = 3; //This is an integer value
  
  int my_array_member = my_array[my_int]; //This gets the FOURTH member of the array (computers count from 0)
  //int my_other_array_member = my_array[my_decimal]; //This is WRONG. You shouldn't access arrays with decimals
  
  //if/else statement
  if (/*condition here*/)
  {
    //code here
  }
  else if (/*2nd condition*/)
  {
    //code here
  }
  else
  {
    //code here
  }
  
  //for loop
  for (int i = 0; i < /*Value to stop before*/; i++)
  {
    //code here runs again and again until i >= [the value above]
  }
  
  //while loop
  while (/*Condition here*/)
  {
    //code runs again and again until condition is false
  }
  
  //switch/case
  switch (/*number or value*/)
  {
    case /*example 1*/:
      //code here
      break; //Then leave the switch statement
    case /*example 2*/:
      //code here
      //Loops back again
    defualt:
      //code here
      break;
  }
  
  ```
  
__How do I use **code from different files?**__

  Use `#include "<filename>.hpp"`! For example: `#include "button.hpp"` allows you to use the `Button` class.
  
__How do I **start the arduino**?__
  ```C
  void setup() 
  {
    Serial.begin(9600); //Do this first so you can get text output in your computer from the arduino
    
    Serial.println("This prints text to your computer and moves one line down");
    Serial.print("This just prints text to your computer");
  }

  void loop() 
  {
    //Code here runs over and over again for the lifetime of your program
  }
```

__How do I store an **integer**?__ 

  Use `int` (16-bit value, stores numbers from [-32,767, 32,767])
  
  
__-How do I store a **positive, large integer**?__ 

  Use `unsigned int` (16-bit value, stores numbers from [0, 65,535]) 
  
  
__-How do I store a **decimal number**?__

  Use `double` 
  
  *(You can also use `float`, but the Aruco library uses `double` so we should just use double instead)*
 
__-How do I store a **sentence**?__ 

  See: https://myhomethings.eu/en/arduino-string-objects/
  
  Try NOT to use `char[]` (C strings). They're really hard!
  
__-How do I convert between data types?__

  Use casting:
  ```C
  //example
  
  double x = 3.14;
  int y = (int)x; //y now equals just "3", but as an integer
  ```
  
  *Note that this **doesn't always work with everything**! There are other methods that you might have to use.*
  
__-What is an **array**?__

  An array is a consecutive set of values. See below:
  ```C
  //example
  
  //Note the addition of the "[]" 
  int your_array[] = {1, 2, 3};
  
  //Computers count up from ZERO, not one.
  your_array[0]; //Will get you the first element
  your_array[1]; //Will get you the second element
  your_array[2]; //Will get you the third element
  
  //your_array[3]; would be an error. However, C will probably not warn you about it, unlike other languages. Therefore, you have to be careful.
  
  int size = sizeof(your_array) / sizeof(*your_array); //Will get you the SIZE of the array
  ```
