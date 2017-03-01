#include "Bullet.h"

void Bullet::CreateBullet(Bullet *a_pBullet, Vector2 a_fStart, Vector2 a_fTarget)
{
	for (int i = 0; i < 10; i++)
	{
		if (a_pBullet[i].bIsActive == false)
		{
			a_pBullet[i].iSpriteID = UG::CreateSprite("./images/Tanks/temp.png", 10, 10, true);//Create the sprite
			UG::DrawSprite(a_pBullet[i].iSpriteID);	//Draws it	
			UG::SetSpriteLayer(a_pBullet[i].iSpriteID, 9);

			a_pBullet[i].vVelocity = DANM::GetForwardVector((DANM::GetBearingDeg(a_fStart, a_fTarget)) + 180);
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