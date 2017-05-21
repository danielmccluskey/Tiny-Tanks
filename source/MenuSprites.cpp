#include "MenuSprites.h"
#include "UGFW.h"
#include "MathUtil.h"
#include "CustomEnum.h"

MenuSprite::MenuSprite(Vector2 a_vStartPos, Vector2 a_vSize, int iLayer, char* a_pcImagePath,float a_fUV[2][4], bool a_bDrawSprite)
{
	iSpriteHeight = a_vSize.GetdY();
	iSpriteWidth = a_vSize.GetdX();
	iSpriteID = UG::CreateSprite(a_pcImagePath, iSpriteWidth, iSpriteHeight, true);
	UG::SetSpriteUVCoordinates(iSpriteID, a_fUV[0]);
	UG::SetSpriteLayer(iSpriteID, iLayer);
	vPos = a_vStartPos;
	UG::MoveSprite(iSpriteID, vPos.GetdX(), vPos.GetdY());	
	
	bBeingDrawn = false;
	bLerpLoop = true;
	fLerpPosition = 0;


	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			fUVCoords[y][x] = a_fUV[y][x];
		}
	}

	if (a_bDrawSprite)
	{
		DrawSprite();
	}	
}

MenuSprite::~MenuSprite()
{
	HideSprite();
	UG::DestroySprite(iSpriteID);
}

void MenuSprite::DrawSprite()
{
	if (bBeingDrawn)
	{
		return;
	}
	else
	{
		bBeingDrawn = true;
		UG::DrawSprite(iSpriteID);
		return;
	}
}
void MenuSprite::HideSprite()
{
	if (bBeingDrawn)
	{
		bBeingDrawn = false;
		UG::StopDrawingSprite(iSpriteID);
		return;
	}
	else
	{
		return;
	}
}

void MenuSprite::RotateSprite(float a_fDeg)
{
	UG::RotateSprite(iSpriteID, a_fDeg);
}

void MenuSprite::ThrobSprite(float a_fSpeed, float a_fSizeReduction)
{
	if (bLerpLoop)
	{
		fLerpPosition += a_fSpeed;
	}
	else
	{
		fLerpPosition -= a_fSpeed;
	}

	if (fLerpPosition >= 1)
	{
		bLerpLoop = false;
	}
	if (fLerpPosition <= 0)
	{
		bLerpLoop = true;
	}
	float fScaleX = Lerp(iSpriteWidth * a_fSizeReduction, iSpriteWidth, fLerpPosition);
	float fScaleY = Lerp(iSpriteHeight * a_fSizeReduction, iSpriteHeight, fLerpPosition);
	UG::SetSpriteScale(iSpriteID, fScaleX, fScaleY);
}

bool MenuSprite::CheckClick()
{
	UG::SetSpriteUVCoordinates(iSpriteID, fUVCoords[0]);
	Vector2 vMousePos;
	double iMouseX, iMouseY;
	UG::GetMousePos(iMouseX, iMouseY);//Gets the mouse position and stores it in the class members variable.
	vMousePos.SetdX(iMouseX);
	vMousePos.SetdY((iMapHeight * fTileWidth) - iMouseY);//Reverses the Y-Value given from UG::GetMousePos since it returns Y=0 at the top instead of the bottom.
	if (CheckCollision(vMousePos))
	{
		UG::SetSpriteUVCoordinates(iSpriteID, fUVCoords[1]);
		if (UG::GetMouseButtonDown(0))
		{
			return true;
		}
	}
	
	return false;
}

bool MenuSprite::CheckCollision(Vector2 a_vMousePos)
{
	if (a_vMousePos.GetdX()  < (vPos.GetdX() - (iSpriteWidth / 2)))
	{
		return false;
	}
	else if (a_vMousePos.GetdX()  > (vPos.GetdX() + (iSpriteWidth / 2)))
	{
		return false;
	}
	else if (a_vMousePos.GetdY() < (vPos.GetdY() - (iSpriteHeight / 2)))
	{
		return false;
	}
	else if (a_vMousePos.GetdY() > (vPos.GetdY() + (iSpriteHeight / 2)))
	{
		return false;
	}

	return true;
}