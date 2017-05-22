#include "Vector2.h"
#include "CustomEnum.h"
#include "Enemy.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>
#include "UGFW.h"
#include "MathUtil.h"
#include "Matrix4x4.h"
//==============================================================================================================================
// Project: WiiTanks
// File: Enemy.h
// Author: Daniel McCluskey
// Date Created: 17/01/17
// Brief: This file controls the Enemy "AI" movement, the bullets for the enemy and the rotation of the enemy.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================

//Function to create the Enemy tank, Need to convert to a constructor.
//float a_fStartXPos = The X position to spawn the tank in.
//float a_fStartYPos = The Y position to spawn the tank in.
void Enemy::CreateTank(float a_fStartXPos, float a_fStartYPos)
{
	iSpriteID = UG::CreateSprite("./images/Tanks/enemy_tank_body.png", iSpriteWidth, iSpriteHeight, true);//Create the sprite																									
	UG::DrawSprite(iSpriteID);	//Draws it
	vPos = Vector2(a_fStartXPos + (fTileWidth/2), a_fStartYPos +(fTileWidth/2));//Sets the position to the middle of the spawning tile.
	UG::MoveSprite(iSpriteID, vPos.GetdX(), vPos.GetdY());//Moves it to the position.
	UG::SetSpriteLayer(iSpriteID, 9);//Sets the layer to above the map tiles.
	bIsRotating = true;//To start the Pathfinding function.
	bIsTravelling = false;//For the Pathfinding function.
	UpdateCollisionMap();//Updates the collision map for movement.
};
//Deconstructor
Enemy::~Enemy()
{
	UG::StopDrawingSprite(iSpriteID);//Stops Drawing that.
	UG::DestroySprite(iSpriteID);//Destroys that.
	UG::StopDrawingSprite(sSpriteTurret.iSpriteID);//Stops Drawing that.
	UG::DestroySprite(sSpriteTurret.iSpriteID);//Destroys that.
}
int Enemy::GetSpriteID()
{
	return iSpriteID;
}
Vector2 Enemy::GetPos()
{
	return vPos;
}
//Function to determine a Path to a_vGoal using the A* pathfinding method, then moves the tank along the path.
//Vector2 a_vStart = The start position of the tank.
//Vector2 a_vGoal = The end of the path (Currently the Players position.)
bool Enemy::MoveTank(Vector2 a_vStart, Vector2 a_vGoal, int a_iEnemySpriteID)
{
	float fDelta = UG::GetDeltaTime();//Gets the Delta time.
	if (bIsRotating == true)
	{
		oPathFinder.FindPath(Vector3(a_vStart.GetdX(), 0, a_vStart.GetdY()), Vector3(a_vGoal.GetdX(), 0, a_vGoal.GetdY()));//This is the main pathfinding function that finds a path to a_vGoal from a_vStart. Searches 1 tile per frame so the game doesnt freeze during search.
		if (oPathFinder.bFoundGoal)//If the goal has been found.
		{
			bIsRotating = false;//Switch to movement part of function
			bIsTravelling = true;//Switch to movement part of function
			vDistanceTarget = oPathFinder.NextPathPos(Vector3(vPos.GetdX(), 0, vPos.GetdY()), false);//Get the position of the next position on the path.
			fLerpPosition = 0;//Sets the lerp value to 0.
			oPathFinder.DrawDebug();//For debug, to draw the search areas so that I could visualise the Pathfinding
		}

		
	}
	if (bIsTravelling == true)
	{		
		RotateSprite(iSpriteID, DegreesToRadians(-fBearing + 90));//Rotates the sprite to face the direction it is travelling in.
		Vector3 vNextSpot = oPathFinder.SecondNextPathPos(vDistanceTarget);//Gets the position of the path, 2 positions away from where the sprite is currently.
		
		if (vNextSpot.GetdY() == -100)//Checks to see if the path has ended.
		{
			bIsTravelling = false;//Switch to pathfinding part of function.
			oPathFinder.bInitialisedStart = false;//Restarts the pathfinding function.
			bIsRotating = true;//Switch to pathfinding part of function.
		}
		
		if (fLerpPosition >= 1)//If the lerp has completed.
		{
			vDistanceTarget = oPathFinder.NextPathPos(vNextSpot, true);//Find the next position of the path.
			if (vDistanceTarget.GetdY() == -100)//Checks to see if the path has ended.
			{
				bIsTravelling = false;//Switch to pathfinding part of function.
				oPathFinder.bInitialisedStart = false;//Restarts the pathfinding function.
				bIsRotating = true;//Switch to pathfinding part of function.
			}
			
			fLerpPosition = 0;//Resets the lerp position.
			BulletArray[0].CreateBullet(BulletArray, Vector2(vPos.GetdX() + fTileWidth / 2, vPos.GetdY() + fTileWidth / 2), a_vGoal, 0);//Creates a bullet and fires it toward the player.
		}
		else if (fLerpPosition >= 0 && fLerpPosition <= 1)//If the lerp is still in progress.
		{
			vPos = Vector2(Lerp(vDistanceTarget.GetdX(), vNextSpot.GetdX(), fLerpPosition), Lerp(vDistanceTarget.GetdZ(), vNextSpot.GetdZ(), fLerpPosition));//Lerps between the Current position and the Next position.
			fBearing = GetBearing(vDistanceTarget, vNextSpot);//Gets the bearing/angle between the current position and the next position.
			fLerpPosition += 1.5f * fDelta;//Adds to the lerp.
		}
		BulletArray[0].UpdateBullets(BulletArray, iEnemyCollisionMap);//Updates the bullet array (Moves and Destroys bullets)
		UG::MoveSprite(iSpriteID, vPos.GetdX() + fTileWidth/2, vPos.GetdY() +fTileWidth/2);//Moves the tank to the lerped position.

	}

	if (BulletArray[0].SpriteCollide(BulletArray, a_iEnemySpriteID, iSpriteWidth, iSpriteHeight, vPos, fBearing))
	{
		return true;
	}
	return false;
}
//Function to Update the Enemy tanks Collision map array and the Pathfinding collision map array.
//Needs to be called for each individual enemy.
void Enemy::UpdateCollisionMap()
{
	std::ifstream pCollision;//Creates an input fstream member
	pCollision.open("./maps/currentCollision.txt");//Opens the file.
	for (int i = 0; i < (iMapHeight*iMapWidth); i++)//Iterates through each tile in the array.
	{
		pCollision >> iEnemyCollisionMap[i];//Stores current tile type into array.
	}
	pCollision.close();//Closes the file.

	oPathFinder.UpdateCollisionMap();//Updates the pathfinding collision map.
}

//Function to rotate a sprite using a combination of the UGSpriteMatrix and a 4x4Matrix.
//Rotates the sprite to a set angle instead of incrementing the angle.
//int a_iSpriteID = The SpriteID of the sprite you want to rotate.
//float a_fRad = The angle in radians that you want to rotate the sprite to.
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
//Vector2 &a_V1 = Starting Position.
//Vector2 &a_V2 = End position.
float Enemy::GetBearing(Vector2 &a_V1, Vector2 &a_V2)
{
	float fXChange = (a_V1.GetdX() - a_V2.GetdX());//Change in X.
	float fYChange = (a_V1.GetdY() - a_V2.GetdY());//Change in Y.
	return atan2(fYChange, fXChange)*(180 / fPI); //Returns the principal value of the arc tangent of y / x, then converted to degrees.
}
//Gets the Angle between two Vector3 co-ordinates. Mainly Used for rotating tank turret.
//Equation used - http://wikicode.wikidot.com/get-angle-of-line-between-two-points
//Vector3 &a_V1 = Starting Position.
//Vector3 &a_V2 = End position.
float Enemy::GetBearing(Vector3 &a_V1, Vector3 &a_V2)
{
	float fXChange = (a_V1.GetdX() - a_V2.GetdX());//Change in X.
	float fYChange = (a_V1.GetdZ() - a_V2.GetdZ());//Change in Y.
	return atan2(fYChange, fXChange)*(180 / fPI); //Returns the principal value of the arc tangent of y / x, then converted to degrees.
}
//Function to make the Turret sprite rotate to look at the player.
//Vector2 a_vPlayerPos = The position of the player.
void Enemy::LookToPlayer(Vector2 a_vPlayerPos)
{
	sSpriteTurret.iRotDeg = GetBearing(vPos, a_vPlayerPos);//Gets the bearing/angle between the player and the enemy.
	RotateSprite(sSpriteTurret.iSpriteID, DegreesToRadians((sSpriteTurret.iRotDeg) - 90));//Rotates the turret to that angle.
	UG::MoveSprite(sSpriteTurret.iSpriteID, vPos.GetdX() + fTileWidth / 2, vPos.GetdY() + fTileWidth / 2);//Moves the turret to the position of the tank.
}

void Enemy::Reset(Vector2 a_fStartPos)
{
	BulletArray[0].Reset(BulletArray);
	BulletArray[0].UpdateBullets(BulletArray, iEnemyCollisionMap);
	vPos = a_fStartPos;
	UG::MoveSprite(iSpriteID, vPos.GetdX(), vPos.GetdY());
	oPathFinder.bInitialisedStart = false;
	bIsRotating = true;
	bIsTravelling = false;
	fLerpPosition = 0;
}