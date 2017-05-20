#include "Bullet.h"
#include "UGFW.h"
#include "CustomEnum.h"
#include "MathUtil.h"
#include <cmath>
void Bullet::CreateBullet(Bullet *a_pBullet, Vector2 a_fStart, Vector2 a_fTarget, int a_iBulletType)
{
	for (int i = 0; i < 10; i++)
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
			a_pBullet[i].vPos += Vector2(a_pBullet[i].vVelocity.dX * 40, a_pBullet[i].vVelocity.dY * 40);//40 is a magic number I know, its the value I use to make the bullet spawn at the end of the turret.
			UG::MoveSprite(a_pBullet[i].iSpriteID, a_pBullet[i].vPos.dX, a_pBullet[i].vPos.dY);
			a_pBullet[i].iLifeTime = 6000;
			a_pBullet[i].bIsActive = true;
			
			break;
		}
	}
}

void Bullet::MoveBullet(Bullet& a_pBullet, int a_iCollisionMap[])
{
	int iTileX = (vPos.dX / fTileWidth);
	int iTileY = (vPos.dY / fTileWidth);
	iTileX *= fTileWidth;
	iTileY *= fTileWidth;
	if (GetTile(a_iCollisionMap, a_pBullet.vPos) == 1)
	{
		if (iBulletType == 0)
		{
			//Top Collision
			if ((vLastPos.dY > (iTileY + fTileWidth)) && (vLastPos.dX < (iTileX + fTileWidth)) && (vLastPos.dX > iTileX))
			{
				vVelocity.dY *= -1;
			}
			//Bottom Collision
			if ((vLastPos.dY < iTileY) && (vLastPos.dX < (iTileX + fTileWidth)) && (vLastPos.dX > iTileX))
			{
				vVelocity.dY *= -1;
			}
			//Right Collision
			if ((vLastPos.dX > (iTileX + fTileWidth)) && (vLastPos.dY < (iTileY + fTileWidth)) && (vLastPos.dY > iTileY))
			{
				vVelocity.dX *= -1;
			}
			//Left Collision
			if ((vLastPos.dX < iTileX) && (vLastPos.dY < (iTileY + fTileWidth)) && (vLastPos.dY > iTileY))
			{
				vVelocity.dX *= -1;
			}
		}
		if (iBulletType == 1)
		{
			iLifeTime = -2;
		}
	}

	if (iBulletType == 1)
	{
		UG::GetMousePos(vMousePos.dX, vMousePos.dY);//Gets the mouse position and stores it in the class members variable.
		vMousePos.dY = (iMapHeight * fTileWidth) - vMousePos.dY;//Reverses the Y-Value given from UG::GetMousePos since it returns Y=0 at the top instead of the bottom.
		vVelocity = vVelocity.RotateX((GetBearing(vPos, vMousePos)-180));
	}
	vLastPos = vPos;
	vPos += vVelocity;
	UG::MoveSprite(iSpriteID, vPos.dX, vPos.dY);

}

int Bullet::GetTile(int a_iCollisionMap[], Vector2 a_vPos)
{
	int a_iX = (a_vPos.dX / 32);
	int a_iY = (a_vPos.dY / 32);

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
	for (int i = 0; i < 10; i++)
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
	float fXChange = (a_V1.dX - a_V2.dX);
	float fYChange = (a_V1.dY - a_V2.dY);
	return atan2(fYChange, fXChange)*(180 / fPI);
}