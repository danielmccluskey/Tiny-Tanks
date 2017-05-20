#include "Bullet.h"
#include "UGFW.h"
#include "CustomEnum.h"
#include "MathUtil.h"
#include <cmath>
void Bullet::CreateBullet(Bullet *a_pBullet, Vector2 a_fStart, Vector2 a_fTarget)
{
	for (int i = 0; i < 10; i++)
	{
		if (a_pBullet[i].bIsActive == false)
		{
			a_pBullet[i].iSpriteID = UG::CreateSprite("./images/Tanks/temp.png", 10, 10, true);//Create the sprite
			UG::DrawSprite(a_pBullet[i].iSpriteID);	//Draws it	
			UG::SetSpriteLayer(a_pBullet[i].iSpriteID, 9);
			a_pBullet[i].fAngle = (GetBearing(a_fStart, a_fTarget) + 180);
			a_pBullet[i].vVelocity = a_pBullet[i].vVelocity.RotateX(a_pBullet[i].fAngle);
			a_pBullet[i].vPos = a_fStart;
			a_pBullet[i].vPos += Vector2(a_pBullet[i].vVelocity.dX * 40, a_pBullet[i].vVelocity.dY * 40);
			UG::MoveSprite(a_pBullet[i].iSpriteID, a_pBullet[i].vPos.dX, a_pBullet[i].vPos.dY);
			a_pBullet[i].iLifeTime = 200;
			a_pBullet[i].bIsActive = true;
			break;
		}
	}
}

void Bullet::MoveBullet(Bullet& a_pBullet, int a_iCollisionMap[])
{
	if (GetTile(a_iCollisionMap, a_pBullet.vPos) == 1)
	{
		std::cout << a_pBullet.fAngle << std::endl;
		if ((a_pBullet.fAngle >= 0 && a_pBullet.fAngle < 90) || (a_pBullet.fAngle >= 180 && a_pBullet.fAngle < 270))
		{
			a_pBullet.vVelocity.dX *= -1;
		}
		if ((a_pBullet.fAngle >= 90 && a_pBullet.fAngle < 180) || (a_pBullet.fAngle >= 270 && a_pBullet.fAngle < 360))
		{
			a_pBullet.vVelocity.dY *= -1;
		}


	}

	a_pBullet.vPos += a_pBullet.vVelocity;
	UG::MoveSprite(a_pBullet.iSpriteID, a_pBullet.vPos.dX, a_pBullet.vPos.dY);

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