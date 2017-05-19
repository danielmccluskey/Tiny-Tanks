#include "PathFinding.h"
#include "UGFW.h"
#include <iostream>
#include <fstream>

PathFinding::PathFinding(void)
{
	bInitialisedStart = false;
	bFoundGoal = false;
}
PathFinding::~PathFinding(void)
{

}
int PathFinding::GetTile(int a_iX, int a_iY)
{


	return iCollisionMap[(a_iY * iMapWidth) + a_iX];
}
void PathFinding::FindPath(Vector3 a_vCurrentPos, Vector3 a_vTargetPos)
{
	if (!bInitialisedStart)
	{
		UpdateCollisionMap();
		for (int i = 0; i < vOpenList.size(); i++)
		{
			delete vOpenList[i];
		}
		vOpenList.clear();

		for (int i = 0; i < vClosedList.size(); i++)
		{
			delete vClosedList[i];
		}
		vClosedList.clear();
		for (int i = 0; i < vGoalPath.size(); i++)
		{
			delete vGoalPath[i];
		}
		vGoalPath.clear();

		SearchCell sStart;
		sStart.iX = a_vCurrentPos.dX / fTileWidth;
		sStart.iY = a_vCurrentPos.dZ / fTileWidth;

		SearchCell sGoal;
		sGoal.iX = a_vTargetPos.dX / fTileWidth;
		sGoal.iY = a_vTargetPos.dZ / fTileWidth;

		SetStartAndGoal(sStart, sGoal);
		bInitialisedStart = true;
		bFoundGoal = false;
	}
	if (bInitialisedStart)
	{
		ContinuePath();
	}
}
void PathFinding::SetStartAndGoal(SearchCell a_sStart, SearchCell a_sGoal)
{
	pStartCell = new SearchCell(a_sStart.iX, a_sStart.iY, NULL);
	pGoalCell = new SearchCell(a_sGoal.iX, a_sGoal.iY, &a_sGoal);

	pStartCell->fG = 0;
	pStartCell->fH = pStartCell->GetManhattenDistance(pGoalCell);
	pStartCell->sParent = 0;

	vOpenList.push_back(pStartCell);
}

SearchCell* PathFinding::GetNextCell()
{
	float fClosestTile = 1000;
	int iCellIndex = -1;
	SearchCell* pNextCell = NULL;

	for (int i = 0; i < vOpenList.size(); i++)
	{
		if (vOpenList[i]->GetF() < fClosestTile)
		{
			fClosestTile = vOpenList[i]->GetF();
			iCellIndex = i;
		}
	}

	if (iCellIndex >= 0)
	{
		pNextCell = vOpenList[iCellIndex];
		vClosedList.push_back(pNextCell);
		vOpenList.erase(vOpenList.begin() + iCellIndex);
	}
	return pNextCell;
}

void PathFinding::PathOpened(int a_iX, int a_iY, float a_fCost, SearchCell *a_pParent)
{
	int iTile = GetTile(a_iX, a_iY);
	
	if (iTile == 1)
	{
		std::cout << "test: " << iTile << std::endl;
		return;
	}

	int iIDNum = a_iY * (fMapHeight*fMapWidth) + a_iX;
	for (int i = 0; i < vClosedList.size(); i++)
	{
		if (iIDNum == vClosedList[i]->iID)
		{
			return;
		}

	}

	SearchCell* pNewChild = new SearchCell(a_iX, a_iY, a_pParent);
	pNewChild->fG = a_fCost;
	pNewChild->fH = a_pParent->GetManhattenDistance(pGoalCell);

	for (int i = 0; i < vOpenList.size(); i++)
	{
		if (iIDNum == vOpenList[i]->iID)
		{
			float fNewF = pNewChild->fG + a_fCost + vOpenList[i]->fH;

			if (vOpenList[i]->GetF() > fNewF)
			{
				vOpenList[i]->fG = pNewChild->fG + a_fCost;
				vOpenList[i]->sParent = pNewChild;
			}
			else
			{
				delete pNewChild;
				return;
			}
		}
	}
	vOpenList.push_back(pNewChild);
}
void PathFinding::UpdateCollisionMap()
{
	std::ifstream pCollision;//Creates an input fstream member
	pCollision.open("./maps/currentCollision.txt");//Opens the file.
	for (int i = 0; i < (iMapHeight*iMapWidth); i++)//Iterates through each tile in the array.
	{
		pCollision >> iCollisionMap[i];//Stores current tile type into array.
	}
	pCollision.close();
}

void PathFinding::ContinuePath()
{
	for (int i = 0; i < 4; i++)
	{
		if (vOpenList.empty())
		{
			return;
		}
		SearchCell* pCurrentCell = GetNextCell();

		if (pCurrentCell->iID == pGoalCell->iID)
		{
			pGoalCell->sParent = pCurrentCell->sParent;

			SearchCell* pGetPath;

			for (pGetPath = pGoalCell; pGetPath != NULL; pGetPath = pGetPath->sParent)
			{
				vGoalPath.push_back(new Vector3(pGetPath->iX * fTileWidth, 0, pGetPath->iY * fTileWidth));

				//Debug code to show path.
				//int iSpriteID = UG::CreateSprite("./images/Tanks/temp3.png", 32, 32, true);//Create the sprite

				//UG::DrawSprite(iSpriteID);	//Draws it
				//UG::MoveSprite(iSpriteID, pGetPath->iX*fTileWidth, pGetPath->iY*fTileWidth);
			}

			bFoundGoal = true;
			return;
		}
		else
		{
			PathOpened(pCurrentCell->iX + 1, pCurrentCell->iY, pCurrentCell->fG + 1, pCurrentCell);//Right Side
			PathOpened(pCurrentCell->iX - 1, pCurrentCell->iY, pCurrentCell->fG + 1, pCurrentCell);//Left Side
			PathOpened(pCurrentCell->iX, pCurrentCell->iY + 1, pCurrentCell->fG + 1, pCurrentCell);//Top Side
			PathOpened(pCurrentCell->iX, pCurrentCell->iY - 1, pCurrentCell->fG + 1, pCurrentCell);//Bottom Side

			for (int i = 0; i < vOpenList.size(); i++)
			{
				if (pCurrentCell->iID == vOpenList[i]->iID)
				{
					vOpenList.erase(vOpenList.begin() + i);
				}
			}

		}
	}
	
}

Vector3 PathFinding::NextPathPos(Vector3 a_vPos, bool a_bFoundGoal)
{

	int iIndex = 1;

	if ((vGoalPath.empty()))
	{
		return Vector3(0, -100, 0);
	}
	if (a_bFoundGoal)
	{
		vGoalPath.erase(vGoalPath.end() - iIndex);
	}

	Vector3 vNextPosCell;
	vNextPosCell.dX = vGoalPath[vGoalPath.size() - iIndex]->dX;
	vNextPosCell.dZ = vGoalPath[vGoalPath.size() - iIndex]->dZ;
	
	return vNextPosCell;
}
Vector3 PathFinding::SecondNextPathPos(Vector3 a_vPos)
{
	int iIndex = 2;
	if ((vGoalPath.size() <= 1))
	{
		
		return Vector3(0, -100, 0);

	}
	Vector3 vNextPosCell;
	vNextPosCell.dX = vGoalPath[vGoalPath.size() - iIndex]->dX;
	vNextPosCell.dZ = vGoalPath[vGoalPath.size() - iIndex]->dZ;

	return vNextPosCell;
}

void PathFinding::DrawDebug()
{
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