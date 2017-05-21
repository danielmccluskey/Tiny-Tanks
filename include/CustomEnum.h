//==============================================================================================================================
// Project: WiiTanks
// File: MapCreation.h
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the header file that contains all of the Enumerations I have used throughout my code. This header is included in every CPP file in the project.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================

#ifndef _CUSTOMENUM_H_
#define _CUSTOMENUM_H_
const float fMapWidth = 24;
const float fMapHeight = 16;
const float fTileWidth = 32;
const int iMapWidth = 24;
const int iMapHeight = 16;






typedef enum GameStates //Enumeration for the different gamestates
{
	SPLASH,
	MENU,
	GAMEPLAY,
	GAMEOVER,
	DIFFICULTY,
	PAUSE,
	SCORES,
	NEXTLEVEL,
	DEATH
}GameState;


enum TileTypes //Enumerations for the Creation of the map to help me understand the values.
{
	wall, floorr
};
enum menuStates//Enumeration for the different main menu options
{
	PLAY, HIGHSCORES, QUIT
};
#endif //_CUSTOMENUM_H_