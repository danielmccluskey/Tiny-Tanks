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
	
	~MapGenerator()
	{
	}

	int iLevelMap[384];
	int iCollisionMap[384];

	void LoadLevel(char* a_cLevelPath, MapGenerator *a_pPosition);//Function to generate the collision map from a certain level map.
	int GetTile(int a_iX, int a_iY);//Function to get a tile from the tilemap at given X,Y Pos
	void SetTile(char* a_cImagePath, int a_iTileX, int a_iTileY, MapGenerator *a_pCurrentTile);//Sets the tile at the given X,Y Pos to given image by creating a sprite
	void UnLoadLevel(MapGenerator *a_pPosition);
	void DrawLevelTiles(MapGenerator *a_pPosition);//Draws all the sprites

	MapGenerator& GetMapPosition(MapGenerator *a_pPosition, int a_iX, int a_iY);

private:
	int iSpriteID = 0;//Sprite ID

	int iTileWidth = 32;
	//Variables to hold the current position in the map
	int	iTileX;
	int iTileY;

};

#endif //_MAPGENERATOR_H_