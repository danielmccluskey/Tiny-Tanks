#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Vector3.h"
#include "Vector2.h"
#include "CustomEnum.h"
#include "PathFinding.h"
#include "Turret.h"


class Enemy
{
public:
	Enemy() {}
	~Enemy();
	
	//Function to handle the movement of the tank.
	int GetTile(int a_iTileWidth, Vector2 a_vPos);
	//Function to create the tank sprite for the player.
	//a_fX = xPos of tank spawn location.
	//a_fY = yPos of tank spawn location.
	void CreateTank(float a_fX, float a_fY);

	//Function that moves the tank
	void UpdateCollisionMap();
	int PathFindHCalc(Vector2 a_vStart, Vector2 a_vGoal);
	int PathFindFCalc(Vector2 a_vStart, Vector2 a_vGoal);
	int PathFindTileCheck(Vector2 a_vStart, Vector2 a_vGoal);
	int GetNextGoal(Vector2 a_vStart, Vector2 a_vGoal);
	void MoveTank(Vector2 a_vStart, Vector2 a_vGoal);
	int iSpriteID;
	void RotateSprite(int a_iSpriteID, float a_fRad);
	float GetBearing(Vector2 &a_V1, Vector2 &a_V2);
	float GetBearing(Vector3 &a_V1, Vector3 &a_V2);
	void LookToPlayer(Vector2 a_vPlayerPos);

	int iEnemyCollisionMap[(iMapHeight*iMapWidth)];
	Vector2 vPos;
	bool bStart;
private:

	Turret sSpriteTurret;
	PathFinding oPathFinder;
	Vector3 vDistanceTarget;

	Vector3 vNextSpot;
	int iStartAngle, iEndAngle;
	float fUGFrameSpriteMatrix[16];
	float fLerpPosition = 0;
	bool bIsTravelling;
	bool bIsRotating;
	float fBearing;
	float fOldBearing = 0;
	int iSpriteWidth = 32;
	int iSpriteHeight = 32;
};



#endif //_ENEMY_H_