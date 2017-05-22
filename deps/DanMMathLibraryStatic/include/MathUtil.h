#ifndef _MATHUTIL_H_
#define _MATHUTIL_H_
#include <cmath>
#include "stdlib.h"
#include <iostream>




const float fPI = 3.14159265359; //Defining PI
const float f2PI = (2 * fPI); //Defining Double PI
const float fHALF_PI = (fPI / 2); //Defining Half of PI
const float f2HALF_PI = (fHALF_PI / 2);

const float RadiansToDegrees(float a_fRad); //Function to convert the given Radians to Degrees
const float DegreesToRadians(float a_fDeg); //Function to convert the given Degrees to Radians
//Function to get the greatest value from two given variables
//a_fVal1 is the first value.
//a_fVal2 is the second value.
const float GetMaxValue(float a_fVal1, float a_fVal2);
//Function to get the greatest value from two given variables
//a_fVal1 is the first value.
//a_fVal2 is the second value.
const float GetMinValue(float a_fVal1, float a_fVal2);

//Function to Check if a value is above or below the minimum value.
//a_fVal is the value being checked.
//a_fLowerBound is the lowest value the value being checked can be.
//a_fUpperBound is the highest value the value being checked can be.
const float ClampValue(float a_fVal, float a_fLowerBound, float a_fUpperBound);
//Function to interpolate between two points - Equation from WikiPedia https://en.wikipedia.org/wiki/Linear_interpolation
//a_fVal1 is the first value.
//a_fVal2 is the second value.
//a_fLerpAmount is the distance between the two points. If 0, then returned value will be Value 1. If 2, then the returned value will be Value 2.
const float Lerp(float a_fVal1, float a_fVal2, float a_fLerpAmount);


const float SetSlerpValue();
//Function to smoothly interpolate between two points using a polynomial - Equation from WikiPedia https://en.wikipedia.org/wiki/Smoothstep
//a_LeftVal is the starting point or the left edge
//a_RightVal is the end point or the right edge.
//a_fPoint is the distance between the two points (Clamped).
const float Smoothstep(float a_fLeftVal, float a_fRightVal, float a_fPoint);

//Function to smoothly interpolate between two points using a polynomial by Ken Perlin - Equation from WikiPedia https://en.wikipedia.org/wiki/Smoothstep
//a_LeftVal is the starting point or the left edge
//a_RightVal is the end point or the right edge.
//a_fPoint is the distance between the two points (Clamped).
const float Smootherstep(float a_fLeftVal, float a_fRightVal, float a_fPoint);



#endif // _MATHUTIL_H_