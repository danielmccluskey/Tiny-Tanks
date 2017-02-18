#ifndef _PLAYERTANK_H_
#define _PLAYERTANK_H_
#include "MathUtil.h"
class PlayerTank
{
public:
	double dX;
	double dY;

	PlayerTank() {}
	~PlayerTank() {}

	void CreateTank(float a_fCenterX, float a_fCenterY);
	void MoveTank();
	void GetSurroundingTiles(int a_iTileWidth);
	int GetTile(int a_iTileWidth, Vector2 a_vPos);
	void UpdateCollisionMap();
	
	
	


	


	


	int iSpriteID;
	int iRotDeg = 0;
	int iSpriteWidth = 32;
	int iSpriteHeight = 32;
	int iCollisionMap[iMapHeight*iMapWidth];

	Vector2 pos;

private:
	
	//Vector3's to hold positional and collision values for each corner of the sprite
	// Vector (XPos, YPos, CurrentTile)
	Vector3 pTopLeft;
	Vector3 pTopRight;
	Vector3 pBotLeft;
	Vector3 pBotRight;
};

#endif //_PLAYERTANK_H_