//==============================================================================================================================
// Project: WiiTanks
// File: MenuSprites.h
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the header file that contains the code that draws the maps from files and generates the collision map.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#ifndef _MENUSPRITES_H_
#define _MENUSPRITES_H_
#include "Vector2.h"

class MenuSprite
{
public:

	MenuSprite(Vector2 a_vStartPos, Vector2 a_vSize, int iLayer, char* a_pcImagePath);
	~MenuSprite();
	void DrawSprite();
	void HideSprite();
	void RotateSprite(float a_fDeg);
	void ThrobSprite(float a_fSpeed, float a_fSizeReduction);
	bool CheckCollision(Vector2 a_vMousePos);
	bool CheckClick();



private:
	int iSpriteID = 0;//Sprite ID
	Vector2 vPos;
	bool bBeingDrawn;
	float fLerpPosition;
	bool bLerpLoop;
	int iSpriteHeight;
	int iSpriteWidth;
};

#endif //_MENUSPRITES_H_