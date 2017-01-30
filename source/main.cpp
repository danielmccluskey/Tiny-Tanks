#include "UGFW.h"
#include "Enumerations.h"
#include "Vector2.h"
//#include <iostream>
//#include <sstream>
//#include <iomanip>

//Screen sizes
int iScreenWidth = 1280;
int iScreenHeight = 720;

//Co-ords of the Center of the screen
float fCenterX = iScreenWidth*0.5f;
float fCenterY = iScreenHeight*0.5f;

struct Tank
{
	Tank()
	{
		iSpriteID = UG::CreateSprite("./images/ball.png", 100, 100, true);//Create the sprite
		UG::DrawSprite(iSpriteID);	//Draws it
		pos.dX = fCenterX;
		pos.dY = fCenterY;
	};
	int iSpriteID = 0;
	Vector2 pos;
	
};

int iSpeed = 1;



int main(int argv, char* argc[])
{

	if (UG::Create(iScreenWidth, iScreenHeight, false, "Pong", 100, 100))
	{

		UG::SetBackgroundColor(UG::SColour(0x2A, 0x57, 0x66, 0xFF));
		UG::AddFont("./fonts/invaders.fnt");

		Tank newTank;
		
		
		do
		{
			if (UG::IsKeyDown(UG::KEY_W))
			{
				newTank.pos += Vector2(0.0f, iSpeed);
			}

			UG::MoveSprite(newTank.iSpriteID, newTank.pos.dX, newTank.pos.dY);

			UG::ClearScreen();
			UG::SetFont(nullptr);

		} while (UG::Process());

		UG::Dispose();


	}
	return 0;
}

