#include "Bullet.h"
#include "UGFW.h"
#include "CustomEnum.h"
#include "Boundaries.h"
#include <string>
#include "MathUtil.h"
#include <cmath>
void Bullet::CreateBullet(Bullet *a_pBullet, Vector2 a_fStart, Vector2 a_fTarget, int a_iBulletType)
{

	for (int i = 0; i < iMaxNormalBullets; i++)
	{
		if (a_pBullet[i].bIsActive == false)
		{

			a_pBullet[i].iBulletType = a_iBulletType;

			if (a_pBullet[i].iBulletType == 0 && iMaxNormalBullets - iActiveNormalBullets > 0)
			{
				a_pBullet[i].iSpriteID = UG::CreateSprite("./images/Powerups/powerup_missile.png", 10, 10, true);//Create the sprite
				iBulletCount--;
				iActiveNormalBullets++;

			}
			else if (a_pBullet[i].iBulletType == 1 && iMissileCount > 0)
			{
				a_pBullet[i].iSpriteID = UG::CreateSprite("./images/Powerups/powerup_missile.png", 20, 20, true);//Create the sprite
				iMissileCount--;
				iActiveMissiles++;
			}
			else if (a_pBullet[i].iBulletType == 2 && iMineCount > 0)
			{
				a_pBullet[i].iSpriteID = UG::CreateSprite("./images/Powerups/powerup_mine.png", 20, 20, true);//Create the sprite
				iMineCount--;
				iActiveMines++;
			}
			else
			{
				return;
			}
			
			UG::DrawSprite(a_pBullet[i].iSpriteID);	//Draws it	
			UG::SetSpriteLayer(a_pBullet[i].iSpriteID, 9);
			a_pBullet[i].fAngle = (GetBearing(a_fStart, a_fTarget) + 180);
			a_pBullet[i].vVelocity = a_pBullet[i].vVelocity.RotateX(a_pBullet[i].fAngle);
			a_pBullet[i].vPos = a_fStart;
			a_pBullet[i].vLastPos = a_fStart;
			a_pBullet[i].vPos += Vector2(a_pBullet[i].vVelocity.GetdX() * 40, a_pBullet[i].vVelocity.GetdY() * 40);//40 is a magic number I know, its the value I use to make the bullet spawn at the end of the turret.
			UG::MoveSprite(a_pBullet[i].iSpriteID, a_pBullet[i].vPos.GetdX(), a_pBullet[i].vPos.GetdY());
			a_pBullet[i].iLifeTime = 500;
			a_pBullet[i].iBulletSpeed = 80;
			a_pBullet[i].bIsActive = true;

			
			break;
		}
	}
}

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
void Bullet::DrawBulletCount()
{
	UG::ClearScreen();
	//Stringstream to draw the current highscore below HIGHSCORES during GAMEPLAY
	std::string ssNormalBullets;
	ssNormalBullets += std::to_string(iMaxNormalBullets - iActiveNormalBullets);
	UG::DrawString(ssNormalBullets.c_str(), (int)(fMapWidth * fTileWidth * 0.2f), (int)(fMapHeight * fTileWidth), 0.8f);

	//Stringstream to draw the current highscore below HIGHSCORES during GAMEPLAY
	std::string ssMissiles;
	ssMissiles += std::to_string(iMissileCount);
	UG::DrawString(ssMissiles.c_str(), (int)(fMapWidth * fTileWidth * 0.5f), (int)(fMapHeight * fTileWidth), 0.8f);
}

void Bullet::MoveBullet(Bullet& a_pBullet, int a_iCollisionMap[])
{
	int iTileX = (vPos.GetdX() / fTileWidth);
	int iTileY = (vPos.GetdY() / fTileWidth);
	iTileX *= fTileWidth;
	iTileY *= fTileWidth;

	if (vPos.GetdX() > (fMapWidth * fTileWidth) || vPos.GetdX() < 0)
	{
		iLifeTime = -2;
	}
	else if (vPos.GetdY() >(fMapHeight * fTileWidth) || vPos.GetdY() < 0)
	{
		iLifeTime = -2;
	}
	if (GetTile(a_iCollisionMap, a_pBullet.vPos) == 1)
	{
		if (iBulletType == 0)
		{
			++iBulletBounce;
			//Top Collision
			if ((vLastPos.GetdY() > (iTileY + fTileWidth)) && (vLastPos.GetdX() < (iTileX + fTileWidth)) && (vLastPos.GetdX() > iTileX))//If the last position of the bullet is ABOVE the top edge of the tile.
			{
				vVelocity.SetdY((vVelocity.GetdY()) * -1);
			}
			//Bottom Collision
			if ((vLastPos.GetdY() < iTileY) && (vLastPos.GetdX() < (iTileX + fTileWidth)) && (vLastPos.GetdX() > iTileX))//If the last position of the bullet is BELOW the bottom edge of the tile.
			{
				vVelocity.SetdY((vVelocity.GetdY()) * -1);
			}
			//Right Collision
			if ((vLastPos.GetdX() > (iTileX + fTileWidth)) && (vLastPos.GetdY() < (iTileY + fTileWidth)) && (vLastPos.GetdY() > iTileY))//If the last position of the bullet is to the RIGHT of the Right edge of the tile.
			{
				vVelocity.SetdX((vVelocity.GetdX()) * -1);
			}
			//Left Collision
			if ((vLastPos.GetdX() < iTileX) && (vLastPos.GetdY() < (iTileY + fTileWidth)) && (vLastPos.GetdY() > iTileY))//If the last position of the bullet is to the Left of the Left edge of the tile.
			{
				vVelocity.SetdX((vVelocity.GetdX()) * -1);
			}
		}
		if (iBulletType == 1)
		{
			iLifeTime = -2;
		}
		if (iBulletType == 2)
		{
			iLifeTime = -2;
		}
		if ((vLastPos.GetdX() > iTileX) && (vLastPos.GetdX() < iTileX + fTileWidth) && (vLastPos.GetdY() > iTileY) && (vLastPos.GetdY() < iTileY + fTileWidth))
		{
			iLifeTime = -2;
		}
	}

	if (iBulletType == 1)
	{
		double iMouseX, iMouseY;
		UG::GetMousePos(iMouseX, iMouseY);//Gets the mouse position and stores it in the class members variable.
		vMousePos.SetdX(iMouseX);
		vMousePos.SetdY((iMapHeight * fTileWidth) - iMouseY);//Reverses the Y-Value given from UG::GetMousePos since it returns Y=0 at the top instead of the bottom.
		vVelocity = vVelocity.RotateX((GetBearing(vPos, vMousePos)-180));
	}
	if (iBulletType == 2)
	{
		vVelocity = vVelocity.Zero();
	}
	float fDeltaTime = UG::GetDeltaTime();
	vLastPos = vPos;
	vPos += (vVelocity * iBulletSpeed) * fDeltaTime;
	UG::MoveSprite(iSpriteID, vPos.GetdX(), vPos.GetdY());

	
}

int Bullet::GetTile(int a_iCollisionMap[], Vector2 a_vPos)
{
	int a_iX = (a_vPos.GetdX() / fTileWidth);
	int a_iY = (a_vPos.GetdY() / fTileWidth);

	return a_iCollisionMap[(a_iY * iMapWidth) + a_iX];
}

void Bullet::DestroyBullets(Bullet& a_pBullet)
{
	if ((iLifeTime < 0 || iBulletBounce >= 5) && bIsActive == true)
	{
		if (iBulletType == 0)
		{
			a_pBullet.iActiveNormalBullets -= 1;
		}
		else if (iBulletType == 1)
		{
			a_pBullet.iActiveMissiles -= 1;
		}
		else if (iBulletType == 2)
		{
			a_pBullet.iActiveMines -= 1;
		}
		bIsActive = false;
		iBulletBounce = 0;
		UG::StopDrawingSprite(iSpriteID);//Stops drawing that.
		UG::DestroySprite(iSpriteID);//Destroys that.
	}
	else
	{
		iLifeTime -= 1;
	}
}
void Bullet::UpdateBullets(Bullet *a_pBullet, int a_iCollisionMap[])
{
	
	for (int i = 0; i < iMaxNormalBullets + iActiveMissiles; i++)
	{
		if (a_pBullet[i].bIsActive == true)
		{
			a_pBullet[i].MoveBullet(a_pBullet[i], a_iCollisionMap);
			a_pBullet[i].DestroyBullets(a_pBullet[0]);
		}

	}
}
//Gets the Angle between two Vector2 co-ordinates. Mainly Used for rotating tank turret.
//Equation used - http://wikicode.wikidot.com/get-angle-of-line-between-two-points
float Bullet::GetBearing(Vector2 &a_V1, Vector2 &a_V2)
{
	float fXChange = (a_V1.GetdX() - a_V2.GetdX());
	float fYChange = (a_V1.GetdY() - a_V2.GetdY());
	return atan2(fYChange, fXChange)*(180 / fPI);
}

bool Bullet::SpriteCollide(Bullet* a_pBullet, int a_iSpriteID, int a_iWidth, int a_iHeight, Vector2 a_vPos, float a_fRad)
{
	Boundaries AABBCheck;
	AABBCheck.AABB(a_iSpriteID, a_iWidth, a_iHeight, a_fRad);
	for (int i = 0; i < iMaxNormalBullets + iActiveMissiles; i++)
	{
		if (a_pBullet[i].bIsActive == true)
		{
			if ((a_pBullet[i].vPos.GetdX() < AABBCheck.vTopRight.GetdX()) && (a_pBullet[i].vPos.GetdX() > AABBCheck.vTopLeft.GetdX()) &&
				(a_pBullet[i].vPos.GetdY() < AABBCheck.vTopRight.GetdY()) && (a_pBullet[i].vPos.GetdY() > AABBCheck.vBotLeft.GetdY()))
			{
				return true;
			}
		}

	}
	return false;
}

void Bullet::Reset(Bullet* a_pBulletArray)
{
	for (int i = 0; i < iMaxNormalBullets + iActiveMissiles; i++)
	{
		if (a_pBulletArray[i].bIsActive == true)
		{
			a_pBulletArray[i].iLifeTime = -2;
			a_pBulletArray[0].DestroyBullets(a_pBulletArray[0]);
		}

	}
	a_pBulletArray[0].iMissileCount = 0;
}