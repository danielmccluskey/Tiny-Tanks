//==============================================================================================================================
// Project: WiiTanks
// File: SearchCell.h
// Author: Daniel McCluskey
// Date Created: 07/01/17
// Brief: This header file contains the struct that the path uses to store details about each tile it checks.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#ifndef _SEARCHCELL_H_
#define _SEARCHCELL_H_
#include <cmath>
#include "CustomEnum.h"

struct SearchCell
{
public:
	SearchCell() : sParent(0) {}//Constructor to set the parent cell to null.
	SearchCell(int a_iX, int a_iY, SearchCell *a_pParent = 0) : iX(a_iX), iY(a_iY), sParent(a_pParent),
		iID(iY * (fMapWidth * fMapHeight) + iX), fG(0), fH(0) {};//Constructor.

	//==============================================================================================================================
	//Ints
	//==============================================================================================================================

	int iX;//X Pos of the cell
	int iY;//Y Pos of the cell
	int iID;//The ID of the cell

	//==============================================================================================================================
	//Structs
	//==============================================================================================================================

	SearchCell *sParent;//A pointer to the cells parent

	//==============================================================================================================================
	//Floats
	//==============================================================================================================================

	float fG;//The movement cost of the cell
	float fH;//The Hueristic	
	
	//Function to get the cost of moving to the next cell.
	float GetF() 
	{
		return fG + fH;
	}

	//Function to get the Hueristic value from A to the goal.
	float GetManhattenDistance(SearchCell *a_pNodeEnd)
	{
		float fX = (float)(fabs((float)(this->iX - a_pNodeEnd->iX)));
		float fY = (float)(fabs((float)(this->iY - a_pNodeEnd->iY)));

		return fX + fY;
	}
};



#endif // !_SEARCHCELL_H_

