#include "Enumerations.h"
#include "MapGenerator.h"
#include "PlayerTank.h"
#include "Enemy.h"
#include "Bullet.h"
#include "UGFW.h"
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

//Declares the global speed of the tanks.
float fGlobalSpeed = 80.f;


//struct Bullet
//{
//	Bullet()
//	{
//		iSpriteID = UG::CreateSprite("./images/Tanks/temp.png", 10, 10, true);//Create the sprite
//		UG::DrawSprite(iSpriteID);	//Draws it
//		pos = Vector2(0, 0);
//		Velocity = Vector2(0,0);
//	};
//	int iSpriteID = 0;
//	Vector2 pos;
//	Vector2 Velocity;
//};

//test
Vector2 vMousePos;

int main(int argv, char* argc[])
{

	if (UG::Create(iScreenWidth, iScreenHeight, false, "Wii Tanks", 100, 100))
	{

		UG::SetBackgroundColor(UG::SColour(0x2A, 0x57, 0x66, 0xFF));
		UG::AddFont("./fonts/invaders.fnt");
		
		//Creates a new Map array and Loads a level from a text file.
		MapGenerator *MapGen = new MapGenerator[384];
		MapGen[0].LoadLevel("./maps/lvl_4.txt", MapGen);

		//Creates a new Player sprite.
		PlayerTank newTank;
		newTank.CreateTank(fCenterX, fCenterY);
		newTank.fSpeed = fGlobalSpeed;
		newTank.UpdateCollisionMap();

		////Enemy Test
		Enemy newEnemy;
		newEnemy.CreateTank(320, 320);

		newEnemy.UpdateCollisionMap();//

		//Bullet *BulletArray = new Bullet[20];

		bool iCurrentMouseState = false;
		bool iLastMouseState = false;
		do
		{

			if (UG::GetMouseButtonDown(0))
			{
				iCurrentMouseState = true;
				
			}
			if (UG::GetMouseButtonReleased(0))
			{
				iCurrentMouseState = false;
				iLastMouseState = false;
			}

			if (iCurrentMouseState == true && iLastMouseState == false)
			{
				iLastMouseState = true;
				
				UG::GetMousePos(vMousePos.dX, vMousePos.dY);//Gets the mouse position and stores it in the class members variable.
				vMousePos.dY = (iMapHeight * fTileWidth) - vMousePos.dY;//Reverses the Y-Value given from UG::GetMousePos since it returns Y=0 at the top instead of the bottom.
				newEnemy.bIsRotating = true;
				
				
			}

			newEnemy.MoveTank(newEnemy.vPos, vMousePos);

			newTank.CalculateBoundaries();
			newTank.MoveTank();

			

			if (UG::GetMouseButtonDown(0))
			{				
				//BulletArray[0].CreateBullet(BulletArray, newTank.pos, newTank.MousePos);
 			}

			//if (OtherFunctions::RayCast(newEnemy.iSpriteID, newTank.iSpriteID, newTank.iCollisionMap))
			//{
			////	BulletArray[0].CreateBullet(BulletArray, newEnemy.pos, newTank.pos);
			//}
			//BulletArray[0].UpdateBullets(BulletArray, newTank.iCollisionMap);


			//Debug
			if (UG::IsKeyDown(UG::KEY_1))
			{
				MapGen[0].UnLoadLevel(MapGen);
				MapGen[0].LoadLevel("./maps/lvl_1.txt", MapGen);
			}
			if (UG::IsKeyDown(UG::KEY_2))
			{
				MapGen[0].UnLoadLevel(MapGen);
				MapGen[0].LoadLevel("./maps/lvl_2.txt", MapGen);
			}
			if (UG::IsKeyDown(UG::KEY_3))
			{
				MapGen[0].UnLoadLevel(MapGen);
				MapGen[0].LoadLevel("./maps/lvl_3.txt", MapGen);
			}
			if (UG::IsKeyDown(UG::KEY_4))
			{
				MapGen[0].UnLoadLevel(MapGen);
				MapGen[0].LoadLevel("./maps/lvl_4.txt", MapGen);
			}
			

			UG::ClearScreen();
			UG::SetFont(nullptr);

		} while (UG::Process());

		MapGen[0].UnLoadLevel(MapGen);
		delete[] MapGen;
		UG::Dispose();

	}
	return 0;
}
