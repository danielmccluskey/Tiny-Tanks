#include "UGFW.h"
#include "Enumerations.h"
#include <iostream>
#include <sstream>
#include <iomanip>

//Screen sizes
int iScreenWidth = 1280;
int iScreenHeight = 720;

//Co-ords of the Center of the screen
float fCenterX = iScreenWidth*0.5f;
float fCenterY = iScreenHeight*0.5f;

int main(int argv, char* argc[])
{
	
	if (UG::Create(iScreenWidth, iScreenHeight, false, "Pong", 100, 100))
	{
		
		UG::SetBackgroundColor(UG::SColour(0x2A, 0x57, 0x66, 0xFF));
		UG::AddFont("./fonts/invaders.fnt");
		
		int iSpriteID = UG::CreateSprite("./imagesball.png", 100, 100, true);//Create the sprite
		UG::DrawSprite(iSpriteID);	//Draws it
		UG::MoveSprite(iSpriteID, fCenterX, fCenterY); //Moves Pacman to starting Position


		do 
		{
			
			UG::ClearScreen();			
			UG::SetFont(nullptr);

		} while (UG::Process());

		UG::Dispose();


	}
	return 0;
}

