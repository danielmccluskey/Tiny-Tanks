#ifndef _PLAYERTANK_H_
#define _PLAYERTANK_H_
#include "MathUtil.h"
struct Turret
{
	Turret()
	{
		iSpriteID = UG::CreateSprite("./images/Tanks/tank_turret.png", 30, 80, true);//Create the sprite
		UG::DrawSprite(iSpriteID);	//Draws it
		UG::SetSpriteLayer(iSpriteID, 10);
	};
	int iSpriteID = 0;
	int iRotDeg = 0;
};

class PlayerTank
{
public:
	PlayerTank() {}
	~PlayerTank() {}
	

	//Function to handle the movement of the tank.
	int GetTile(int a_iTileWidth, Vector2 a_vPos);
	//Function to create the tank sprite for the player.
	//a_fX = xPos of tank spawn location.
	//a_fY = yPos of tank spawn location.
	void CreateTank(float a_fX, float a_fY);

	//Function that moves the tank
	void MoveTank();
	void GetSurroundingTiles(int a_iTileWidth);	
	void UpdateCollisionMap();
	void CollisionDetection(int a_iLowerBound, int a_iUpperBound, Vector3& a_vForwards, Vector3& a_vBackwards);

	int iSpriteID;
	int iRotDeg = 0;
	int iSpriteWidth = 32;
	int iSpriteHeight = 32;
	int iCollisionMap[(iMapHeight*iMapWidth)];

	Turret sTurret;
	Vector2 pos;	

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