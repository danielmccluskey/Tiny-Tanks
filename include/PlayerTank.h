//==============================================================================================================================
// Project: WiiTanks
// File: Bullet.h
// Author: Daniel McCluskey
// Date Created: 07/01/17
// Brief: This is the file that controls player movement and collision. Bullets and powerups too.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#ifndef _PLAYERTANK_H_
#define _PLAYERTANK_H_
#include "Vector2.h"
#include "Turret.h"
#include "Vector3.h"
#include "Bullet.h"
#include "CustomEnum.h"
#include "PowerUps.h"

class PlayerTank
{
public:

	//Constructor
	//float a_fCenterX = Spawn Position X
	//float a_fCenterY = Spawn Position Y
	//float A_fGlobalSpeed = Speed of the tank
	PlayerTank(float a_fCenterX, float a_fCenterY, float a_fGlobalSpeed);
	
	//Desconstructor
	~PlayerTank();
	friend class Vector2;
	friend class Turret;

	//==============================================================================================================================
	//Ints
	//==============================================================================================================================
	
	//Gets the tile from the collision map array with the given co-ordinates.
	//int a_iTileWidth = Width of a map tile
	//Vector2 a_vPos = The Position to check.
	int GetTile(int a_iTileWidth, Vector2 a_vPos);

	//Gets the tile from the collision map array with the given co-ordinates.
	//int a_iTileWidth = Width of a map tile
	//Vector3 a_vPos = The Position to check.
	int GetTile(int a_iTileWidth, Vector3 a_vPos);

	//Simple function to return the sprite id of the tank
	int GetSpriteID();


	//==============================================================================================================================
	//Voids
	//==============================================================================================================================

	//Function to create the tank sprite for the player.
	//a_fX = xPos of tank spawn location.
	//a_fY = yPos of tank spawn location.
	void CreateTank(float a_fX, float a_fY);
	
	//Updates the Collision map for the powerups and the player.
	void UpdateCollisionMap();
	
	//Sets the sprite rotation to an exact value, used over UG::SetSpriteRotation since that increments the rotation instead of setting it.
	//int a_iSpriteID = SpriteID of the sprite you want to rotate.
	//float a_fRad = The amount to rotate it in radians.
	void RotateSprite(int a_iSpriteID, float a_fRad);
	
	//Function to get the position of each corner of the sprite depending on its rotation, then does a collision check on each point.
	void CalculateBoundaries();

	//Resets the players tank and bullets for next level use.
	//Vector2 a_vStartPos = The position to move the tank to.
	void Reset(Vector2 a_vStartPos);

	//==============================================================================================================================
	//Bools
	//==============================================================================================================================
	
	//Function to handle the movement of the tank.
	//int a_iEnemySpriteID = The SpriteID of the enemy tank, will be changed to array in future to allow for multiple enemies
	bool MoveTank(int a_iEnemySpriteID);
	
	//Function to detect if a point is colliding with a tile and if so, what side of the tile.
	//Also handles cross product sliding on collision
	//Vector3 a_vPos = The point being checked.
	bool CollisionDetection(Vector3 a_vPos);

	//Gets the Angle between two Vector2 co - ordinates.Mainly Used for rotating tank turret.
	//Equation used - http://wikicode.wikidot.com/get-angle-of-line-between-two-points
	float GetBearing(Vector2 &a_V1, Vector2 &a_V2);
	
	//==============================================================================================================================
	//Vector2
	//==============================================================================================================================

	//Simple function to return the position of the tank.
	Vector2 GetPos();
	

private:
	//==============================================================================================================================
	//Vectors
	//==============================================================================================================================


	Vector2 vNormalPlane;//Holds the normal plane for cross product.
	Vector2 vPos;//Holds the players position
	Vector2 vMousePos;//Holds the mouse position
	Vector2 vLastPos;//Holds the last positon
	Vector2 vVelocity;//Holds the velocity.

	//==============================================================================================================================
	//Class members
	//==============================================================================================================================

	Bullet *BulletArray = new Bullet[20];//Bullet array
	PowerUps *pPowerUpArray = new PowerUps[20];//Powerup array
	Turret sSpriteTurret;//Turret class

	//==============================================================================================================================
	//Floats
	//==============================================================================================================================
	
	float fWallSlideSlow;//How slow the player slides along walls.
	float fSpeed = 1000.f;//Player speed
	float fUGFrameSpriteMatrix[16];//Holds the UGFramework matrix from UG::GetSpriteMatrix

	//==============================================================================================================================
	//Ints
	//==============================================================================================================================

	int iCollisionMap[(iMapHeight*iMapWidth)];//Collision map
	int iSpriteID;//SpriteID
	int iRotDeg = 0;//Rotation of the player
	int iSpriteWidth = 32;//Width
	int iSpriteHeight = 32;//Height


	//==============================================================================================================================
	//Bools
	//==============================================================================================================================

	bool iTankMouseState;//Current Mouse state
	bool iTankLastMouseState;//Last mouse state
	bool bHitPowerUp;//Has hit powerup.
};



#endif //_PLAYERTANK_H_