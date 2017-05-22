//==============================================================================================================================
// Project: WiiTanks
// File: MapCreation.h
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the header file that contains the code that draws the maps from files and generates the collision map.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#include "Enumerations.h"
#include "MapGenerator.h"
#include "PlayerTank.h"
#include "Enemy.h"
#include "Bullet.h"
#include "UGFW.h"
#include "stdlib.h"
#include "MenuSprites.h"
#include <iostream>
#include "windows.h"

#pragma comment(lib, "winmm.lib")//Include PlaySound function
//Screen sizes
int iScreenWidth = 768;
int iScreenHeight = 512;

//Co-ords of the Center of the screen
float fCenterX = iScreenWidth*0.5f;
float fCenterY = iScreenHeight*0.5f;

//Declares the global speed of the player tank.
float fGlobalSpeed = 80.f;

//Declares the UV types
float fButtonUV[2][4] = { { 0.f, 0.5f, 1.f, 1.f },{ 0.f, 0.f, 1.f, 0.5f } };//UV for a button
float fFullUV[2][4] = { { 0.f, 0.f, 1.f, 1.f },{ 0.f, 0.f, 1.f, 1.f } };//UV for a non hovering sprite that uses full UV

int main(int argv, char* argc[])
{

	if (UG::Create(iScreenWidth, iScreenHeight, false, "Wii Tanks", 100, 100))
	{
		UG::SetBackgroundColor(UG::SColour(0x2A, 0x57, 0x66, 0xFF));//Sets the background colour to blue
		UG::AddFont("./fonts/invaders.fnt");//Adds a font.
		
		//Creates a new Map array and Loads a level from a text file.
		MapGenerator *MapGen = new MapGenerator[384];
		MapGen[0].LoadLevel("./maps/lvl_1.txt", MapGen);//Loads the first level to generate the map tile sprites.	

		//Creates a new Player sprite.
		PlayerTank oPlayerTank(704, 448, fGlobalSpeed);

		//Enemy Test
		Enemy oEnemyTank;//Constructor not used, need to fix.
		oEnemyTank.CreateTank(100, 100);//Temp constructor


		//Below are all the GUI parts of the game being declared. Looks messy I know.

		//Bullet count overlay during gameplay
		MenuSprite oAmmoOverlay(Vector2(fCenterX, iScreenHeight - fTileWidth/2), Vector2(iScreenWidth, fTileWidth), 10, "./Images/menu/overlay_ammo.png", fFullUV, true);

		//Main menu screen sprites
		MenuSprite oMenuBackground(Vector2(fCenterX, fCenterY), Vector2((fMapWidth*fTileWidth) + 200, (fMapWidth*fTileWidth) + 200), 10, "./Images/menu/background.png", fFullUV, true);
		MenuSprite oMenuTitle(Vector2(fCenterX, iScreenHeight*0.78f), Vector2(500, 137), 11, "./Images/menu/title.png", fFullUV, true);
		MenuSprite oMenuButtonPlay(Vector2(fCenterX, iScreenHeight*0.48f), Vector2(300, 82), 11, "./Images/menu/button_play.png", fButtonUV, true);
		MenuSprite oMenuButtonQuit(Vector2(fCenterX, iScreenHeight*0.28f), Vector2(300, 82), 11, "./Images/menu/button_quit.png", fButtonUV, true);

		//Text to display if a user failed or passed a level
		MenuSprite oLevelFail (Vector2(fCenterX, iScreenHeight*0.68f), Vector2(300, 82), 11, "./Images/menu/level_failed.png", fFullUV, false);
		MenuSprite oLevelPass (Vector2(fCenterX, iScreenHeight*0.68f), Vector2(300, 82), 11, "./Images/menu/level_passed.png", fFullUV, false);

		//Buttons to display if the player pauses or wins
		MenuSprite oNextButtonNext(Vector2(fCenterX, iScreenHeight*0.48f), Vector2(300, 82), 11, "./Images/menu/button_next.png", fButtonUV, false);
		MenuSprite oNextButtonQuit(Vector2(fCenterX, iScreenHeight*0.28f), Vector2(300, 82), 11, "./Images/menu/button_quit.png", fButtonUV, false);
		MenuSprite oNextButtonRestart(Vector2(fCenterX, iScreenHeight*0.48f), Vector2(300, 82), 11, "./Images/menu/button_restart.png", fButtonUV, false);

		//Displays as a splash screen to show the user the controls for the game.
		MenuSprite oControls(Vector2(fCenterX, fCenterY), Vector2((fMapWidth*fTileWidth), (fMapHeight*fTileWidth)), 16, "./Images/menu/controls.png", fFullUV, true);

		//Variables to make a users single click not carry over into multiple frames
		bool iCurrentMouseState = false;
		bool iLastMouseState = false;

		int iGameState = SPLASH;//Sets the game state to splash
		do
		{

			if (UG::GetMouseButtonDown(0))//IF the mouse button is down
			{
				iCurrentMouseState = true;//Current mouse state
			
			}
			if (UG::GetMouseButtonReleased(0))//If the mouse button is released
			{
				iCurrentMouseState = false;//Current mouse state
				iLastMouseState = false;//Last mouse state
			}
		
			switch (iGameState)
			{
			case SPLASH:
			{
				if (oControls.CheckClick() && (iCurrentMouseState == true && iLastMouseState == false))//If the user clicks the mouse
				{
					oControls.HideSprite();//Hide the controls
					iGameState = MENU;//Change gamestate
				}
			}
			break;

			case PAUSE:
			{
				if (oMenuButtonPlay.CheckClick() && (iCurrentMouseState == true && iLastMouseState == false))//If the user clicks play/resume
				{
					oMenuButtonPlay.HideSprite();//Hide play button
					oMenuButtonQuit.HideSprite();//Hide quit button
					iGameState = GAMEPLAY;
				}
				else if (oMenuButtonQuit.CheckClick() && (iCurrentMouseState == true && iLastMouseState == false))//If the user clicks the quit button
				{
					MapGen[0].Quit(MapGen);//Unload the level map
					oMenuBackground.DrawSprite();//Draw the menu
					oMenuTitle.DrawSprite();//Draw the menu
					iGameState = MENU;
				}

			}
			break;
			case MENU:
			{
				oMenuBackground.RotateSprite(0.1f);//Rotates the background image each frame
				oMenuTitle.ThrobSprite(0.01f, 0.8f);//Makes the title zoom in and out each frame

				if (oMenuButtonPlay.CheckClick() && (iCurrentMouseState == true && iLastMouseState == false))//If the user clicks play
				{
					bool bLevelLoad = MapGen[0].NextLevel(MapGen);
					if (bLevelLoad)
					{
						//Hide all the menu sprites
						oMenuBackground.HideSprite();
						oMenuTitle.HideSprite();
						oMenuButtonPlay.HideSprite();
						oMenuButtonQuit.HideSprite();

						//Update the collision maps for both the player and their child classes + reset their positions
						oPlayerTank.UpdateCollisionMap();
						oEnemyTank.UpdateCollisionMap();
						oPlayerTank.Reset(Vector2(704, 448));
						oEnemyTank.Reset(Vector2(100, 100));
						iGameState = GAMEPLAY;
					}
					

				}
				if (oMenuButtonQuit.CheckClick() && (iCurrentMouseState == true && iLastMouseState == false))//If the user clicks quit
				{
					UG::Close();//Close window.
				}

			}
			break;

			case GAMEPLAY:
			{
				oPlayerTank.CalculateBoundaries();//Calculates each position of the corners of the sprite.
				if (oPlayerTank.MoveTank(oEnemyTank.GetSpriteID()))//If the enemy collides with one of the players bullets
				{
					//Draw next level screen and reset the Player and enemy.
					PlaySound(TEXT("./sounds/player_win.wav"), NULL, SND_FILENAME | SND_NOSTOP | SND_ASYNC);//Plays the sound chosen at the start of the function
					iGameState = NEXTLEVEL;
					oNextButtonNext.DrawSprite();
					oNextButtonQuit.DrawSprite();
					oLevelPass.DrawSprite();
					oPlayerTank.Reset(Vector2(704, 448));
					oEnemyTank.Reset(Vector2(100,100));
				}
				
				if (oEnemyTank.MoveTank(oEnemyTank.GetPos(), oPlayerTank.GetPos(), oPlayerTank.GetSpriteID()))//If the player collides with a bullet fired by an enemy.
				{
					PlaySound(TEXT("./sounds/player_death.wav"), NULL, SND_FILENAME | SND_NOSTOP | SND_ASYNC);//Plays the sound chosen at the start of the function
					//Draw death screen and reset the player and enemy.
					iGameState = DEATH;
					oNextButtonRestart.DrawSprite();
					oNextButtonQuit.DrawSprite();
					oLevelFail.DrawSprite();
					oPlayerTank.Reset(Vector2(704, 448));
					oEnemyTank.Reset(Vector2(100, 100));
				}
				oEnemyTank.LookToPlayer(oPlayerTank.GetPos());//Makes the enemy tanks turret look towards the player.

				if (UG::IsKeyDown(UG::KEY_ESCAPE))//If the player presses escape
				{
					//Show the Pause menu.
					iGameState = PAUSE;
					oMenuButtonPlay.DrawSprite();
					oMenuButtonQuit.DrawSprite();
				}

				
			}
			break;

			case NEXTLEVEL:
			{
				if (oNextButtonNext.CheckClick() && (iCurrentMouseState == true && iLastMouseState == false))//If the player clicks next level
				{
					bool bLevelLoad = MapGen[0].NextLevel(MapGen);//See if the next custom level can be loaded
					if (bLevelLoad)//If the level was loaded correctly
					{
						//Hide the next level menu and load the next level and play.
						oNextButtonNext.HideSprite();
						oLevelPass.HideSprite();
						oNextButtonQuit.HideSprite();
						iGameState = GAMEPLAY;
						oPlayerTank.UpdateCollisionMap();
						oEnemyTank.UpdateCollisionMap();
					}
					else//No more custom levels to play, return to main menu
					{
						//Unload the level and show the main menu.
						MapGen[0].Quit(MapGen);
						oMenuBackground.DrawSprite();
						oMenuTitle.DrawSprite();
						oMenuButtonPlay.DrawSprite();
						oMenuButtonQuit.DrawSprite();

						oNextButtonNext.HideSprite();
						oLevelPass.HideSprite();
						oNextButtonQuit.HideSprite();
						iGameState = MENU;
					}
				}
				else if (oNextButtonQuit.CheckClick() && (iCurrentMouseState == true && iLastMouseState == false))//If the player clicks quit
				{
					//Unload the level and show the main menu.
					MapGen[0].Quit(MapGen);
					oMenuBackground.DrawSprite();
					oMenuTitle.DrawSprite();
					oMenuButtonPlay.DrawSprite();
					oMenuButtonQuit.DrawSprite();

					oNextButtonNext.HideSprite();
					oLevelPass.HideSprite();
					oNextButtonQuit.HideSprite();
					iGameState = MENU;
				}
			}
			break;
			case DEATH:
			{
				if (oNextButtonRestart.CheckClick() && (iCurrentMouseState == true && iLastMouseState == false))//If the player clicks restart.
				{
					//Hide menu and just go back to gameplay
					oNextButtonRestart.HideSprite();
					oNextButtonQuit.HideSprite();
					oLevelFail.HideSprite();
					iGameState = GAMEPLAY;
				}
				else if (oNextButtonQuit.CheckClick() && (iCurrentMouseState == true && iLastMouseState == false))
				{
					//Unload the level and show the main menu.
					MapGen[0].Quit(MapGen);
					oMenuBackground.DrawSprite();
					oMenuTitle.DrawSprite();
					oMenuButtonPlay.DrawSprite();
					oMenuButtonQuit.DrawSprite();

					oNextButtonRestart.HideSprite();
					oNextButtonQuit.HideSprite();
					oLevelFail.HideSprite();
					iGameState = MENU;
				}
			}
			break;
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
