#include "PlayerTank.h"
#include "CustomEnum.h"
#include "Enumerations.h"
#include "UGFW.h"
#include "MathUtil.h"
#include "Vector2.h"
#include "Matrix4x4.h"



void PlayerTank::CreateTank(float a_fCenterX, float a_fCenterY)
{
	iSpriteID = UG::CreateSprite("./images/Tanks/tank_body.png", iSpriteWidth, iSpriteHeight, true);//Create the sprite
																									//UG::SetSpriteLayer(iSpriteID, 4);
	UG::DrawSprite(iSpriteID);	//Draws it
	vPos = Vector2(300, 300);
	UG::MoveSprite(iSpriteID, a_fCenterX, a_fCenterY);
	UG::SetSpriteLayer(iSpriteID, 9);
};

//Function to handle the movement of the tank.
void PlayerTank::MoveTank()
{
	//Function that checks the corner positions of the sprite to see if they are colliding with the map
	/*CollisionDetection(0, 90, pTopRight, pBotLeft);
	CollisionDetection(90, 180, pTopLeft, pBotRight);
	CollisionDetection(180, 270, pBotLeft, pTopRight);
	CollisionDetection(270, 359, pBotRight, pTopLeft);*/


	if (UG::IsKeyDown(UG::KEY_A))
	{
		iRotDeg -= 1;
	}
	if (UG::IsKeyDown(UG::KEY_D))
	{
		iRotDeg += 1;
	}

	if (iRotDeg >= 360)
	{
		iRotDeg = 0;
	}
	else if (iRotDeg < 0)
	{
		iRotDeg = 359;
	}

	
	UG::GetMousePos(vMousePos.dX, vMousePos.dY);
	vMousePos.dY = (iMapHeight * fTileWidth) - vMousePos.dY;

	vVelocity = vVelocity.RotateX(-iRotDeg+90);
	if (UG::IsKeyDown(UG::KEY_W))
	{
		vPos += vVelocity;
	}
	if (UG::IsKeyDown(UG::KEY_S))
	{
		vPos -= vVelocity;
	}

	
	
	UG::GetSpriteMatrix(iSpriteID, fSpriteyMatrix);
	Matrix4x4 mSpriteMatrix(fSpriteyMatrix);
	Matrix4x4 mRotateMatrix(fSpriteyMatrix);
	mRotateMatrix.RotateZ((DegreesToRadians((iRotDeg))));
	//mSpriteMatrix *= mRotateMatrix;
	

	mRotateMatrix.GetMatrix(fSpriteyMatrix);

	UG::SetSpriteMatrix(iSpriteID, fSpriteyMatrix);


	UG::MoveSprite(iSpriteID, vPos.dX, vPos.dY);

}