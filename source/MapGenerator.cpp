//==============================================================================================================================
// Project: Pacman
// File: MapCreation.cpp
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the file that contains the code that draws the "Maze" of the Pacman game.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================

#include "UGFW.h"
#include "MapGenerator.h"
#include "CustomEnum.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>
#include <sstream>


//Map for drawing the walls and corners 
int iMap[384];

void MapGenerator::DrawMap()
{
	//The following is the code that draws out the tiles from the Array map
	for (int y = 0; y < fMapHeight; ++y)  //Counts through the Y axis of the array each time the X axis completes a row
	{
		for (int x = 0; x < fMapWidth; ++x) //Counts through the X axis
		{
			int iTileType = GetTile(x, y); //Finds what type of tile needs to be placed at current place in map.

			switch (iTileType) //Switch statement to actually create the tiles and draw them.
			{
			case bottom:
			{

				SetTile("./images/walls/bottom.png", x, y);

			}
			break;
			}
		}
	}
}


void MapGenerator::SetTile(char* a_cImagePath, int a_iTileX, int a_iTileY)
{
	//Converts the Map position to the coordinates of the users window
	int iRealTileX = (a_iTileX * 16) + 15;
	int iRealTileY = (a_iTileY * 16) + 15;

	//Creates, moves and draws the sprite
	int iSpriteID = UG::CreateSprite(a_cImagePath, 16, 16, true);
	UG::SetSpriteLayer(iSpriteID, 1);
	UG::MoveSprite(iSpriteID, iRealTileX, iRealTileY);
	UG::DrawSprite(iSpriteID);
}


int MapGenerator::GetTile(int a_iX, int a_iY)
{
	return iMap[(a_iY*int(fMapWidth)) + a_iX];
}

void MapGenerator::GenerateCollisionMap(char* a_cLevelPath)
{
	std::ifstream LEVELMAP;
	LEVELMAP.open(a_cLevelPath);
	

	for (int i = 0; i < 384; i++)
	{
		LEVELMAP >> iLevelMap[i];
		std::cout << iLevelMap[i] << std::endl;
		switch (iLevelMap[i])
		{
		case 2:
			iCollisionMap[i] = 1;
			break;

		case 4:
			iCollisionMap[i] = 0;
			break;
		}
	}
	
}