#include "PlayerTank.h"
#include "CustomEnum.h"
#include "Enumerations.h"
#include "UGFW.h"
#include "MathUtil.h"
#include "Matrix4x4.h"
#include "Boundaries.h"
#include <iostream>
#include <fstream>


int TEMPSPRITEID;

PlayerTank::PlayerTank(float a_fCenterX, float a_fCenterY, float a_fGlobalSpeed)
{
	CreateTank(a_fCenterX, a_fCenterY);
	fSpeed = a_fGlobalSpeed;
}
void PlayerTank::CreateTank(float a_fCenterX, float a_fCenterY)
{

	iSpriteID = UG::CreateSprite("./images/Tanks/tank_body.png", iSpriteWidth, iSpriteHeight, true);//Create the sprite
	UG::DrawSprite(iSpriteID);//Draws it
	vPos = Vector2(a_fCenterX, a_fCenterY);//Sets the Starting position ########Convert to function arguement input.
	UG::MoveSprite(iSpriteID, a_fCenterX, a_fCenterY);//Moves sprite to starting position.
	UG::SetSpriteLayer(iSpriteID, 9);//Makes sure the tank is drawn above the map.
	UpdateCollisionMap();
	fWallSlideSlow = 0.3f;
};


PlayerTank::~PlayerTank()
{
	UG::StopDrawingSprite(iSpriteID);
	UG::DestroySprite(iSpriteID);
	UG::StopDrawingSprite(sSpriteTurret.iSpriteID);
	UG::DestroySprite(sSpriteTurret.iSpriteID);
}


//Function to handle the movement of the tank.
void PlayerTank::MoveTank()
{
	


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
	
	UG::GetMousePos(vMousePos.dX, vMousePos.dY);//Gets the mouse position and stores it in the class members variable.
	vMousePos.dY = (iMapHeight * fTileWidth) - vMousePos.dY;//Reverses the Y-Value given from UG::GetMousePos since it returns Y=0 at the top instead of the bottom.
	sSpriteTurret.iRotDeg = GetBearing(vPos, vMousePos);

	vVelocity = vVelocity.RotateX(-iRotDeg + 90);//Calculates the velocity.

	float fDeltaTime = UG::GetDeltaTime();
	vVelocity.dX = (vVelocity.dX * fDeltaTime) * fSpeed;
	vVelocity.dY = (vVelocity.dY * fDeltaTime) * fSpeed;

	
	RotateSprite(iSpriteID, DegreesToRadians(-iRotDeg));
	RotateSprite(sSpriteTurret.iSpriteID, DegreesToRadians((sSpriteTurret.iRotDeg)-90));

	UG::MoveSprite(iSpriteID, vPos.dX, vPos.dY);
	UG::MoveSprite(sSpriteTurret.iSpriteID, vPos.dX, vPos.dY);
	

}

bool PlayerTank::CollisionDetection(Vector3 a_vPos)
{

	int a_iX = (a_vPos.dX / fTileWidth);
	int a_iY = (a_vPos.dY / fTileWidth);
	int iTileX = a_iX * fTileWidth;
	int iTileY = a_iY * fTileWidth;
	int iCount = 0;

	//Top Collision
	if ((vLastPos.dY > (iTileY + fTileWidth)) && (vLastPos.dX < (iTileX + fTileWidth)) && (vLastPos.dX > iTileX))//If the last position of the bullet is ABOVE the top edge of the tile.
	{
		vNormalPlane = Vector2(0, 1);
		++iCount;
	}
	//Bottom Collision
	if ((vLastPos.dY < iTileY) && (vLastPos.dX < (iTileX + fTileWidth)) && (vLastPos.dX > iTileX))//If the last position of the bullet is BELOW the bottom edge of the tile.
	{
		vNormalPlane = Vector2(0, 1);
		++iCount;
	}
	//Right Collision
	if ((vLastPos.dX > (iTileX + fTileWidth)) && (vLastPos.dY < (iTileY + fTileWidth)) && (vLastPos.dY > iTileY))//If the last position of the bullet is to the RIGHT of the Right edge of the tile.
	{
		vNormalPlane = Vector2(1, 0);
		++iCount;
	}
	//Left Collision
	if ((vLastPos.dX < iTileX) && (vLastPos.dY < (iTileY + fTileWidth)) && (vLastPos.dY > iTileY))//If the last position of the bullet is to the Left of the Left edge of the tile.
	{
		vNormalPlane = Vector2(1, 0);
		++iCount;
	}





	if (a_vPos.dX < (iTileX - (fTileWidth / 2)))
	{
		return false;
	}

	if (a_vPos.dX > (iTileX + (fTileWidth / 2)))
	{
		return false;
	}

	if (a_vPos.dY < (iTileY - (fTileWidth / 2)))
	{
		return false;
	}

	if (a_vPos.dY > (iTileY + (fTileWidth / 2)))
	{
		return false;
	}
	else
	{
		return true;
	}





}

void PlayerTank::CalculateBoundaries()
{
	Boundaries sSATCheck;
	sSATCheck.SeparatingAxisTheorem(iSpriteID, iSpriteHeight, iSpriteWidth, DegreesToRadians((iRotDeg-90)));

	sSATCheck.vFrontLeft.dZ = GetTile(fTileWidth, sSATCheck.vFrontLeft);
	sSATCheck.vFrontRight.dZ = GetTile(fTileWidth, sSATCheck.vFrontRight);
	sSATCheck.vBackLeft.dZ = GetTile(fTileWidth, sSATCheck.vBackLeft);
	sSATCheck.vBackRight.dZ = GetTile(fTileWidth, sSATCheck.vBackRight);

	if (UG::IsKeyDown(UG::KEY_W))
	{
		if (sSATCheck.vFrontLeft.dZ == 1 && sSATCheck.vFrontRight.dZ == 1)
		{
			vNormalPlane = Vector2(0, 0);
			std::cout << "AYYYYY: " << vVelocity.dX << std::endl;
		}
		else if (sSATCheck.vFrontLeft.dZ == 1)
		{
			CollisionDetection(sSATCheck.vFrontLeft);
			vPos += (vVelocity.CrossProduct(vNormalPlane)) *= fWallSlideSlow;
		}
		else if (sSATCheck.vFrontRight.dZ == 1)
		{
			CollisionDetection(sSATCheck.vFrontRight);
 
			vPos += (vVelocity.CrossProduct(vNormalPlane)) *= fWallSlideSlow;
		}
		else
		{
			vLastPos = vPos;
			vPos += vVelocity;

			std::cout << "X: " << vVelocity.dX << std::endl;
			std::cout << "Y: " << vVelocity.dY << std::endl << std::endl;
		}
	
	}

	if (UG::IsKeyDown(UG::KEY_S))
	{
		if (sSATCheck.vFrontLeft.dZ == 1 && sSATCheck.vFrontRight.dZ == 1)
		{
			vNormalPlane = Vector2(0, 0);
		}
		else if (sSATCheck.vBackLeft.dZ == 1)
		{
			CollisionDetection(sSATCheck.vBackLeft);
			vPos -= (vVelocity.CrossProduct(vNormalPlane)) *= fWallSlideSlow;
		}
		else if (sSATCheck.vBackRight.dZ == 1)
		{
			CollisionDetection(sSATCheck.vBackRight);

			vPos -= (vVelocity.CrossProduct(vNormalPlane)) *= fWallSlideSlow;
		}
		else
		{
			vLastPos = vPos;
			vPos -= vVelocity;
		}

	}

	

	

	

	
}

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
	float fXChange = (a_V1.dX - a_V2.dX);
	float fYChange = (a_V1.dY - a_V2.dY);
	return atan2(fYChange, fXChange)*(180 / fPI);
}

void PlayerTank::UpdateCollisionMap()
{
	std::ifstream pCollision;//Creates an input fstream member
	pCollision.open("./maps/currentCollision.txt");//Opens the file.
	for (int i = 0; i < (iMapHeight*iMapWidth); i++)//Iterates through each tile in the array.
	{
		pCollision >> iCollisionMap[i];//Stores current tile type into array.
	}
	pCollision.close();
}
int PlayerTank::GetTile(int a_iTileWidth, Vector2 a_vPos)
{
	int a_iX = (a_vPos.dX / a_iTileWidth);
	int a_iY = (a_vPos.dY / a_iTileWidth);

	return iCollisionMap[(a_iY * iMapWidth) + a_iX];
}
int PlayerTank::GetTile(int a_iTileWidth, Vector3 a_vPos)
{
	int a_iX = (a_vPos.dX / a_iTileWidth);
	int a_iY = (a_vPos.dY / a_iTileWidth);

	return iCollisionMap[(a_iY * iMapWidth) + a_iX];
}