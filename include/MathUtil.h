#ifndef _MATHUTIL_H_
#define _MATHUTIL_H_
#include <cmath>
#include "stdlib.h"
#include <iostream>
#include "UGFW.h"
#include "Vector2.h"
#include "Vector4.h"
#include "CustomEnum.h"

/*SpriteMatrix
[0] = Scales X Axis
[1] = Skews +RightUp -RightDown
[2] = Crops Sprites X axis +Right -Left
[3] = ?????
[4] = Skews -Left +Right
[5] = Scales Y Axis
[6] = ?????
[7] =
[8] =
[9] =
[10] =
[11] =
[12] = XPOS
[13] = YPOS
*/

static float fSpriteMatrix[16];//Variable to temporarly hold the Sprite Matrix in some functions such as the SetRotation functions.

const float fPI = 3.14159265359; //Defining PI
const float f2PI = (2 * fPI); //Defining Double PI
const float fHALF_PI = (fPI / 2); //Defining Half of PI
const float f2HALF_PI = (fHALF_PI / 2);

const float RadiansToDegrees(float a_fRad); //Function to convert the given Radians to Degrees
const float DegreesToRadians(float a_fDeg); //Function to convert the given Degrees to Radians


const float AABBTest(float a_fDeg);

namespace DANM //Incase other includes use the same function names as my functions
{

	//Gets the Angle between two Vector2 co-ordinates. Mainly Used for rotating tank turret.
	//Equation used - http://wikicode.wikidot.com/get-angle-of-line-between-two-points
	const float GetBearingRad(Vector2 &a_V1, Vector2 &a_V2);
	//Gets the Angle between two Vector2 co-ordinates. Mainly Used for rotating tank turret.
	//Equation used - http://wikicode.wikidot.com/get-angle-of-line-between-two-points
	const float GetBearingDeg(Vector2 &a_V1, Vector2 &a_V2);

	//Sets the rotation to a certain angle instead of incrementing it like UG::SetSpriteRotation does.
	//Used from Daniel Budworth-Mead's UGFW++ linked on the Facebook group http://pastebin.com/fHGNgjrL
	void SetRotationRad(float a_fRad, int a_iSpriteID);
	//Sets the rotation to a certain angle instead of incrementing it like UG::SetSpriteRotation does.
	//Used from Daniel Budworth-Mead's UGFW++ linked on the Facebook group http://pastebin.com/fHGNgjrL
	void SetRotationDeg(float a_fDeg, int a_iSpriteID);
	Vector2 GetForwardVector(float a_fDeg);

	Vector4 GetVertices(float fRotation, int iWidth, int iHeight);

}






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