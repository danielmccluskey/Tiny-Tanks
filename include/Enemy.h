#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "OtherFunctions.h"
#include "Vector3.h"
#include "Vector2.h"
struct EnemyTurret;

class Enemy
{
public:
	Enemy() {}
	~Enemy() {}
	
	//Function to handle the movement of the tank.
	int GetTile(int a_iTileWidth, Vector2 a_vPos);
	//Function to create the tank sprite for the player.
	//a_fX = xPos of tank spawn location.
	//a_fY = yPos of tank spawn location.
	void CreateTank(float a_fX, float a_fY);

	//Function that moves the tank
	void MoveTank(float a_fDeg);
	void GetSurroundingTiles(int a_iTileWidth);
	void UpdateCollisionMap();
	void CollisionDetection(int a_iLowerBound, int a_iUpperBound, Vector3& a_vForwards, Vector3& a_vBackwards);
	int iSpriteID;
};



#endif //_ENEMY_H_