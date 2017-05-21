#include "PathFinding.h"
#include "UGFW.h"
#include <iostream>
#include <fstream>

//==============================================================================================================================
// Project: WiiTanks
// File: Pathfinding.cpp
// Author: Daniel McCluskey
// Date Created: 17/01/17

// Brief: This file contains the code that generates a path from A to B using the A* pathfinding method.
// Brief: My understanding of how it works is quite limited but I get the jist of the process after hearing an explanation from Will.
// Brief: I have commented the code as best to my knowledge.
// Brief: I followed a Youtube Video tutorial in order to create it. (https://www.youtube.com/watch?v=NJOf_MYGrYs)
// Brief: However, I was successfully able to implement it into my game with my Tile maps and enemy sprites. Collisions work fine.
// 
// Known Bugs: Crashes if there is no path to the goal. Did not have time to complete.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================

//Constructor
PathFinding::PathFinding(void)
{
	bInitialisedStart = false;//Tells the program that it is the first run.
	bFoundGoal = false;//Tells the program that the goal has not been found.
}
//Desconstructor.
PathFinding::~PathFinding(void)
{

}
//Gets the tile from the collision map array with the given co-ordinates.
//int a_iX = The TILE X Co-ordinate, not the Realworld co-ordinate.
//int a_iY = The TILE Y Co-ordinate, not the Realworld co-ordinate.
int PathFinding::GetTile(int a_iX, int a_iY)
{
	return iCollisionMap[(a_iY * iMapWidth) + a_iX];
}
//Function to Start or Continue the Pathfinding process depending on bInitilisedStart.
//Vector3 a_vCurrentPos = The current position of the enemy.
//Vector3 a_vTargetPos = The Target you wish to move to.
void PathFinding::FindPath(Vector3 a_vCurrentPos, Vector3 a_vTargetPos)
{
	if (!bInitialisedStart)
	{
		for (int i = 0; i < vOpenList.size(); i++)//For loop to reset the open list.
		{
			delete vOpenList[i];
		}
		vOpenList.clear();//Clears that.

		for (int i = 0; i < vClosedList.size(); i++)//For loop to reset the Closed list.
		{
			delete vClosedList[i];
		}
		vClosedList.clear();//Clears that.
		for (int i = 0; i < vGoalPath.size(); i++)//For loop to reset the Vector3 array containing the old path.
		{
			delete vGoalPath[i];
		}
		vGoalPath.clear();//Clears that.

		SearchCell sStart;//Creates a Search Cell class member for the start pos.
		sStart.iX = a_vCurrentPos.dX / fTileWidth;//Sets its X pos to the Tile Co-ords.
		sStart.iY = a_vCurrentPos.dZ / fTileWidth;//Sets its Y pos to the Tile Co-ords.

		SearchCell sGoal;//Creates a Search Cell class member for the goal.
		sGoal.iX = a_vTargetPos.dX / fTileWidth;//Sets its X pos to the Tile Co-ords.
		sGoal.iY = a_vTargetPos.dZ / fTileWidth;//Sets its Y pos to the Tile Co-ords.

		SetStartAndGoal(sStart, sGoal);//Sets the Start and the goal of the path.
		bInitialisedStart = true;//Finishes the starting function.
		bFoundGoal = false;//Resets the found goal state.
	}
	if (bInitialisedStart)
	{
		ContinuePath();//Continue finding the path.
	}
}
void PathFinding::SetStartAndGoal(SearchCell a_sStart, SearchCell a_sGoal)
{
	pStartCell = new SearchCell(a_sStart.iX, a_sStart.iY, NULL);//Declares the Starting cell, NULL on third parameter since the starting cell does not need a Parent node.
	pGoalCell = new SearchCell(a_sGoal.iX, a_sGoal.iY, &a_sGoal);//Declares the last cell.

	pStartCell->fG = 0;//Cost of starting cell is 0;
	pStartCell->fH = pStartCell->GetManhattenDistance(pGoalCell);//Gets the distance from Start to Goal using (Change in X)+(Change in Y)
	pStartCell->sParent = 0;//Starting cell does not need a parent cell.

	vOpenList.push_back(pStartCell);//Pushes the Starting cell to the open list.
}

SearchCell* PathFinding::GetNextCell()
{
	float fClosestTile = 1000;//Large value to start with so that the minimum value can be determined.
	int iCellIndex = -1;//Sets Cell index to -1 to start with.
	SearchCell* pNextCell = NULL;//Resets the pNextcell.

	for (int i = 0; i < vOpenList.size(); i++)//Loops through the current open list.
	{
		if (vOpenList[i]->GetF() < fClosestTile)//If the Hueristic of the current cell is less than the fClosest tile.
		{
			fClosestTile = vOpenList[i]->GetF();//Sets the new minimum value.
			iCellIndex = i;//Saves which cell that was.
		}
	}

	if (iCellIndex >= 0)//If the cell index has changed from -1. This is where I could add a function to cancel pathfinding if a path could not be found, however, lack of time.
	{
		pNextCell = vOpenList[iCellIndex];//Sets the next path position to the previously found closest cell.
		vClosedList.push_back(pNextCell);//Pushes that cell to the closed list so that it is not searched through again.
		vOpenList.erase(vOpenList.begin() + iCellIndex);//Erases the Open list ready for the next time the function is used.
	}
	return pNextCell;//Returns the found closest cell.
}

void PathFinding::PathOpened(int a_iX, int a_iY, float a_fCost, SearchCell *a_pParent)
{
	int iTile = GetTile(a_iX, a_iY);//Gets the tile type at the XY pos for collision.
	
	if (iTile == 1)//If tile is a wall.
	{
		return;//Return, this does nothing with the tile since it is a wall. This is inefficient since the cell will be checked again if an adjacent tile is checked. Will add fix later.
	}

	int iIDNum = a_iY * (fMapHeight*fMapWidth) + a_iX;//Gets the position of the X+Y in the collision array.
	for (int i = 0; i < vClosedList.size(); i++)//Loops through the closed list.
	{
		if (iIDNum == vClosedList[i]->iID)//If the Tile is already in the closed list.
		{
			return;//Do nothing.
		}

	}

	SearchCell* pNewChild = new SearchCell(a_iX, a_iY, a_pParent);//Creates the child node.
	pNewChild->fG = a_fCost;//Cost implemented so that I can make different tiles less preferable for travel.
	pNewChild->fH = a_pParent->GetManhattenDistance(pGoalCell);//Gets the distance from Start to Goal using (Change in X)+(Change in Y)

	for (int i = 0; i < vOpenList.size(); i++)//Loops through the open list.
	{
		if (iIDNum == vOpenList[i]->iID)//If the id of the tile is already in the open list.
		{
			float fNewF = pNewChild->fG + a_fCost + vOpenList[i]->fH;//Make a new F with the G of the child and the H of the potential parent tile.

			if (vOpenList[i]->GetF() > fNewF)//If the new Hueristic is smaller than the old one.
			{
				vOpenList[i]->fG = pNewChild->fG + a_fCost;//Set the new Hueristic to the new tile.
				vOpenList[i]->sParent = pNewChild;//Set the parent of the new tile to the last tile.
			}
			else//If the new Hueristic is larger than the old one.
			{
				delete pNewChild;//Remove the potential new tile
				return;//Do nothing.
			}
		}
	}
	vOpenList.push_back(pNewChild);//Push the new tile to the open list.
}
void PathFinding::UpdateCollisionMap()
{
	std::ifstream pCollision;//Creates an input fstream member
	pCollision.open("./maps/currentCollision.txt");//Opens the file.
	for (int i = 0; i < (iMapHeight*iMapWidth); i++)//Iterates through each tile in the array.
	{
		pCollision >> iCollisionMap[i];//Stores current tile type into array.
	}
	pCollision.close();//Closes the file.
}

void PathFinding::ContinuePath()
{
	for (int i = 0; i < 4; i++)//Only runs 4 times since I only have 4 directions.
	{
		if (vOpenList.empty())//If the open list has no tiles in it.
		{
			return;//Do nothing.
		}
		SearchCell* pCurrentCell = GetNextCell();//Gets the next cell of the path.

		if (pCurrentCell->iID == pGoalCell->iID)//If the current cell is the same as the Goal cell, the path has finished and found the goal.
		{
			pGoalCell->sParent = pCurrentCell->sParent;//Sets the Goals parent to the parent of the current cell.

			SearchCell* pGetPath;//Creates a new search cell member.

			for (pGetPath = pGoalCell; pGetPath != NULL; pGetPath = pGetPath->sParent)//Follows the path backwards through each cells parent node.
			{
				vGoalPath.push_back(new Vector3(pGetPath->iX * fTileWidth, 0, pGetPath->iY * fTileWidth));//Pushes each parent of the correct path to the goal path.

				
				//Uncomment the code below to view the path that the program has found.
				//int iSpriteID = UG::CreateSprite("./images/Tanks/temp3.png", 32, 32, true);//Create the sprite

				//UG::DrawSprite(iSpriteID);	//Draws it
				//UG::MoveSprite(iSpriteID, pGetPath->iX*fTileWidth, pGetPath->iY*fTileWidth);
			}

			bFoundGoal = true;//Tells the program that the goal has been found
			return;
		}
		else//Goal has not been found.
		{
			PathOpened(pCurrentCell->iX + 1, pCurrentCell->iY, pCurrentCell->fG + 1, pCurrentCell);//Checks the cell to the Right side.
			PathOpened(pCurrentCell->iX - 1, pCurrentCell->iY, pCurrentCell->fG + 1, pCurrentCell);//Checks the cell to the Left Side
			PathOpened(pCurrentCell->iX, pCurrentCell->iY + 1, pCurrentCell->fG + 1, pCurrentCell);//Checks the cell to the Top Side
			PathOpened(pCurrentCell->iX, pCurrentCell->iY - 1, pCurrentCell->fG + 1, pCurrentCell);//Checks the cell to the Bottom Side

			for (int i = 0; i < vOpenList.size(); i++)//Loops through Open list.
			{
				if (pCurrentCell->iID == vOpenList[i]->iID)//If the Current cell is already in the open list.
				{
					vOpenList.erase(vOpenList.begin() + i);//Erase the cell after that.
				}
			}

		}
	}
	
}

Vector3 PathFinding::NextPathPos(Vector3 a_vPos, bool a_bFoundGoal)
{

	int iIndex = 1;//Index for searching the Goal path.

	if ((vGoalPath.empty()))//If there is nothing left in the goal path.
	{
		return Vector3(0, -100, 0);//Since Y value is not used, I return -100 too tell the Enemy class that the path has ended.
	}
	if (a_bFoundGoal)//If the goal has been found.
	{
		vGoalPath.erase(vGoalPath.end() - iIndex);//Erase the last position.
	}

	Vector3 vNextPosCell;//Creates Vector3 to store the next position.
	vNextPosCell.dX = vGoalPath[vGoalPath.size() - iIndex]->dX;//Gets the X Pos.
	vNextPosCell.dZ = vGoalPath[vGoalPath.size() - iIndex]->dZ;//Gets the Y Pos.
	
	return vNextPosCell;
}
Vector3 PathFinding::SecondNextPathPos(Vector3 a_vPos)
{
	int iIndex = 2;//Index for searching the Goal path.
	if ((vGoalPath.size() <= 1))//If there is nothing left in the goal path. (<=1 used to stop exception error when searching below 0 on an array)
	{
		
		return Vector3(0, -100, 0);//Since Y value is not used, I return -100 too tell the Enemy class that the path has ended.

	}
	Vector3 vNextPosCell;//Creates Vector3 to store the next position.
	vNextPosCell.dX = vGoalPath[vGoalPath.size() - iIndex]->dX;//Gets the X Pos.
	vNextPosCell.dZ = vGoalPath[vGoalPath.size() - iIndex]->dZ;//Gets the Y Pos.

	return vNextPosCell;
}

void PathFinding::DrawDebug()
{
	//Uncomment the code below to see the search algorithm visualised.
	//for (int i = 0; i < vOpenList.size(); i++)
	//{
	//	int iSpriteID = UG::CreateSprite("./images/Tanks/temp.png", 32, 32, true);//Create the sprite
	//	UG::DrawSprite(iSpriteID);	//Draws it
	//	UG::MoveSprite(iSpriteID, vOpenList[i]->iX*fTileWidth, vOpenList[i]->iY*fTileWidth);
	//}

	//for (int i = 0; i < vClosedList.size(); i++)
	//{
	//	int iSpriteID = UG::CreateSprite("./images/Tanks/temp2.png", 32, 32, true);//Create the sprite

	//	UG::DrawSprite(iSpriteID);	//Draws it
	//	UG::MoveSprite(iSpriteID, vClosedList[i]->iX*fTileWidth, vClosedList[i]->iY*fTileWidth);
	//}

}