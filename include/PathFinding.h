//==============================================================================================================================
// Project: WiiTanks
// File: Bullet.h
// Author: Daniel McCluskey
// Date Created: 07/01/17
// Brief: This file contains the code that generates a path from A to B using the A* pathfinding method.
// Brief: My understanding of how it works is quite limited but I get the jist of the process after hearing an explanation from Will.
// Brief: I have commented the code as best to my knowledge.
// Brief: I followed a Youtube Video tutorial in order to create it. (https://www.youtube.com/watch?v=NJOf_MYGrYs)
// Brief: However, I was successfully able to implement it into my game with my Tile maps and enemy sprites. Collisions work fine.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#ifndef _PATHFINDING_H_
#define _PATHFINDING_H_
#include "Vector3.h"
#include <vector>
#include "SearchCell.h"
#include "CustomEnum.h"


class PathFinding
{
public:
	PathFinding(void);
	~PathFinding(void);


	//==============================================================================================================================
	//Voids
	//==============================================================================================================================

	void ClearOpenList() { vOpenList.clear(); }//Clears the open list
	void ClearClosedList() { vClosedList.clear(); }//Clears the Closed list
	void ClearPathToGoal() { vGoalPath.clear(); }//Clears the goal path

	//Function to visualise the search algorithm.
	void DrawDebug();

	//Updates the collision map for the pathfinder.
	void UpdateCollisionMap();

	//Function to Start or Continue the Pathfinding process depending on bInitilisedStart.
	//Vector3 a_vCurrentPos = The current position of the enemy.
	//Vector3 a_vTargetPos = The Target you wish to move to.
	void FindPath(Vector3 a_vCurrentPos, Vector3 a_vTargetPos);

	//==============================================================================================================================
	//Ints
	//==============================================================================================================================

	//Gets the tile from the collision map array with the given co-ordinates.
	//int a_iX = The TILE X Co-ordinate, not the Realworld co-ordinate.
	//int a_iY = The TILE Y Co-ordinate, not the Realworld co-ordinate.
	int GetTile(int a_iX, int a_iY);

	//==============================================================================================================================
	//Vector3
	//==============================================================================================================================

	//Function to return the next path position
	//Vector3 a_vPos = The position of the enemy tank.
	//bool a_bFoundGoal = If the goal has been found.
	Vector3 NextPathPos(Vector3 a_vPos, bool a_bFoundGoal);

	//Function to return the second next path position
	//Vector3 a_vPos = The position of the enemy tank.
	Vector3 SecondNextPathPos(Vector3 a_vPos);

	//==============================================================================================================================
	//Bools
	//==============================================================================================================================

	bool bInitialisedStart;//Determines whether the path finding had started or not.
	bool bFoundGoal;//Determines if the program has found the goal or not.

private:

	//==============================================================================================================================
	//Void
	//==============================================================================================================================

	//Continues finding the path, this function allows the program to run at runtime meaning
	//that the program will not freeze whilst it is finding a path, instead, it will search one cell per frame.
	void ContinuePath();

	//Sets the starting cells and the end cells. Removes parent from starting cell.
	//SearchCell a_sStart == Start cell
	//SearchCell a_sGoal == End Cell
	void SetStartAndGoal(SearchCell a_sStart, SearchCell a_sGoal);

	//Function to set the values of a cell, such as what its parent is, where it is and what it would cost to get there.
	//int a_iX = X Co-ordinate
	//int a_iY = y Co-ordinate
	//float a_fCost = Cost to travel to that cell.
	//SearchCell *a_pParent = The parent cell.
	void PathOpened(int a_iX, int a_iY, float a_fCost, SearchCell *a_pParent);

	//==============================================================================================================================
	//Int
	//==============================================================================================================================

	int iCollisionMap[(iMapHeight*iMapWidth)];//Collision map to check against.

	//==============================================================================================================================
	//Other
	//==============================================================================================================================

	//Function to decide which neighboring cell is the fastest to the goal.
	SearchCell *GetNextCell();

	SearchCell *pStartCell;//The starting cell
	SearchCell *pGoalCell;//The cell the program has to find
	std::vector<SearchCell*> vOpenList;//List of cells that are open to move to.
	std::vector<SearchCell*> vClosedList;//List of cells that have been checked.
	std::vector<Vector3*> vGoalPath;//List of cells that correctly lead to the goal.
};


#endif