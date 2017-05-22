//==============================================================================================================================
// Project: WiiTanks
// File: MenuSprites.h
// Author: Daniel McCluskey
// Date Created: 07/01/17
// Brief: This is the header file that contains the code that handles menu sprites.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#ifndef _MENUSPRITES_H_
#define _MENUSPRITES_H_
#include "Vector2.h"

class MenuSprite
{
public:

	//Constructor for a menu sprite.
	//Vector2 a_vStartPos = The position to place the sprite in.
	//Vector2 a_vSize = The size that the sprite should be.
	//int iLayer = The layer to draw the sprite on.
	//char* a_pcImagePath = The image the sprite should display.
	//float a_fUV[2][4] = The UV co-ordinates that the sprite can have.
	//bool a_bDrawSprite = Whether the sprite should be drawn straight away or not.
	MenuSprite(Vector2 a_vStartPos, Vector2 a_vSize, int iLayer, char* a_pcImagePath, float a_fUV[2][4], bool a_bDrawSprite);
	~MenuSprite();
	//==============================================================================================================================
	//Voids
	//==============================================================================================================================

	//Function to draw the sprite. Includes check to see if sprite is already being drawn to avoid UG framework error.
	void DrawSprite();

	//Function to stop drawing the sprite. Includes check to see if sprite is already being drawn to avoid UG framework error.
	void HideSprite();

	//Function to rotate a sprite by a_fDeg degrees (Increments rotation, does not set it)
	//a_fDeg = Degrees to rotate by.
	void RotateSprite(float a_fDeg);

	//Function to make sprite "Throb" using UG::SetSpriteScale. Couldn't think of a better word than Throb.
	//a_fSpeed = The speed at which to throb the object (Between 0 and 1).
	//a_fSizeReduction = The size to throb between, e.g. 0.5 will make it throb between Half the sprites size and its full size.
	void ThrobSprite(float a_fSpeed, float a_fSizeReduction);

	//==============================================================================================================================
	//Bools
	//==============================================================================================================================

	//Function to check if given position is colliding with the sprite.
	//a_vMousePos = The position to check the collision against the sprite.
	bool CheckCollision(Vector2 a_vMousePos);
		
	//Function to check if the mouse is hovering over a sprite and if it has been clicked.
	bool CheckClick();



private:
	//==============================================================================================================================
	//Ints
	//==============================================================================================================================

	int iCurrentLevel;//Stores the current level.
	int iSpriteID = 0;//Sprite ID
	int iSpriteHeight;//Stores the Sprite Height
	int iSpriteWidth;//Stores the Sprite Width

	//==============================================================================================================================
	//Vector2
	//==============================================================================================================================

	Vector2 vPos;//Stores the position of the sprite.

	//==============================================================================================================================
	//Bools
	//==============================================================================================================================

	bool bBeingDrawn;//Stores whether the sprite is being drawn or not.
	bool bLerpLoop;//Stores what direction the lerp should be going.

	//==============================================================================================================================
	//Floats
	//==============================================================================================================================

	float fLerpPosition;//Store the lerp value.
	float fUVCoords[2][4];//Stores the UV co-ordinates.
};

#endif //_MENUSPRITES_H_