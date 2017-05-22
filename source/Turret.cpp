//==============================================================================================================================
// Project: WiiTanks
// File: Turret.cpp
// Author: Daniel McCluskey
// Date Created: 07/01/17
// Brief: This is the header file used to create a turret for each the Playr and the enemies.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#include "Turret.h"
#include "UGFW.h"

//Creates the turret
//char* a_cImagePath = The image for the sprite to use.
Turret::Turret(char* a_cImagePath)
{
	iSpriteID = UG::CreateSprite(a_cImagePath, 30, 80, true);//Create the sprite
	UG::DrawSprite(iSpriteID);	//Draws it
	UG::SetSpriteLayer(iSpriteID, 10);//Draws the turret above the tank.
};