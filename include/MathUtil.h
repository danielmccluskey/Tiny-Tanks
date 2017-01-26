#ifndef _MATHLIBARY_H_
#define _MATHLIBARY_H_


const float fPI = 3.14159265359; //Defining PI
const float f2PI = (2 * fPI); //Defining Double PI
const float fHALF_PI = (fPI / 2); //Defining Half of PI

const float RadiansToDegrees(float a_Rad) { return ((a_Rad * 180.0f) / fPI); }; //Function to convert the given Radians to Degrees
const float DegreesToRadians(float a_Deg) { return ((a_Deg * fPI) / 180.0f); }; //Function to convert the given Degrees to Radians



#endif // _MATHLIBARY_H_