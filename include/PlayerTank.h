#ifndef _PLAYERTANK_H_
#define _PLAYERTANK_H_
#include "Vector2.h"
class PlayerTank
{
public:
	double dX;
	double dY;

	PlayerTank()
	{
		
	}

	void CreateTank(float a_fCenterX, float a_fCenterY);
	
	int iSpriteID;
	int iRotDeg = 0;
	Vector2 pos;


	void MoveTank();
	void GetSurroundingTiles();


	~PlayerTank()
	{

	}



	int iSpriteWidth = 32;
	int iSpriteHeight = 64;

private:
	

	int iTileRight;
};

#endif //_PLAYERTANK_H_