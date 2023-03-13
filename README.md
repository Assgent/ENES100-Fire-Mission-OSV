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

### `Navigation()`

Relevant library for movement and navigation

### `Motor()`

Represents an individual motor on the OSV

### `Servo()`

Represents an individual Servo on the OSV

## Coding Helpsheet

**ENES100 Aruco Library Docs:** https://enes100.umd.edu/libraries/enes100

-How do I store an **integer**? 

  Use `int` (16-bit value, stores numbers from [-32,767, 32,767])
  
  
-How do I store a **positive, large integer**? 

  Use `unsigned int` (16-bit value, stores numbers from [0, 65,535]) 
  
  
-How do I store a **decimal number**?

  Use `double` 
  
  *(You can also use `float`, but the Aruco library uses `double` so we should just use double instead)*
 
-How do I store a **sentence**? 

  See: https://myhomethings.eu/en/arduino-string-objects/
  
  Try NOT to use `char[]` (C strings). They're really hard!
  
-How do I convert between data types?

  Use casting:
  ```C
  //example
  
  double x = 3.14;
  int y = (int)x; //y now equals just "3", but as an integer
  ```
  
  *Note that this **doesn't work with everything**!*
  
