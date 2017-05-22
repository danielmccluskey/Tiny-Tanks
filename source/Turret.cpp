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