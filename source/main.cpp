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
struct Turret
{
	Turret()
	{
		iSpriteID = UG::CreateSprite("./images/Tanks/tank_turret.png", 30, 80, true);//Create the sprite
		UG::DrawSprite(iSpriteID);	//Draws it
		pos.dX = fCenterX;
		pos.dY = fCenterY;
	};
	int iSpriteID = 0;
	int iRotDeg = 0;
	Vector2 pos;


};

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


void test(int a_iSpriteIDStart, int a_iSpriteIDPlayer, Bullet& ayy);

int iSpeed = 1;
PlayerTank RayCastTest;



int main(int argv, char* argc[])
{

	if (UG::Create(iScreenWidth, iScreenHeight, false, "Wii Tanks", 100, 100))
	{

		UG::SetBackgroundColor(UG::SColour(0x2A, 0x57, 0x66, 0xFF));
		UG::AddFont("./fonts/invaders.fnt");

		
		int ayiSpriteID = UG::CreateSprite("./images/Tanks/tank_turret.png", 30, 80, true);//Create the sprite
		UG::DrawSprite(ayiSpriteID);	//Draws it
		UG::MoveSprite(ayiSpriteID, fCenterX, fCenterY);




		
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

		do
		{
			newTank.MoveTank();


			
			newTurret.pos = newTank.pos;
			
			UG::MoveSprite(newTurret.iSpriteID, newTank.pos.dX, newTank.pos.dY);

			Vector2 mousePos;//New Vector2 to hold Mouse position.
			UG::GetMousePos(mousePos.dX, mousePos.dY);//Gets the mouse position.
			mousePos.dY = iScreenHeight - mousePos.dY;//Reverses the Y-Value given from UG::GetMousePos since it returns Y=0 at the top instead of the bottom.

			

			if (UG::GetMouseButtonDown(0))
			{
				
				newBullet.Velocity = DANM::GetForwardVector((DANM::GetBearingDeg(newTurret.pos, mousePos)) + 180);

				newBullet.pos = newTank.pos;
				newBullet.pos += Vector2(newBullet.Velocity.dX * 40, newBullet.Velocity.dY * 40);
 
			}
			
			Vertices Test(newTank.iSpriteID, newTank.iSpriteHeight, newTank.iSpriteWidth, DegreesToRadians(newTank.iRotDeg+90));

			
			test(ayiSpriteID, newTank.iSpriteID, newBullet5);

			UG::MoveSprite(newTank.iSpriteID, newTank.pos.dX, newTank.pos.dY);

			DANM::SetRotationDeg(-(DANM::GetBearingDeg(newTurret.pos, mousePos))+90, newTurret.iSpriteID);

			newBullet.pos += newBullet.Velocity;
			UG::MoveSprite(newBullet.iSpriteID, newBullet.pos.dX, newBullet.pos.dY);

			newTank.GetSurroundingTiles(MapGen[0].iTileWidth);

			UG::MoveSprite(newBullet4.iSpriteID, newTank.pTopLeft.dX, newTank.pTopLeft.dY);
			UG::MoveSprite(newBullet1.iSpriteID, newTank.pTopRight.dX, newTank.pTopRight.dY);
			UG::MoveSprite(newBullet2.iSpriteID, newTank.pBotLeft.dX, newTank.pBotLeft.dY);
			UG::MoveSprite(newBullet3.iSpriteID, newTank.pFront.dX, newTank.pFront.dY);
			




			for (float i = 0; i < 1; i += (1.f/32.f))
			{
				RayCastTest.pos.dX = Lerp(50, DANM::GetSpriteXPos(newTank.iSpriteID), i);
				RayCastTest.pos.dY = Lerp(50, DANM::GetSpriteYPos(newTank.iSpriteID), i);
				std::cout << "x: " << RayCastTest.pos.dX << std::endl;
				std::cout << "y: " << RayCastTest.pos.dY << std::endl;
				//Vector2(300, 300);
				UG::MoveSprite(RayCastTest.iSpriteID, float(RayCastTest.pos.dX), float(RayCastTest.pos.dY));
				UG::MoveSprite(newBullet5.iSpriteID, float(RayCastTest.pos.dX), float(RayCastTest.pos.dY));
				int iTileTypes = RayCastTest.GetTile(32, RayCastTest.pos);

				std::cout << "tile: " << iTileTypes << std::endl << std::endl;
				if (iTileTypes == 1)
				{
					std::cout << "AYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY" << std::endl;
					break;
				}
			}





			UG::ClearScreen();
			UG::SetFont(nullptr);//

		} while (UG::Process());

		MapGen[0].UnLoadLevel(MapGen);
		delete[] MapGen;
		UG::Dispose();

		


	}
	return 0;
}

void test(int a_iSpriteIDStart, int a_iSpriteIDPlayer, Bullet& ayy)
{
	
	
	
	
}