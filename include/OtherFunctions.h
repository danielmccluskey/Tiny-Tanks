#ifndef _OTHERFUNCTIONS_H_
#define _OTHERFUNCTIONS_H_
#include <cmath>
#include "stdlib.h"
#include <iostream>
#include "UGFW.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "CustomEnum.h"
#include "PlayerTank.h"

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
	//Function that returns the width of the given sprite.
	const float GetSpriteWidth(int a_iSpriteWidth, int a_iSpriteHeight, float a_fRad);
	//Function to return the height of a given sprite.
	const float GetSpriteHeight(int a_iSpriteWidth, int a_iSpriteHeight, float a_fRad);
	//Function to Get just the Xpos of a sprite.
	//Used from Daniel Budworth-Mead's UGFW++ linked on the Facebook group http://pastebin.com/fHGNgjrL
	const float GetSpriteXPos(int a_uiSpriteID);
	//Function to Get just the Ypos of a sprite.
	//Used from Daniel Budworth-Mead's UGFW++ linked on the Facebook group http://pastebin.com/fHGNgjrL
	const float GetSpriteYPos(int a_uiSpriteID);

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

	bool RayCast(int a_iSpriteIDEnemy, int a_iSpriteIDPlayer, int a_iCollisionMap[]);

	Vector2 GetMousePosition();

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


struct AABB
{
	AABB(int a_iSpriteID, int a_iHeight, int a_iWidth, float a_fRad)
	{
		vTopLeft = Vector2(
			(DANM::GetSpriteXPos(a_iSpriteID) - (DANM::GetSpriteWidth(a_iWidth, a_iHeight, a_fRad)) / 2),
			(DANM::GetSpriteYPos(a_iSpriteID) + (DANM::GetSpriteHeight(a_iWidth, a_iHeight, a_fRad)) / 2)
		);
		vTopRight = Vector2(
			(DANM::GetSpriteXPos(a_iSpriteID) + (DANM::GetSpriteWidth(a_iWidth, a_iHeight, a_fRad)) / 2),
			(DANM::GetSpriteYPos(a_iSpriteID) + (DANM::GetSpriteHeight(a_iWidth, a_iHeight, a_fRad)) / 2)
		);
		vBotLeft = Vector2(
			(DANM::GetSpriteXPos(a_iSpriteID) - (DANM::GetSpriteWidth(a_iWidth, a_iHeight, a_fRad)) / 2),
			(DANM::GetSpriteYPos(a_iSpriteID) - (DANM::GetSpriteHeight(a_iWidth, a_iHeight, a_fRad)) / 2)
		);
		vBotRight = Vector2(
			(DANM::GetSpriteXPos(a_iSpriteID) + (DANM::GetSpriteWidth(a_iWidth, a_iHeight, a_fRad)) / 2),
			(DANM::GetSpriteYPos(a_iSpriteID) - (DANM::GetSpriteHeight(a_iWidth, a_iHeight, a_fRad)) / 2)
		);
		vFront = Vector2(
			(DANM::GetSpriteXPos(a_iSpriteID) + cos(a_fRad - fHALF_PI) * 20), 
			(DANM::GetSpriteYPos(a_iSpriteID) + sin(a_fRad - fHALF_PI) * 20)
		);
	}
	Vector2 vTopLeft;
	Vector2 vTopRight;
	Vector2 vBotLeft;
	Vector2 vBotRight;
	Vector2 vFront;
	Vector2 vBack;
};
#endif // _MATHUTIL_H_