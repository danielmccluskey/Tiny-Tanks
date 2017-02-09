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
struct Turret
{
	Turret()
	{
		iSpriteID = UG::CreateSprite("./images/Tanks/temp.png", 10, 80, true);//Create the sprite
		UG::DrawSprite(iSpriteID);	//Draws it
		pos.dX = fCenterX;
		pos.dY = fCenterY;
	};
	int iSpriteID = 0;
	int iRotDeg = 0;
	Vector2 pos;


};
struct Tank
{
	Tank()
	{
		iSpriteID = UG::CreateSprite("./images/Tanks/temp.png", 32, 64, true);//Create the sprite
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
		Turret newTurret;
		MapGenerator *MapGen = new MapGenerator[384];
		MapGen[0].LoadLevel("./maps/lvl_1.txt", MapGen);

		do
		{
			if (UG::IsKeyDown(UG::KEY_W))
			{
				newTank.pos += DANM::GetForwardVector(newTank.iRotDeg);
			}
			if (UG::IsKeyDown(UG::KEY_S))
			{
				newTank.pos -= DANM::GetForwardVector(newTank.iRotDeg);
			}
			if (UG::IsKeyDown(UG::KEY_D))
			{
				newTank.iRotDeg -= 1;
			}
			if (UG::IsKeyDown(UG::KEY_A))
			{
				newTank.iRotDeg += 1;					
			}
			DANM::SetRotationDeg(-(newTank.iRotDeg), newTank.iSpriteID);
			newTurret.pos = newTank.pos;
			UG::MoveSprite(newTank.iSpriteID, newTank.pos.dX, newTank.pos.dY);
			UG::MoveSprite(newTurret.iSpriteID, newTank.pos.dX, newTank.pos.dY);

			Vector2 mousePos;
			UG::GetMousePos(mousePos.dX, mousePos.dY);

			
			
			DANM::SetRotationRad(-(DANM::GetBearingRad(newTurret.pos, mousePos)), newTurret.iSpriteID);
			UG::ClearScreen();
			UG::SetFont(nullptr);

		} while (UG::Process());

		MapGen[0].UnLoadLevel(MapGen);
		delete[] MapGen;
		UG::Dispose();

		


	}
	return 0;
}

