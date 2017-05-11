#include "OtherFunctions.h"
#include <cmath>
#include "stdlib.h"
#include <iostream>
#include "Vector2.h"
#include "Vector3.h"
#include "MathUtil.h"
#include "Matrix4x4.h"
#include "UGFW.h"
#include "CustomEnum.h"
struct AABB
{
	AABB(int a_iSpriteID, int a_iHeight, int a_iWidth, float a_fRad)
	{
		vTopLeft = Vector2(
			(OtherFunctions::GetSpriteXPos(a_iSpriteID) - (OtherFunctions::GetSpriteWidth(a_iWidth, a_iHeight, a_fRad)) / 2),
			(OtherFunctions::GetSpriteYPos(a_iSpriteID) + (OtherFunctions::GetSpriteHeight(a_iWidth, a_iHeight, a_fRad)) / 2)
		);
		vTopRight = Vector2(
			(OtherFunctions::GetSpriteXPos(a_iSpriteID) + (OtherFunctions::GetSpriteWidth(a_iWidth, a_iHeight, a_fRad)) / 2),
			(OtherFunctions::GetSpriteYPos(a_iSpriteID) + (OtherFunctions::GetSpriteHeight(a_iWidth, a_iHeight, a_fRad)) / 2)
		);
		vBotLeft = Vector2(
			(OtherFunctions::GetSpriteXPos(a_iSpriteID) - (OtherFunctions::GetSpriteWidth(a_iWidth, a_iHeight, a_fRad)) / 2),
			(OtherFunctions::GetSpriteYPos(a_iSpriteID) - (OtherFunctions::GetSpriteHeight(a_iWidth, a_iHeight, a_fRad)) / 2)
		);
		vBotRight = Vector2(
			(OtherFunctions::GetSpriteXPos(a_iSpriteID) + (OtherFunctions::GetSpriteWidth(a_iWidth, a_iHeight, a_fRad)) / 2),
			(OtherFunctions::GetSpriteYPos(a_iSpriteID) - (OtherFunctions::GetSpriteHeight(a_iWidth, a_iHeight, a_fRad)) / 2)
		);
		vFront = Vector2(
			(OtherFunctions::GetSpriteXPos(a_iSpriteID) + cos(a_fRad - fHALF_PI) * 20),
			(OtherFunctions::GetSpriteYPos(a_iSpriteID) + sin(a_fRad - fHALF_PI) * 20)
		);
	}
	Vector2 vTopLeft;
	Vector2 vTopRight;
	Vector2 vBotLeft;
	Vector2 vBotRight;
	Vector2 vFront;
	Vector2 vBack;
};

float OtherFunctions::GetSpriteWidth(int a_iSpriteWidth, int a_iSpriteHeight, float a_fRad)
{
	return ((a_iSpriteWidth * abs(cos(a_fRad))) + (a_iSpriteHeight * abs(sin(a_fRad))));
}
//Function to return the height of a given sprite.
//Equation from Stack overflow - http://stackoverflow.com/a/6657768
float OtherFunctions::GetSpriteHeight(int a_iSpriteWidth, int a_iSpriteHeight, float a_fRad)
{
	return ((a_iSpriteWidth * abs(sin(a_fRad))) + (a_iSpriteHeight * abs(cos(a_fRad))));
}
//Function to Get just the Xpos of a sprite.
//Used from Daniel Budworth-Mead's UGFW++ linked on the Facebook group http://pastebin.com/fHGNgjrL
float OtherFunctions::GetSpriteXPos(int a_uiSpriteID)
{
	UG::GetSpriteMatrix(a_uiSpriteID, fSpriteMatrix);
	return fSpriteMatrix[12];
}
//Function to Get just the Ypos of a sprite.
//Used from Daniel Budworth-Mead's UGFW++ linked on the Facebook group http://pastebin.com/fHGNgjrL
float OtherFunctions::GetSpriteYPos(int a_uiSpriteID)
{
	UG::GetSpriteMatrix(a_uiSpriteID, fSpriteMatrix);
	return fSpriteMatrix[13];
}
//Gets the Angle between two Vector2 co-ordinates. Mainly Used for rotating tank turret.
//Equation used - http://wikicode.wikidot.com/get-angle-of-line-between-two-points
float OtherFunctions::GetBearingRad(Vector2 &a_V1, Vector2 &a_V2)
{
	float fXChange = int(a_V2.dX - a_V1.dX);
	float fYChange = int(a_V2.dY - a_V1.dY);
	return atan2(fYChange, fXChange);
}
//Gets the Angle between two Vector2 co-ordinates. Mainly Used for rotating tank turret.
//Equation used - http://wikicode.wikidot.com/get-angle-of-line-between-two-points
float OtherFunctions::GetBearingDeg(Vector2 &a_V1, Vector2 &a_V2)
{
	float fXChange = (a_V1.dX - a_V2.dX);
	float fYChange = (a_V1.dY - a_V2.dY);
	return atan2(fYChange, fXChange)*(180 / fPI);
}

//Sets the rotation to a certain angle instead of incrementing it like UG::SetSpriteRotation does.
//Used from Daniel Budworth-Mead's UGFW++ linked on the Facebook group http://pastebin.com/fHGNgjrL
//Will Convert to 4x4 Matrix later.
void OtherFunctions::SetRotationRad(float a_fRad, int a_iSpriteID)
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
void OtherFunctions::SetRotationDeg(float a_fDeg, int a_iSpriteID)
{
	SetRotationRad((DegreesToRadians(a_fDeg)), a_iSpriteID);
}
Vector2 OtherFunctions::GetForwardVector(float a_fDeg)
{
	float x = 0;
	float y = 0;
	x = cos(DegreesToRadians(a_fDeg));
	y = sin(DegreesToRadians(a_fDeg));
	return Vector2(x, y);
}

int OtherFunctions::GetMapTile(int a_iTileWidth, Vector2 a_vPos, int a_iCollisionMap[])
{
	int a_iX = (a_vPos.dX / a_iTileWidth);
	int a_iY = (a_vPos.dY / a_iTileWidth);

	return a_iCollisionMap[(a_iY * iMapWidth) + a_iX];
}

//Function to cast a ray at a sprite from anotherto see if they can see each other.
bool OtherFunctions::RayCast(int a_iSpriteIDEnemy, int a_iSpriteIDPlayer, int a_iCollisionMap[])
{
	Vector2 vPos;
	for (float i = 0; i < 1; i += (1.f / iMapWidth))
	{

		vPos.dX = Lerp(GetSpriteXPos(a_iSpriteIDEnemy), GetSpriteXPos(a_iSpriteIDPlayer), i);
		vPos.dY = Lerp(GetSpriteYPos(a_iSpriteIDEnemy), GetSpriteYPos(a_iSpriteIDPlayer), i);
		int iTileTypes = GetMapTile(32, vPos, a_iCollisionMap);

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

Vector2 OtherFunctions::GetMousePosition()
{
	Vector2 vMousePos;//New Vector2 to hold Mouse position.
	UG::GetMousePos(vMousePos.dX, vMousePos.dY);//Gets the mouse position.
	int iScrX, iScrY;
	UG::GetScreenSize(iScrX, iScrY);
	vMousePos.dY = iScrY - vMousePos.dY;//Reverses the Y-Value given from UG::GetMousePos since it returns Y=0 at the top instead of the bottom.
	return vMousePos;
}