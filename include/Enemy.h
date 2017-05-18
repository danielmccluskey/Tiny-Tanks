#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Vector3.h"
#include "Vector2.h"
#include "CustomEnum.h"


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
	int PathFindHCalc(Vector2 a_vStart, Vector2 a_vGoal);
	int PathFindFCalc(Vector2 a_vStart, Vector2 a_vGoal);
	int PathFindTileCheck(Vector2 a_vStart, Vector2 a_vGoal);
	int GetNextGoal(Vector2 a_vStart, Vector2 a_vGoal);
	void MoveTank(Vector2 a_vStart, Vector2 a_vGoal);
	int iSpriteID;
	void RotateSprite(int a_iSpriteID, float a_fRad);

	int iEnemyCollisionMap[(iMapHeight*iMapWidth)];
	Vector2 vPos;

private:

	Vector2 vStartPos;
	Vector2 vEndPos;
	int iStartAngle, iEndAngle;
	float fUGFrameSpriteMatrix[16];
	float fLerpPosition = 0;
	bool bIsTravelling;
	bool bIsRotating;
	int iLastDirection;
	int iSpriteWidth = 32;
	int iSpriteHeight = 32;
	int iLeftCost = 0;
	int iTopCost = 0;
	int iRightCost = 0;
	int iBottomCost = 0;
};



#endif //_ENEMY_H_