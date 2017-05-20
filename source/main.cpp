#include "Enumerations.h"
#include "MapGenerator.h"
#include "PlayerTank.h"
#include "Enemy.h"
#include "Bullet.h"
#include "UGFW.h"
#include "stdlib.h"
#include "MenuSprites.h"
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


//Declares all the level files.

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
		MapGen[0].LoadLevel("./maps/lvl_1.txt", MapGen);
		

		//Creates a new Player sprite.
		PlayerTank oPlayerTank(200, 200, fGlobalSpeed);
		
		

		////Enemy Test
		Enemy oEnemyTank;
		oEnemyTank.CreateTank(320, 320);



		MenuSprite oMenuBackground(Vector2(fCenterX, fCenterY), Vector2((fMapWidth*fTileWidth) + 200, (fMapWidth*fTileWidth) + 200), 10, "./Images/menu/background.png", true);
		MenuSprite oMenuTitle(Vector2(fCenterX, iScreenHeight*0.78f), Vector2(500, 137), 11, "./Images/menu/title.png", true);
		MenuSprite oMenuButtonPlay(Vector2(fCenterX, iScreenHeight*0.48f), Vector2(300, 82), 11, "./Images/menu/button_play.png", true);
		MenuSprite oMenuButtonQuit(Vector2(fCenterX, iScreenHeight*0.28f), Vector2(300, 82), 11, "./Images/menu/button_quit.png", true);

		MenuSprite oNextButtonNext(Vector2(fCenterX, iScreenHeight*0.48f), Vector2(300, 82), 11, "./Images/menu/button_next.png", false);
		MenuSprite oNextButtonQuit(Vector2(fCenterX, iScreenHeight*0.28f), Vector2(300, 82), 11, "./Images/menu/button_quit.png", false);

		//

		bool iCurrentMouseState = false;
		bool iLastMouseState = false;

		int iGameState = MENU;
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
		
			switch (iGameState)
			{
			case MENU:
			{
				oMenuBackground.RotateSprite(0.1f);
				oMenuTitle.ThrobSprite(0.01f, 0.8f);

				if (oMenuButtonPlay.CheckClick() && (iCurrentMouseState == true && iLastMouseState == false))
				{
					bool bLevelLoad = MapGen[0].NextLevel(MapGen);
					if (bLevelLoad)
					{
						oMenuBackground.HideSprite();
						oMenuTitle.HideSprite();
						oMenuButtonPlay.HideSprite();
						oMenuButtonQuit.HideSprite();
						iGameState = GAMEPLAY;
					}
					

				}
				if (oMenuButtonQuit.CheckClick() && (iCurrentMouseState == true && iLastMouseState == false))
				{
					UG::Close();
				}

			}
			break;

			case GAMEPLAY:
			{
				oPlayerTank.CalculateBoundaries();
				oPlayerTank.MoveTank();
				oEnemyTank.MoveTank(oEnemyTank.vPos, oPlayerTank.vPos);
				oEnemyTank.LookToPlayer(oPlayerTank.vPos);

				if ((iCurrentMouseState == true && iLastMouseState == false))
				{
					oPlayerTank.BulletArray[0].CreateBullet(oPlayerTank.BulletArray, oPlayerTank.vPos, oPlayerTank.vMousePos, 0);
				}
				if (UG::IsKeyDown(UG::KEY_SPACE))
				{
					oPlayerTank.BulletArray[0].CreateBullet(oPlayerTank.BulletArray, oPlayerTank.vPos, oPlayerTank.vMousePos, 1);
				}
				if (UG::IsKeyDown(UG::KEY_P))
				{
					iGameState = NEXTLEVEL;
					oNextButtonNext.DrawSprite();
					oNextButtonQuit.DrawSprite();

					
				}
				oPlayerTank.BulletArray[0].UpdateBullets(oPlayerTank.BulletArray, oPlayerTank.iCollisionMap);
			}
			break;

			case NEXTLEVEL:
			{
				if (oNextButtonNext.CheckClick() && (iCurrentMouseState == true && iLastMouseState == false))
				{
					bool bLevelLoad = MapGen[0].NextLevel(MapGen);
					if (bLevelLoad)
					{
						oNextButtonNext.HideSprite();
						oNextButtonQuit.HideSprite();
						iGameState = GAMEPLAY;
						oPlayerTank.UpdateCollisionMap();
						oEnemyTank.UpdateCollisionMap();
					}
					else
					{
						MapGen[0].Quit(MapGen);
						oMenuBackground.DrawSprite();
						oMenuTitle.DrawSprite();
						oMenuButtonPlay.DrawSprite();
						oMenuButtonQuit.DrawSprite();

						oNextButtonNext.HideSprite();
						oNextButtonQuit.HideSprite();
						iGameState = MENU;
					}
				}
				else if (oNextButtonQuit.CheckClick() && (iCurrentMouseState == true && iLastMouseState == false))
				{

					MapGen[0].Quit(MapGen);
					oMenuBackground.DrawSprite();
					oMenuTitle.DrawSprite();
					oMenuButtonPlay.DrawSprite();
					oMenuButtonQuit.DrawSprite();

					oNextButtonNext.HideSprite();
					oNextButtonQuit.HideSprite();
					iGameState = MENU;
				}
			}
			break;
			}

			

			

			

			


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
			if (UG::IsKeyDown(UG::KEY_5))
			{
				MapGen[0].UnLoadLevel(MapGen);
				MapGen[0].LoadLevel("./maps/lvl_5.txt", MapGen);
			}
			

			UG::ClearScreen();
			UG::SetFont(nullptr);



			
			if (iCurrentMouseState == true && iLastMouseState == false)
			{
				iLastMouseState = true;
			}

		} while (UG::Process());

		MapGen[0].UnLoadLevel(MapGen);
		delete[] MapGen;

		oPlayerTank.~PlayerTank();
		oEnemyTank.~Enemy();

		oMenuBackground.~MenuSprite();
		oMenuTitle.~MenuSprite();
		oMenuButtonPlay.~MenuSprite();
		oMenuButtonQuit.~MenuSprite();


		UG::Dispose();

	}
	return 0;
}
