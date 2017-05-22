//==============================================================================================================================
// Project: WiiTanks
// File: Bullet.h
// Author: Daniel McCluskey
// Date Created: 07/01/17
// Brief: This is the header file that contains the function declarations and variables required to make the bullets functional.
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
	//==============================================================================================================================
	//Voids
	//==============================================================================================================================

	//Function that simply draws the counts of the bullets at the top of the screen using UG::DrawString
	//Function takes no Arguments
	void DrawBulletCount();
	//Function that creates a new bullet when called.
	//Bullet *a_pBullet = The Bullet array pased through so it can be looped through.
	//Vector2 a_fStart = The start position of the bullet.
	//Vector2 a_fTarget = Where you want the bullet to head toward.
	//int a_iBulletType = The type of bullet you want to fire. 0 = Normal, 1 = Missile, 2 = Mine
	void CreateBullet(Bullet *a_pBullet, Vector2 a_fStart, Vector2 a_fTarget, int a_iBulletType);

	//Function that checks collision of the bullet against the map tiles and then moves it depending on its bullet type.
	//Bullet& a_pBullet = The Bullet being checked/Moved.
	//int a_iCollisionMap[] = The collision map that the bullet should check against.
	void MoveBullet(Bullet& a_pBullet, int a_iCollisionMap[]);

	//Function to destroy a bullet or subtract from its lifetime.
	//Bullet& a_pBullet = The bullet that contains the variables for the array, usually Bullet[0].
	void DestroyBullets(Bullet& a_pBullet);

	//Function to run through each active bullet, move it and then check if it needs to be destroyed.
	//Bullet *a_pBullet = The Bullet array that needs to be checked through.
	//int a_iCollisionMap[] == The collision map to check against.
	void UpdateBullets(Bullet *a_pBullet, int a_iCollisionMap[]);

	//Function that increments the bullet counts, usually used when the player picks up a powerup.
	//int a_iBulletType = The type of bullet you want to give the player. 1 = Missile, 2 = Mine.
	void AddBullet(int a_iBulletType);

	//Function to reset all bullets.
	//Bullet* a_pBulletArray = The Bullet array to reset.
	void Reset(Bullet* a_pBulletArray);

	//==============================================================================================================================
	//Ints
	//==============================================================================================================================

	//Function to get the current type of tile at a certain point.
	//int a_iCollisionMap[] = The collision map to check against.
	//Vector2 a_vPos = The position to check.
	int GetTile(int a_iCollisionMap[], Vector2 a_vPos);

	//==============================================================================================================================
	//Floats
	//==============================================================================================================================

	//Gets the Angle between two Vector2 co-ordinates from the starting point.
	//Equation used - http://wikicode.wikidot.com/get-angle-of-line-between-two-points
	//Vector2 &a_V1 = The Starting point
	//Vector2 &a_V2 = The End point
	float GetBearing(Vector2 &a_V1, Vector2 &a_V2);

	//==============================================================================================================================
	//Bools
	//==============================================================================================================================
	
	//Checks if the bullet has collided with a sprites AABB box.
	//Bullet* a_pBullet = The bullet array to check through.
	//int a_iSpriteID = The spriteid of the sprite that you want to check collision against.
	//int a_iWidth = The width of the un-rotated sprite.
	//int a_iHeight = The height of the un-rotated sprite.
	//Vector2 a_vPos = The Position of the sprite to check. (Unused currently)
	//float a_fRad = The rotation of the sprite to check.
	bool SpriteCollide(Bullet* a_pBullet, int a_iSpriteID, int a_iWidth, int a_iHeight, Vector2 a_vPos, float a_fRad);


private:
	//==============================================================================================================================
	//Floats
	//==============================================================================================================================

	float iLifeTime;//Controls the lifetime left on each bullet, mine or missile.
	float fAngle;//The Angle in which the bullet will be fired.

	//==============================================================================================================================
	//Bools
	//==============================================================================================================================

	bool bIsActive = false;//If the bullet is active.
	
	//==============================================================================================================================
	//Ints
	//==============================================================================================================================

	int iCollisionMap[384];//The collision map for the bullets to bounce off.
	int iSpeed;//The Speed of the bullets.
	int iSpriteID = 0;//Sprite ID
	int iMineCount = 0;//Count of the mines the player has picked up.
	int iActiveMines = 0;//Count of the currently placed mines on the map.
	int iMaxNormalBullets = 3;//Max amount of normal bullets has.
	int iMissileCount = 0;//Count of the missiles the player has picked up.
	int iBulletCount = 0;//Count of the amount of bullets the player has.
	int iActiveNormalBullets = 0;//Count of the amount of normal bullets currently being fired.
	int iActiveMissiles = 0;//Count of the amount of missiles currently being fired.
	int iBulletBounce = 0;//Count of how many times the bullet has bounced against a wall.
	int iBulletType;//Type of bullet being fired.
	int iBulletSpeed;//Speed of the bullet being fired.

	//"Holy Mother of Ints" - Everyone who saw me make this.

	//=============================================================================================================================
	//Vector2
	//==============================================================================================================================

	Vector2 vMousePos;//Stores the mousepos so a bearing can be created between the mouse and the tank.
	Vector2 vLastPos;//Stores the last position of the bullet for collision purposes.
	Vector2 vVelocity;//Stores the velocity of the bullet.
	Vector2 vPos;//Stores the position of the bullet.
};

#endif //_BULLET_H_