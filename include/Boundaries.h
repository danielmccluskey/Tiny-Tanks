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

	Vector3 vTopLeft;
	Vector3 vTopRight;
	Vector3 vBotLeft;
	Vector3 vBotRight;

	Vector3 vFrontRight;
	Vector3 vFrontLeft;
	Vector3 vBackLeft;
	Vector3 vBackRight;

	Vector2 vAxis1;
	Vector2 vAxis2;
	Vector2 vAxis3;
	Vector2 vAxis4;

	float GetSpriteXPos(int a_iSpriteID);
	float GetSpriteYPos(int a_iSpriteID);
	float GetSpriteHeight(int a_iSpriteWidth, int a_iSpriteHeight, float a_fRad);
	float GetSpriteWidth(int a_iSpriteWidth, int a_iSpriteHeight, float a_fRad);
	void AABB(int a_iSpriteID, int a_iHeight, int a_iWidth, float a_fRad);
	void SeparatingAxisTheorem(int a_iSpriteID, int a_iHeight, int a_iWidth, float a_fRad);
	void SATGetAxis(Boundaries a_sBox1, Boundaries a_sBox2);
	float fUGSpriteMatrix[16];


	

private:


};

#endif //_BOUNDARIES_H_