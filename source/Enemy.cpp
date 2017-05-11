#include "Enemy.h"
#include "OtherFunctions.h"
#include "Enumerations.h"
#include "UGFW.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>
struct EnemyTurret
{
	EnemyTurret()
	{
		iSpriteID = UG::CreateSprite("./images/Tanks/tank_turret.png", 30, 80, true);//Create the sprite
		UG::DrawSprite(iSpriteID);	//Draws it
		UG::SetSpriteLayer(iSpriteID, 10);
	};
	int iSpriteID = 0;
	int iRotDeg = 0;
};
void Enemy::CreateTank(float a_fCenterX, float a_fCenterY)
{
	iSpriteID = UG::CreateSprite("./images/Tanks/tank_body.png", iSpriteWidth, iSpriteHeight, true);//Create the sprite
																									//UG::SetSpriteLayer(iSpriteID, 4);
	UG::DrawSprite(iSpriteID);	//Draws it
	pos = Vector2(a_fCenterX, a_fCenterX);
	UG::MoveSprite(iSpriteID, a_fCenterX, a_fCenterY);
	UG::SetSpriteLayer(iSpriteID, 9);
};

//Function to handle the movement of the tank.
void Enemy::MoveTank(float a_fDeg)
{	
	UG::MoveSprite(iSpriteID, pos.dX, pos.dY);
	UG::MoveSprite(sTurret.iSpriteID, pos.dX, pos.dY);
	SetRotationDeg(-(iRotDeg)+90, iSpriteID);
	SetRotationDeg(-a_fDeg, sTurret.iSpriteID);

}
void Enemy::CollisionDetection(int a_iLowerBound, int a_iUpperBound, Vector3& a_vForwards, Vector3& a_vBackwards)
{

	if (iRotDeg >= a_iLowerBound && iRotDeg <= a_iUpperBound)
	{
		if (UG::IsKeyDown(UG::KEY_W) && a_vForwards.dZ == 0 && pFront.dZ == 0)
		{
			pos += GetForwardVector(iRotDeg);
		}
		if (UG::IsKeyDown(UG::KEY_S) && a_vBackwards.dZ == 0)
		{
			pos -= GetForwardVector(iRotDeg);
		}
	}
}
void Enemy::UpdateCollisionMap()
{
	std::ifstream pCollision;//Creates an input fstream member
	pCollision.open("./maps/currentCollision.txt");//Opens the file.
	for (int i = 0; i < (iMapHeight*iMapWidth); i++)//Iterates through each tile in the array.
	{
		pCollision >> iCollisionMap[i];//Stores current tile type into array.
	}
	pCollision.close();
}
void Enemy::GetSurroundingTiles(int a_iTileWidth)
{
	AABB pCorners(iSpriteID, iSpriteHeight, iSpriteWidth, DegreesToRadians(iRotDeg + 90));
	pTopLeft = Vector3(
		pCorners.vTopLeft.dX,
		pCorners.vTopLeft.dY,
		GetTile(a_iTileWidth, pCorners.vTopLeft)
	);
	pTopRight = Vector3(
		pCorners.vTopRight.dX,
		pCorners.vTopRight.dY,
		GetTile(a_iTileWidth, pCorners.vTopRight)
	);
	pBotLeft = Vector3(
		pCorners.vBotLeft.dX,
		pCorners.vBotLeft.dY,
		GetTile(a_iTileWidth, pCorners.vBotLeft)
	);
	pBotRight = Vector3(
		pCorners.vBotRight.dX,
		pCorners.vBotRight.dY,
		GetTile(a_iTileWidth, pCorners.vBotRight)
	);
	pFront = Vector3(
		pCorners.vFront.dX,
		pCorners.vFront.dY,
		GetTile(a_iTileWidth, pCorners.vFront)

	);

	pBack = Vector3(
		pCorners.vBack.dX,
		pCorners.vBack.dY,
		GetTile(a_iTileWidth, pCorners.vBack)
	);
}

int Enemy::GetTile(int a_iTileWidth, Vector2 a_vPos)
{
	int a_iX = (a_vPos.dX / a_iTileWidth);
	int a_iY = (a_vPos.dY / a_iTileWidth);

	return iCollisionMap[(a_iY * iMapWidth) + a_iX];
}