//==============================================================================================================================
// Project: Wii Tanks
// File: MapGenerator.cpp
// Author: Daniel McCluskey
// Date Created: 07/02/17
// Brief: This is the file that contains the code that draws the Level and generates the Collision maps from text files.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================

#include "MapGenerator.h"
#include "stdlib.h"
#include "CustomEnum.h"
#include <iostream>
#include <fstream>
#include "UGFW.h"

void MapGenerator::DrawLevelTiles(MapGenerator *a_pPosition)
{

	//The following is the code that draws out the tiles from the Array map
	for (int y = 0; y < fMapHeight; ++y)  //Counts through the Y axis of the array each time the X axis completes a row
	{
		for (int x = 0; x < fMapWidth; ++x) //Counts through the X axis
		{
			
			int iTileType = GetTile(x, y); //Finds what type of tile needs to be placed at current place in map.

			switch (iTileType) //Switch statement to actually create the tiles and draw them.
			{
			case 2:
			{
				SetTile("./images/maps/box1.png", x, y, a_pPosition);
			}
			break;
			case 4:
			{
				SetTile("./images/maps/floor1.png", x, y, a_pPosition);
			}
			break;
			}
		}
	}
}


void MapGenerator::SetTile(char* a_cImagePath, int a_iTileX, int a_iTileY, MapGenerator *a_pCurrentTile)
{
	MapGenerator &pCurrentTile = GetMapPosition(a_pCurrentTile, a_iTileX, a_iTileY);
	//Converts the Map position to the coordinates of the users window with an offset of half the tile width since sprites are drawn at the center
	int iRealTileX = (a_iTileX * iTileWidth) + (iTileWidth / 2);
	int iRealTileY = (a_iTileY * iTileWidth) + (iTileWidth / 2);

	//Creates, moves and draws the sprite
	pCurrentTile.iSpriteID = UG::CreateSprite(a_cImagePath, iTileWidth, iTileWidth, true);
	UG::SetSpriteLayer(pCurrentTile.iSpriteID, 1);
	UG::MoveSprite(pCurrentTile.iSpriteID, iRealTileX, iRealTileY);
	UG::DrawSprite(pCurrentTile.iSpriteID);
}


int MapGenerator::GetTile(int a_iX, int a_iY)
{
	return iLevelMap[(a_iY*iMapWidth) + a_iX];
}
MapGenerator& MapGenerator::GetMapPosition(MapGenerator *a_pPosition, int a_iX, int a_iY)
{
	return a_pPosition[(a_iY * iMapWidth) + a_iX];//Finds and returns what tile is at X,Y
}

void MapGenerator::LoadLevel(std::string a_sLevelPath, MapGenerator *a_pPosition)
{
	std::ifstream LEVELMAP;//Creates an input fstream member
	LEVELMAP.open(a_sLevelPath);//Opens the file.

	std::ofstream COLLISIONMAP;//Creates an output fstream member
	COLLISIONMAP.open("./maps/currentCollision.txt", std::ofstream::trunc);//Opens and Removes all of the text inside the file.
	for (int i = 0; i < (iMapHeight*iMapWidth); i++)//Iterates through each tile in the array.
	{
		LEVELMAP >> iLevelMap[i];//Stores current tile type into array.
		switch (iLevelMap[i])
		{
		case 4:
			iCollisionMap[i] = 0;
			break;
		default:
			iCollisionMap[i] = 1;
			break;
		}
		COLLISIONMAP << iCollisionMap[i] << " ";//Stores current collision value into a file.

		//Function to layout the text inside the collision text file in a readable way.
		if ((i + 1) % iMapWidth == 0)
		{
			COLLISIONMAP << "\n";
		}
	}
	LEVELMAP.close();
	COLLISIONMAP.close();
	
	DrawLevelTiles(a_pPosition);
}


void MapGenerator::UnLoadLevel(MapGenerator *a_pPosition)
{
	//The following is the code that draws out the tiles from the Array map
	for (int y = 0; y < fMapHeight; ++y)  //Counts through the Y axis of the array each time the X axis completes a row
	{
		for (int x = 0; x < fMapWidth; ++x) //Counts through the X axis
		{
			MapGenerator &pCurrentTile = GetMapPosition(a_pPosition, x, y);//Gets and stores the tile at the current position in the nested loop.
			UG::StopDrawingSprite(pCurrentTile.iSpriteID);//Stops drawing that tile.
			UG::DestroySprite(pCurrentTile.iSpriteID);//Deletes that tile.
		}
	}
}

bool MapGenerator::NextLevel(MapGenerator *a_pPosition)
{
	UnLoadLevel(a_pPosition);
	iCurrentLevel += 1;
	std::string ifLevelPath;
	ifLevelPath += "./maps/lvl_";
	ifLevelPath += std::to_string(iCurrentLevel);
	ifLevelPath += ".txt";
	std::cout << ifLevelPath << std::endl;

	if (std::ifstream(ifLevelPath))
	{
		std::cout << "File already exists" << std::endl;
		LoadLevel(ifLevelPath, a_pPosition);
		return true;
	}
	return false;

}