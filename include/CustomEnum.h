//==============================================================================================================================
// Project: WiiTanks
// File: CustomEnum.h
// Author: Daniel McCluskey
// Date Created: 07/01/17
// Brief: This is the header file that contains all of the Enumerations I have used throughout my code. This header is included in almost every CPP file in the project.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================

#ifndef _CUSTOMENUM_H_
#define _CUSTOMENUM_H_

//==============================================================================================================================
//Floats
//==============================================================================================================================

const float fMapWidth = 24;//Defines the Mapwidth as a FLOAT.
const float fMapHeight = 16;//Defines the Mapheight as a FLOAT.
const float fTileWidth = 32;//Defines the TileWidth as a FLOAT.

//==============================================================================================================================
//Ints
//==============================================================================================================================

const int iMapWidth = 24;//Defines the Mapwidth as an INT.
const int iMapHeight = 16;//Defines the Mapheight as an INT.




//==============================================================================================================================
//ENUMS
//==============================================================================================================================


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