#include "PlayerTank.h"
#include "MathUtil.h"
#include "Enumerations.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>
void PlayerTank::CreateTank(float a_fCenterX, float a_fCenterY)
{
	iSpriteID = UG::CreateSprite("./images/Tanks/tank_body.png", iSpriteWidth, iSpriteHeight, true);//Create the sprite
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

	if (iRotDeg >= 360)
	{
		iRotDeg = 0;
	}
	else if (iRotDeg < 0)
	{
		iRotDeg = 359;
	}
	DANM::SetRotationDeg(-(iRotDeg)+90, iSpriteID);
	
}
void PlayerTank::UpdateCollisionMap()
{
	std::ifstream pCollision;//Creates an input fstream member
	pCollision.open("./maps/currentCollision.txt");//Opens the file.
	for (int i = 0; i < (iMapHeight*iMapWidth); i++)//Iterates through each tile in the array.
	{
		pCollision >> iCollisionMap[i];//Stores current tile type into array.
	}
	pCollision.close();
}
void PlayerTank::GetSurroundingTiles(int a_iTileWidth)
{
	Vertices pCorners(iSpriteID, iSpriteHeight, iSpriteWidth, DegreesToRadians(iRotDeg));
	pTopLeft = Vector3(
		pCorners.vTopLeft.dX,
		pCorners.vTopLeft.dY,
		GetTile(a_iTileWidth, pCorners.vTopLeft)
	);
	pTopRight;
	pBotLeft;
	pBotRight;
}

int PlayerTank::GetTile(int a_iTileWidth, Vector2 a_vPos)
{
	int a_iX = (a_vPos.dX / a_iTileWidth);
	int a_iY = (a_vPos.dY / a_iTileWidth);
	std::cout << iCollisionMap[(a_iY * iMapWidth) + a_iX] << std::endl;
	return iCollisionMap[(a_iY * iMapWidth) + a_iX];
}