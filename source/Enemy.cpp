#include "Vector2.h"
#include "CustomEnum.h"
#include "Enemy.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>
#include "UGFW.h"

void Enemy::CreateTank(float a_fCenterX, float a_fCenterY)
{
	iSpriteID = UG::CreateSprite("./images/Tanks/tank_body.png", iSpriteWidth, iSpriteHeight, true);//Create the sprite
																									
	UG::DrawSprite(iSpriteID);	//Draws it
	vPos = Vector2(a_fCenterX, a_fCenterX);
	UG::MoveSprite(iSpriteID, a_fCenterX, a_fCenterY);
	UG::SetSpriteLayer(iSpriteID, 9);
};
void Enemy::StepTank(Vector2 a_vStart, Vector2 a_vGoal)
{
	int iDirection = PathFindTileCheck(a_vStart, a_vGoal);
	switch (iDirection)
	{
	case 0:
		vPos.dX -= fTileWidth;
		break;
	case 1:
		vPos.dX += fTileWidth;
		break;
	case 2:
		vPos.dY -= fTileWidth;
		break;
	case 3:
		vPos.dY += fTileWidth;
		break;
	}

	UG::MoveSprite(iSpriteID, vPos.dX + (iSpriteWidth/2), vPos.dY + (iSpriteHeight/2));
}

int Enemy::PathFindTileCheck(Vector2 a_vStart, Vector2 a_vGoal)
{

	a_vStart.dX = int(a_vStart.dX / fTileWidth);
	a_vStart.dY = int(a_vStart.dY / fTileWidth);
	a_vGoal.dX = int(a_vGoal.dX / fTileWidth);
	a_vGoal.dY = int(a_vGoal.dY / fTileWidth);
	Vector2 vLeftTile = Vector2(a_vStart.dX - 1, a_vStart.dY);
	Vector2 vRightTile = Vector2(a_vStart.dX + 1, a_vStart.dY);
	Vector2 vTopTile = Vector2(a_vStart.dX, a_vStart.dY + 1);
	Vector2 vBottomTile = Vector2(a_vStart.dX, a_vStart.dY - 1);
	
	iLeftCost = GetTile(fTileWidth, vLeftTile);
	iRightCost = GetTile(fTileWidth, vRightTile);
	iTopCost = GetTile(fTileWidth, vTopTile);
	iBottomCost = GetTile(fTileWidth, vBottomTile);



	(iLeftCost == 0) ? (iLeftCost = PathFindHCalc(vLeftTile, a_vGoal)) : (iLeftCost = 100);
	(iRightCost == 0) ? (iRightCost = PathFindHCalc(vRightTile, a_vGoal)) : (iRightCost = 100);
	(iTopCost == 0) ? (iTopCost = PathFindHCalc(vTopTile, a_vGoal)) : (iTopCost = 100);
	(iBottomCost == 0) ? (iBottomCost = PathFindHCalc(vBottomTile, a_vGoal)) : (iBottomCost = 100);
	

	std::cout << "Left: " << iLeftCost << std::endl;
	std::cout << "Right: " << iRightCost << std::endl;
	std::cout << "Top: " << iTopCost << std::endl;
	std::cout << "Bot: " << iBottomCost << std::endl;

	int iNewMin = 0;
	int iOldMin = 0;
	int iChooseMin = 100;
	int minArray[4] = { iLeftCost, iRightCost, iBottomCost, iTopCost };
	for (int i = 0; i < 4; i++)
	{
		if (minArray[i] < iChooseMin)
		{
			iOldMin = iNewMin;
			iNewMin = i;
			iChooseMin = minArray[i];
		}
	}

	return iNewMin;
	if (iNewMin == 0 && iLastDirection != 1)
	{
		iLastDirection = iNewMin;
		return iNewMin;
	}
	else if (iNewMin == 1 && iLastDirection != 0)
	{
		iLastDirection = iNewMin;
		return iNewMin;
	}
	else if (iNewMin == 2 && iLastDirection != 3)
	{
		iLastDirection = iNewMin;
		return iNewMin;
	}
	else if (iNewMin == 3 && iLastDirection != 2)
	{
		iLastDirection = iNewMin;
		return iNewMin;
	}
	else
	{
		iLastDirection = iOldMin;
		return iOldMin;
	}

	
}
int Enemy::PathFindFCalc(Vector2 a_vStart, Vector2 a_vGoal)
{
	int iHueristic = PathFindHCalc(a_vStart, a_vGoal);
	int iCost = 1;
	return iCost + iHueristic;
}
int Enemy::PathFindHCalc(Vector2 a_vStart, Vector2 a_vGoal)
{
	//Works out the "As the crow flies" distance to the goal first moving down to the X and then the Y.
	int iX = 0;
	int iY = 0;

	if (a_vStart.dX == a_vGoal.dX)
	{
		iX = 0;
	}
	else if (a_vStart.dX > a_vGoal.dX)
	{
		iX = a_vStart.dX - a_vGoal.dX;
	}
	else if (a_vStart.dX < a_vGoal.dX)
	{
		iX = a_vGoal.dX - a_vStart.dX;
	}

	if (a_vStart.dY == a_vGoal.dY)
	{
		iY = 0;
	}
	else if (a_vStart.dY > a_vGoal.dY)
	{
		iY = a_vStart.dY - a_vGoal.dY;
	}
	else if (a_vStart.dY < a_vGoal.dY)
	{
		iY = a_vGoal.dY - a_vStart.dY;
	}

	std::cout << "\n\n\n\X: " << iX << std::endl;
	std::cout << "Y: " << iY << std::endl;

	return iX + iY;
}

void Enemy::UpdateCollisionMap()
{
	std::ifstream pCollision;//Creates an input fstream member
	pCollision.open("./maps/currentCollision.txt");//Opens the file.
	for (int i = 0; i < (iMapHeight*iMapWidth); i++)//Iterates through each tile in the array.
	{
		pCollision >> iEnemyCollisionMap[i];//Stores current tile type into array.
	}
	pCollision.close();
}
int Enemy::GetTile(int a_iTileWidth, Vector2 a_vPos)
{
	int a_iX = (a_vPos.dX);
	int a_iY = (a_vPos.dY);

	return iEnemyCollisionMap[(a_iY * iMapWidth) + a_iX];
}