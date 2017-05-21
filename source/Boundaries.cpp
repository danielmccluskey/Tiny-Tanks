#include "Boundaries.h"
#include "UGFW.h"
#include "MathUtil.h"
//==============================================================================================================================
// Project: WiiTanks
// File: Boundaries.cpp
// Author: Daniel McCluskey
// Date Created: 17/01/17
// Brief: This file generates positions for AABB corners and the four corners of any sprite. Separated Axis Therom is mentioned, but is not actually used/Complete.
// Brief: This was not included in the Math library since I did not have time to re-do the functions that use the UG Framework.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================

//Function to return the Width of a given sprite.
//Equation from Stack overflow - http://stackoverflow.com/a/6657768
//int a_iSpriteWidth = Width of the Sprite.
//int a_iSpriteHeight = Height of the Sprite.
//float a_fRad = The rotation of the sprite in radians.
float Boundaries::GetSpriteWidth(int a_iSpriteWidth, int a_iSpriteHeight, float a_fRad)
{
	return ((a_iSpriteWidth * abs(cos(a_fRad))) + (a_iSpriteHeight * abs(sin(a_fRad))));
}
//Function to return the height of a given sprite.
//Equation from Stack overflow - http://stackoverflow.com/a/6657768
//int a_iSpriteWidth = Width of the Sprite.
//int a_iSpriteHeight = Height of the Sprite.
//float a_fRad = The rotation of the sprite in radians.
float Boundaries::GetSpriteHeight(int a_iSpriteWidth, int a_iSpriteHeight, float a_fRad)
{
	return ((a_iSpriteWidth * abs(sin(a_fRad))) + (a_iSpriteHeight * abs(cos(a_fRad))));
}
//Function to Get just the Xpos of a sprite.
//Used from Daniel Budworth-Mead's UGFW++ linked on the Facebook group http://pastebin.com/fHGNgjrL
//int a_uiSpriteID = The ID of the given sprite.
float Boundaries::GetSpriteXPos(int a_uiSpriteID)
{
	UG::GetSpriteMatrix(a_uiSpriteID, fUGSpriteMatrix);
	return fUGSpriteMatrix[12];
}
//Function to Get just the Ypos of a sprite.
//Used from Daniel Budworth-Mead's UGFW++ linked on the Facebook group http://pastebin.com/fHGNgjrL
//int a_uiSpriteID = The ID of the given sprite.
float Boundaries::GetSpriteYPos(int a_uiSpriteID)
{
	UG::GetSpriteMatrix(a_uiSpriteID, fUGSpriteMatrix);
	return fUGSpriteMatrix[13];
}

//Function to generate the corner positions for an AABB.
//int a_iSpriteID = The ID of the given sprite.
//int a_iHeight = Height of the Sprite.
//int a_iWidth = Width of the Sprite.
//float a_fRad = The rotation of the sprite in radians.
void Boundaries::AABB(int a_iSpriteID, int a_iHeight, int a_iWidth, float a_fRad)
{
	Vector3 vPos = Vector3(GetSpriteXPos(a_iSpriteID), GetSpriteYPos(a_iSpriteID),0);//Gets the position of the sprite and stores it.
	float fWidth = GetSpriteWidth(a_iWidth, a_iHeight, a_fRad);//Gets the width of the rotated sprite.
	float fHeight = GetSpriteHeight(a_iWidth, a_iHeight, a_fRad);//Gets the height of the rotated sprite.
	vTopLeft = Vector3(
		(vPos.dX - (fWidth) / 2),
		(vPos.dY + (fHeight) / 2),
		0
	);//Gets the X + Y of the Top Left corner of the AABB.
	vTopRight = Vector3(
		(vPos.dX + (fWidth) / 2),
		(vPos.dY + (fHeight) / 2),
		0
	);//Gets the X + Y of the Top right corner of the AABB.
	vBotLeft = Vector3(
		(vPos.dX - (fWidth) / 2),
		(vPos.dY - (fHeight) / 2),
		0
	);//Gets the X + Y of the Bottom Left corner of the AABB.
	vBotRight = Vector3(
		(vPos.dX + (fWidth) / 2),
		(vPos.dY - (fHeight) / 2),
		0
	);//Gets the X + Y of the Bottom right corner of the AABB.

}

//Function that simply gets the positions of the corners of a Rectangular box sprite.
//int a_iSpriteID = The ID of the given sprite.
//int a_iHeight = Height of the Sprite.
//int a_iWidth = Width of the Sprite.
//float a_fRad = The rotation of the sprite in radians.
void Boundaries::SeparatingAxisTheorem(int a_iSpriteID, int a_iHeight, int a_iWidth, float a_fRad)
{
	Vector3 vPos = Vector3(GetSpriteXPos(a_iSpriteID), GetSpriteYPos(a_iSpriteID), 0);//Gets the position of the sprite and stores it.
	vFrontRight = Vector3(
		(vPos.dX) + cos(-a_fRad - f2HALF_PI) * a_iWidth / 2,
		(vPos.dY) + sin(-a_fRad - f2HALF_PI) * a_iHeight / 2,
		0
	);//Gets the Front right X+Y position of the given sprite.
	vFrontLeft = Vector3(
		(vPos.dX) + cos(-a_fRad + f2HALF_PI) * a_iWidth / 2,
		(vPos.dY) + sin(-a_fRad + f2HALF_PI) * a_iHeight / 2,
		0
	);//Gets the Front Left X+Y position of the given sprite.
	vBackLeft = Vector3(
		(vPos.dX) - cos(-a_fRad - f2HALF_PI) * a_iWidth / 2,
		(vPos.dY) - sin(-a_fRad - f2HALF_PI) * a_iHeight / 2,
		0
	);//Gets the Back Left X+Y position of the given sprite.
	vBackRight = Vector3(
		(vPos.dX) - cos(-a_fRad + f2HALF_PI) * a_iWidth / 2,
		(vPos.dY) - sin(-a_fRad + f2HALF_PI) * a_iHeight / 2,
		0
	);//Gets the Back right X+Y position of the given sprite.

	
}
//Functions to get the Axis for the Separated Axis therom collision.
//Boundaries a_sBox1 = Any given Boundaries class member.
//Boundaries a_sBox2 = Any given Boundaries class member.
void Boundaries::SATGetAxis(Boundaries a_sBox1, Boundaries a_sBox2)
{
	vAxis1.dX = a_sBox1.vFrontRight.dX - a_sBox1.vFrontLeft.dX;
	vAxis1.dY = a_sBox1.vFrontRight.dY - a_sBox1.vFrontLeft.dY;
	vAxis2.dX = a_sBox1.vFrontRight.dX - a_sBox1.vBackRight.dX;
	vAxis2.dY = a_sBox1.vFrontRight.dY - a_sBox1.vBackRight.dY;
	vAxis3.dX = a_sBox2.vFrontLeft.dX - a_sBox2.vBackLeft.dX;
	vAxis3.dY = a_sBox2.vFrontLeft.dY - a_sBox2.vBackLeft.dY;
	vAxis4.dX = a_sBox2.vFrontLeft.dX - a_sBox2.vFrontRight.dX;
	vAxis4.dY = a_sBox2.vFrontLeft.dY - a_sBox2.vFrontRight.dY;
}