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
	bIsRotating = false;
	bIsTravelling = false;

};
void Enemy::MoveTank(Vector2 a_vStart, Vector2 a_vGoal)
{
	if (bIsRotating == true)
	{
		oPathFinder.FindPath(Vector3(a_vStart.dX, 0, a_vStart.dY), Vector3(a_vGoal.dX, 0, a_vGoal.dY));
		//oPathFinder.FindPath(Vector3(a_vStart.dX, 0, a_vStart.dY), Vector3(a_vGoal.dX, 0, a_vGoal.dY));
		if (oPathFinder.bFoundGoal)
		{
			//oPathFinder.DrawDebug();
			bIsRotating = false;
			bIsTravelling = true;
			vDistanceTarget = oPathFinder.NextPathPos(Vector3(vPos.dX, 0, vPos.dY), false);
			fLerpPosition = 0;
		}

		/*if (fLerpPosition == 0)
		{
			UG::GetSpriteMatrix(iSpriteID, fUGFrameSpriteMatrix);
			iStartAngle = acos(fUGFrameSpriteMatrix[0]);
			iEndAngle = GetNextGoal(a_vStart, a_vGoal);
			if (iEndAngle == iLastDirection)
			{
				bIsRotating = false;
				fLerpPosition = 1;
			}
			vStartPos = vPos;
			switch (iEndAngle)
			{
			case 0:
				iEndAngle = 270;
				vEndPos = Vector2(vPos.dX - fTileWidth, vPos.dY);
				break;
			case 1:
				iEndAngle = 90;
				vEndPos = Vector2(vPos.dX + fTileWidth, vPos.dY);
				break;
			case 2:
				iEndAngle = 180;
				vEndPos = Vector2(vPos.dX , vPos.dY - fTileWidth);
				break;
			case 3:
				iEndAngle = 0;
				vEndPos = Vector2(vPos.dX , vPos.dY + fTileWidth);
				break;
			}
		}
		if (fLerpPosition >= 0 && fLerpPosition <= 1)
		{
			RotateSprite(iSpriteID, DegreesToRadians((Lerp(iStartAngle, iEndAngle, fLerpPosition))));
			fLerpPosition += 0.05f;
		}
		if (fLerpPosition >= 1 || iStartAngle == iEndAngle)
		{
			RotateSprite(iSpriteID, DegreesToRadians((Lerp(iStartAngle, iEndAngle, 1))));
			bIsRotating = false;
			bIsTravelling = true;
			fLerpPosition = 0;
		}*/
	}
	if (bIsTravelling == true)
	{
		
		Vector3 vNextSpot = oPathFinder.SecondNextPathPos(vDistanceTarget);
		if (vNextSpot.dY == -100)
		{
			bIsTravelling = false;
			oPathFinder.bInitialisedStart = false;
		}
		
		if (fLerpPosition >= 1)
		{
			vDistanceTarget = oPathFinder.NextPathPos(vNextSpot, true);
			if (vDistanceTarget.dY == -100)
			{
				bIsTravelling = false;
				oPathFinder.bInitialisedStart = false;
			}
			fLerpPosition = 0;
		}
		else if (fLerpPosition >= 0 && fLerpPosition <= 1)
		{
			vPos = Vector2(Lerp(vDistanceTarget.dX, vNextSpot.dX, fLerpPosition), Lerp(vDistanceTarget.dZ, vNextSpot.dZ, fLerpPosition));
			fLerpPosition += 0.2f;
		}
		
		


		
		UG::MoveSprite(iSpriteID, vPos.dX + fTileWidth/2, vPos.dY+fTileWidth/2);


		/*if (fLerpPosition >= 1)
		{
			bIsTravelling = false;
			fLerpPosition = 0;
			vPos = vEndPos;
			std::cout << "GOAL" << std::endl;
		}
		else if (fLerpPosition >= 0 && fLerpPosition <= 1)
		{
			vPos = Vector2(Lerp(vStartPos.dX, vEndPos.dX, fLerpPosition), Lerp(vStartPos.dY, vEndPos.dY, fLerpPosition));
			fLerpPosition += 0.01f;
		}
		UG::MoveSprite(iSpriteID, vPos.dX + (fTileWidth / 2), vPos.dY + (fTileWidth / 2));*/
	}
}

int Enemy::GetNextGoal(Vector2 a_vStart, Vector2 a_vGoal)
{
	int iDirection = PathFindTileCheck(a_vStart, a_vGoal);

	return iDirection;
}

int Enemy::PathFindTileCheck(Vector2 a_vStart, Vector2 a_vGoal)
{

	a_vStart.dX = int(a_vStart.dX / fTileWidth);
	a_vStart.dY = int(a_vStart.dY / fTileWidth);
	a_vGoal.dX = int(a_vGoal.dX / fTileWidth);
	a_vGoal.dY = int(a_vGoal.dY / fTileWidth);
	Vector2 vLeftTile = Vector2(a_vStart.dX - 1, a_vStart.dY);
	Vector2 vRightTile = Vector2(a_vStart.dX + 1, a_vStart.dY);
	Vector2 vTopTile = Vector2(a_vStart.dX, a_vStart.dY + 1);
	Vector2 vBottomTile = Vector2(a_vStart.dX, a_vStart.dY - 1);
	
	iLeftCost = GetTile(fTileWidth, vLeftTile);
	iRightCost = GetTile(fTileWidth, vRightTile);
	iTopCost = GetTile(fTileWidth, vTopTile);
	iBottomCost = GetTile(fTileWidth, vBottomTile);



	(iLeftCost == 0) ? (iLeftCost = PathFindHCalc(vLeftTile, a_vGoal)) : (iLeftCost = 100);
	(iRightCost == 0) ? (iRightCost = PathFindHCalc(vRightTile, a_vGoal)) : (iRightCost = 100);
	(iTopCost == 0) ? (iTopCost = PathFindHCalc(vTopTile, a_vGoal)) : (iTopCost = 100);
	(iBottomCost == 0) ? (iBottomCost = PathFindHCalc(vBottomTile, a_vGoal)) : (iBottomCost = 100);
	

	int iPriorityArray[4] = { -1,-1,-1,-1 };
	int iChooseMin = 100;
	int minArray[4] = { iLeftCost, iRightCost, iBottomCost, iTopCost };
	for (int i = 0; i < 4; i++)
	{
		if (minArray[i] < iChooseMin)
		{
			iPriorityArray[3] = iPriorityArray[2];
			iPriorityArray[2] = iPriorityArray[1];
			iPriorityArray[1] = iPriorityArray[0];
			iPriorityArray[0] = i;
		}
	}

	if (iPriorityArray[0] != -1)
	{
		return iPriorityArray[0];
	}
	else if (iPriorityArray[1] != -1)
	{
		return iPriorityArray[1];
	}
	else if (iPriorityArray[2] != -1)
	{
		return iPriorityArray[2];
	}
	else if (iPriorityArray[3] != -1)
	{
		return iPriorityArray[3];
	}
	else
	{
		return iPriorityArray[0];
	}

	
}
int Enemy::PathFindFCalc(Vector2 a_vStart, Vector2 a_vGoal)
{
	int iHueristic = PathFindHCalc(a_vStart, a_vGoal);
	int iCost = 1;
	return iCost + iHueristic;
}
int Enemy::PathFindHCalc(Vector2 a_vStart, Vector2 a_vGoal)
{
	//Works out the "As the crow flies" distance to the goal first moving down to the X and then the Y.
	int iX = 0;
	int iY = 0;

	if (a_vStart.dX == a_vGoal.dX)
	{
		iX = 0;
	}
	else if (a_vStart.dX > a_vGoal.dX)
	{
		iX = a_vStart.dX - a_vGoal.dX;
	}
	else if (a_vStart.dX < a_vGoal.dX)
	{
		iX = a_vGoal.dX - a_vStart.dX;
	}

	if (a_vStart.dY == a_vGoal.dY)
	{
		iY = 0;
	}
	else if (a_vStart.dY > a_vGoal.dY)
	{
		iY = a_vStart.dY - a_vGoal.dY;
	}
	else if (a_vStart.dY < a_vGoal.dY)
	{
		iY = a_vGoal.dY - a_vStart.dY;
	}

	std::cout << "\n\n\n\X: " << iX << std::endl;
	std::cout << "Y: " << iY << std::endl;

	return iX + iY;
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