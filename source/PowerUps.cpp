#include "PowerUps.h"
#include "Boundaries.h"
#include "CustomEnum.h"
#include <fstream>
#include "UGFW.h"
#include <random>
#include <iostream>
#include <time.h>
#include "MathUtil.h"
PowerUps::PowerUps()
{
	iMaxPowerUps = 18;
	iCurrentActive = 0;
	bActive = false;
	fTimer = 10.f;
	srand(time(NULL));
}

void PowerUps::SetTankID(int a_iSpriteID)
{
	iTankSpriteID = a_iSpriteID;
}
bool PowerUps::SpawnPowerUps(PowerUps* a_pPowerUpArray,int a_iSpriteID, int a_iWidth, int a_iHeight, float a_fRad)
{
	bool bDestroyed = DestroyPowerUps(a_pPowerUpArray, a_iSpriteID, a_iWidth, a_iHeight, a_fRad);
	fTimer -= 0.1f;
	if (CheckChance())
	{
		Vector2 vRandomCheck;
		vRandomCheck.SetdX(rand() % int(fTileWidth*fMapWidth));
		vRandomCheck.SetdY(rand() % int(fTileWidth*fMapHeight));

		if (GetTile(iCollisionMap, vRandomCheck) == 1)
		{
			vRandomCheck.SetdX(rand() % int(fTileWidth*fMapWidth));
			vRandomCheck.SetdY(rand() % int(fTileWidth*fMapHeight));
		}
		else if(GetTile(iCollisionMap, vRandomCheck) == 0)
		{
			fTimer = 10.f;
			CreatePowerup(vRandomCheck, a_pPowerUpArray);
		}
	}
	
	return bDestroyed;
}
bool PowerUps::CheckChance()
{
	if (iCurrentActive < iMaxPowerUps)
	{
		
		fRandChance = rand() % 100;
		
		if (fRandChance <= 25 && fTimer <= 0)
		{
			
			return true;
		}
	}
	return false;
}

void PowerUps::CreatePowerup(Vector2 a_vPos, PowerUps* a_pPowerUpArray)
{
	if (iCurrentActive < iMaxPowerUps)
	{
		for (int i = 0; i < iMaxPowerUps; i++)
		{
			if (a_pPowerUpArray[i].bActive == false)
			{
				a_pPowerUpArray[i].iSpriteID = UG::CreateSprite("./images/Tanks/temp.png", 4, 4, true);//Create the sprite
				UG::DrawSprite(a_pPowerUpArray[i].iSpriteID);	//Draws it
				a_pPowerUpArray[i].vPos = a_vPos;
				UG::SetSpriteLayer(a_pPowerUpArray[i].iSpriteID, 9);
				UG::MoveSprite(a_pPowerUpArray[i].iSpriteID, a_pPowerUpArray[i].vPos.GetdX(), a_pPowerUpArray[i].vPos.GetdY());
				a_pPowerUpArray[i].bActive = true;
				iCurrentActive++;
				break;
			}
		}
	}
	
}
bool PowerUps::CheckSpriteCollision(int a_iSpriteID, int a_iWidth, int a_iHeight, float a_fRad)
{
	Boundaries AABBCheck;
	AABBCheck.AABB(a_iSpriteID, a_iWidth, a_iHeight, a_fRad);
	for (int i = 0; i < iMaxPowerUps; i++)
	{
		if (bActive == true)
		{
			if ((vPos.GetdX() < AABBCheck.vTopRight.GetdX()) && (vPos.GetdX() > AABBCheck.vTopLeft.GetdX()) &&
				(vPos.GetdY() < AABBCheck.vTopRight.GetdY()) && (vPos.GetdY() > AABBCheck.vBotLeft.GetdY()))
			{
				return true;
			}
		}

	}
	return false;
}
int PowerUps::GetTile(int a_iCollisionMap[], Vector2 a_vPos)
{
	int a_iX = (a_vPos.GetdX() / fTileWidth);
	int a_iY = (a_vPos.GetdY() / fTileWidth);

	return a_iCollisionMap[(a_iY * iMapWidth) + a_iX];
}
void PowerUps::UpdateCollisionMap()
{
	std::ifstream pCollision;//Creates an input fstream member
	pCollision.open("./maps/currentCollision.txt");//Opens the file.
	for (int i = 0; i < (iMapHeight*iMapWidth); i++)//Iterates through each tile in the array.
	{
		pCollision >> iCollisionMap[i];//Stores current tile type into array.
	}
	pCollision.close();
}

bool PowerUps::DestroyPowerUps(PowerUps* a_pPowerUpArray, int a_iSpriteID, int a_iWidth, int a_iHeight, float a_fRad)
{
	for (int i = 0; i < iMaxPowerUps; i++)
	{
		if (a_pPowerUpArray[i].bActive == true)
		{
			std::cout << "x: " << a_pPowerUpArray[i].vPos.GetdX() << std::endl;
			std::cout << "y: " << a_pPowerUpArray[i].vPos.GetdY() << std::endl;
			std::cout << iCurrentActive << std::endl;
			if (a_pPowerUpArray[i].CheckSpriteCollision(a_iSpriteID, a_iWidth, a_iHeight, DegreesToRadians( a_fRad)))
			{
				UG::StopDrawingSprite(a_pPowerUpArray[i].iSpriteID);
				UG::DestroySprite(a_pPowerUpArray[i].iSpriteID);
				--iCurrentActive;
				a_pPowerUpArray[i].bActive = false;
				return true;
			}
		}

	}
	return false;
}
