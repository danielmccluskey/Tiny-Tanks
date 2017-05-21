#include "Bullet.h"
#include "UGFW.h"
#include "CustomEnum.h"
#include "Boundaries.h"
#include "MathUtil.h"
#include <cmath>
void Bullet::CreateBullet(Bullet *a_pBullet, Vector2 a_fStart, Vector2 a_fTarget, int a_iBulletType)
{
	iBulletCount = 3;
	for (int i = 0; i < iBulletCount; i++)
	{
		if (a_pBullet[i].bIsActive == false)
		{

			a_pBullet[i].iBulletType = a_iBulletType;
			switch (a_iBulletType)
			{
			case 0:
				a_pBullet[i].iSpriteID = UG::CreateSprite("./images/Tanks/temp.png", 10, 10, true);//Create the sprite
				break;
			case 1:
				a_pBullet[i].iSpriteID = UG::CreateSprite("./images/Tanks/temp2.png", 10, 10, true);//Create the sprite
				break;
			}
			
			UG::DrawSprite(a_pBullet[i].iSpriteID);	//Draws it	
			UG::SetSpriteLayer(a_pBullet[i].iSpriteID, 9);
			a_pBullet[i].fAngle = (GetBearing(a_fStart, a_fTarget) + 180);
			a_pBullet[i].vVelocity = a_pBullet[i].vVelocity.RotateX(a_pBullet[i].fAngle);
			a_pBullet[i].vPos = a_fStart;
			a_pBullet[i].vLastPos = a_fStart;
			a_pBullet[i].vPos += Vector2(a_pBullet[i].vVelocity.GetdX() * 40, a_pBullet[i].vVelocity.GetdY() * 40);//40 is a magic number I know, its the value I use to make the bullet spawn at the end of the turret.
			UG::MoveSprite(a_pBullet[i].iSpriteID, a_pBullet[i].vPos.GetdX(), a_pBullet[i].vPos.GetdY());
			a_pBullet[i].iLifeTime = 200;
			a_pBullet[i].iBulletSpeed = 80;
			a_pBullet[i].bIsActive = true;
			
			break;
		}
	}
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
	float fDeltaTime = UG::GetDeltaTime();
	vLastPos = vPos;
	vPos += (vVelocity * iBulletSpeed) * fDeltaTime;
	UG::MoveSprite(iSpriteID, vPos.GetdX(), vPos.GetdY());

	
}

int Bullet::GetTile(int a_iCollisionMap[], Vector2 a_vPos)
{
	int a_iX = (a_vPos.GetdX() / 32);
	int a_iY = (a_vPos.GetdY() / 32);

	return a_iCollisionMap[(a_iY * iMapWidth) + a_iX];
}

void Bullet::DestroyBullets(Bullet& a_pBullet)
{
	if (a_pBullet.iLifeTime < 0)
	{
		a_pBullet.bIsActive = false;
		UG::StopDrawingSprite(a_pBullet.iSpriteID);//Stops drawing that.
		UG::DestroySprite(a_pBullet.iSpriteID);//Destroys that.
	}
	else
	{
		a_pBullet.iLifeTime -= 1;
	}
}
void Bullet::UpdateBullets(Bullet *a_pBullet, int a_iCollisionMap[])
{
	for (int i = 0; i < iBulletCount; i++)
	{
		if (a_pBullet[i].bIsActive == true)
		{
			a_pBullet[i].MoveBullet(a_pBullet[i], a_iCollisionMap);
			a_pBullet[i].DestroyBullets(a_pBullet[i]);
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
	for (int i = 0; i < iBulletCount; i++)
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