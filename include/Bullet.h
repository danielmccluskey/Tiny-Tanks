//==============================================================================================================================
// Project: WiiTanks
// File: MapCreation.h
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the header file that contains the code that draws the maps from files and generates the collision map.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#ifndef _BULLET_H_
#define _BULLET_H_


class Bullet
{
public:

	~Bullet()
	{
	}

	int iSpriteID = 0;//Sprite ID


	int iCollisionMap[384];

	int iSpeed;
	float iLifeTime;

	

private:
	

};

#endif //_BULLET_H_