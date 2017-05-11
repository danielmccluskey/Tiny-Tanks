#include "OtherFunctions.h"
#include <cmath>
#include "stdlib.h"
#include <iostream>
#include "UGFW.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "MathUtil.h"
#include "CustomEnum.h"
#include "PlayerTank.h"
#include "Matrix4x4.h"

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
const float RadiansToDegrees(float a_fRad) { return ((a_fRad * 180.0f) / fPI); }; //Function to convert the given Radians to Degrees
const float DegreesToRadians(float a_fDeg) { return ((a_fDeg * fPI) / 180.0f); }; //Function to convert the given Degrees to Radians


const float AABBTest(float a_fDeg)
{
	return 0;
}


namespace DANM //Incase other includes use the same function names as my functions
{
	//Function that returns the width of the given sprite.
	//Equation from Stack overflow - http://stackoverflow.com/a/6657768
	const float GetSpriteWidth(int a_iSpriteWidth, int a_iSpriteHeight, float a_fRad)
	{
		return ((a_iSpriteWidth * abs(cos(a_fRad))) + (a_iSpriteHeight * abs(sin(a_fRad))));
	}
	//Function to return the height of a given sprite.
	//Equation from Stack overflow - http://stackoverflow.com/a/6657768
	const float GetSpriteHeight(int a_iSpriteWidth, int a_iSpriteHeight, float a_fRad)
	{
		return ((a_iSpriteWidth * abs(sin(a_fRad))) + (a_iSpriteHeight * abs(cos(a_fRad))));
	}
	//Function to Get just the Xpos of a sprite.
	//Used from Daniel Budworth-Mead's UGFW++ linked on the Facebook group http://pastebin.com/fHGNgjrL
	const float GetSpriteXPos(int a_uiSpriteID)
	{
		UG::GetSpriteMatrix(a_uiSpriteID, fSpriteMatrix);
		return fSpriteMatrix[12];
	}
	//Function to Get just the Ypos of a sprite.
	//Used from Daniel Budworth-Mead's UGFW++ linked on the Facebook group http://pastebin.com/fHGNgjrL
	const float GetSpriteYPos(int a_uiSpriteID)
	{
		UG::GetSpriteMatrix(a_uiSpriteID, fSpriteMatrix);
		return fSpriteMatrix[13];
	}
	//Gets the Angle between two Vector2 co-ordinates. Mainly Used for rotating tank turret.
	//Equation used - http://wikicode.wikidot.com/get-angle-of-line-between-two-points
	const float GetBearingRad(Vector2 &a_V1, Vector2 &a_V2)
	{
		float fXChange = int(a_V2.dX - a_V1.dX);
		float fYChange = int(a_V2.dY - a_V1.dY);
		return atan2(fYChange, fXChange);
	}
	//Gets the Angle between two Vector2 co-ordinates. Mainly Used for rotating tank turret.
	//Equation used - http://wikicode.wikidot.com/get-angle-of-line-between-two-points
	const float GetBearingDeg(Vector2 &a_V1, Vector2 &a_V2)
	{
		float fXChange = (a_V1.dX - a_V2.dX);
		float fYChange = (a_V1.dY - a_V2.dY);
		return atan2(fYChange, fXChange)*(180 / fPI);
	}

	//Sets the rotation to a certain angle instead of incrementing it like UG::SetSpriteRotation does.
	//Used from Daniel Budworth-Mead's UGFW++ linked on the Facebook group http://pastebin.com/fHGNgjrL
	//Will Convert to 4x4 Matrix later.
	void SetRotationRad(float a_fRad, int a_iSpriteID)
	{
		UG::GetSpriteMatrix(a_iSpriteID, fSpriteMatrix);
		Matrix4x4 oSpriteMatrix(fSpriteMatrix);
		oSpriteMatrix.RotateZ(a_fRad);
		/*fSpriteMatrix[0] = cos(a_fRad);
		fSpriteMatrix[1] = -sin(a_fRad);
		fSpriteMatrix[4] = sin(a_fRad);
		fSpriteMatrix[5] = cos(a_fRad);*/
		UG::SetSpriteMatrix(a_iSpriteID, oSpriteMatrix.GetMatrix());


	}
	//Sets the rotation to a certain angle in Degrees instead of incrementing it like UG::SetSpriteRotation does.
	void SetRotationDeg(float a_fDeg, int a_iSpriteID)
	{
		SetRotationRad((DegreesToRadians(a_fDeg)), a_iSpriteID);
	}
	Vector2 GetForwardVector(float a_fDeg)
	{
		float x = 0;
		float y = 0;
		x = cos(DegreesToRadians(a_fDeg));
		y = sin(DegreesToRadians(a_fDeg));
		return Vector2(x, y);
	}

	Vector4 GetVertices(float fRotation, int iWidth, int iHeight)
	{
		return Vector4(0, 0, 0, 0);
	}

	//Function to cast a ray at a sprite from anotherto see if they can see each other.
	bool RayCast(int a_iSpriteIDEnemy, int a_iSpriteIDPlayer, int a_iCollisionMap[])
	{
		PlayerTank RayCaster;
		RayCaster.UpdateCollisionMap();
		for (float i = 0; i < 1; i += (1.f / iMapWidth))
		{

			RayCaster.pos.dX = Lerp(DANM::GetSpriteXPos(a_iSpriteIDEnemy), DANM::GetSpriteXPos(a_iSpriteIDPlayer), i);
			RayCaster.pos.dY = Lerp(DANM::GetSpriteYPos(a_iSpriteIDEnemy), DANM::GetSpriteYPos(a_iSpriteIDPlayer), i);
			int iTileTypes = RayCaster.GetTile(32, RayCaster.pos);

			if (iTileTypes == 1)
			{
				std::cout << "NOT SEEN" << std::endl;
				return false;
				break;
			}
		}
		std::cout << "SEEN" << std::endl;
		return true;
	}

	Vector2 GetMousePosition()
	{
		Vector2 vMousePos;//New Vector2 to hold Mouse position.
		UG::GetMousePos(vMousePos.dX, vMousePos.dY);//Gets the mouse position.
		int iScrX, iScrY;
		UG::GetScreenSize(iScrX, iScrY);
		vMousePos.dY = iScrY - vMousePos.dY;//Reverses the Y-Value given from UG::GetMousePos since it returns Y=0 at the top instead of the bottom.
		return vMousePos;
	}

}






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