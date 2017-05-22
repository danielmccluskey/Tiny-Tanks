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
#include "Vector2.h"
class Bullet
{
public:

	Bullet() {}
	~Bullet() {}
	int iSpriteID = 0;//Sprite ID


	void DrawBulletCount();
	void CreateBullet(Bullet *a_pBullet, Vector2 a_fStart, Vector2 a_fTarget, int a_iBulletType);
	void MoveBullet(Bullet& a_pBullet, int a_iCollisionMap[]);
	void DestroyBullets(Bullet& a_pBullet);
	int GetTile(int a_iCollisionMap[], Vector2 a_vPos);
	void UpdateBullets(Bullet *a_pBullet, int a_iCollisionMap[]);
	float GetBearing(Vector2 &a_V1, Vector2 &a_V2);
	bool SpriteCollide(Bullet* a_pBullet, int a_iSpriteID, int a_iWidth, int a_iHeight, Vector2 a_vPos, float a_fRad);
	void AddBullet(int a_iBulletType);
	void Reset(Bullet* a_pBulletArray);

private:

	int iCollisionMap[384];
	int iSpeed;
	float iLifeTime;
	bool bIsActive = false;
	float fAngle;

	int iMineCount = 0;
	int iActiveMines = 0;
	int iMaxNormalBullets = 3;
	int iMissileCount = 0;
	int iBulletCount = 0;
	int iActiveNormalBullets = 0;
	int iActiveMissiles = 0;
	int iBulletBounce = 0;
	int iBulletType;
	int iBulletSpeed;
	Vector2 vMousePos;
	Vector2 vLastPos;
	Vector2 vVelocity;
	Vector2 vPos;
};

#endif //_BULLET_H_