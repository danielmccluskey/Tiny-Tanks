#include "../include/MathUtil.h"


const float RadiansToDegrees(float a_fRad) { return ((a_fRad * 180.0f) / fPI); }; //Function to convert the given Radians to Degrees
const float DegreesToRadians(float a_fDeg) { return ((a_fDeg * fPI) / 180.0f); }; //Function to convert the given Degrees to Radians

//Function to get the greatest value from two given variables
//a_fVal1 is the first value.
//a_fVal2 is the second value.
const float GetMaxValue(float a_fVal1, float a_fVal2)
{
	return (a_fVal1 > a_fVal2) ? a_fVal1 : a_fVal2; //Ternary Operator to simulate If/Else statement in one line. If true, return Value 1, else return Value 2.
}
//Function to get the greatest value from two given variables
//a_fVal1 is the first value.
//a_fVal2 is the second value.
const float GetMinValue(float a_fVal1, float a_fVal2)
{
	return (a_fVal1 < a_fVal2) ? a_fVal1 : a_fVal2; //Ternary Operator to simulate If/Else statement in one line. If true, return Value 1, else return Value 2.
}

//Function to Check if a value is above or below the minimum value.
//a_fVal is the value being checked.
//a_fLowerBound is the lowest value the value being checked can be.
//a_fUpperBound is the highest value the value being checked can be.
const float ClampValue(float a_fVal, float a_fLowerBound, float a_fUpperBound)
{
	return (a_fVal < a_fLowerBound) ? a_fLowerBound : ((a_fVal > a_fUpperBound) ? a_fUpperBound : a_fVal);//Ternary Operater to simulate If/IfElse/Else statement.
}
//Function to interpolate between two points - Equation from WikiPedia https://en.wikipedia.org/wiki/Linear_interpolation
//a_fVal1 is the first value.
//a_fVal2 is the second value.
//a_fLerpAmount is the distance between the two points. If 0, then returned value will be Value 1. If 2, then the returned value will be Value 2.
const float Lerp(float a_fVal1, float a_fVal2, float a_fLerpAmount)
{
	return (a_fVal1 + ((a_fVal2 - a_fVal1)*a_fLerpAmount));//Ternary Operator to simulate If/Else statement in one line. If true, return Value 1, else return Value 2.
}


const float SetSlerpValue()
{
	return 0;
}
//Function to smoothly interpolate between two points using a polynomial - Equation from WikiPedia https://en.wikipedia.org/wiki/Smoothstep
//a_LeftVal is the starting point or the left edge
//a_RightVal is the end point or the right edge.
//a_fPoint is the distance between the two points (Clamped).
const float Smoothstep(float a_fLeftVal, float a_fRightVal, float a_fPoint)
{
	a_fPoint = ClampValue((a_fPoint - a_fLeftVal) / (a_fRightVal - a_fLeftVal), 0.0f, 1.0f);
	a_fPoint = (a_fPoint * a_fPoint * (3 - 2 * a_fPoint));
	return a_fPoint;
}

//Function to smoothly interpolate between two points using a polynomial by Ken Perlin - Equation from WikiPedia https://en.wikipedia.org/wiki/Smoothstep
//a_LeftVal is the starting point or the left edge
//a_RightVal is the end point or the right edge.
//a_fPoint is the distance between the two points (Clamped).
const float Smootherstep(float a_fLeftVal, float a_fRightVal, float a_fPoint)
{
	a_fPoint = ClampValue((a_fPoint - a_fLeftVal) / (a_fRightVal - a_fLeftVal), 0.0f, 1.0f);
	a_fPoint = (a_fPoint * a_fPoint *a_fPoint*(a_fPoint*(a_fPoint * 6 - 15) + 10));
	return a_fPoint;
}

