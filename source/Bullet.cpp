//==============================================================================================================================
// Project: WiiTanks
// File: Bullet.cpp
// Author: Daniel McCluskey
// Date Created: 07/01/17
// Brief: This file contains the functions that make the bullets functional.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#include "Bullet.h"
#include "UGFW.h"
#include "CustomEnum.h"
#include "Boundaries.h"
#include <string>
#include "MathUtil.h"
#include <cmath>
#include "windows.h"

#pragma comment(lib, "winmm.lib")

//Function that creates a new bullet when called.
//Bullet *a_pBullet = The Bullet array pased through so it can be looped through.
//Vector2 a_fStart = The start position of the bullet.
//Vector2 a_fTarget = Where you want the bullet to head toward.
//int a_iBulletType = The type of bullet you want to fire. 0 = Normal, 1 = Missile, 2 = Mine
void Bullet::CreateBullet(Bullet *a_pBullet, Vector2 a_fStart, Vector2 a_fTarget, int a_iBulletType)
{

	for (int i = 0; i < iMaxNormalBullets; i++)//Loops through the max amount of bullets the player can fire.
	{
		if (a_pBullet[i].bIsActive == false)//Checks for the first inactive bullet.
		{

			a_pBullet[i].iBulletType = a_iBulletType;//Stores its bullet type.

			if (a_pBullet[i].iBulletType == 0 && iMaxNormalBullets - iActiveNormalBullets > 0)//If the bullet type is normal and the player has bullets left.
			{
				a_pBullet[i].iSpriteID = UG::CreateSprite("./images/Powerups/powerup_missile.png", 10, 10, true);//Create the sprite with the bullet texture.
				iBulletCount--;//Takes away from the bullet count.
				iActiveNormalBullets++;//Adds 1 to the active bullet count.

			}
			else if (a_pBullet[i].iBulletType == 1 && iMissileCount > 0)//If the bulelt type is a missile and the player has missiles left.
			{
				a_pBullet[i].iSpriteID = UG::CreateSprite("./images/Powerups/powerup_missile.png", 20, 20, true);//Create the sprite
				iMissileCount--;//Takes from the missile count.
				iActiveMissiles++;//Adds 1 to the active missile count
			}
			else if (a_pBullet[i].iBulletType == 2 && iMineCount > 0)//If the bullet type is a mine and the player has mines left
			{
				a_pBullet[i].iSpriteID = UG::CreateSprite("./images/Powerups/powerup_mine.png", 20, 20, true);//Create the sprite
				iMineCount--;//Takes from mine count
				iActiveMines++;//Adds to active mine count.
			}
			else//If the bullet type is not correct for whatever reason.
			{
				return;//Ends function.
			}
			
			UG::DrawSprite(a_pBullet[i].iSpriteID);	//Draws the bullet
			UG::SetSpriteLayer(a_pBullet[i].iSpriteID, 9);//Sets the layer above the Map tile sprites.
			a_pBullet[i].fAngle = (GetBearing(a_fStart, a_fTarget) + 180);//Gets the Angle using the Get Bearing function.
			a_pBullet[i].vVelocity = a_pBullet[i].vVelocity.RotateX(a_pBullet[i].fAngle);//Sets the velocity vector using the bearing.
			a_pBullet[i].vPos = a_fStart;//Sets the position to the starting position.
			a_pBullet[i].vLastPos = a_fStart;//Sets the last position to the starting position.
			a_pBullet[i].vPos += Vector2(a_pBullet[i].vVelocity.GetdX() * 40, a_pBullet[i].vVelocity.GetdY() * 40);//40 is a magic number I know, its the value I use to make the bullet spawn at the end of the turret.
			UG::MoveSprite(a_pBullet[i].iSpriteID, a_pBullet[i].vPos.GetdX(), a_pBullet[i].vPos.GetdY());//Moves the sprite to the starting position.
			a_pBullet[i].iLifeTime = 500;//Sets its lifetime to 500.
			a_pBullet[i].iBulletSpeed = 80;//Sets the speed.
			a_pBullet[i].bIsActive = true;//Sets the bullet to active so it an be operated on.
			PlaySound(TEXT("./sounds/tank_fire.wav"), NULL, SND_FILENAME | SND_ASYNC);//Plays the sound chosen at the start of the function
			
			break;
		}
	}
}

//Function that increments the bullet counts, usually used when the player picks up a powerup.
//int a_iBulletType = The type of bullet you want to give the player. 1 = Missile, 2 = Mine.
void Bullet::AddBullet(int a_iBulletType)
{
	switch (a_iBulletType)
	{
	case 0:
		break;
	case 1:
		iMissileCount += 1;
		break;
	case 2:
		iMineCount += 1;
		break;
	}
}
//Function that simply draws the counts of the bullets at the top of the screen using UG::DrawString
//Function takes no Arguments
void Bullet::DrawBulletCount()
{
	UG::ClearScreen();//Clears the screen.
	std::string ssNormalBullets;//Declares a string to store the bullet count in.
	ssNormalBullets += std::to_string(iMaxNormalBullets - iActiveNormalBullets);//Adds the bullet count to the string as a string.
	UG::DrawString(ssNormalBullets.c_str(), (int)(fMapWidth * fTileWidth * 0.2f), (int)(fMapHeight * fTileWidth), 0.8f);//Draws it.

	//Stringstream to draw the current highscore below HIGHSCORES during GAMEPLAY
	std::string ssMissiles;//Declares a string to store the bullet count in.
	ssMissiles += std::to_string(iMissileCount);//Adds the bullet count to the string as a string.
	UG::DrawString(ssMissiles.c_str(), (int)(fMapWidth * fTileWidth * 0.5f), (int)(fMapHeight * fTileWidth), 0.8f);//Draws it.

	//Stringstream to draw the current highscore below HIGHSCORES during GAMEPLAY
	std::string ssMines;//Declares a string to store the bullet count in.
	ssMines += std::to_string(iMineCount);//Adds the bullet count to the string as a string.
	UG::DrawString(ssMines.c_str(), (int)(fMapWidth * fTileWidth * 0.8f), (int)(fMapHeight * fTileWidth), 0.8f);//Draws it.
}

//Function that checks collision of the bullet against the map tiles and then moves it depending on its bullet type.
//Bullet& a_pBullet = The Bullet being checked/Moved.
//int a_iCollisionMap[] = The collision map that the bullet should check against.
void Bullet::MoveBullet(Bullet& a_pBullet, int a_iCollisionMap[])
{
	int iTileX = (vPos.GetdX() / fTileWidth);//Converts the X position into Tile co-ordinates for the array.
	int iTileY = (vPos.GetdY() / fTileWidth);//Converts the Y position into Tile co-ordinates for the array.
	iTileX *= fTileWidth;//Multiplies it by tilewidth again to make it get the exact co-ordinate of the tile.
	iTileY *= fTileWidth;//Multiplies it by tilewidth again to make it get the exact co-ordinate of the tile.

	if (vPos.GetdX() > (fMapWidth * fTileWidth) || vPos.GetdX() < 0)//Checks to see if the bullet is outside of the map.
	{
		iLifeTime = -2;//Kill the bullet.
	}
	else if (vPos.GetdY() >(fMapHeight * fTileWidth) || vPos.GetdY() < 0)//Checks to see if the bullet is outside of the map.
	{
		iLifeTime = -2;//Kills the bullet.
	}
	if (GetTile(a_iCollisionMap, a_pBullet.vPos) == 1)//Checks to see if the bullet is currently on a wall tile.
	{
		if (iBulletType == 0)//If the bullet is a normal bullet.
		{
			++iBulletBounce;//Add to the amount of times the bullet has bounced.
			//Top Collision
			if ((vLastPos.GetdY() > (iTileY + fTileWidth)) && (vLastPos.GetdX() < (iTileX + fTileWidth)) && (vLastPos.GetdX() > iTileX))//If the last position of the bullet is ABOVE the top edge of the tile.
			{
				vVelocity.SetdY((vVelocity.GetdY()) * -1);//Invert the Y velocity.
			}
			//Bottom Collision
			if ((vLastPos.GetdY() < iTileY) && (vLastPos.GetdX() < (iTileX + fTileWidth)) && (vLastPos.GetdX() > iTileX))//If the last position of the bullet is BELOW the bottom edge of the tile.
			{
				vVelocity.SetdY((vVelocity.GetdY()) * -1);//Invert the Y Velocity.
			}
			//Right Collision
			if ((vLastPos.GetdX() > (iTileX + fTileWidth)) && (vLastPos.GetdY() < (iTileY + fTileWidth)) && (vLastPos.GetdY() > iTileY))//If the last position of the bullet is to the RIGHT of the Right edge of the tile.
			{
				vVelocity.SetdX((vVelocity.GetdX()) * -1);//Invert the X Velocity.
			}
			//Left Collision
			if ((vLastPos.GetdX() < iTileX) && (vLastPos.GetdY() < (iTileY + fTileWidth)) && (vLastPos.GetdY() > iTileY))//If the last position of the bullet is to the Left of the Left edge of the tile.
			{
				vVelocity.SetdX((vVelocity.GetdX()) * -1);//Invert the X Velocity.
			}
		}
		if (iBulletType == 1)//If the bullet is a missile.
		{
			iLifeTime = -2;//Kill the bullet.
		}
		if (iBulletType == 2)//If the bullet is a mine.
		{
			iLifeTime = -2;//Kill the bullet
		}
		if ((vLastPos.GetdX() > iTileX) && (vLastPos.GetdX() < iTileX + fTileWidth) && (vLastPos.GetdY() > iTileY) && (vLastPos.GetdY() < iTileY + fTileWidth))//If the sprites LAST position is inside a map tile.
		{
			iLifeTime = -2;//Kill the bullet.
		}
	}

	if (iBulletType == 1)//If the bullet is a missile.
	{
		double iMouseX, iMouseY;//Declares variables to temporarily store the Mouse positions in
		UG::GetMousePos(iMouseX, iMouseY);//Gets the mouse position and stores it in the variables.
		vMousePos.SetdX(iMouseX);//Stores the MouseX in the vMousePos vector.
		vMousePos.SetdY((iMapHeight * fTileWidth) - iMouseY);//Reverses the Y-Value given from UG::GetMousePos since it returns Y=0 at the top of the screen instead of the bottom.
		vVelocity = vVelocity.RotateX((GetBearing(vPos, vMousePos)-180));//Uses the Vector2 rotate function to get the Velocity vector.
	}
	if (iBulletType == 2)//If the bullet is a mine.
	{
		vVelocity = vVelocity.Zero();//Set the velocity to 0.
	}
	float fDeltaTime = UG::GetDeltaTime();//Gets the delta time.
	vLastPos = vPos;//Sets the last position to the current position.
	vPos += (vVelocity * iBulletSpeed) * fDeltaTime;//Moves the bullet in the Velocity direction.
	UG::MoveSprite(iSpriteID, vPos.GetdX(), vPos.GetdY());//Moves the sprite.

	
}

//Function to get the current type of tile at a certain point.
//int a_iCollisionMap[] = The collision map to check against.
//Vector2 a_vPos = The position to check.
int Bullet::GetTile(int a_iCollisionMap[], Vector2 a_vPos)
{
	int a_iX = (a_vPos.GetdX() / fTileWidth);//Converts to Array co-ordinates.
	int a_iY = (a_vPos.GetdY() / fTileWidth);//Converts to Array co-ordinates.

	return a_iCollisionMap[(a_iY * iMapWidth) + a_iX];//Returns the point in array.
}
//Function to destroy a bullet or subtract from its lifetime.
//Bullet& a_pBullet = The bullet that contains the variables for the array, usually Bullet[0].
void Bullet::DestroyBullets(Bullet& a_pBullet)
{
	if ((iLifeTime < 0 || iBulletBounce >= 5) && bIsActive == true)//If the bullet is out of lifetime or it has bounced 5 times AND is an active bullet.
	{
		if (iBulletType == 0)//If the bullet is normal.
		{
			a_pBullet.iActiveNormalBullets -= 1;//Reduce the Active normal bullet count.
		}
		else if (iBulletType == 1)//If the bullet is a missile.
		{
			a_pBullet.iActiveMissiles -= 1;//Reduce the Active missile count.
		}
		else if (iBulletType == 2)//If the bullet is a mine.
		{
			a_pBullet.iActiveMines -= 1;//Reduce the active mine count.
		}
		bIsActive = false;//Set the bullet back to inactive.
		iBulletBounce = 0;//Resets bullet bounce.
		UG::StopDrawingSprite(iSpriteID);//Stops drawing that.
		UG::DestroySprite(iSpriteID);//Destroys that.
	}
	else
	{
		iLifeTime -= 1;//Subtract from the lifetime.
	}
}

//Function to run through each active bullet, move it and then check if it needs to be destroyed.
//Bullet *a_pBullet = The Bullet array that needs to be checked through.
//int a_iCollisionMap[] == The collision map to check against.
void Bullet::UpdateBullets(Bullet *a_pBullet, int a_iCollisionMap[])
{	
	for (int i = 0; i < iMaxNormalBullets + iActiveMissiles; i++)//Runs through the max amount of bullets
	{
		if (a_pBullet[i].bIsActive == true)//IF the bullet in question is active.
		{
			a_pBullet[i].MoveBullet(a_pBullet[i], a_iCollisionMap);//Move that bullet
			a_pBullet[i].DestroyBullets(a_pBullet[0]);//Check if that bullet needs to be destroyed, pass through the variable buillet.
		}

	}
}
//Gets the Angle between two Vector2 co-ordinates from the starting point.
//Equation used - http://wikicode.wikidot.com/get-angle-of-line-between-two-points
//Vector2 &a_V1 = The Starting point
//Vector2 &a_V2 = The End point
float Bullet::GetBearing(Vector2 &a_V1, Vector2 &a_V2)
{
	float fXChange = (a_V1.GetdX() - a_V2.GetdX());
	float fYChange = (a_V1.GetdY() - a_V2.GetdY());
	return atan2(fYChange, fXChange)*(180 / fPI);
}

//Checks if the bullet has collided with a sprites AABB box.
//Bullet* a_pBullet = The bullet array to check through.
//int a_iSpriteID = The spriteid of the sprite that you want to check collision against.
//int a_iWidth = The width of the un-rotated sprite.
//int a_iHeight = The height of the un-rotated sprite.
//Vector2 a_vPos = The Position of the sprite to check. (Unused currently)
//float a_fRad = The rotation of the sprite to check.
bool Bullet::SpriteCollide(Bullet* a_pBullet, int a_iSpriteID, int a_iWidth, int a_iHeight, Vector2 a_vPos, float a_fRad)
{
	Boundaries AABBCheck;//Creates a class member for AABB checking.
	AABBCheck.AABB(a_iSpriteID, a_iWidth, a_iHeight, a_fRad);//Creates the AABB boundaries for collsion check.
	for (int i = 0; i < iMaxNormalBullets + iActiveMissiles; i++)//Loops through the bullet array.
	{
		if (a_pBullet[i].bIsActive == true)//If the bullet in question is active.
		{
			if ((a_pBullet[i].vPos.GetdX() < AABBCheck.vTopRight.GetdX()) && (a_pBullet[i].vPos.GetdX() > AABBCheck.vTopLeft.GetdX()) &&
				(a_pBullet[i].vPos.GetdY() < AABBCheck.vTopRight.GetdY()) && (a_pBullet[i].vPos.GetdY() > AABBCheck.vBotLeft.GetdY()))//Check if the bullet is inside the AABB of the sprite.
			{
				return true;
			}
		}

	}
	return false;
}

//Function to reset all bullets.
//Bullet* a_pBulletArray = The Bullet array to reset.
void Bullet::Reset(Bullet* a_pBulletArray)
{
	for (int i = 0; i < iMaxNormalBullets + iActiveMissiles; i++)//Loops through the Bullet array.
	{
		if (a_pBulletArray[i].bIsActive == true)//If the bullet is active.
		{
			a_pBulletArray[i].iLifeTime = -2;//Kill the bullet.
			a_pBulletArray[0].DestroyBullets(a_pBulletArray[0]);//Destroy that bullet.
		}

	}
	a_pBulletArray[0].iMissileCount = 0;//Resets Missile count.
	a_pBulletArray[0].iMineCount = 0;//Resets mine count.
}