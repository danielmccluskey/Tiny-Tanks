//==============================================================================================================================
// Project: WiiTanks
// File: Boundaries.h
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the header file for the collision boundaries generator.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#ifndef _BOUNDARIES_H_
#define _BOUNDARIES_H_
#include "Vector3.h"
#include "Vector2.h"

class Boundaries		
{
public:
	//==============================================================================================================================
	//Vector3
	//==============================================================================================================================

	//Variables to store the AABB Positions.
	Vector3 vTopLeft;
	Vector3 vTopRight;
	Vector3 vBotLeft;
	Vector3 vBotRight;

	//Variables to store the forward and Backward positions of a sprite.
	Vector3 vFrontRight;
	Vector3 vFrontLeft;
	Vector3 vBackLeft;
	Vector3 vBackRight;

	//==============================================================================================================================
	//Floats
	//==============================================================================================================================

	//Function to Get just the Xpos of a sprite.
	//Used from Daniel Budworth-Mead's UGFW++ linked on the Facebook group http://pastebin.com/fHGNgjrL
	//int a_uiSpriteID = The ID of the given sprite.
	float GetSpriteXPos(int a_iSpriteID);

	//Function to Get just the Ypos of a sprite.
	//Used from Daniel Budworth-Mead's UGFW++ linked on the Facebook group http://pastebin.com/fHGNgjrL
	//int a_uiSpriteID = The ID of the given sprite.
	float GetSpriteYPos(int a_iSpriteID);

	//Function to return the height of a given sprite.
	//Equation from Stack overflow - http://stackoverflow.com/a/6657768
	//int a_iSpriteWidth = Width of the Sprite.
	//int a_iSpriteHeight = Height of the Sprite.
	//float a_fRad = The rotation of the sprite in radians.
	float GetSpriteHeight(int a_iSpriteWidth, int a_iSpriteHeight, float a_fRad);

	//Function to return the Width of a given sprite.
	//Equation from Stack overflow - http://stackoverflow.com/a/6657768
	//int a_iSpriteWidth = Width of the Sprite.
	//int a_iSpriteHeight = Height of the Sprite.
	//float a_fRad = The rotation of the sprite in radians.
	float GetSpriteWidth(int a_iSpriteWidth, int a_iSpriteHeight, float a_fRad);
	
	//==============================================================================================================================
	//Voids
	//==============================================================================================================================

	//Function to generate the corner positions for an AABB.
	//int a_iSpriteID = The ID of the given sprite.
	//int a_iHeight = Height of the Sprite.
	//int a_iWidth = Width of the Sprite.
	//float a_fRad = The rotation of the sprite in radians.
	void AABB(int a_iSpriteID, int a_iHeight, int a_iWidth, float a_fRad);

	//Function that simply gets the positions of the corners of a Rectangular box sprite.
	//int a_iSpriteID = The ID of the given sprite.
	//int a_iHeight = Height of the Sprite.
	//int a_iWidth = Width of the Sprite.
	//float a_fRad = The rotation of the sprite in radians.
	void SeparatingAxisTheorem(int a_iSpriteID, int a_iHeight, int a_iWidth, float a_fRad);
	


	

private:
	//==============================================================================================================================
	//Floats
	//==============================================================================================================================

	float fUGSpriteMatrix[16];//Stores the UGFramework sprite matrix.

};

#endif //_BOUNDARIES_H_