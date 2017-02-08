#include "UGFW.h"
#include "Enumerations.h"
#include "MathUtil.h"
#include "MapGenerator.h"
//#include <iostream>
//#include <sstream>
//#include <iomanip>

//Screen sizes
int iScreenWidth = 768;
int iScreenHeight = 512;

//Co-ords of the Center of the screen
float fCenterX = iScreenWidth*0.5f;
float fCenterY = iScreenHeight*0.5f;

struct Tank
{
	Tank()
	{
		iSpriteID = UG::CreateSprite("./images/Tanks/temp.png", 64, 32, true);//Create the sprite
		UG::DrawSprite(iSpriteID);	//Draws it
		pos.dX = fCenterX;
		pos.dY = fCenterY;
	};
	int iSpriteID = 0;
	int iRotDeg = 0;
	Vector2 pos;
	
};

int iSpeed = 1;



int main(int argv, char* argc[])
{

	if (UG::Create(iScreenWidth, iScreenHeight, false, "Wii Tanks", 100, 100))
	{

		UG::SetBackgroundColor(UG::SColour(0x2A, 0x57, 0x66, 0xFF));
		UG::AddFont("./fonts/invaders.fnt");

		Tank newTank;
		MapGenerator *MapGen = new MapGenerator[384];
		MapGen[0].LoadLevel("./maps/lvl_1.txt", MapGen);

		do
		{
			if (UG::IsKeyDown(UG::KEY_W))
			{
				newTank.pos += GetForwardVector(newTank.iRotDeg);				
			}
			if (UG::IsKeyDown(UG::KEY_S))
			{
				newTank.pos -= GetForwardVector(newTank.iRotDeg);
			}
			if (UG::IsKeyDown(UG::KEY_D))
			{
				UG::RotateSprite(newTank.iSpriteID, -1);
				newTank.iRotDeg -= 1;
			}
			if (UG::IsKeyDown(UG::KEY_A))
			{
				UG::RotateSprite(newTank.iSpriteID, 1);
				newTank.iRotDeg += 1;				
			}

			UG::MoveSprite(newTank.iSpriteID, newTank.pos.dX, newTank.pos.dY);


			static float spriteArray[16];
			UG::GetSpriteMatrix(newTank.iSpriteID, spriteArray);


			UG::ClearScreen();
			UG::SetFont(nullptr);

		} while (UG::Process());

		MapGen[0].UnLoadLevel(MapGen);
		delete[] MapGen;
		UG::Dispose();

		


	}
	return 0;
}

