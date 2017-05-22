//==============================================================================================================================
// Project: WiiTanks
// File: MapCreation.h
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the header file that contains the code that draws the maps from files and generates the collision map.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#include "PowerUps.h"
#include "Boundaries.h"
#include "CustomEnum.h"
#include <fstream>
#include "UGFW.h"
#include <random>
#include <iostream>
#include <time.h>
#include "MathUtil.h"

//Constructor
PowerUps::PowerUps()
{
	iMaxPowerUps = 2;//Sets the max amount of powerups to spawn
	iCurrentActive = 0;//Resets currently active
	bActive = false;//Sets bActive to false
	fTimer = 10.f;//Sets the timer to 10
	srand(time(NULL));//Resets random seed to get more random positions.
}

//Sets the collision id to the given parameter
//int a_iSpriteID = The sprite to collide with.
void PowerUps::SetTankID(int a_iSpriteID)
{
	iTankSpriteID = a_iSpriteID;
}

//Function to randomly spawn powerups
//PowerUps* a_pPowerUpArray = The Powerup array to loop through
//int a_iSpriteID = The sprite id of the tank to check collisions against.
//int a_iWidth = The width of the sprite
//int a_iHeight = The height of the tank sprite
//float a_fRad = The rotation of the tank sprite
int PowerUps::SpawnPowerUps(PowerUps* a_pPowerUpArray,int a_iSpriteID, int a_iWidth, int a_iHeight, float a_fRad)
{
	int iCollidedSprite = DestroyPowerUps(a_pPowerUpArray, a_iSpriteID, a_iWidth, a_iHeight, a_fRad);//Detects collisions against powerups.
	if (iCollidedSprite >= 0)//If there was a collision
	{
		return iCollidedSprite;//Return the type of powerup
	}
	fTimer -= 0.1f;//Reduce the timer
	if (CheckChance())//Check random function
	{
		Vector2 vRandomCheck;//Stores random variables in
		vRandomCheck.SetdX(rand() % int(fTileWidth*fMapWidth));//Chooses a random X point on the map
		vRandomCheck.SetdY(rand() % int(fTileWidth*fMapHeight));//Chooses a random Y Point on the map

		if (GetTile(iCollisionMap, vRandomCheck) == 1)//If the randomly chosen point is colliding with a map tile
		{
			vRandomCheck.SetdX(rand() % int(fTileWidth*fMapWidth));//Gets a different Random point
			vRandomCheck.SetdY(rand() % int(fTileWidth*fMapHeight));//Gets a different Random point
		}
		else if(GetTile(iCollisionMap, vRandomCheck) == 0)//If the randomly chosen point is clear.
		{
			fTimer = 10.f;//Set the timer again
			CreatePowerup(vRandomCheck, a_pPowerUpArray);//Create a power up at that point.
		}
	}
	
	return -1;
}

//Function to check if a random number is between A and B
bool PowerUps::CheckChance()
{
	if (iCurrentActive < iMaxPowerUps)//If there is space.
	{
		
		fRandChance = rand() % 100;//Rand number between 0 - 100
		
		if (fRandChance <= 25 && fTimer <= 0)//If the number is between 0-25
		{
			
			return true;
		}
	}
	return false;
}

//Creates a powerup at a certain point.
void PowerUps::CreatePowerup(Vector2 a_vPos, PowerUps* a_pPowerUpArray)
{
	if (iCurrentActive < iMaxPowerUps)//Makes sure there is space for the powerup
	{
		for (int i = 0; i < iMaxPowerUps; i++)//Loops through the powerup array
		{
			if (a_pPowerUpArray[i].bActive == false)//Finds the first inactive one
			{
				int iRand = rand() % 2 + 1;//Chooses random number between 0 and 2

				if (iRand <= 1)
				{
					a_pPowerUpArray[i].iSpriteID = UG::CreateSprite("./images/Powerups/powerup_missile.png", 32, 32, true);//Create the sprite
					a_pPowerUpArray[i].iSpriteType = 0;
				}
				else
				{
					a_pPowerUpArray[i].iSpriteID = UG::CreateSprite("./images/Powerups/powerup_mine.png", 32, 32, true);//Create the sprite
					a_pPowerUpArray[i].iSpriteType = 1;
				}
				
				UG::DrawSprite(a_pPowerUpArray[i].iSpriteID);	//Draws it
				a_pPowerUpArray[i].vPos = a_vPos;//Sets its position
				UG::SetSpriteLayer(a_pPowerUpArray[i].iSpriteID, 9);//Sets the layer
				UG::MoveSprite(a_pPowerUpArray[i].iSpriteID, a_pPowerUpArray[i].vPos.GetdX(), a_pPowerUpArray[i].vPos.GetdY());//Moves it to its position
				a_pPowerUpArray[i].bActive = true;//Sets the powerup to active
				iCurrentActive++;
				break;
			}
		}
	}
	
}

//Checks if the powerup has collided with a sprites AABB box.
//Bullet* a_pBullet = The bullet array to check through.
//int a_iSpriteID = The spriteid of the sprite that you want to check collision against.
//int a_iWidth = The width of the un-rotated sprite.
//int a_iHeight = The height of the un-rotated sprite.
//float a_fRad = The rotation of the sprite to check.
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

//Function to get the current type of tile at a certain point.
//int a_iCollisionMap[] = The collision map to check against.
//Vector2 a_vPos = The position to check.
int PowerUps::GetTile(int a_iCollisionMap[], Vector2 a_vPos)
{
	int a_iX = (a_vPos.GetdX() / fTileWidth);
	int a_iY = (a_vPos.GetdY() / fTileWidth);

	return a_iCollisionMap[(a_iY * iMapWidth) + a_iX];
}

//Function to update the Collision map.
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

//Function to loop through and destroy any power ups which are colliding with a_iSpriteID
//PowerUps* a_pPowerUpArray = The Power up array to check
//int a_iSpriteID = The spriteid of the sprite that you want to check collision against.
//int a_iWidth = The width of the un-rotated sprite.
//int a_iHeight = The height of the un-rotated sprite.
//float a_fRad = The rotation of the sprite to check.
int PowerUps::DestroyPowerUps(PowerUps* a_pPowerUpArray, int a_iSpriteID, int a_iWidth, int a_iHeight, float a_fRad)
{
	for (int i = 0; i < iMaxPowerUps; i++)//Loops through power up array
	{
		if (a_pPowerUpArray[i].bActive == true)//If it is active
		{
			
			if (a_pPowerUpArray[i].CheckSpriteCollision(a_iSpriteID, a_iWidth, a_iHeight, DegreesToRadians( a_fRad)))//If it is colliding with the passed through sprite array
			{
				UG::StopDrawingSprite(a_pPowerUpArray[i].iSpriteID);//Stop drawing that
				UG::DestroySprite(a_pPowerUpArray[i].iSpriteID);//Destroy that
				--iCurrentActive;//Subtracts from the currently active count
				a_pPowerUpArray[i].bActive = false;//Sets it to false.
				return a_pPowerUpArray[i].iSpriteType;//Returns the sprite type

			}
		}

	}
	return -1;
}

//Function to reset the powerup array
//PowerUps* a_pPowerUpArray = The Array to reset
void PowerUps::Reset(PowerUps* a_pPowerUpArray)
{
	for (int i = 0; i < iMaxPowerUps; i++)
	{
		if (a_pPowerUpArray[i].bActive == true)
		{
			UG::StopDrawingSprite(a_pPowerUpArray[i].iSpriteID);//Stop drawing that
			UG::DestroySprite(a_pPowerUpArray[i].iSpriteID);//Destroy that
			--iCurrentActive;//Subtracts from the currently active count
			a_pPowerUpArray[i].bActive = false;//Sets it to false.

		}
	}
}