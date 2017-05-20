#include "Boundaries.h"
#include "UGFW.h"
#include "MathUtil.h"

//Function to return the Width of a given sprite.
//Equation from Stack overflow - http://stackoverflow.com/a/6657768
float Boundaries::GetSpriteWidth(int a_iSpriteWidth, int a_iSpriteHeight, float a_fRad)
{
	return ((a_iSpriteWidth * abs(cos(a_fRad))) + (a_iSpriteHeight * abs(sin(a_fRad))));
}
//Function to return the height of a given sprite.
//Equation from Stack overflow - http://stackoverflow.com/a/6657768
float Boundaries::GetSpriteHeight(int a_iSpriteWidth, int a_iSpriteHeight, float a_fRad)
{
	return ((a_iSpriteWidth * abs(sin(a_fRad))) + (a_iSpriteHeight * abs(cos(a_fRad))));
}
//Function to Get just the Xpos of a sprite.
//Used from Daniel Budworth-Mead's UGFW++ linked on the Facebook group http://pastebin.com/fHGNgjrL
float Boundaries::GetSpriteXPos(int a_uiSpriteID)
{
	UG::GetSpriteMatrix(a_uiSpriteID, fUGSpriteMatrix);
	return fUGSpriteMatrix[12];
}
//Function to Get just the Ypos of a sprite.
//Used from Daniel Budworth-Mead's UGFW++ linked on the Facebook group http://pastebin.com/fHGNgjrL
float Boundaries::GetSpriteYPos(int a_uiSpriteID)
{
	UG::GetSpriteMatrix(a_uiSpriteID, fUGSpriteMatrix);
	return fUGSpriteMatrix[13];
}

void Boundaries::AABB(int a_iSpriteID, int a_iHeight, int a_iWidth, float a_fRad)
{
	Vector3 vPos = Vector3(GetSpriteXPos(a_iSpriteID), GetSpriteYPos(a_iSpriteID),0);
	float fWidth = GetSpriteWidth(a_iWidth, a_iHeight, a_fRad);
	float fHeight = GetSpriteHeight(a_iWidth, a_iHeight, a_fRad);
	vTopLeft = Vector3(
		(vPos.dX - (fWidth) / 2),
		(vPos.dY + (fHeight) / 2),
		0
	);
	vTopRight = Vector3(
		(vPos.dX + (fWidth) / 2),
		(vPos.dY + (fHeight) / 2),
		0
	);
	vBotLeft = Vector3(
		(vPos.dX - (fWidth) / 2),
		(vPos.dY - (fHeight) / 2),
		0
	);
	vBotRight = Vector3(
		(vPos.dX + (fWidth) / 2),
		(vPos.dY - (fHeight) / 2),
		0
	);
	vFront = Vector3(
		(vPos.dX) + cos(-a_fRad - fHALF_PI) * a_iWidth/2,
		(vPos.dY) + sin(-a_fRad - fHALF_PI) * a_iHeight/2,
		0
	);

}