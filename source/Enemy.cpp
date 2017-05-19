#include "Vector2.h"
#include "CustomEnum.h"
#include "Enemy.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>
#include "UGFW.h"
#include "MathUtil.h"
#include "Matrix4x4.h"


void Enemy::CreateTank(float a_fCenterX, float a_fCenterY)
{
	iSpriteID = UG::CreateSprite("./images/Tanks/tank_body.png", iSpriteWidth, iSpriteHeight, true);//Create the sprite
																									
	UG::DrawSprite(iSpriteID);	//Draws it
	vPos = Vector2(a_fCenterX + (fTileWidth/2), a_fCenterX+(fTileWidth/2));
	UG::MoveSprite(iSpriteID, vPos.dX, vPos.dY);
	UG::SetSpriteLayer(iSpriteID, 9);
	bIsRotating = true;
	bIsTravelling = false;

};
Enemy::~Enemy()
{
	UG::StopDrawingSprite(iSpriteID);
	UG::DestroySprite(iSpriteID);
}
void Enemy::MoveTank(Vector2 a_vStart, Vector2 a_vGoal)
{
	float fDelta = UG::GetDeltaTime();
	if (bIsRotating == true)
	{
		oPathFinder.FindPath(Vector3(a_vStart.dX, 0, a_vStart.dY), Vector3(a_vGoal.dX, 0, a_vGoal.dY));
		//oPathFinder.FindPath(Vector3(a_vStart.dX, 0, a_vStart.dY), Vector3(a_vGoal.dX, 0, a_vGoal.dY));
		if (oPathFinder.bFoundGoal)
		{
			bIsRotating = false;
			bIsTravelling = true;
			vDistanceTarget = oPathFinder.NextPathPos(Vector3(vPos.dX, 0, vPos.dY), false);
			fLerpPosition = 0;
			oPathFinder.DrawDebug();
		}

		
	}
	if (bIsTravelling == true)
	{
		
		RotateSprite(iSpriteID, DegreesToRadians(-fBearing + 90));
		Vector3 vNextSpot = oPathFinder.SecondNextPathPos(vDistanceTarget);
		
		if (vNextSpot.dY == -100)
		{
			bIsTravelling = false;
			oPathFinder.bInitialisedStart = false;
			bIsRotating = true;
		}
		
		if (fLerpPosition >= 1)
		{
			vDistanceTarget = oPathFinder.NextPathPos(vNextSpot, true);
			if (vDistanceTarget.dY == -100)
			{
				bIsTravelling = false;
				oPathFinder.bInitialisedStart = false;
				bIsRotating = true;
			}
			
			fLerpPosition = 0;
		}
		else if (fLerpPosition >= 0 && fLerpPosition <= 1)
		{
			vPos = Vector2(Lerp(vDistanceTarget.dX, vNextSpot.dX, fLerpPosition), Lerp(vDistanceTarget.dZ, vNextSpot.dZ, fLerpPosition));
			fBearing = GetBearing(vDistanceTarget, vNextSpot);
			fLerpPosition += 2.f * fDelta;
		}
		
		


		
		UG::MoveSprite(iSpriteID, vPos.dX + fTileWidth/2, vPos.dY+fTileWidth/2);

	}
}






void Enemy::UpdateCollisionMap()
{
	std::ifstream pCollision;//Creates an input fstream member
	pCollision.open("./maps/currentCollision.txt");//Opens the file.
	for (int i = 0; i < (iMapHeight*iMapWidth); i++)//Iterates through each tile in the array.
	{
		pCollision >> iEnemyCollisionMap[i];//Stores current tile type into array.
	}
	pCollision.close();
}
int Enemy::GetTile(int a_iTileWidth, Vector2 a_vPos)
{
	int a_iX = (a_vPos.dX);
	int a_iY = (a_vPos.dY);

	return iEnemyCollisionMap[(a_iY * iMapWidth) + a_iX];
}
void Enemy::RotateSprite(int a_iSpriteID, float a_fRad)
{
	UG::GetSpriteMatrix(a_iSpriteID, fUGFrameSpriteMatrix);//Gets the sprite matrix of the given sprite and stores it in a size[16] float array.
	Matrix4x4 mRotateMatrix(fUGFrameSpriteMatrix);//Creates a 4x4 Matrix with the UG Framework matrix.
	mRotateMatrix.RotateZ(a_fRad);//Rotates that with the given rotation on the Z Axis.

	//Method Discovered after reading Daniel Budworth-Mead's UGFW++ linked on the Facebook group http://pastebin.com/fHGNgjrL
	//Sets the newly rotated values to the UGFramework matrix. I tried just multiplying the Matrix together but always ended up with errors.
	fUGFrameSpriteMatrix[0] = mRotateMatrix.GetMatrixValue(0);//cos
	fUGFrameSpriteMatrix[1] = mRotateMatrix.GetMatrixValue(1);//-sin
	fUGFrameSpriteMatrix[4] = mRotateMatrix.GetMatrixValue(4);//sin
	fUGFrameSpriteMatrix[5] = mRotateMatrix.GetMatrixValue(5);//cos

	UG::SetSpriteMatrix(a_iSpriteID, fUGFrameSpriteMatrix);//Sets the Matrix, rotating the sprite.
}
//Gets the Angle between two Vector2 co-ordinates. Mainly Used for rotating tank turret.
//Equation used - http://wikicode.wikidot.com/get-angle-of-line-between-two-points
float Enemy::GetBearing(Vector2 &a_V1, Vector2 &a_V2)
{
	float fXChange = (a_V1.dX - a_V2.dX);
	float fYChange = (a_V1.dY - a_V2.dY);
	return atan2(fYChange, fXChange)*(180 / fPI);
}
float Enemy::GetBearing(Vector3 &a_V1, Vector3 &a_V2)
{
	float fXChange = (a_V1.dX - a_V2.dX);
	float fYChange = (a_V1.dZ - a_V2.dZ);
	return atan2(fYChange, fXChange)*(180 / fPI);
}