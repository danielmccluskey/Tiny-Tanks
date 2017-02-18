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




int iSpeed = 1;



int main(int argv, char* argc[])
{

	if (UG::Create(iScreenWidth, iScreenHeight, false, "Wii Tanks", 100, 100))
	{

		UG::SetBackgroundColor(UG::SColour(0x2A, 0x57, 0x66, 0xFF));
		UG::AddFont("./fonts/invaders.fnt");

		
		
		MapGenerator *MapGen = new MapGenerator[384];
		MapGen[0].LoadLevel("./maps/lvl_1.txt", MapGen);


		PlayerTank newTank;
		newTank.CreateTank(fCenterX, fCenterY);
		Turret newTurret;

		Bullet newBullet;
		Bullet newBullet1;
		Bullet newBullet2;
		Bullet newBullet3;
		Bullet newBullet4;

		newTank.UpdateCollisionMap();

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
			}
			
			Vertices Test(newTank.iSpriteID, newTank.iSpriteHeight, newTank.iSpriteWidth, DegreesToRadians(newTank.iRotDeg+90));

			newTank.GetSurroundingTiles(MapGen[0].iTileWidth);


			UG::MoveSprite(newTank.iSpriteID, newTank.pos.dX, newTank.pos.dY);

			DANM::SetRotationDeg(-(DANM::GetBearingDeg(newTurret.pos, mousePos))+90, newTurret.iSpriteID);

			newBullet.pos += newBullet.Velocity;
			UG::MoveSprite(newBullet.iSpriteID, newBullet.pos.dX, newBullet.pos.dY);

			UG::MoveSprite(newBullet4.iSpriteID, Test.vTopLeft.dX, Test.vTopLeft.dY);
			UG::MoveSprite(newBullet1.iSpriteID, Test.vTopRight.dX, Test.vTopRight.dY);
			UG::MoveSprite(newBullet2.iSpriteID, Test.vBotLeft.dX, Test.vBotLeft.dY);
			UG::MoveSprite(newBullet3.iSpriteID, Test.vBotRight.dX, Test.vBotRight.dY);
			UG::ClearScreen();
			UG::SetFont(nullptr);

		} while (UG::Process());

		MapGen[0].UnLoadLevel(MapGen);
		delete[] MapGen;
		UG::Dispose();

		


	}
	return 0;
}

