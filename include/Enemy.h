//==============================================================================================================================
// Project: WiiTanks
// File: Enemy.h
// Author: Daniel McCluskey
// Date Created: 07/01/17
// Brief: This is the header file that contains the function declarations and variables required to make the Enemies functional.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Vector3.h"
#include "Vector2.h"
#include "CustomEnum.h"
#include "PathFinding.h"
#include "Bullet.h"
#include "Turret.h"


class Enemy
{
public:
	Enemy()
		: oSpriteTurret("./images/Tanks/enemy_tank_turret.png")//Constructor for the Turret class member
	{
		
	}
	~Enemy();
	//==============================================================================================================================
	//Voids
	//==============================================================================================================================

	//Function to create the tank sprite for the player.
	//a_fX = xPos of tank spawn location.
	//a_fY = yPos of tank spawn location.
	void CreateTank(float a_fX, float a_fY);

	//Function to Update the Enemy tanks Collision map array and the Pathfinding collision map array.
	//Needs to be called for each individual enemy.
	void UpdateCollisionMap(); 

	//Function to rotate a sprite using a combination of the UGSpriteMatrix and a 4x4Matrix.
	//Rotates the sprite to a set angle instead of incrementing the angle.
	//int a_iSpriteID = The SpriteID of the sprite you want to rotate.
	//float a_fRad = The angle in radians that you want to rotate the sprite to.
	void RotateSprite(int a_iSpriteID, float a_fRad);

	//Function to make the Turret sprite rotate to look at the player.
	//Vector2 a_vPlayerPos = The position of the player.
	void LookToPlayer(Vector2 a_vPlayerPos);

	//Function to reset all variables of the class members, kill its bullets, stops pathfinding and then moves back to the starting position.
	//Vector2 a_fStartPos = The position to return to.
	void Reset(Vector2 a_fStartPos);
	//==============================================================================================================================
	//Ints
	//==============================================================================================================================
	
	//Function that just returns the sprite ID of the class member.
	int GetSpriteID();

	//Function to get the current type of tile at a certain point.
	//int a_iCollisionMap[] = The collision map to check against.
	//Vector2 a_vPos = The position to check.
	int GetTile(int a_iCollisionMap[], Vector2 a_vPos);

	//==============================================================================================================================
	//Floats
	//==============================================================================================================================
	
	//Gets the Angle between two Vector2 co-ordinates. Mainly Used for rotating tank turret.
	//Equation used - http://wikicode.wikidot.com/get-angle-of-line-between-two-points
	//Vector2 &a_V1 = Starting Position.
	//Vector2 &a_V2 = End position.
	float GetBearing(Vector2 &a_V1, Vector2 &a_V2);

	//Gets the Angle between two Vector3 co-ordinates. Mainly Used for rotating tank turret.
	//Equation used - http://wikicode.wikidot.com/get-angle-of-line-between-two-points
	//Vector3 &a_V1 = Starting Position.
	//Vector3 &a_V2 = End position.
	float GetBearing(Vector3 &a_V1, Vector3 &a_V2);

	//==============================================================================================================================
	//Bools
	//==============================================================================================================================
	
	//Function to determine a Path to a_vGoal using the A* pathfinding method, then moves the tank along the path.
	//Returns true if the enemies bullet has hit the given sprite ID.
	//Vector2 a_vStart = The start position of the tank.
	//Vector2 a_vGoal = The end of the path (Currently the Players position.)
	bool MoveTank(Vector2 a_vStart, Vector2 a_vGoal, int a_iEnemySpriteID);

	//Function to get line of sight between Enemy and player.
	//int a_iSpriteIDEnemy = The starting sprite ID
	//int a_iSpriteIDPlayer = The Player Sprite ID
	//int a_iCollisionMap[] = The collision map
	bool RayCast(int a_iSpriteIDEnemy, int a_iSpriteIDPlayer, int a_iCollisionMap[]);

	//==============================================================================================================================
	//Vector2
	//==============================================================================================================================

	//Function to return the position of the class member as a vector2.
	Vector2 GetPos();

private:
	//==============================================================================================================================
	//Ints
	//==============================================================================================================================
	
	int iEnemyCollisionMap[(iMapHeight*iMapWidth)];//The collision map to check collisions against.
	int iStartAngle, iEndAngle;	//Start angle and end angle used for lerps.
	int iSpriteWidth = 32;//Width of sprite
	int iSpriteHeight = 32;//Height of sprite.
	int iSpriteID;//Sprite iD
	int iBearing;//Stores angle of sprite.

	//==============================================================================================================================
	//Floats
	//==============================================================================================================================
	
	float fUGFrameSpriteMatrix[16];//Stores the UGFramework sprite matrix.
	float fLerpPosition = 0;//Declares lerp variable.
	float fOldBearing = 0;//Stores last angle.

	//==============================================================================================================================
	//Bools
	//==============================================================================================================================
	
	bool bIsTravelling;//Function to control state of pathfinding.
	bool bIsRotating;//Function to control state of pathfinding.
	bool bStart;//Function to control the state of pathfinding.

	//==============================================================================================================================
	//Class Members
	//==============================================================================================================================
	
	Turret oSpriteTurret;//The turret on top of the tank.
	PathFinding oPathFinder;//The pathfinding class.
	Bullet *oBulletArray = new Bullet[20];//BulletArray

	//==============================================================================================================================
	//Vector2 + Vector3
	//==============================================================================================================================
	
	Vector2 vPos;//Stores the Position of the Player.
	
	Vector3 vDistanceTarget;//Stores the starting position of the pathfinding.
	Vector3 vNextSpot;	//Stores the next spot on the pathfinding path.
};



#endif //_ENEMY_H_