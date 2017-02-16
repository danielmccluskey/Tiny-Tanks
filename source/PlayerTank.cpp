#include "PlayerTank.h"
#include "MathUtil.h"
#include "Enumerations.h"
void PlayerTank::CreateTank(float a_fCenterX, float a_fCenterY)
{
	iSpriteID = UG::CreateSprite("./images/Tanks/temp.png", 32, 64, true);//Create the sprite
	//UG::SetSpriteLayer(iSpriteID, 4);
	UG::DrawSprite(iSpriteID);	//Draws it
	pos = Vector2(a_fCenterX, a_fCenterY);
	UG::MoveSprite(iSpriteID, a_fCenterX, a_fCenterY);
};

void PlayerTank::MoveTank()
{
	if (UG::IsKeyDown(UG::KEY_W))
	{
		pos += DANM::GetForwardVector(iRotDeg);
	}
	if (UG::IsKeyDown(UG::KEY_S))
	{
		pos -= DANM::GetForwardVector(iRotDeg);
	}
	if (UG::IsKeyDown(UG::KEY_D))
	{
		iRotDeg -= 1;
	}
	if (UG::IsKeyDown(UG::KEY_A))
	{
		iRotDeg += 1;
	}
	DANM::SetRotationDeg(-(iRotDeg), iSpriteID);
	
}
void PlayerTank::GetSurroundingTiles()
{
	
}