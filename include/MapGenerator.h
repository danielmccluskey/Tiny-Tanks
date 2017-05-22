//==============================================================================================================================
// Project: WiiTanks
// File: MapCreation.h
// Author: Daniel McCluskey
// Date Created: 07/01/17
// Brief: This is the header file that contains the code that draws the maps from files and generates the collision map.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#ifndef _MAPGENERATOR_H_
#define _MAPGENERATOR_H_
#include <string>

class MapGenerator
{
public:
	
	~MapGenerator()
	{
	}

	//==============================================================================================================================
	//Ints
	//==============================================================================================================================

	//Function to get the current type of tile at a certain point.
	//int a_iX = X co-ords of tile array.
	//int a_iY = Y co-ords of tile array.
	int GetTile(int a_iX, int a_iY);

	//==============================================================================================================================
	//Bools
	//==============================================================================================================================
	
	//Function to load the next level. Allows for infinite, custom levels. User can add their own.
	//However there is no validation on the files to see if they are actually map files.
	//Returns true if level loads correctly.
	//MapGenerator *a_pPosition = The Map class member to loop through.
	bool NextLevel(MapGenerator *a_pPosition);

	//==============================================================================================================================
	//Class Members
	//==============================================================================================================================
	
	//Function to get the tile class member at a certain point.
	//MapGenerator *a_pPosition = The Class member to loop through.
	//int a_iX = X co-ords of tile array.
	//int a_iY = Y co-ords of tile array.
	MapGenerator& GetMapPosition(MapGenerator *a_pPosition, int a_iX, int a_iY);

	//==============================================================================================================================
	//Voids
	//==============================================================================================================================

	//Function to Load the level. It opens the level path, stores it in an array, then generates a collision map.
	//std::string a_sLevelPath = The level path given in format "./maps/lvl_X".txt" with X being the level to load.
	//MapGenerator *a_pPosition = The Class member to loop through.
	void LoadLevel(std::string a_sLevelPath, MapGenerator *a_pPosition);
	
	//Creates a sprite for the class member and draws it at the correct position.
	//char* a_cImagePath = The image that the sprite should be created with.
	//int a_iTileX = The X of the tile array
	//int a_iTileY = The Y of the tile array
	//MapGenerator *a_pCurrentTile = The Map class member.
	void SetTile(char* a_cImagePath, int a_iTileX, int a_iTileY, MapGenerator *a_pCurrentTile);

	//Function to Unload the level.
	//MapGenerator *a_pPosition = The Class member to loop through.
	void UnLoadLevel(MapGenerator *a_pPosition);

	//Loops through the tile array, checks what tile type is there and then draws it.
	//MapGenerator *a_pPosition = The Map class array to loop through.
	void DrawLevelTiles(MapGenerator *a_pPosition);

	//Function to reset the level count and unload the current map.
	//MapGenerator *a_pPosition = The Map class member to loop through
	void Quit(MapGenerator *a_pPosition);

private:
	//==============================================================================================================================
	//Ints
	//==============================================================================================================================

	int iSpriteID = 0;//Sprite ID
	int iCurrentLevel = 0;//Current level to load
	int iLevelMap[384];//Stores the texture array.
	int iCollisionMap[384];//Stores the collision array.
	int iTileWidth = 32;//Stores the tile width.
	
	//Variables to hold the current position in the map
	int	iTileX;
	int iTileY;

};

#endif //_MAPGENERATOR_H_