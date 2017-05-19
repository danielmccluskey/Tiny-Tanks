#ifndef _PLAYERTANK_H_
#define _PLAYERTANK_H_
#include "Vector2.h"
#include "Turret.h"
#include "Vector3.h"
#include "CustomEnum.h"


class PlayerTank
{
public:
	PlayerTank() {}
	~PlayerTank();
	friend class Vector2;
	friend class Turret;

	//Function to handle the movement of the tank.
	int GetTile(int a_iTileWidth, Vector2 a_vPos);
	int GetTile(int a_iTileWidth, Vector3 a_vPos);
	//Function to create the tank sprite for the player.
	//a_fX = xPos of tank spawn location.
	//a_fY = yPos of tank spawn location.
	void CreateTank(float a_fX, float a_fY);

	//Function that moves the tank
	void MoveTank();
	void GetSurroundingTiles(int a_iTileWidth);
	void UpdateCollisionMap();
	void RotateSprite(int a_iSpriteID, float a_fRad);
	float GetBearing(Vector2 &a_V1, Vector2 &a_V2);
	void CalculateBoundaries();
	bool CollisionDetection(Vector3 a_vPos);

	int iCollisionMap[(iMapHeight*iMapWidth)];
	int iSpriteID;
	int iRotDeg = 0;
	int iSpriteWidth = 32;
	int iSpriteHeight = 32;
	float fSpeed = 1000.f;
	
	Turret sSpriteTurret;

	Vector2 vPos;
	Vector2 vVelocity;
	Vector2 vMousePos;

	float fUGFrameSpriteMatrix[16];

	

private:
	//Vector3's to hold positional and collision values for each corner of the sprite
	// Vector (XPos, YPos, CurrentTile)
	Vector3 pTopLeft;
	Vector3 pTopRight;
	Vector3 pBotLeft;
	Vector3 pBotRight;
	Vector3 pFront;
	Vector3 pBack;
	

};



#endif //_PLAYERTANK_H_