#include "Bullet.h"

void Bullet::CreateBullet(Vector2 a_fStart, Vector2 a_fTarget)
{
	iSpriteID = UG::CreateSprite("./images/Tanks/temp.png", 10, 10, true);//Create the sprite
	UG::DrawSprite(iSpriteID);	//Draws it	
	UG::SetSpriteLayer(iSpriteID, 9);

	vVelocity = DANM::GetForwardVector((DANM::GetBearingDeg(a_fStart, a_fTarget)) + 180);
	vPos = a_fStart;
	vPos += Vector2(vVelocity.dX * 40, vVelocity.dY * 40);
	UG::MoveSprite(iSpriteID, vPos.dX, vPos.dY);
}

void Bullet::MoveBullet(int a_iCollisionMap[])
{
	vPos += vVelocity;
	UG::MoveSprite(iSpriteID, vPos.dX, vPos.dY);
	DestroyBullets();
}

int Bullet::GetTile(int a_iCollisionMap[], Vector2 a_vPos)
{
	int a_iX = (a_vPos.dX / a_iTileWidth);
	int a_iY = (a_vPos.dY / a_iTileWidth);

	return a_iCollisionMap[(a_iY * iMapWidth) + a_iX];
}

void Bullet::DestroyBullets()
{
	if (iLifeTime < 0)
	{
		UG::StopDrawingSprite(iSpriteID);//Stops drawing that.
		UG::DestroySprite(iSpriteID);//Deletes that.
	}
	else
	{
		iLifeTime -= 1;
	}
}