#ifndef _MATHLIBARY_H_
#define _MATHLIBARY_H_


const float fPI = 3.14159265359; //Defining PI
const float f2PI = (2 * fPI); //Defining Double PI
const float fHALF_PI = (fPI / 2); //Defining Half of PI

const float RadiansToDegrees(float a_Rad) { return ((a_Rad * 180.0f) / fPI); }; //Function to convert the given Radians to Degrees
const float DegreesToRadians(float a_Deg) { return ((a_Deg * fPI) / 180.0f); }; //Function to convert the given Degrees to Radians

//Function to get the greatest value from two given variables (Reminder to convert to Ternary Operators)##################################################################
//a_fVal1 is the first value.
//a_fVal2 is the second value.
const float GetMaxValue(float a_fVal1, float a_fVal2)
{
	if (a_fVal1 > a_fVal2)//If Value 1 is Greater than Value 2
	{
		return a_fVal1;//Return Value 1
	}
	else
	{
		return a_fVal2;//Return Value 2
	}
}
//Function to get the greatest value from two given variables (Reminder to convert to Ternary Operators)##################################################################
//a_fVal1 is the first value.
//a_fVal2 is the second value.
const float GetMinValue(float a_fVal1, float a_fVal2)
{
	if (a_fVal1 < a_fVal2)//If Value 1 is Less than Value 2
	{
		return a_fVal1;//Return Value 1
	}
	else
	{
		return a_fVal2;//Return Value 2
	}
}

//Function to Check if a value is above or below the minimum value.
//a_fVal is the value being checked.
//a_fLowerBound is the lowest value the value being checked can be.
//a_fUpperBound is the highest value the value being checked can be.
const float SetClampValue(float a_fVal, float a_fLowerBound, float a_fUpperBound)
{
	if (a_fVal < a_fLowerBound)
	{
		return a_fLowerBound;
	}
	else if (a_fVal > a_fUpperBound)
	{
		return a_fUpperBound;
	}
	else
	{
		return a_fVal;
	}
}
//Function to interpolate between two points - Equation from WikiPedia https://en.wikipedia.org/wiki/Linear_interpolation
//a_fVal1 is the first value.
//a_fVal2 is the second value.
//a_fLerpAmount is the distance between the two points. If 0, then returned value will be Value 1. If 2, then the returned value will be Value 2.
//REMINDER TO CLAMP BETWEEN 0 AND 1 ################################################################
const float SetLerpValue(float a_fVal1, float a_fVal2, float a_fLerpAmount)
{
	return (a_fVal1 + ((a_fVal2 - a_fVal1)*a_fLerpAmount));
}


const float SetSlerpValue()
{
	return 0;
}
//Function to smoothly interpolate between two points using a polynomial - Equation from WikiPedia https://en.wikipedia.org/wiki/Smoothstep
//a_LeftVal is the starting point or the left edge
//a_RightVal is the end point or the right edge.
//a_fPoint is the distance between the two points (Clamped).
const float SetSmoothstep(float a_fLeftVal, float a_fRightVal, float a_fPoint)
{
	a_fPoint = SetClampValue((a_fPoint - a_fLeftVal)/(a_fRightVal - a_fLeftVal), 0.0f, 1.0f);
	a_fPoint = (a_fPoint * a_fPoint * (3 - 2 * a_fPoint));
	return a_fPoint;
}
#endif // _MATHLIBARY_H_