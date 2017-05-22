//==============================================================================================================================
// Project: WiiTanks
// File: MapCreation.h
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the header file that contains the code that draws the maps from files and generates the collision map.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#ifndef _POWERUPS_H_
#define _POWERUPS_H_
#include "Vector2.h"
class PowerUps
{
public:

	PowerUps();
	~PowerUps()
	{
	}

	int SpawnPowerUps(PowerUps* a_pPowerUpArray, int a_iSpriteID, int a_iWidth, int a_iHeight, float a_fRad);
	bool CheckChance();
	bool CheckSpriteCollision(int a_iSpriteID, int a_iWidth, int a_iHeight, float a_fRad);
	int GetTile(int a_iCollisionMap[], Vector2 a_vPos);
	void UpdateCollisionMap();
	void CreatePowerup(Vector2 a_vPos, PowerUps* a_pPowerUpArray);
	void SetTankID(int a_iSpriteID);
	int DestroyPowerUps(PowerUps* a_pPowerUpArray, int a_iSpriteID, int a_iWidth, int a_iHeight, float a_fRad);
	void Reset(PowerUps* a_pPowerUpArray);


private:
	int iCollisionMap[384];
	int iSpriteID;
	int iSpriteType;
	int iCurrentActive;
	int iMaxPowerUps;
	bool bActive;
	Vector2 vPos;
	float fRandChance;
	float fTimer;
	int iTankSpriteID;
};

#endif //_POWERUPS_H_