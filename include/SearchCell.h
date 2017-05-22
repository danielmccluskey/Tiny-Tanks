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
	int iX;
	int iY;
	int iID;
	SearchCell *sParent;
	float fG;
	float fH;

	SearchCell() : sParent(0) {}
	SearchCell(int a_iX, int a_iY, SearchCell *a_pParent = 0) : iX(a_iX), iY(a_iY), sParent(a_pParent),
		iID(iY * (fMapWidth * fMapHeight) + iX), fG(0), fH(0) {};

	float GetF() 
	{
		return fG + fH;
	}

	float GetManhattenDistance(SearchCell *a_pNodeEnd)
	{
		float fX = (float)(fabs((float)(this->iX - a_pNodeEnd->iX)));
		float fY = (float)(fabs((float)(this->iY - a_pNodeEnd->iY)));

		return fX + fY;
	}
};



#endif // !_SEARCHCELL_H_

