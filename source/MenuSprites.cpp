//==============================================================================================================================
// Project: WiiTanks
// File: MenuSprites.cpp
// Author: Daniel McCluskey
// Date Created: 07/01/17
// Brief: This is the file that contains the code that handles the menu sprites.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#include "MenuSprites.h"
#include "UGFW.h"
#include "MathUtil.h"
#include "CustomEnum.h"

//Constructor for a menu sprite.
//Vector2 a_vStartPos = The position to place the sprite in.
//Vector2 a_vSize = The size that the sprite should be.
//int iLayer = The layer to draw the sprite on.
//char* a_pcImagePath = The image the sprite should display.
//float a_fUV[2][4] = The UV co-ordinates that the sprite can have.
//bool a_bDrawSprite = Whether the sprite should be drawn straight away or not.
MenuSprite::MenuSprite(Vector2 a_vStartPos, Vector2 a_vSize, int iLayer, char* a_pcImagePath,float a_fUV[2][4], bool a_bDrawSprite)
{
	iSpriteHeight = a_vSize.GetdY();//Gets the Height of the sprite.
	iSpriteWidth = a_vSize.GetdX();//Gets the Width of the sprite.
	iSpriteID = UG::CreateSprite(a_pcImagePath, iSpriteWidth, iSpriteHeight, true);//Creates the sprite.
	UG::SetSpriteUVCoordinates(iSpriteID, a_fUV[0]);//Sets the UV co-ordinates.
	UG::SetSpriteLayer(iSpriteID, iLayer);//Sets the sprites layer.
	vPos = a_vStartPos;//Sets the sprites position.
	UG::MoveSprite(iSpriteID, vPos.GetdX(), vPos.GetdY());//Moves the sprite to that position.
	
	bBeingDrawn = false;//Declares that the sprite is not being drawn.
	bLerpLoop = true;//Declares the lerp loop variable.
	fLerpPosition = 0;//Sets lerp position to 0;

	//Loops through the UV co-ordinates parameter and stores them in the class member.
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			fUVCoords[y][x] = a_fUV[y][x];
		}
	}

	if (a_bDrawSprite)//If the sprite should be drawn.
	{
		DrawSprite();//Draw the sprite.
	}	
}

//Deconstructor
MenuSprite::~MenuSprite()
{
	HideSprite();
	UG::DestroySprite(iSpriteID);
}

//Function to draw the sprite. Includes check to see if sprite is already being drawn to avoid UG framework error.
void MenuSprite::DrawSprite()
{
	if (bBeingDrawn)//If it is already being drawn.
	{
		return;//end
	}
	else
	{
		bBeingDrawn = true;//Toggle
		UG::DrawSprite(iSpriteID);//Draws that.
		return;
	}
}

//Function to stop drawing the sprite. Includes check to see if sprite is already being drawn to avoid UG framework error.
void MenuSprite::HideSprite()
{
	if (bBeingDrawn)
	{
		bBeingDrawn = false;//Toggle
		UG::StopDrawingSprite(iSpriteID);//Stops drawing that.
		return;
	}
	else
	{
		return;
	}
}

//Function to rotate a sprite by a_fDeg degrees (Increments rotation, does not set it)
//a_fDeg = Degrees to rotate by.
void MenuSprite::RotateSprite(float a_fDeg)
{
	UG::RotateSprite(iSpriteID, a_fDeg);
}

//Function to make sprite "Throb" using UG::SetSpriteScale. Couldn't think of a better word than Throb.
//a_fSpeed = The speed at which to throb the object (Between 0 and 1).
//a_fSizeReduction = The size to throb between, e.g. 0.5 will make it throb between Half the sprites size and its full size.
void MenuSprite::ThrobSprite(float a_fSpeed, float a_fSizeReduction)
{
	if (bLerpLoop)//If the lerp is going forwards.
	{
		fLerpPosition += a_fSpeed;//Adds to the lerp.
	}
	else
	{
		fLerpPosition -= a_fSpeed;//Takes from the lerp.
	}

	if (fLerpPosition >= 1)//If lerp has finished
	{
		bLerpLoop = false;//Toggle lerp direction
	}
	if (fLerpPosition <= 0)//If Lerp has finished
	{
		bLerpLoop = true;//Toggle lerp direction.
	}
	float fScaleX = Lerp(iSpriteWidth * a_fSizeReduction, iSpriteWidth, fLerpPosition);//Lerp the X.
	float fScaleY = Lerp(iSpriteHeight * a_fSizeReduction, iSpriteHeight, fLerpPosition);//Lerp the Y.
	UG::SetSpriteScale(iSpriteID, fScaleX, fScaleY);//Sets the scale.
}

//Function to check if the mouse is hovering over a sprite and if it has been clicked.
bool MenuSprite::CheckClick()
{
	UG::SetSpriteUVCoordinates(iSpriteID, fUVCoords[0]);//Sets the UV to its normal state.
	Vector2 vMousePos;//Declares a Vector 2 to store the mouse pos.
	double iMouseX, iMouseY;//Declares 2 variables to store the mousepos.
	UG::GetMousePos(iMouseX, iMouseY);//Gets the mouse position and stores it in the class members variable.
	vMousePos.SetdX(iMouseX);//Stores the Mousepos in the vector2.
	vMousePos.SetdY((iMapHeight * fTileWidth) - iMouseY);//Reverses the Y-Value given from UG::GetMousePos since it returns Y=0 at the top instead of the bottom.
	if (CheckCollision(vMousePos))//If the mouse is colliding with the sprite.
	{
		UG::SetSpriteUVCoordinates(iSpriteID, fUVCoords[1]);//Set the UV to its hovered state.
		if (UG::GetMouseButtonDown(0))//If the mouse is being clicked.
		{
			return true;
		}
	}
	
	return false;
}

//Function to check if given position is colliding with the sprite.
//a_vMousePos = The position to check the collision against the sprite.
bool MenuSprite::CheckCollision(Vector2 a_vMousePos)
{
	if (a_vMousePos.GetdX()  < (vPos.GetdX() - (iSpriteWidth / 2)))//If the pos is to the left of the sprite.
	{
		return false;
	}
	else if (a_vMousePos.GetdX()  > (vPos.GetdX() + (iSpriteWidth / 2)))//If the pos is to the right of the sprite.
	{
		return false;
	}
	else if (a_vMousePos.GetdY() < (vPos.GetdY() - (iSpriteHeight / 2)))//If the pos is below the sprite.
	{
		return false;
	}
	else if (a_vMousePos.GetdY() > (vPos.GetdY() + (iSpriteHeight / 2)))//If the pos is above the sprite.
	{
		return false;
	}

	//If it hasnt returned by now it means that the position HAS to be in the sprite.
	return true;
}