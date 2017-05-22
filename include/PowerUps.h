//==============================================================================================================================
// Project: WiiTanks
// File: MapCreation.h
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the header file that contains the code that draws the maps from files and generates the collision map.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#ifndef _POWERUPS_H_
#define _POWERUPS_H_
#include "Vector2.h"
class PowerUps
{
public:
	//Constructor
	PowerUps();
	~PowerUps()
	{
	}
	//==============================================================================================================================
	//Ints
	//==============================================================================================================================

	//Function to randomly spawn powerups
	//PowerUps* a_pPowerUpArray = The Powerup array to loop through
	//int a_iSpriteID = The sprite id of the tank to check collisions against.
	//int a_iWidth = The width of the sprite
	//int a_iHeight = The height of the tank sprite
	//float a_fRad = The rotation of the tank sprite
	int SpawnPowerUps(PowerUps* a_pPowerUpArray, int a_iSpriteID, int a_iWidth, int a_iHeight, float a_fRad);

	//Function to get the current type of tile at a certain point.
	//int a_iCollisionMap[] = The collision map to check against.
	//Vector2 a_vPos = The position to check.
	int GetTile(int a_iCollisionMap[], Vector2 a_vPos);

	//Function to loop through and destroy any power ups which are colliding with a_iSpriteID
	//PowerUps* a_pPowerUpArray = The Power up array to check
	//int a_iSpriteID = The spriteid of the sprite that you want to check collision against.
	//int a_iWidth = The width of the un-rotated sprite.
	//int a_iHeight = The height of the un-rotated sprite.
	//float a_fRad = The rotation of the sprite to check.
	int DestroyPowerUps(PowerUps* a_pPowerUpArray, int a_iSpriteID, int a_iWidth, int a_iHeight, float a_fRad);
	
	//==============================================================================================================================
	//Bools
	//==============================================================================================================================
	
	//Function to check if a random number is between A and B
	bool CheckChance();
	
	//Checks if the powerup has collided with a sprites AABB box.
	//Bullet* a_pBullet = The bullet array to check through.
	//int a_iSpriteID = The spriteid of the sprite that you want to check collision against.
	//int a_iWidth = The width of the un-rotated sprite.
	//int a_iHeight = The height of the un-rotated sprite.
	//float a_fRad = The rotation of the sprite to check.
	bool CheckSpriteCollision(int a_iSpriteID, int a_iWidth, int a_iHeight, float a_fRad);
	
	
	//==============================================================================================================================
	//Voids
	//==============================================================================================================================

	//Function to update the Collision map.
	void UpdateCollisionMap();

	//Creates a powerup at a certain point.
	void CreatePowerup(Vector2 a_vPos, PowerUps* a_pPowerUpArray);

	//Sets the collision id to the given parameter
	//int a_iSpriteID = The sprite to collide with.
	void SetTankID(int a_iSpriteID);	

	//Function to reset the powerup array
	//PowerUps* a_pPowerUpArray = The Array to reset
	void Reset(PowerUps* a_pPowerUpArray);


private:
	//==============================================================================================================================
	//Ints
	//==============================================================================================================================

	int iCollisionMap[384];//Contains the collision map
	int iSpriteID;//Sprite ID
	int iSpriteType;//Power up type
	int iCurrentActive;//Amount of powerups currently active
	int iMaxPowerUps;//Max amount of powerups allowed.
	int iTankSpriteID;//The Target sprite id

	//==============================================================================================================================
	//Bools
	//==============================================================================================================================

	bool bActive;//Is the power up active

	//==============================================================================================================================
	//Vectors
	//==============================================================================================================================

	Vector2 vPos;//Position of the powerup

	//==============================================================================================================================
	//Floats
	//==============================================================================================================================

	float fRandChance;//The chance of a powerup spawning
	float fTimer;//The time it will take for a powerup to spawn.
	
};

#endif //_POWERUPS_H_