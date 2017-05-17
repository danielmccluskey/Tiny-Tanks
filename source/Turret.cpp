#include "Turret.h"
#include "UGFW.h"

Turret::Turret()
{
	iSpriteID = UG::CreateSprite("./images/Tanks/tank_turret.png", 30, 80, true);//Create the sprite
	UG::DrawSprite(iSpriteID);	//Draws it
	UG::SetSpriteLayer(iSpriteID, 10);//Draws the turret above the tank.
};