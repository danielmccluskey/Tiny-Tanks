#include "PlayerTank.h"
#include "CustomEnum.h"
#include "Enumerations.h"
#include "UGFW.h"
#include "MathUtil.h"
#include "Vector2.h"
#include "Matrix4x4.h"



void PlayerTank::CreateTank(float a_fCenterX, float a_fCenterY)
{
	iSpriteID = UG::CreateSprite("./images/Tanks/tank_body.png", iSpriteWidth, iSpriteHeight, true);//Create the sprite
	UG::DrawSprite(iSpriteID);//Draws it
	vPos = Vector2(a_fCenterX, a_fCenterY);//Sets the Starting position ########Convert to function arguement input.
	UG::MoveSprite(iSpriteID, a_fCenterX, a_fCenterY);//Moves sprite to starting position.
	UG::SetSpriteLayer(iSpriteID, 9);//Makes sure the tank is drawn above the map.
};

//Function to handle the movement of the tank.
void PlayerTank::MoveTank()
{
	//Function that checks the corner positions of the sprite to see if they are colliding with the map
	/*CollisionDetection(0, 90, pTopRight, pBotLeft);
	CollisionDetection(90, 180, pTopLeft, pBotRight);
	CollisionDetection(180, 270, pBotLeft, pTopRight);
	CollisionDetection(270, 359, pBotRight, pTopLeft);*/


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
	if (UG::IsKeyDown(UG::KEY_W))
	{
		vPos += vVelocity;
	}
	if (UG::IsKeyDown(UG::KEY_S))
	{
		vPos -= vVelocity;
	}

	
	RotateSprite(iSpriteID, DegreesToRadians(-iRotDeg));
	RotateSprite(sSpriteTurret.iSpriteID, DegreesToRadians((sSpriteTurret.iRotDeg)-90));

	UG::MoveSprite(iSpriteID, vPos.dX, vPos.dY);
	UG::MoveSprite(sSpriteTurret.iSpriteID, vPos.dX, vPos.dY);

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