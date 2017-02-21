#include "Enumerations.h"
#include "MathUtil.h"
#include "MapGenerator.h"
#include "PlayerTank.h"
#include "stdlib.h"
#include <iostream>
//#include <iostream>
//#include <sstream>
//#include <iomanip>

//Screen sizes
int iScreenWidth = 768;
int iScreenHeight = 512;

//Co-ords of the Center of the screen
float fCenterX = iScreenWidth*0.5f;
float fCenterY = iScreenHeight*0.5f;


struct Bullet
{
	Bullet()
	{
		iSpriteID = UG::CreateSprite("./images/Tanks/temp.png", 10, 10, true);//Create the sprite
		UG::DrawSprite(iSpriteID);	//Draws it
		pos = Vector2(0, 0);
		Velocity = Vector2(0,0);
	};
	int iSpriteID = 0;
	Vector2 pos;
	Vector2 Velocity;
};



int iSpeed = 1;
PlayerTank RayCastTest;



int main(int argv, char* argc[])
{

	if (UG::Create(iScreenWidth, iScreenHeight, false, "Wii Tanks", 100, 100))
	{

		UG::SetBackgroundColor(UG::SColour(0x2A, 0x57, 0x66, 0xFF));
		UG::AddFont("./fonts/invaders.fnt");

		
		




		
		MapGenerator *MapGen = new MapGenerator[384];
		MapGen[0].LoadLevel("./maps/lvl_4.txt", MapGen);


		PlayerTank newTank;
		newTank.CreateTank(fCenterX, fCenterY);
		Turret newTurret;

		Bullet newBullet;
		Bullet newBullet1;
		Bullet newBullet2;
		Bullet newBullet3;
		Bullet newBullet4;
		Bullet newBullet5;

		newTank.UpdateCollisionMap();
		RayCastTest.UpdateCollisionMap();

		int ayiSpriteID = UG::CreateSprite("./images/Tanks/tank_turret.png", 30, 80, true);//Create the sprite
		UG::DrawSprite(ayiSpriteID);	//Draws it
		UG::MoveSprite(ayiSpriteID, fCenterX, fCenterY);

		do
		{
			newTank.MoveTank();

			Vector2 mousePos;//New Vector2 to hold Mouse position.
			UG::GetMousePos(mousePos.dX, mousePos.dY);//Gets the mouse position.
			mousePos.dY = iScreenHeight - mousePos.dY;//Reverses the Y-Value given from UG::GetMousePos since it returns Y=0 at the top instead of the bottom.
			
			float ayyy[16];
			UG::GetSpriteMatrix(newTank.sTurret.iSpriteID, ayyy);
			

			

			

			if (UG::GetMouseButtonDown(0))
			{
				
				newBullet.Velocity = DANM::GetForwardVector((DANM::GetBearingDeg(newTank.pos, mousePos)) + 180);
				newBullet.pos = newTank.pos;
				newBullet.pos += Vector2(newBullet.Velocity.dX * 40, newBullet.Velocity.dY * 40);
 
			}

			DANM::SetRotationDeg(-(DANM::GetBearingDeg(newTank.pos, mousePos))+90, newTank.sTurret.iSpriteID);

			newBullet.pos += newBullet.Velocity;
			UG::MoveSprite(newBullet.iSpriteID, newBullet.pos.dX, newBullet.pos.dY);

			newTank.GetSurroundingTiles(MapGen[0].iTileWidth);

			




			





			UG::ClearScreen();
			UG::SetFont(nullptr);//

		} while (UG::Process());

		MapGen[0].UnLoadLevel(MapGen);
		delete[] MapGen;
		UG::Dispose();

		


	}
	return 0;
}
