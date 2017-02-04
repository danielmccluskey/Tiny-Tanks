//==============================================================================================================================
// Project: WiiTanks
// File: MapCreation.h
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the header file that contains the code that draws the maps from files and generates the collision map.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#ifndef _MAPGENERATOR_H_
#define _MAPGENERATOR_H_


class MapGenerator
{
public:
	//Variables to hold the current position in the map
	int	iTileX;
	int iTileY;

	int GetTile(int a_iX, int a_iY);//Function to get a tile from the tilemap at given X,Y Pos
	void SetTile(char* a_cImagePath, int a_iTileX, int a_iTileY);//Sets the tile at the given X,Y Pos to given image by creating a sprite
	void DrawMap();//Draws all the sprites

private:
	int iSpriteID = 0;//Sprite ID

};

#endif //_MAPGENERATOR_H_