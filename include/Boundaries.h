//==============================================================================================================================
// Project: WiiTanks
// File: Boundaries.h
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the header file that contains the code that draws the maps from files and generates the collision map.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#ifndef _BOUNDARIES_H_
#define _BOUNDARIES_H_
#include "Vector3.h"
//class Vector2;//Forward Declaration.

class Boundaries		
{
public:

	Vector3 vTopLeft;
	Vector3 vTopRight;
	Vector3 vBotLeft;
	Vector3 vBotRight;
	Vector3 vFront;
	Vector3 vBack;

	float GetSpriteXPos(int a_iSpriteID);
	float GetSpriteYPos(int a_iSpriteID);
	float GetSpriteHeight(int a_iSpriteWidth, int a_iSpriteHeight, float a_fRad);
	float GetSpriteWidth(int a_iSpriteWidth, int a_iSpriteHeight, float a_fRad);
	void AABB(int a_iSpriteID, int a_iHeight, int a_iWidth, float a_fRad);

	float fUGSpriteMatrix[16];


	

private:


};

#endif //_BOUNDARIES_H_