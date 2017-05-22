//==============================================================================================================================
// Project: WiiTanks
// File: Bullet.h
// Author: Daniel McCluskey
// Date Created: 07/01/17
// Brief: This is the header file that contains the function declarations and variables required to make the bullets functional.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#ifndef _TURRET_H_
#define _TURRET_H_
class Turret
{
public:
	Turret(char* a_cImagePath);
	int iSpriteID;
	int iRotDeg = 0;

};


#endif//_TURRET_H_