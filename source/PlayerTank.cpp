//==============================================================================================================================
// Project: WiiTanks
// File: Bullet.h
// Author: Daniel McCluskey
// Date Created: 07/01/17
// Brief: This is the file that controls player movement and collision. Bullets and powerups too.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#include "PlayerTank.h"
#include "CustomEnum.h"
#include "Enumerations.h"
#include "UGFW.h"
#include "MathUtil.h"
#include "Matrix4x4.h"
#include "Boundaries.h"
#include <iostream>
#include <fstream>

//Simple function to return the position of the tank.
Vector2 PlayerTank::GetPos()
{
	return vPos;
}

//Simple function to return the sprite id of the tank
int PlayerTank::GetSpriteID()
{
	return iSpriteID;
}

//Constructor
//float a_fCenterX = Spawn Position X
//float a_fCenterY = Spawn Position Y
//float A_fGlobalSpeed = Speed of the tank
PlayerTank::PlayerTank(float a_fCenterX, float a_fCenterY, float a_fGlobalSpeed)
	: sSpriteTurret("./images/Tanks/tank_turret.png")//Constructor for the turret
{
	CreateTank(a_fCenterX, a_fCenterY);//Creates the tank
	fSpeed = a_fGlobalSpeed;//Sets the speed to the global speed.
}

//Function to spawn a player tank.
//float a_fCenterX = Spawn Position X
//float a_fCenterY = Spawn Position Y
void PlayerTank::CreateTank(float a_fCenterX, float a_fCenterY)
{
	iSpriteID = UG::CreateSprite("./images/Tanks/tank_body.png", iSpriteWidth, iSpriteHeight, true);//Create the sprite
	UG::DrawSprite(iSpriteID);//Draws it
	vPos = Vector2(a_fCenterX, a_fCenterY);//Sets the Starting position ########Convert to function arguement input.
	UG::MoveSprite(iSpriteID, a_fCenterX, a_fCenterY);//Moves sprite to starting position.
	UG::SetSpriteLayer(iSpriteID, 9);//Makes sure the tank is drawn above the map.
	UpdateCollisionMap();//Updates the collision map
	fWallSlideSlow = 0.3f;//Sets how slow the player should slide against walls.
	pPowerUpArray[0].SetTankID(iSpriteID);//Lets the power up array know what to collide against.
};

//Desconstructor
PlayerTank::~PlayerTank()
{
	UG::StopDrawingSprite(iSpriteID);
	UG::DestroySprite(iSpriteID);
	UG::StopDrawingSprite(sSpriteTurret.iSpriteID);
	UG::DestroySprite(sSpriteTurret.iSpriteID);
}

//Function to handle the movement of the tank.
//int a_iEnemySpriteID = The SpriteID of the enemy tank, will be changed to array in future to allow for multiple enemies
bool PlayerTank::MoveTank(int a_iEnemySpriteID)
{
	//Handles mouse clicks so that a single click is not carried to the next frame.
	if (UG::GetMouseButtonDown(0))//If the mouse button is down.
	{
		iTankMouseState = true;//Current mouse state

	}
	if (UG::GetMouseButtonReleased(0))//If the player releases the mouse
	{
		iTankMouseState = false;//Current state
		iTankLastMouseState = false;//Last state
	}


	int iCollidedSprite = pPowerUpArray[0].SpawnPowerUps(pPowerUpArray, iSpriteID, iSpriteWidth, iSpriteHeight, iRotDeg);//Spawns powerups and stores the returned value if the player collides with one.
	if (iCollidedSprite == 0)//Missile
	{		
		BulletArray[0].AddBullet(1);//Give the player a missile.
	}
	else if (iCollidedSprite == 1)//Mine
	{
		BulletArray[0].AddBullet(2);//Give the player a mine.
	}
	
	if ((iTankMouseState == true && iTankLastMouseState == false))//If the player has clicked
	{
		BulletArray[0].CreateBullet(BulletArray, vPos, vMousePos, 0);//Create a bullet
	}
	if (UG::IsKeyDown(UG::KEY_1))//If the user clicks 1
	{
		BulletArray[0].CreateBullet(BulletArray, vPos, vMousePos, 1);//Create a missile.
	}
	if (UG::IsKeyDown(UG::KEY_2))//If the user clicks 2
	{
		BulletArray[0].CreateBullet(BulletArray, vPos, vMousePos, 2);//Create a mine.
	}

	BulletArray[0].UpdateBullets(BulletArray, iCollisionMap);//Moves and destroys bullets



	if (UG::IsKeyDown(UG::KEY_A))//If the A key is down
	{
		iRotDeg -= 1;//Rotate the sprite Anti clockwise
	}
	if (UG::IsKeyDown(UG::KEY_D))//If the D Key is down.
	{
		iRotDeg += 1;//Rotate the sprite clockwise.
	}

	if (iRotDeg >= 360)//If the rotation value is greater than 359.
	{
		iRotDeg = 0;//Sets the rotation value back to 0.
	}
	else if (iRotDeg < 0)//If the rotation value is less than 0.
	{
		iRotDeg = 359;//Set the rotation back to 359.
	}

	double iMouseX, iMouseY;
	UG::GetMousePos(iMouseX, iMouseY);//Gets the mouse position and stores it in the class members variable.
	vMousePos.SetdX(iMouseX);
	vMousePos.SetdY((iMapHeight * fTileWidth) - iMouseY);//Reverses the Y-Value given from UG::GetMousePos since it returns Y=0 at the top instead of the bottom.
	
	sSpriteTurret.iRotDeg = GetBearing(vPos, vMousePos);//Gets the angle between the mouse and the player.

	vVelocity = vVelocity.RotateX(-iRotDeg + 90);//Calculates the velocity.

	float fDeltaTime = UG::GetDeltaTime();//Get delta
	vVelocity.SetdX((vVelocity.GetdX() * fDeltaTime) * fSpeed);//Set Velocity *speed
	vVelocity.SetdY((vVelocity.GetdY() * fDeltaTime) * fSpeed);//Set Velocity *speed

	
	RotateSprite(iSpriteID, DegreesToRadians(-iRotDeg));//Rotates the sprite
	RotateSprite(sSpriteTurret.iSpriteID, DegreesToRadians((sSpriteTurret.iRotDeg)-90));//Rotates the turret to the mouse

	UG::MoveSprite(iSpriteID, vPos.GetdX(), vPos.GetdY());//Moves the tank
	UG::MoveSprite(sSpriteTurret.iSpriteID, vPos.GetdX(), vPos.GetdY());//Moves the turret to the tank

	if (iTankMouseState == true && iTankLastMouseState == false)//Reset click
	{
		iTankLastMouseState = true;
	}
	
	if (BulletArray[0].SpriteCollide(BulletArray, a_iEnemySpriteID, iSpriteWidth, iSpriteHeight, vPos, iRotDeg))//If the Enemy has collided with one of the players bullets.
	{
		return true;
	}
	BulletArray[0].DrawBulletCount();//Draws the amount of each bullets the player has on screen.
	return false;
}

//Function to detect if a point is colliding with a tile and if so, what side of the tile.
//Also handles cross product sliding on collision
//Vector3 a_vPos = The point being checked.
bool PlayerTank::CollisionDetection(Vector3 a_vPos)
{

	//Below converts the X + Y to the exact tile position for more accurate collisions.
	int a_iX = (a_vPos.GetdX() / fTileWidth);
	int a_iY = (a_vPos.GetdY() / fTileWidth);
	int iTileX = a_iX * fTileWidth;
	int iTileY = a_iY * fTileWidth;

	
	int iCount = 0;//Counts the amount of sides it has collided with.,

	//Top Collision
	if ((vLastPos.GetdY() > (iTileY + fTileWidth)) && (vLastPos.GetdX() < (iTileX + fTileWidth)) && (vLastPos.GetdX() > iTileX))//If the last position of the bullet is ABOVE the top edge of the tile.
	{
		vNormalPlane = Vector2(0, 1);//Sets the normal plane to a Up Vector
		++iCount;
	}
	//Bottom Collision
	if ((vLastPos.GetdY() < iTileY) && (vLastPos.GetdX() < (iTileX + fTileWidth)) && (vLastPos.GetdX() > iTileX))//If the last position of the bullet is BELOW the bottom edge of the tile.
	{
		vNormalPlane = Vector2(0, 1);//Sets the normal plane to a Up Vector
		++iCount;
	}
	//Right Collision
	if ((vLastPos.GetdX() > (iTileX + fTileWidth)) && (vLastPos.GetdY() < (iTileY + fTileWidth)) && (vLastPos.GetdY() > iTileY))//If the last position of the bullet is to the RIGHT of the Right edge of the tile.
	{
		vNormalPlane = Vector2(1, 0);//Sets the normal plane to a side Vector
		++iCount;
	}
	//Left Collision
	if ((vLastPos.GetdX() < iTileX) && (vLastPos.GetdY() < (iTileY + fTileWidth)) && (vLastPos.GetdY() > iTileY))//If the last position of the bullet is to the Left of the Left edge of the tile.
	{
		vNormalPlane = Vector2(1, 0);//Sets the normal plane to a side Vector
		++iCount;
	}

	
	if (a_vPos.GetdX() < (iTileX - (fTileWidth / 2)))//If the point is to the left of the tile.
	{
		return false;
	}

	if (a_vPos.GetdX() > (iTileX + (fTileWidth / 2)))//If the point is to the right of the tile.
	{
		return false;
	}

	if (a_vPos.GetdY() < (iTileY - (fTileWidth / 2)))//If the point is to the bottom of the tile.
	{
		return false;
	}

	if (a_vPos.GetdY() > (iTileY + (fTileWidth / 2)))//If the point is to the top of the tile.
	{
		return false;
	}
	else//If the point is inside the tile.
	{
		return true;
	}





}

//Function to get the position of each corner of the sprite depending on its rotation, then does a collision check on each point.
void PlayerTank::CalculateBoundaries()
{
	Boundaries sSATCheck;
	sSATCheck.SeparatingAxisTheorem(iSpriteID, iSpriteHeight, iSpriteWidth, DegreesToRadians((iRotDeg-90)));//Gets the positions of the corners of the sprite.

	sSATCheck.vFrontLeft.SetdZ(GetTile(fTileWidth, sSATCheck.vFrontLeft));//Checks what tile that point is on.
	sSATCheck.vFrontRight.SetdZ(GetTile(fTileWidth, sSATCheck.vFrontRight));//Checks what tile that point is on.
	sSATCheck.vBackLeft.SetdZ(GetTile(fTileWidth, sSATCheck.vBackLeft));//Checks what tile that point is on.
	sSATCheck.vBackRight.SetdZ(GetTile(fTileWidth, sSATCheck.vBackRight));//Checks what tile that point is on.

	if (UG::IsKeyDown(UG::KEY_W))//If the player is moving forwards.
	{
		if (sSATCheck.vFrontLeft.GetdZ() == 1 && sSATCheck.vFrontRight.GetdZ() == 1)//If the two front corners are both colliding
		{
			vNormalPlane = Vector2(0, 0);//Stop the tank since they are hitting a wall head on.
		}
		else if (sSATCheck.vFrontLeft.GetdZ() == 1)//If only left front corner is colliding
		{
			CollisionDetection(sSATCheck.vFrontLeft);
			vPos += (vVelocity.CrossProduct(vNormalPlane)) * fWallSlideSlow;//Add the Cross product of the Velocity and the normal plane to make the tank slide against the wall.
		}
		else if (sSATCheck.vFrontRight.GetdZ() == 1)//If only right front corner is colliding
		{
			CollisionDetection(sSATCheck.vFrontRight);//Get the normal plane
 
			vPos += (vVelocity.CrossProduct(vNormalPlane)) * fWallSlideSlow;//Add the Cross product of the Velocity and the normal plane to make the tank slide against the wall.
		}
		else//IF there are no collisions.
		{
			vLastPos = vPos;//Last pos = current pos
			vPos += vVelocity;//Add the velocity to the position
		}
	
	}

	if (UG::IsKeyDown(UG::KEY_S)) // If the player is moving backwards
	{
		if (sSATCheck.vFrontLeft.GetdZ() == 1 && sSATCheck.vFrontRight.GetdZ() == 1)//If the two back corners are both colliding
		{
			vNormalPlane = Vector2(0, 0);//Stop the tank since they are hitting a wall head on.
		}
		else if (sSATCheck.vBackLeft.GetdZ() == 1)//If only left back corner is colliding
		{
			CollisionDetection(sSATCheck.vBackLeft);//Get the normal plane
			vPos -= (vVelocity.CrossProduct(vNormalPlane)) * fWallSlideSlow;//Add the Cross product of the Velocity and the normal plane to make the tank slide against the wall.
		}
		else if (sSATCheck.vBackRight.GetdZ() == 1)//If only left back corner is colliding
		{
			CollisionDetection(sSATCheck.vBackRight);//Get the normal plane
			vPos -= (vVelocity.CrossProduct(vNormalPlane)) * fWallSlideSlow;//Add the Cross product of the Velocity and the normal plane to make the tank slide against the wall.
		}
		else
		{
			vLastPos = vPos;//Last pos = current pos
			vPos -= vVelocity;//Add the velocity to the position
		}

	}	
}

//Sets the sprite rotation to an exact value, used over UG::SetSpriteRotation since that increments the rotation instead of setting it.
//int a_iSpriteID = SpriteID of the sprite you want to rotate.
//float a_fRad = The amount to rotate it in radians.
void PlayerTank::RotateSprite(int a_iSpriteID, float a_fRad)
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
float PlayerTank::GetBearing(Vector2 &a_V1, Vector2 &a_V2)
{
	float fXChange = (a_V1.GetdX() - a_V2.GetdX());
	float fYChange = (a_V1.GetdY() - a_V2.GetdY());
	return atan2(fYChange, fXChange)*(180 / fPI);
}

//Updates the Collision map for the powerups and the player.
void PlayerTank::UpdateCollisionMap()
{
	std::ifstream pCollision;//Creates an input fstream member
	pCollision.open("./maps/currentCollision.txt");//Opens the file.
	for (int i = 0; i < (iMapHeight*iMapWidth); i++)//Iterates through each tile in the array.
	{
		pCollision >> iCollisionMap[i];//Stores current tile type into array.
	}
	pCollision.close();

	pPowerUpArray[0].UpdateCollisionMap();//Updates the collisions for the Power ups.
}

//Gets the tile from the collision map array with the given co-ordinates.
//int a_iTileWidth = Width of a map tile
//Vector2 a_vPos = The Position to check.
int PlayerTank::GetTile(int a_iTileWidth, Vector2 a_vPos)
{
	int a_iX = (a_vPos.GetdX() / a_iTileWidth);
	int a_iY = (a_vPos.GetdY() / a_iTileWidth);

	return iCollisionMap[(a_iY * iMapWidth) + a_iX];
}

//Gets the tile from the collision map array with the given co-ordinates.
//int a_iTileWidth = Width of a map tile
//Vector3 a_vPos = The Position to check.
int PlayerTank::GetTile(int a_iTileWidth, Vector3 a_vPos)
{
	int a_iX = (a_vPos.GetdX() / a_iTileWidth);
	int a_iY = (a_vPos.GetdY() / a_iTileWidth);

	return iCollisionMap[(a_iY * iMapWidth) + a_iX];
}

//Resets the players tank and bullets for next level use.
//Vector2 a_vStartPos = The position to move the tank to.
void PlayerTank::Reset(Vector2 a_vStartPos)
{
	BulletArray[0].Reset(BulletArray);//Resets the bullet array
	pPowerUpArray[0].Reset(pPowerUpArray);//Resets the powerup array
	vPos = a_vStartPos;//Sets the position to the starting position
	iRotDeg = 200;//Sets rotation to 200
	RotateSprite(iSpriteID, DegreesToRadians(iRotDeg));//Rotates the sprite
	UG::MoveSprite(iSpriteID, vPos.GetdX(), vPos.GetdY());//Moves the sprite
	UG::MoveSprite(sSpriteTurret.iSpriteID, vPos.GetdX() + fTileWidth/2, vPos.GetdY()+fTileWidth/2);//Moves the turret
}